#pragma once
#include"../Geometrics/Vector2f.h"
#include<list>
#include"../BartaObject.h"
#include"../Events/BartaEventLoggerInterface.h"
namespace Barta{
	class BartaGraphicsBridgeInterface{
	public:
		BartaGraphicsBridgeInterface() = default;
		virtual ~BartaGraphicsBridgeInterface() = default;

		virtual void createWindow( Vector2f size, std::string title ) = 0;
		virtual void drawObjects( std::list<BartaObjectInterface*> objects ) = 0;
		virtual bool logEvents( BartaEventLoggerInterface& eventLogger ) = 0;
	};
}

