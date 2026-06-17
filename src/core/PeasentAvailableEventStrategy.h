
#ifndef MICRO_PROJET_JIN4526_PEASENTAVAILABLEEVENTSTRATEGY_H
#define MICRO_PROJET_JIN4526_PEASENTAVAILABLEEVENTSTRATEGY_H

#include "EventStrategy.h"
#include "EventStrategyFactory.h"

class PeasentAvailableEventStrategy : public EventStrategy {

    static inline bool s_registered = EventStrategyFactory::register_class_name("PeasentAvailableEventStrategy", []() -> std::shared_ptr<EventStrategy> {
        return std::make_shared<PeasentAvailableEventStrategy>();
    });

public:
    PeasentAvailableEventStrategy() = default;
    void activateEvent(Game* game, int amount) override;
};

#endif //MICRO_PROJET_JIN4526_PEASENTAVAILABLEEVENTSTRATEGY_H
