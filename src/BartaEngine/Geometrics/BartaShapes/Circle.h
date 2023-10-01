#pragma once
#include"../Vector2f.h"

namespace Barta{

	class Circle{
	public:
		Circle( float radius, Vector2f center );

		float getRadius() const;

		Vector2f getCenter() const;

		bool isWithin(Vector2f point) const noexcept;

	private:
		const float radius;
		const Vector2f center;
	};
}

