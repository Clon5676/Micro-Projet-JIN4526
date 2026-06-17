
#ifndef MICRO_PROJET_JIN4526_SOLDIERAVAILABLEEVENTSTRATEGY_H
#define MICRO_PROJET_JIN4526_SOLDIERAVAILABLEEVENTSTRATEGY_H

#include "EventStrategy.h"
#include "EventStrategyFactory.h"

class SoldierAvailableEventStrategy : public EventStrategy {

    static inline bool s_registered = EventStrategyFactory::register_class_name("SoldierAvailableEventStrategy", []() -> std::shared_ptr<EventStrategy> {
        return std::make_shared<SoldierAvailableEventStrategy>();
    });

public:
    SoldierAvailableEventStrategy() = default;
    void activateEvent(Game* game, int amount) override;
};

#endif //MICRO_PROJET_JIN4526_SOLDIERAVAILABLEEVENTSTRATEGY_H
