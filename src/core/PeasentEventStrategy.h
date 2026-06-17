
#ifndef MICRO_PROJET_JIN4526_PEASENTEVENTSTRATEGY_H
#define MICRO_PROJET_JIN4526_PEASENTEVENTSTRATEGY_H

#include "EventStrategy.h"
#include "EventStrategyFactory.h"

class PeasentEventStrategy : public EventStrategy {

    static inline bool s_registered = EventStrategyFactory::register_class_name("PeasentEventStrategy", []() -> std::shared_ptr<EventStrategy> {
        return std::make_shared<PeasentEventStrategy>();
    });

public:
    PeasentEventStrategy() = default;
    void activateEvent(Game* game, int amount) override;
};

#endif //MICRO_PROJET_JIN4526_PEASENTEVENTSTRATEGY_H
