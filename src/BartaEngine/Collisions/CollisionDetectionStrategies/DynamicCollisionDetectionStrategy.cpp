#include "pch.h"
#include "DynamicCollisionDetectionStrategy.h"

Barta::DynamicCollisionDetectionStrategy::DynamicCollisionDetectionStrategy(
    MathLibraryInterface* const mathLibrary,
    const TimerInterface& timer
) :
    timer( timer ),
    mathLibrary( mathLibrary )
    {}

Barta::DynamicCollisionDetectionStrategy::~DynamicCollisionDetectionStrategy(){
    delete this->mathLibrary;
}

Barta::CollisionTestResult Barta::DynamicCollisionDetectionStrategy::acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const{
    auto builder = CollisionTestResultBuilder();

    return checkCollisionVisitor.checkDynamicCollision(*this->mathLibrary, this->timer.getCurrentDeltaTime(), builder);
}
