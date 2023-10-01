#include "pch.h"
#include "AABB.h"

Barta::AABB::AABB( const Vector2f& leftTop, const Vector2f& widthHeight ) : 
	leftTop( leftTop ),
	widthHeight( widthHeight )
{}

Barta::Vector2f Barta::AABB::getLeftTop() const{
	return this->leftTop;
}

Barta::Vector2f Barta::AABB::getRightTop() const {
	return this->getLeftTop() + Vector2f(this->getWidthHeight().getX(), 0.f);
}

Barta::Vector2f Barta::AABB::getRightBottom() const{
	return this->getLeftTop() + this->getWidthHeight();
}

Barta::Vector2f Barta::AABB::getLeftBottom() const {
	return this->getLeftTop() + Vector2f(0.f, this->getWidthHeight().getY());
}

Barta::Vector2f Barta::AABB::getWidthHeight() const{
	return this->widthHeight;
}

std::vector<Barta::Segment> Barta::AABB::getSides() const noexcept {
	return {
		Segment(this->getLeftTop(), this->getRightTop()),
		Segment(this->getRightTop(), this->getRightBottom()),
		Segment(this->getRightBottom(), this->getLeftBottom()),
		Segment(this->getLeftBottom(), this->getLeftTop())
	};
}

std::vector<Barta::Vector2f> Barta::AABB::getVertices() const noexcept {
	return {
		this->getLeftTop(),
		this->getRightTop(),
		this->getRightBottom(),
		this->getLeftBottom(),
	};
}

bool Barta::AABB::isWithin(const Vector2f& point) const noexcept {
	return this->leftTop.getX() <= point.getX() && point.getX() <= this->leftTop.getX() + this->widthHeight.getX()
		&& this->leftTop.getY() <= point.getY() && point.getY() <= this->leftTop.getY() + this->widthHeight.getY();
}

Barta::AABB::VoronoiRegion Barta::AABB::findVoronoiRegionType(const Vector2f& point) const noexcept {
	auto sides = this->getSides();
	auto regionMask = VoronoiRegion::INSIDE;
	VoronoiRegion regionsMap[4] = {
		VoronoiRegion::TOP,
		VoronoiRegion::RIGHT,
		VoronoiRegion::BOTTOM,
		VoronoiRegion::LEFT
	};
	for (int i = 0; i < sides.size(); i++) {
		if (sides[i].calculateRelationToPoint(point) == Segment::Relation::LEFT) {
			regionMask = regionMask | regionsMap[i];
		}
	}

	return regionMask;
}
