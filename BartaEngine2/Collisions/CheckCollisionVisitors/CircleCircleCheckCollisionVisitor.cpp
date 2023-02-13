#include "CircleCircleCheckCollisionVisitor.h"
#include <math.h>

Barta::CircleCircleCheckCollisionVisitor::CircleCircleCheckCollisionVisitor( const Circle& circle1, const Circle& circle2 ) :
    circle1( circle1 ),
    circle2( circle2 )
{}

Barta::CircleCircleCheckCollisionVisitor::~CircleCircleCheckCollisionVisitor(){}

bool Barta::CircleCircleCheckCollisionVisitor::checkStaticCollision() const{
    auto o1 = circle1.getCenter();
    auto o2 = circle2.getCenter();

    return pow( circle1.getRadius() + circle2.getRadius(), 2 ) >= o1.squareOfDistance( o2 );
}

bool Barta::CircleCircleCheckCollisionVisitor::checkDynamicCollision() const{
    return false;
}
