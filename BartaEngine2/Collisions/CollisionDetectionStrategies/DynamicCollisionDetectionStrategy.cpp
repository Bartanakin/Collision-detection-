#include "DynamicCollisionDetectionStrategy.h"

Barta::DynamicCollisionDetectionStrategy::DynamicCollisionDetectionStrategy()
    {}

Barta::DynamicCollisionDetectionStrategy::~DynamicCollisionDetectionStrategy(){}

bool Barta::DynamicCollisionDetectionStrategy::acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const{
    return checkCollisionVisitor.checkDynamicCollision();
}
