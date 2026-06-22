
#ifndef MICRO_PROJET_JIN4526_ADDPEASENTSSTRATEGY_H
#define MICRO_PROJET_JIN4526_ADDPEASENTSSTRATEGY_H
#include "EventStrategy.h"
#include "EventStrategyFactory.h"

class FoodEventStrategy : public EventStrategy {

    static inline bool s_registered = EventStrategyFactory::register_class_name("FoodEventStrategy", []() -> std::shared_ptr<EventStrategy> {
        return std::make_shared<FoodEventStrategy>();
    });

    public:
    FoodEventStrategy() = default;
    void activateEvent(Game* game, int amount) override;
};

#endif //MICRO_PROJET_JIN4526_ADDPEASENTSSTRATEGY_H
