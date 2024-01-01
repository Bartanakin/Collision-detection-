#pragma once
#include "pch.h"
#include <Graphics/SFML_Bridge/ResourceContainerInterface.h>

class SimpleResourceContainer : public Barta::ResourceContainerInterface{
public:
    SimpleResourceContainer(
        std::string repositoryDir
    );
    virtual ~SimpleResourceContainer();

    virtual bool hasTexture( const int resource ) const override;

    virtual const sf::Texture& getTexture( const int resource ) const override;

    virtual const sf::IntRect getTextureRect( const int resource ) const override;

private:
    const std::string repositoryDir;

    sf::Texture texture;
    sf::IntRect redBallTextureRect;
    sf::IntRect greenBallTextureRect;
    sf::IntRect yellowBlockRect;
    sf::Texture inputTexture;
    sf::IntRect greenArrow;
    sf::IntRect bomb;
    sf::IntRect instruction;

    void init();
};

