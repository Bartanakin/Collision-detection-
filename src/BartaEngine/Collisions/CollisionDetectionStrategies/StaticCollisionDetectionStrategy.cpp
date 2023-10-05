#include "pch.h"
#include "StaticCollisionDetectionStrategy.h"

Barta::StaticCollisionDetectionStrategy::StaticCollisionDetectionStrategy( std::unique_ptr<MathLibraryInterface> mathLibrary ) :
    mathLibrary(std::move(mathLibrary))
{}

Barta::CollisionTestResult Barta::StaticCollisionDetectionStrategy::acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const{
    auto builder = CollisionTestResultBuilder();

    return checkCollisionVisitor.checkStaticCollision(*this->mathLibrary, builder);
}
