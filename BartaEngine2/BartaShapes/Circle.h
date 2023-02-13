#pragma once
#include"../Geometrics/Vector2f.h"

namespace Barta{
	class Circle{
	public:
		Circle( float radius, Vector2f center );

		float getRadius() const;

		Vector2f getCenter() const;

	private:
		const float radius;
		const Vector2f center;
	};
}

