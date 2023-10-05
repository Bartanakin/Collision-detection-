#include<Events/Events/LeftClickEvent.h>
#include<Events/BartaEventLoggerInterface.h>
#include "../Ball.h"

class ChangeBallColorSubscriber : public Barta::LeftClickEventSubscriberInterface {
public:
	ChangeBallColorSubscriber(Ball& ball);
	virtual ~ChangeBallColorSubscriber() = default;

	bool handle(Barta::LeftClickEvent& event) override;

	bool isValid() const noexcept override;

private:
	Ball& ball;
};