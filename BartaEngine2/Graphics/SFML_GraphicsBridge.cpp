#include "SFML_GraphicsBridge.h"
#include"SFML_Bridge/SimpleResourceContainer.h"
#include"SFML_Bridge/SpriteResourceMatcher.h"
#include"../Events/Events/LeftClickEvent.h"

Barta::SFML_GraphicsBridge::SFML_GraphicsBridge() noexcept
	: sf_window( nullptr ),
	resourceMatcher( new Barta::SpriteResourceMatcher( new Barta::SimpleResourceContainer() ) )
{}

Barta::SFML_GraphicsBridge::~SFML_GraphicsBridge(){
	delete this->sf_window;
	delete this->resourceMatcher;
}

void Barta::SFML_GraphicsBridge::createWindow( Vector2f size, std::string title ){
	delete this->sf_window;
	this->sf_window = new sf::RenderWindow( sf::VideoMode( size.getX(), size.getY() ), title );
	this->sf_window->setFramerateLimit( 59 );
}

void Barta::SFML_GraphicsBridge::drawObjects( std::list<BartaObjectInterface*> objects ){
	this->sf_window->clear();

	for( auto object : objects ){
		auto hash = ( void* )object;
		if( object->isToBeDeleted() ){
			this->resourceMatcher->drop( hash );
			continue;
		}

		this->resourceMatcher->matchResource( hash, object->getResourceId() );
		this->sf_window->draw( 
			this->resourceMatcher->matchAndTransform( 
				hash,
				SFML_GraphicsBridge::convertTransformable( object->getTransformable() )
			)
		);
	}

	this->sf_window->display();
}

bool Barta::SFML_GraphicsBridge::logEvents( BartaEventLoggerInterface& eventLogger ){
	sf::Event event = sf::Event();
	while (this->sf_window->pollEvent( event )) {
		if( event.type == sf::Event::Closed ){
			this->sf_window->close();

			return false;
		} if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left ){
			auto ptr = new LeftClickEvent( Vector2f( ( float )event.mouseButton.x, ( float )event.mouseButton.y ) );
			eventLogger.logEvent( ptr );
		}
	}

	return true;
}

const sf::Transformable Barta::SFML_GraphicsBridge::convertTransformable( const TransformableInterface& myTransformable ){
	auto newTransformable = sf::Transformable();
	auto myVector = myTransformable.getPosition();
	newTransformable.setPosition( myVector.getX(), myVector.getY() );

	return std::move( newTransformable );
}
