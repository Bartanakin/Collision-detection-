#pragma once
#include"../BartaEvent.h"

namespace Barta{
	class LeftClickEvent : public BartaEvent {
	public:
		inline LeftClickEvent( Vector2f position ) noexcept : position( position ){};

		inline EventType getStaticType() const noexcept override{ return LEFT_CLICK; };

		inline Vector2f getPosition() const noexcept{ return this->position;  };

	private:
		Vector2f position;
	};
}

