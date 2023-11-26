#include "GiantBlock.h"
#include "Hitbox/AABB_Hitbox.h"
#include "../BartaGraph.h"
#include "../SandboxResource.h"

GiantBlock::GiantBlock(Barta::Vector2f initialPosition) 
	: Wall(
        initialPosition,
	    Barta::AABB(Barta::Vector2f(0.f, 0.f), Barta::Vector2f(500.f, 500.f)),
        std::move(Barta::BartaSprite(static_cast<int>(SandboxResource::GIANT_BLOCK)))
    )
{
	this->transformable->setPosition(initialPosition);
}
