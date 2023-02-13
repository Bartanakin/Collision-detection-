#pragma once
#include "../Geometrics/Vector2f.h"

namespace Barta{
	struct DynamicsDTO{
		inline DynamicsDTO( Vector2f velocity ) :
			velocity( std::move( velocity ) ){}

		inline DynamicsDTO& operator=( const DynamicsDTO& second ){
			this->velocity = second.velocity;

			return *this;
		}

		Vector2f velocity;
	};
}

