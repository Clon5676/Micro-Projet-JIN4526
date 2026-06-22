
#ifndef MICRO_PROJET_JIN4526_ENEMYHEALTHSTRATEGY_H
#define MICRO_PROJET_JIN4526_ENEMYHEALTHSTRATEGY_H

#include "EventStrategy.h"
#include "EventStrategyFactory.h"

class EnemyHealthEventStrategy : public EventStrategy {

    static inline bool s_registered = EventStrategyFactory::register_class_name("EnemyHealthEventStrategy", []() -> std::shared_ptr<EventStrategy> {
        return std::make_shared<EnemyHealthEventStrategy>();
    });

public:
    EnemyHealthEventStrategy() = default;
    void activateEvent(Game* game, int amount) override;
};


#endif //MICRO_PROJET_JIN4526_ENEMYHEALTHSTRATEGY_H
