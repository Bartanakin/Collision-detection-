#include "pch.h"
#include "SimpleResourceContainer.h"
#include "SandboxResource.h"

SimpleResourceContainer::SimpleResourceContainer(
    std::string repositoryDir
)
    : repositoryDir(std::move(repositoryDir)),
    texture({}),
    redBallTextureRect({}),
    greenBallTextureRect({}),
    yellowBlockRect({}),
    inputTexture({}),
    greenArrow({}),
    bomb({})
{
	this->init();
}

SimpleResourceContainer::~SimpleResourceContainer(){}

bool SimpleResourceContainer::hasTexture(const int resource) const{
	switch(static_cast<SandboxResource>(resource)){
	case SandboxResource::RED_BALL:
	case SandboxResource::GREEN_BALL:
	case SandboxResource::YELLOW_BLOCK:
	case SandboxResource::GREEN_ARROW:
	case SandboxResource::BOMB:
	case SandboxResource::INSTRUCTION:
		return true;

	case SandboxResource::NONE:
	default:
		return false;
	}
}

const sf::Texture& SimpleResourceContainer::getTexture(const int resource) const{
	switch( static_cast<SandboxResource>(resource) ){
	case SandboxResource::RED_BALL:
	case SandboxResource::GREEN_BALL:
	case SandboxResource::YELLOW_BLOCK:
	case SandboxResource::BOMB:
		return this->texture;

	case SandboxResource::GREEN_ARROW:
    case SandboxResource::INSTRUCTION:
		return this->inputTexture;

	case SandboxResource::NONE:
	default:
		throw "No resource found";
	}
}

const sf::IntRect SimpleResourceContainer::getTextureRect( const int resource ) const{
	switch( static_cast<SandboxResource>(resource) ){
	case SandboxResource::RED_BALL:
		return this->redBallTextureRect;

	case SandboxResource::GREEN_BALL:
		return this->greenBallTextureRect;

	case SandboxResource::YELLOW_BLOCK:
		return this->yellowBlockRect;

	case SandboxResource::GREEN_ARROW:
		return this->greenArrow;

	case SandboxResource::BOMB:
		return this->bomb;

    case SandboxResource::INSTRUCTION:
        return this->instruction;

	case SandboxResource::NONE:
	default:
	throw "No resource found";
	}
}

void SimpleResourceContainer::init(){

		sf::RenderTexture renderTexture;
		renderTexture.create( 780, 600 );
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
		yellowBlock.setSize( sf::Vector2f( 40.f, 60.f ) );
		yellowBlock.setFillColor( sf::Color( 250, 243, 50 ) );
		yellowBlock.setPosition( sf::Vector2f( 160, 0 ) );
		renderTexture.draw( yellowBlock );

		sf::CircleShape bomb;
		bomb.setRadius(10.f);
		bomb.setFillColor(sf::Color(255, 250, 160));
		bomb.setPosition(sf::Vector2f(700.f, 0));
		renderTexture.draw(bomb);
	
		renderTexture.display();
		this->texture = renderTexture.getTexture();

		this->redBallTextureRect = std::move( sf::IntRect( 0, 0, 80, 80 ) );
		this->greenBallTextureRect = std::move( sf::IntRect( 80, 0, 80, 80 ) );
		this->yellowBlockRect = std::move( sf::IntRect( 160, 0, 40, 60 ) );
		this->bomb = std::move( sf::IntRect( 700, 0, 20, 20 ) );

        this->inputTexture.loadFromFile(this->repositoryDir + "\\images\\texture.png");

        this->greenArrow = std::move(sf::IntRect(0, 0, 20, 40));
        this->instruction = std::move(sf::IntRect(20, 0, 500, 500));
}
