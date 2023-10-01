#pragma once
#include "Block.h"
#include "BartaGraph.h"
#include "Hitbox/AABB_Hitbox.h"

Block::Block(
	Barta::Vector2f initialPosition,
	Barta::DynamicsDTO initialDynamics
) : 
	transformable( BartaGraph::createNewTransformableInstance() ),
	hitbox( new Barta::AABB_Hitbox( Barta::AABB( Barta::Vector2f( 0.f, 0.f ), Barta::Vector2f( 100.f, 100.f ) ) ) ),
	dynamicsDTO( initialDynamics)
{
	this->transformable->setPosition( initialPosition );
}

Block::~Block(){
	delete this->transformable;
	delete this->hitbox;
}

bool Block::isToBeDeleted() const{
	return false;
}

const Barta::TransformableInterface& Block::getTransformable() const{
	return *this->transformable;
}

const Barta::Resource Block::getResourceId() const noexcept{
	return Barta::Resource::YELLOW_BLOCK;
}

std::unique_ptr<const Barta::HitboxInterface> Block::getHitbox() const{
	return std::unique_ptr<const Barta::HitboxInterface>( this->hitbox->getTransformedHitbox( *this->transformable ) );
}

void Block::move( const Barta::Vector2f& shift ){
	this->transformable->move( shift );
}

const Barta::DynamicsDTO& Block::getDynamicsDTO() const{
	return this->dynamicsDTO;
}

void Block::setDynamicsDTO( const Barta::DynamicsDTO& dynamics ){
	this->dynamicsDTO = dynamics;
}
