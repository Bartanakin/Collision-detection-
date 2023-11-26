#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"
#include "../../Collisions/CollisionExecutors/CollisionTestExecutorInterface.h"
#include "../../Collisions/CollcionTestResult/ExtendedCollisionResult.h"
#include "../../Tests/Utilities/TestUtilities.h"

#define DEBUG_COLLISION_EVENT 0

namespace Barta {

	class CollisionEvent 
	{
		public:
		CollisionEvent(const ExtendedCollisionResult collisionResuslt, float delta_t) noexcept:
			collisionResuslt(std::move(collisionResuslt)), delta_t(delta_t) {}
        CollisionEvent(const CollisionEvent&) = delete;
        CollisionEvent(CollisionEvent&&) noexcept = default;
        CollisionEvent& operator=(const CollisionEvent&) = delete;
        ~CollisionEvent() noexcept = default;

		bool compareObjects(CollisionAwareInterface* first, CollisionAwareInterface* second) const noexcept;
		bool isOneOf(CollisionAwareInterface* needle) const noexcept;

        template<typename T, typename List>
        T* matchEitherFromList(List& list) const {
            for (auto ptr : list) {
                if (this->getTestResult().object1 == static_cast<Barta::CollisionAwareInterface*>(ptr)) {
                    return ptr;
                }

                if (this->getTestResult().object2 == static_cast<Barta::CollisionAwareInterface*>(ptr)) {
                    return ptr;
                }
            }

            return nullptr;
        }

        template<typename T1, typename T2, typename List1, typename List2>
        std::pair<T1*, T2*> matchBothFrom(List1& list1, List2& list2) const {
            T1* p1 = nullptr;
            T2* p2 = nullptr;
            for (auto ptr : list1) {
                if (this->getTestResult().object1 == static_cast<Barta::CollisionAwareInterface*>(ptr)) {
                    p1 = ptr;

                    break;
                }
            }

            for (auto ptr : list2) {
                if (this->getTestResult().object2 == static_cast<Barta::CollisionAwareInterface*>(ptr)) {
                    p2 = ptr;

                    break;
                }
            }

            if (p1 != nullptr && p2 != nullptr) {
                return { p1, p2 };
            }

            for (auto ptr : list1) {
                if (this->getTestResult().object2 == static_cast<Barta::CollisionAwareInterface*>(ptr)) {
                    p1 = ptr;

                    break;
                }
            }

            for (auto ptr : list2) {
                if (this->getTestResult().object1 == static_cast<Barta::CollisionAwareInterface*>(ptr)) {
                    p2 = ptr;

                    break;
                }
            }

            if (p1 != nullptr && p2 != nullptr) {
                return { p1, p2 };
            }

            return { nullptr, nullptr };
        }

		inline const ExtendedCollisionResult getTestResult() const noexcept {
			return this->collisionResuslt;
		}

		inline float getDelta_t() const noexcept {
			return this->delta_t;
		}

		private:
		const ExtendedCollisionResult collisionResuslt;
		const float delta_t;
	};

	template<>
	class EventSubscriber<CollisionEvent> {
		public:
        virtual ~EventSubscriber() noexcept = default;

		virtual bool handle(CollisionEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<CollisionEvent> CollisionEventSubscriberInterface;
}

