#pragma once
#include"ResourceMatcherInterface.h"
#include<unordered_map>
#include "ResourceContainerInterface.h"
#include "NullDrawableObject.h"

namespace Barta{
	class SpriteResourceMatcher : public RecourseMatcherInterface{
	public:
		SpriteResourceMatcher( ResourceContainerInterface* const resourceContainer );
		virtual ~SpriteResourceMatcher();

		void matchResource( const void* hash, const Resource resource ) override;
		const sf::Drawable& matchAndTransform( const void* hash, const sf::Transformable& transformable ) const override;
		void drop( const void* hash ) override;
	private:
		std::unordered_map<const void*, sf::Sprite*> sf_spriteMap;
		ResourceContainerInterface* const resourceContainer;

		NullDrawableObject nullDrawableObject;
	};
}

