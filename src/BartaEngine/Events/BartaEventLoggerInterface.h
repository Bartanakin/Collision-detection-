#pragma once
#include "../pch.h"
#include "Events/LeftClickEvent.h"
#include "Events/CollisionEvent.h"
#include "Events/VelocityChangeEvent.h"

namespace Barta {
	template<typename EventType, typename ... OtherTypes>
	class EventMatcher:public EventMatcher<const EventType>, EventMatcher<const OtherTypes...> {
		public:
		using EventMatcher<const EventType>::logEvent;
		using EventMatcher<const OtherTypes...>::logEvent;
		using EventMatcher<const EventType>::logSubscriber;
		using EventMatcher<const OtherTypes...>::logSubscriber;

		void runSubscribers() {
			EventMatcher<const EventType>::runSubscribers();
			EventMatcher<const OtherTypes...>::runSubscribers();
		}
	};

	template<typename EventType>
	class EventMatcher<const EventType> {
		public:

		void logEvent(std::unique_ptr<const EventType> event) noexcept {
			this->events.push_back(std::move(event));
		}

		void logSubscriber(std::unique_ptr<EventSubscriber<const EventType>> subscriber) noexcept {
			this->subscribers.push_back(std::move(subscriber));
		}

		void runSubscribers() {
			if (this->events.empty() || this->subscribers.empty()) {
				return;
			}

			auto iSub = this->subscribers.begin();
			while (iSub != this->subscribers.end()) {
				bool subErased = false;
				auto iEv = this->events.begin();
				while (iEv != this->events.end()) {
					bool eventErased = false;
					if ((*iSub)->handle(**iEv)) {
						iEv = this->events.erase(iEv);
						eventErased = true;
					}

					if (!(*iSub)->isValid()) {
						iSub = this->subscribers.erase(iSub);
						subErased = true;

						break;
					}

					if (!eventErased) {
						iEv++;
					}
				}

				if (!subErased) {
					iSub++;
				}
			}

			this->events.clear();
		}

		private:

		std::list<std::unique_ptr<const EventType>> events;
		std::list<std::unique_ptr<EventSubscriber<const EventType>>> subscribers;
	};

	class CollisionEvent;
	class DynamicsChangeEvent;

	typedef EventMatcher<
		const LeftClickEvent,
		const CollisionEvent,
		const DynamicsChangeEvent
	> BartaEventLoggerInterface;
}