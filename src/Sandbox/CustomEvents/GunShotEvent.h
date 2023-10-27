#pragma once
#include <Events/TemplateEventSubscriber.h>

class GunShotEvent {
    public:
    GunShotEvent(
        std::chrono::time_point<std::chrono::steady_clock> beginnning
    ) noexcept: 
        beginnning(beginnning)
    {}
    GunShotEvent(const GunShotEvent&) = delete;
    GunShotEvent(GunShotEvent&&) noexcept = default;
    GunShotEvent& operator=(const GunShotEvent&) = delete;
    ~GunShotEvent() noexcept = default;

    inline std::chrono::time_point<std::chrono::steady_clock> getBeginning() const { return this->beginnning; }

    private:
    std::chrono::time_point<std::chrono::steady_clock> beginnning;
};

template<>
class Barta::EventSubscriber<GunShotEvent> {
    public:
    virtual ~EventSubscriber() noexcept = default;

    virtual bool handle(GunShotEvent& event) = 0;

    virtual bool isValid() const noexcept = 0;
};

typedef Barta::EventSubscriber<GunShotEvent> GunShotEventSubscriberInterface;

