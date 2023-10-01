#pragma once
#include "../pch.h"
#include "../Geometrics/Vector2f.h"

namespace Barta{

	struct DynamicsDTO{
		inline DynamicsDTO(Vector2f velocity, bool hasInfiniteMass = true, float mass = 1.f) :
			velocity( std::move( velocity ) ),
			hasInfiniteMass(hasInfiniteMass),
			mass(mass) {}

		inline DynamicsDTO& operator=( const DynamicsDTO& second ){
			this->velocity = second.velocity;
			this->hasInfiniteMass = second.hasInfiniteMass;
			this->mass = second.mass;

			return *this;
		}

		inline DynamicsDTO( const DynamicsDTO& second ) :
			velocity( second.velocity ),
			hasInfiniteMass(second.hasInfiniteMass),
		    mass(second.mass) {}

		inline DynamicsDTO operator-( const DynamicsDTO& second ) const{
			return DynamicsDTO(this->velocity - second.velocity, false);
		}

		Vector2f velocity;
		bool hasInfiniteMass;
		float mass;
	};
}

