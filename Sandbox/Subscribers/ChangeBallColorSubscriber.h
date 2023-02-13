#include<Events/EventSubscriberInterface.h>
#include<Events/Events/LeftClickEvent.h>
#include "../Ball.h"


class ChangeBallColorSubscriber : public Barta::EventSubscriberInterface{
public:
	ChangeBallColorSubscriber(Ball& ball);
	virtual ~ChangeBallColorSubscriber() = default;

	virtual Barta::EventType getSupportedType() const noexcept override;
	
	virtual bool handle( const Barta::BartaEvent& event ) override;

	virtual bool isValid() const noexcept override;

private:
	Ball& ball;
};