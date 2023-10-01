#include "pch.h"
#include "CircleAABBCheckCollisionVisitor.h"
#include "../../Geometrics/Segment.h"
#include "../../Geometrics/Intersections.h"

Barta::CircleAABBCheckCollisionVisitor::CircleAABBCheckCollisionVisitor(
	const Circle& circle,
	const AABB& aabb,
	const DynamicsDTO& dynamicsDifference
) : 
	circle( circle ),
	aabb( aabb ),
	dynamicsDifference( dynamicsDifference ),
	expandedAABB(AABB(
		this->aabb.getLeftTop() - Vector2f(this->circle.getRadius(), this->circle.getRadius()),
		this->aabb.getWidthHeight() + Vector2f(2.f * this->circle.getRadius(), 2.f * this->circle.getRadius())
	))
{}

Barta::CircleAABBCheckCollisionVisitor::~CircleAABBCheckCollisionVisitor(){}

Barta::CollisionTestResult Barta::CircleAABBCheckCollisionVisitor::checkStaticCollision(
	const MathLibraryInterface& mathLib,
	CollisionTestResultBuilder& collisionTestResultBuilder
) const {
	collisionTestResultBuilder
		.setStaticCollision(true)
		->setCollisionDetected(false)
		->setTimePassed(0.f);
	if (!this->expandedAABB.isWithin(this->circle.getCenter())) {
		return collisionTestResultBuilder.build();
	}

	auto regionMask = this->aabb.findVoronoiRegionType(this->circle.getCenter());
	if (
		regionMask == AABB::VoronoiRegion::TOP ||
		regionMask == AABB::VoronoiRegion::RIGHT ||
		regionMask == AABB::VoronoiRegion::BOTTOM ||
		regionMask == AABB::VoronoiRegion::LEFT ||
		regionMask == AABB::VoronoiRegion::INSIDE
		) {
		collisionTestResultBuilder.setCollisionDetected(true);

		return collisionTestResultBuilder.build();
	}

	auto cornerCircle = Circle(this->circle.getRadius(), this->matchCornerCenter(regionMask, this->aabb));
	if (cornerCircle.isWithin(this->circle.getCenter())) {
		collisionTestResultBuilder.setCollisionDetected(true);

		return collisionTestResultBuilder.build();
	}

	return collisionTestResultBuilder.build();
}

Barta::CollisionTestResult Barta::CircleAABBCheckCollisionVisitor::checkDynamicCollision(
	const MathLibraryInterface& mathLib,
	const float delta_time,
	CollisionTestResultBuilder& collisionTestResultBuilder
) const {
	auto staticResult = this->checkStaticCollision(mathLib, collisionTestResultBuilder);
	if (staticResult.collisionDetected) {
		return staticResult;
	}

	collisionTestResultBuilder.setStaticCollision(false);
	Vector2f A = this->circle.getCenter();
	Vector2f B = A + (this->dynamicsDifference.velocity * delta_time);
	Segment L = Segment(A, B);
	auto tContainer = Intersections::segmentAndAABB(L, this->expandedAABB);
	if (!this->expandedAABB.isWithin(circle.getCenter()) && tContainer.empty()) {
		return collisionTestResultBuilder.build();
	}

	Vector2f P;
	auto t = 0.f;
	if (!tContainer.empty()) {
		t = std::get<0>(tContainer[0]);
		P = A * (1.f - t) + B * t;
	} else {
		P = this->circle.getCenter();
	}

	auto regionMask = this->aabb.findVoronoiRegionType(P);
	auto normVector = this->calculateNormVector();
	if (normVector == Vector2f()) {
		throw "Incorrect normal vector found";
	}

	collisionTestResultBuilder.setNormVector(std::move(normVector));
	if (
		regionMask == AABB::VoronoiRegion::TOP ||
		regionMask == AABB::VoronoiRegion::RIGHT ||
		regionMask == AABB::VoronoiRegion::BOTTOM ||
		regionMask == AABB::VoronoiRegion::LEFT ||
		regionMask == AABB::VoronoiRegion::INSIDE
	) {
		collisionTestResultBuilder
			.setTimePassed(t * delta_time)
			->setCollisionDetected(true);

		return collisionTestResultBuilder.build();
	}

	auto cornerCircle = Circle(this->circle.getRadius(), this->matchCornerCenter(regionMask, this->aabb));
	auto circleIntersections = Intersections::segmentAndCircle(L, cornerCircle);
	if (circleIntersections.empty()) {
		return collisionTestResultBuilder.build();
	}

	collisionTestResultBuilder
		.setTimePassed(circleIntersections[0] * delta_time)
		->setCollisionDetected(true);

	return collisionTestResultBuilder.build();
}

Barta::Vector2f Barta::CircleAABBCheckCollisionVisitor::matchCornerCenter(AABB::VoronoiRegion regionMask, const AABB& aabb) const {
	switch (regionMask) {
	case AABB::VoronoiRegion::LEFT_TOP:
		return aabb.getLeftTop();
	case AABB::VoronoiRegion::RIGTH_TOP:
		return aabb.getRightTop();
	case AABB::VoronoiRegion::RIGTH_BOTTOM:
		return aabb.getRightBottom();
	case AABB::VoronoiRegion::LEFT_BOTTOM:
		return aabb.getLeftBottom();
	default:
		throw std::runtime_error("Invalid regionMask supplied");
	}
}

Barta::Vector2f Barta::CircleAABBCheckCollisionVisitor::calculateNormVector() const {
	std::vector<Vector2f> possibleNormalVectors = {{0.f, -1.f}, {1.f, 0.f}, {0.f, 1.f}, {-1.f, 0.f}};
	auto vertices = this->expandedAABB.getVertices();
	for (int i = 0; i < 4; i++) {
		auto seg = Segment(
			this->circle.getCenter(),
			this->circle.getCenter() + this->dynamicsDifference.velocity
		);
		if (seg.calculateRelationToPoint(vertices[i]) == Segment::Relation::RIGHT) {
			if (seg.calculateRelationToPoint(vertices[(i + 1) % 4]) == Segment::Relation::LEFT) {
				return possibleNormalVectors[i];
			}
		}
	}

	return {};
}
