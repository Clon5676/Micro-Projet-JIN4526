
#ifndef MICRO_PROJET_JIN4526_SOLDIEREVENTSTRATEGY_H
#define MICRO_PROJET_JIN4526_SOLDIEREVENTSTRATEGY_H

#include "EventStrategy.h"
#include "EventStrategyFactory.h"

class SoldierEventStrategy : public EventStrategy {

    static inline bool s_registered = EventStrategyFactory::register_class_name("SoldierEventStrategy", []() -> std::shared_ptr<EventStrategy> {
        return std::make_shared<SoldierEventStrategy>();
    });

public:
    SoldierEventStrategy() = default;
    void activateEvent(Game* game, int amount) override;
};

#endif //MICRO_PROJET_JIN4526_SOLDIEREVENTSTRATEGY_H
