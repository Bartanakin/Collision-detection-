#pragma once
#include "../../pch.h"
#include"../Resource.h"

namespace Barta{
	class RecourseMatcherInterface{
	public:
        virtual ~RecourseMatcherInterface() noexcept = default;
		virtual void matchResource( const void* hash, const Resource resource ) = 0;
		virtual const sf::Drawable& matchAndTransform( const void* hash, const sf::Transformable& transformable ) const = 0;
		virtual void drop( const void* hash ) = 0;
	};
}
