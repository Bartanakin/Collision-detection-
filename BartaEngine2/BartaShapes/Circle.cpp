#include "Circle.h"

Barta::Circle::Circle( float radius, Vector2f center )
:radius(radius), center(center){}

float Barta::Circle::getRadius() const{
	return this->radius;
}

Barta::Vector2f Barta::Circle::getCenter() const{
	return this->center;
}
