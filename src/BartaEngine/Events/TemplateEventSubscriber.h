#pragma once
#include "../pch.h"

namespace Barta {

	template<typename EventType>
	class EventSubscriber {
		public:

		bool handle(EventType& event) { return false; }

		bool isValid() const noexcept { return false; }
	};

}