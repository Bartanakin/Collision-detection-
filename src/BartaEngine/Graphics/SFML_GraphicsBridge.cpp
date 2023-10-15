#include "pch.h"
#include "SFML_GraphicsBridge.h"
#include "SFML_Bridge/SpriteResourceMatcher.h"
#include "../Events/Events/LeftClickEvent.h"
#include "../Events/Events/KeyPressedEvent.h"
#include "../Events/Events/KeyReleasedEvent.h"

Barta::SFML_GraphicsBridge::SFML_GraphicsBridge(
    std::unique_ptr<Barta::ResourceContainerInterface> resourceContainer
) noexcept
	: sf_window( nullptr ),
	resourceMatcher(std::make_unique<Barta::SpriteResourceMatcher>(std::move(resourceContainer)))
{}

Barta::SFML_GraphicsBridge::~SFML_GraphicsBridge(){
	delete this->sf_window;
}

void Barta::SFML_GraphicsBridge::createWindow( Vector2f size, std::string title ){
	delete this->sf_window;
	this->sf_window = new sf::RenderWindow( sf::VideoMode( static_cast<unsigned int>(size.getX()), static_cast<unsigned int>(size.getY()) ), title );
	this->sf_window->setFramerateLimit( 59 );
}

void Barta::SFML_GraphicsBridge::drawObjects(const std::list<BartaObjectInterface*>& objects) {
    
	this->sf_window->clear();

	for( const auto& object : objects ){
		auto hash = static_cast<const void*>(object);
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
		}
        
        if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left ){
			eventLogger.logEvent(
                LeftClickEvent(Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
            );
		}
        
        BartaKeyMap key;
        if (event.key.code == sf::Keyboard::D)
            key = BartaKeyMap::D;

        if (event.key.code == sf::Keyboard::A)
            key = BartaKeyMap::A;

        if (event.key.code == sf::Keyboard::Left)
            key = BartaKeyMap::LEFT;

        if (event.key.code == sf::Keyboard::Right)
            key = BartaKeyMap::RIGHT;

        if (event.key.code == sf::Keyboard::Space)
            key = BartaKeyMap::SPACEBAR;

        if (event.type == sf::Event::KeyPressed)
            eventLogger.logEvent(KeyPressedEvent(key));

        if (event.type == sf::Event::KeyReleased)
            eventLogger.logEvent(KeyReleasedEvent(key));

	}

	return true;
}

const sf::Transformable Barta::SFML_GraphicsBridge::convertTransformable(const TransformableInterface& myTransformable) {
	auto newTransformable = sf::Transformable();
	auto myVector = myTransformable.getPosition();
	newTransformable.setPosition(myVector.getX(), myVector.getY());
    newTransformable.setRotation(myTransformable.getRotaion());

	return newTransformable;
}
