#pragma once
#include "BartaGraphicsBridgeInterface.h"
#include "SFML_Bridge/ResourceMatcherInterface.h"

namespace Barta{
    class SFML_GraphicsBridge :
        public BartaGraphicsBridgeInterface{
    public:
        SFML_GraphicsBridge() noexcept;
        SFML_GraphicsBridge( const SFML_GraphicsBridge& ) noexcept = delete;
        virtual ~SFML_GraphicsBridge();

        void createWindow( Vector2f size, std::string title ) override;
        void drawObjects( const std::list<BartaObjectInterface*>& objects ) override;
        bool logEvents( BartaEventLoggerInterface& eventLogger ) override;

        static const sf::Transformable convertTransformable( const TransformableInterface& myTransformable );
    private:
        sf::RenderWindow* sf_window;
        RecourseMatcherInterface* const resourceMatcher;
    };
}

