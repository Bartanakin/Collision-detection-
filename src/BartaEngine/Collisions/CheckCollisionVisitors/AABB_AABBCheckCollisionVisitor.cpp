#include "AABB_AABBCheckCollisionVisitor.h"

Barta::AABB_AABBCheckCollisionVisitor::AABB_AABBCheckCollisionVisitor(
    const AABB &aabb1,
    const AABB &aabb2,
    const DynamicsDTO &dynamicsDifference
) noexcept :
    aabb1(aabb1),
    aabb2(aabb2),
    dynamicsDifference(dynamicsDifference)
{}

Barta::CollisionTestResult Barta::AABB_AABBCheckCollisionVisitor::checkStaticCollision(
    const MathLibraryInterface &mathLib,
    CollisionTestResultBuilder &collisionTestResultBuilder
) const {
    std::stringstream ss;
    ss << "aabb1 " << this->aabb1 << " aabb2: " << this->aabb2 << " velocity: " << this->dynamicsDifference.velocity;

    return collisionTestResultBuilder.setCollisionDetected(
        this->aabb1.getLeftTop().getX() <= this->aabb2.getRightTop().getX()
        && this->aabb1.getRightTop().getX() >= this->aabb2.getLeftTop().getX()
        && this->aabb1.getLeftTop().getY() <= this->aabb2.getLeftBottom().getY()
        && this->aabb1.getLeftBottom().getY() >= this->aabb2.getLeftTop().getY()
    )
    ->setStaticCollision(true)
    ->setDebugInfo("AABB - AABB static")
    ->setObjectsDebugInfo(ss.str())
    ->build();
}

Barta::CollisionTestResult Barta::AABB_AABBCheckCollisionVisitor::checkDynamicCollision(
    const MathLibraryInterface &mathLib,
    const float delta_time,
    CollisionTestResultBuilder &collisionTestResultBuilder
) const {
    auto staticCollisionResult = this->checkStaticCollision(mathLib, collisionTestResultBuilder);
    if (staticCollisionResult.collisionDetected) {
        return staticCollisionResult;
    }

    collisionTestResultBuilder.setStaticCollision(false)->setCollisionDetected(false);
    if (this->dynamicsDifference.velocity == Vector2f()) {
        return collisionTestResultBuilder
            .setDebugInfo("AABB - AABB zero velocity")
            ->build();
    }

    float t_first = 0.f;
    float t_last = delta_time;
    Vector2f normVector = {};
    std::vector<std::tuple<
        const float,
        const float,
        const float,
        const float,
        const float,
        const Vector2f,
        std::string
    >> dataVector = {
        {
            this->dynamicsDifference.velocity.getX(),
            this->aabb2.getLeftTop().getX(),
            this->aabb2.getRightTop().getX(),
            this->aabb1.getLeftTop().getX(),
            this->aabb1.getRightTop().getX(),
            Vector2f(1.f, 0.f),
            "x"
        },
        {
            this->dynamicsDifference.velocity.getY(),
            this->aabb2.getLeftTop().getY(),
            this->aabb2.getLeftBottom().getY(),
            this->aabb1.getLeftTop().getY(),
            this->aabb1.getLeftBottom().getY(),
            Vector2f(0.f, 1.f),
            "y"
        }
    };
    constexpr static const int VELOCITY = 0;
    constexpr static const int MIN_1 = 1;
    constexpr static const int MAX_1 = 2;
    constexpr static const int MIN_2 = 3;
    constexpr static const int MAX_2 = 4;
    constexpr static const int NORM_VECTOR = 5;
    constexpr static const int AXIS = 6;
    for (const auto& data : dataVector) {
        if (std::get<VELOCITY>(data) < 0.f) {
            if (std::get<MAX_2>(data) < std::get<MIN_1>(data))
                return collisionTestResultBuilder
                    .setDebugInfo("AABB - AABB dynamic, velocity in the opposite direction (negative)")
                    ->build();

            if (std::get<MAX_1>(data) < std::get<MIN_2>(data)) {
                t_first = std::max((std::get<MAX_1>(data) - std::get<MIN_2>(data)) / std::get<VELOCITY>(data), t_first);
                normVector = std::get<NORM_VECTOR>(data);
            }

            t_last = std::min((std::get<MIN_1>(data) - std::get<MAX_2>(data)) / std::get<VELOCITY>(data), t_last);
        }

        if (std::get<VELOCITY>(data) > 0.f) {
            if (std::get<MIN_2>(data) > std::get<MAX_1>(data))
                return collisionTestResultBuilder
                    .setDebugInfo("AABB - AABB dynamic, velocity in the opposite direction (positive)" + std::get<AXIS>(data))
                    ->build();

            if (std::get<MAX_2>(data) < std::get<MIN_1>(data)) {
                t_first = std::max((std::get<MIN_1>(data) - std::get<MAX_2>(data)) / std::get<VELOCITY>(data), t_first);
                normVector = -std::get<NORM_VECTOR>(data);
            }

            t_last = std::min((std::get<MAX_1>(data) - std::get<MIN_2>(data)) / std::get<VELOCITY>(data), t_last);
        }

        if (std::get<VELOCITY>(data) == 0.f) 
            if (std::get<MIN_2>(data) > std::get<MAX_1>(data) || std::get<MIN_1>(data) > std::get<MAX_2>(data))
                return collisionTestResultBuilder
                    .setDebugInfo("AABB - AABB dynamic, velocity in the opposite direction (positive)" + std::get<AXIS>(data))
                    ->build();

        if (t_first > t_last)
            return collisionTestResultBuilder
                .setDebugInfo("AABB - AABB dynamic, 0 velocity in axis"  + std::get<AXIS>(data))
                ->build(); 
    }

    return collisionTestResultBuilder
        .setCollisionDetected(true)
        ->setTimePassed(t_first)
        ->setNormVector(normVector)
        ->setDebugInfo("AABB - AABB succesful dynamic")
        ->build();
}
