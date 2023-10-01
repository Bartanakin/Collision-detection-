#pragma once
#include "../pch.h"

namespace Barta {

	template<typename EventType>
	class EventSubscriber {
		public:

		bool handle(const EventType& event) {}

		bool isValid() const noexcept {}
	};

}