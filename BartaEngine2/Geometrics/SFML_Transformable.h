#pragma once
#include"TransformableInterface.h"
#include"SFML/Graphics.hpp"
namespace Barta{
	class SFML_Transformable : public TransformableInterface {
	public:
		SFML_Transformable();
		SFML_Transformable( const SFML_Transformable& second );
		virtual ~SFML_Transformable();

		Vector2f getPosition() const override;

		void setPosition( Vector2f position ) override;
		
		virtual Circle&& getTransformedCircle( const Circle& circle ) const override;

		virtual void move( Vector2f shift ) override;

	private:
		sf::Transformable* transformable;

	};
}

