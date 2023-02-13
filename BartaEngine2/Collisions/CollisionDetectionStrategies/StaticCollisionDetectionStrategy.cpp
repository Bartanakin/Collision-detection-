#include "StaticCollisionDetectionStrategy.h"

Barta::StaticCollisionDetectionStrategy::StaticCollisionDetectionStrategy()
{}

Barta::StaticCollisionDetectionStrategy::~StaticCollisionDetectionStrategy(){}

bool Barta::StaticCollisionDetectionStrategy::acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const{
    return checkCollisionVisitor.checkStaticCollision();
}
