#pragma once
#include"../Geometrics/Vector2f.h"
namespace Barta{
	enum EventType{
		LEFT_CLICK = 0
	};

	class BartaEvent
	{
	public:
		BartaEvent() = default;
		virtual ~BartaEvent() = default;
		BartaEvent( BartaEvent&& ) noexcept = default;

		virtual EventType getStaticType() const noexcept = 0;
	};

}
