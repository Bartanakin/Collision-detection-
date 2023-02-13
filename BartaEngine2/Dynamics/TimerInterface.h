#pragma once

namespace Barta{

	class TimerInterface{
	public:
		TimerInterface() = default;
		virtual ~TimerInterface() = default;

		virtual float getElapsedTime() const = 0;
	};
}
