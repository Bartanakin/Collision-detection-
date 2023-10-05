#include "pch.h"
#include "SimpleResourceContainer.h"

Barta::SimpleResourceContainer::SimpleResourceContainer()
    : texture({}),
    redBallTextureRect({}),
    greenBallTextureRect({}),
    yellowBlockRect({}),
    giantBlock({}) 
{
	this->init();
}

Barta::SimpleResourceContainer::~SimpleResourceContainer(){}

bool Barta::SimpleResourceContainer::hasTexture( const Resource resource ) const{
	switch( resource ){
	case Resource::RED_BALL:
	case Resource::GREEN_BALL:
	case Resource::YELLOW_BLOCK:
	case Resource::GIANT_BLOCK:
		return true;
	case Resource::NONE:
	default:
		return false;
	}
}

const sf::Texture& Barta::SimpleResourceContainer::getTexture( const Resource resource ) const{
	switch( resource ){
	case Resource::RED_BALL:
	case Resource::GREEN_BALL:
	case Resource::YELLOW_BLOCK:
	case Resource::GIANT_BLOCK:
		return this->texture;

	case Resource::NONE:
	default:
		throw "No resource found";
	}
}

const sf::IntRect Barta::SimpleResourceContainer::getTextureRect( const Resource resource ) const{
	switch( resource ){
	case Resource::RED_BALL:
		return this->redBallTextureRect;

	case Resource::GREEN_BALL:
		return this->greenBallTextureRect;

	case Resource::YELLOW_BLOCK:
		return this->yellowBlockRect;

	case Resource::GIANT_BLOCK:
		return this->giantBlock;

	case Resource::NONE:
	default:
	throw "No resource found";
	}
}

void Barta::SimpleResourceContainer::init(){

		sf::RenderTexture renderTexture;
		renderTexture.create( 760, 600 );
		renderTexture.clear( sf::Color( 0, 0, 0, 0 ) );

		sf::CircleShape redBall;
		redBall.setRadius( 40.f );
		redBall.setFillColor( sf::Color( 255, 0, 0, 255 ) );
		renderTexture.draw( redBall );

		sf::CircleShape greenBall;
		greenBall.setRadius( 40.f );
		greenBall.setFillColor( sf::Color( 0, 255, 0, 255 ) );
		greenBall.setPosition( sf::Vector2f( 80.f, 0 ) );
		renderTexture.draw( greenBall );

		sf::RectangleShape yellowBlock;
		yellowBlock.setSize( sf::Vector2f( 100.f, 100.f ) );
		yellowBlock.setFillColor( sf::Color( 250, 243, 50 ) );
		yellowBlock.setPosition( sf::Vector2f( 160, 0 ) );
		renderTexture.draw( yellowBlock );

		sf::RectangleShape giantBlock;
		giantBlock.setSize(sf::Vector2f(500.f, 500.f));
		giantBlock.setFillColor(sf::Color(87, 150, 138));
		giantBlock.setPosition(sf::Vector2f(260, 0));
		renderTexture.draw(giantBlock);
	
	
		renderTexture.display();
		this->texture = renderTexture.getTexture();

		this->redBallTextureRect = std::move( sf::IntRect( 0, 0, 80, 80 ) );
		this->greenBallTextureRect = std::move( sf::IntRect( 80, 0, 80, 80 ) );
		this->yellowBlockRect = std::move( sf::IntRect( 160, 0, 100, 100 ) );
		this->giantBlock = std::move( sf::IntRect( 260, 0, 500, 500 ) );
}
