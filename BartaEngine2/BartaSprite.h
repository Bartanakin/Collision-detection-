#pragma once
#include"BartaObject.h"
#include"Hitbox/CircleHitbox.h"
//namespace Barta{
//
//	class ColorBall : public BartaObjectInterface
//	{
//	public:
//		ColorBall( const sf::Texture& texture, const HitboxInterface& hitbox );
//		void draw( sf::RenderWindow& window ) override;
//		bool isWithinHitbox( sf::Vector2f position ) const;
//	private:
//		const HitboxInterface& hitbox;
//		sf::Sprite sprite;
//	};
//
//}
//
//
//// Event condition macros 
//#define IS_LEFT_BUTTON_CLICKED(pointer_to_BartaSprite) [&]( Barta::BartaEvent& event ){                            \
//    return event.mouseButton.button == sf::Mouse::Left														\
//    && event.type == sf::Event::MouseButtonPressed															\
//    && pointer_to_BartaSprite->isWithinHitbox( event.getMouseButtonPosition() );  \
//}