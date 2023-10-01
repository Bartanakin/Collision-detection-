#pragma once
/******************************************************************************
 * MIT License
 *
 * Copyright (c) 2022 Quirijn Bouts
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#ifndef BOQ_TEST_UTILS_H
#define BOQ_TEST_UTILS_H

#include <array>
#include <exception>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

namespace bits_of_q {

	struct CopyStats {
		int n_default_constructs = 0;
		int n_copies = 0;
		int n_moves = 0;
		int n_destructs = 0;
	};

	inline std::ostream& operator<<(std::ostream& os, const CopyStats& stats) {
		os << "{ default_constructs: " << stats.n_default_constructs << ", copies: " << stats.n_copies
			<< ", moves: " << stats.n_moves << ", destructs: " << stats.n_destructs << " }";
		return os;
	}
	template <size_t i>
	struct IndexedCopyCounter {
		struct reset_after_construct_t {};
		static constexpr reset_after_construct_t reset_after_construct{};

		inline static CopyStats stats;

		explicit IndexedCopyCounter(reset_after_construct_t) { reset(); }
		IndexedCopyCounter() { stats.n_default_constructs++; }
		IndexedCopyCounter(const IndexedCopyCounter&) { stats.n_copies++; }
		IndexedCopyCounter& operator=(const IndexedCopyCounter&) {
			stats.n_copies++;
			return *this;
		}
		IndexedCopyCounter(IndexedCopyCounter&&) noexcept { stats.n_moves++; };
		IndexedCopyCounter& operator=(IndexedCopyCounter&&) noexcept {
			stats.n_moves++;
			return *this;
		}
		static CopyStats reset() {
			CopyStats old_stats = stats;
			stats.n_copies = 0;
			stats.n_moves = 0;
			stats.n_default_constructs = 0;
			stats.n_destructs = 0;
			return old_stats;
		}
		template <size_t i2>
		bool operator==(const IndexedCopyCounter<i2>& other) const {
			return stats == other.stats;
		}
		~IndexedCopyCounter() noexcept { stats.n_destructs++; }
	};

	namespace detail {
		static constexpr size_t default_copycounter_index = 2734987;  // just some random number so you don't easily create an
																	  // IndexedCopyCounter with the same index
	}  // namespace detail
	using CopyCounter = IndexedCopyCounter<detail::default_copycounter_index>;

	template <size_t index = detail::default_copycounter_index>
	IndexedCopyCounter<index> make_copy_counter() {
		return IndexedCopyCounter<index>{IndexedCopyCounter<index>::reset_after_construct};
	}

}  // namespace bits_of_q


#endif  // BOQ_TEST_UTILS_H