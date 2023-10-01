#pragma once
#include "../../pch.h"
#include"ResourceContainerInterface.h"

namespace Barta{
	class SimpleResourceContainer : public ResourceContainerInterface{
	public:
		SimpleResourceContainer();
		virtual ~SimpleResourceContainer();

		virtual bool hasTexture( const Resource resource ) const override;

		virtual const sf::Texture& getTexture( const Resource resource ) const override;

		virtual const sf::IntRect getTextureRect( const Resource resource ) const override;

	private:
		sf::Texture texture;
		sf::IntRect redBallTextureRect;
		sf::IntRect greenBallTextureRect;
		sf::IntRect yellowBlockRect;
		sf::IntRect giantBlock;

		void init();
	};
}

