#include "SimpleResourceContainer.h"

Barta::SimpleResourceContainer::SimpleResourceContainer(){
	this->init();
}

Barta::SimpleResourceContainer::~SimpleResourceContainer(){}

bool Barta::SimpleResourceContainer::hasTexture( const Resource resource ) const{
	switch( resource ){
	case Resource::RED_BALL:
	case Resource::GREEN_BALL:
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

	case Resource::NONE:
	default:
	throw "No resource found";
	}
}

void Barta::SimpleResourceContainer::init(){

		sf::RenderTexture renderTexture;
		renderTexture.create( 160, 80 );
		sf::CircleShape redBall;
		sf::CircleShape greenBall;
		redBall.setRadius( 40.f );
		greenBall.setRadius( 40.f );
		redBall.setFillColor( sf::Color( 255, 0, 0, 255 ) );
		greenBall.setFillColor( sf::Color( 0, 255, 0, 255 ) );
		greenBall.setPosition( sf::Vector2f( 80.f, 0 ) );
	
		renderTexture.clear( sf::Color( 0, 0, 0, 0 ) );
		renderTexture.draw( redBall );
		renderTexture.draw( greenBall );
		renderTexture.display();
	
		this->texture = renderTexture.getTexture();

		this->redBallTextureRect = std::move( sf::IntRect( 0, 0, 80, 80 ) );
		this->greenBallTextureRect = std::move( sf::IntRect( 80, 0, 80, 80 ) );
}
