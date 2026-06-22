
#ifndef MICRO_PROJET_JIN4526_MATERIALSEVENTSTRATEGY_H
#define MICRO_PROJET_JIN4526_MATERIALSEVENTSTRATEGY_H
#include "EventStrategy.h"
#include "EventStrategyFactory.h"

class MaterialsEventStrategy : public EventStrategy {

    static inline bool s_registered = EventStrategyFactory::register_class_name("MaterialsEventStrategy", []() -> std::shared_ptr<EventStrategy> {
        return std::make_shared<MaterialsEventStrategy>();
    });

public:
    MaterialsEventStrategy() = default;
    void activateEvent(Game* game, int amount) override;
};

#endif //MICRO_PROJET_JIN4526_MATERIALSEVENTSTRATEGY_H
