#pragma once
#include "../../pch.h"
#include "../Resource.h"

namespace Barta{

	class ResourceContainerInterface{
	public:
		ResourceContainerInterface() = default;
		virtual ~ResourceContainerInterface() = default;
		ResourceContainerInterface( const ResourceContainerInterface& ) = delete;

		virtual bool hasTexture( const Resource resource ) const = 0;

		virtual const sf::Texture& getTexture( const Resource resource ) const = 0;

		virtual const sf::IntRect getTextureRect( const Resource resource ) const = 0;
	};
}
