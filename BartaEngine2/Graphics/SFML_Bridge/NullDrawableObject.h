#pragma once
#include"SFML/Graphics.hpp"
namespace Barta{
	class NullDrawableObject : public sf::Drawable {
	public:
		inline void draw( sf::RenderTarget& renderTarget, sf::RenderStates states ) const override{};
	};
}

