#pragma once
#include "pch.h"
#include <Graphics/SFML_Bridge/ResourceContainerInterface.h>

class SimpleResourceContainer : public Barta::ResourceContainerInterface{
public:
    SimpleResourceContainer();
    virtual ~SimpleResourceContainer();

    virtual bool hasTexture( const int resource ) const override;

    virtual const sf::Texture& getTexture( const int resource ) const override;

    virtual const sf::IntRect getTextureRect( const int resource ) const override;

private:
    const static std::string REPOSITORY_DIR;

    sf::Texture texture;
    sf::IntRect redBallTextureRect;
    sf::IntRect greenBallTextureRect;
    sf::IntRect yellowBlockRect;
    sf::IntRect giantBlock;
    sf::Texture inputTexture;
    sf::IntRect greenArrow;
    sf::IntRect bomb;

    void init();
};

