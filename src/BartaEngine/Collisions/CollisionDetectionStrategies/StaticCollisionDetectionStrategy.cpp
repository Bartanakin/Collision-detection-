#include "pch.h"
#include "StaticCollisionDetectionStrategy.h"

Barta::StaticCollisionDetectionStrategy::StaticCollisionDetectionStrategy( MathLibraryInterface* const mathLibrary ) :
    mathLibrary( mathLibrary )
{}

Barta::StaticCollisionDetectionStrategy::~StaticCollisionDetectionStrategy(){
    delete this->mathLibrary;
}

Barta::CollisionTestResult Barta::StaticCollisionDetectionStrategy::acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const{
    auto builder = CollisionTestResultBuilder();

    return checkCollisionVisitor.checkStaticCollision(*this->mathLibrary, builder);
}
