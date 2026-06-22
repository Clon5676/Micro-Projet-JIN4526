#include "GameEvent.h"
#include <string>

#include "EventStrategyFactory.h"

GameEvent::GameEvent(pugi::xml_node node) {
    value = node.attribute("value").as_int();
    effect = node.attribute("effect").as_string();
    eventstrategie = EventStrategyFactory::create((std::string_view)node.attribute("strategy").as_string());
    std::shared_ptr<GameEvent> lastEvent = nullptr;

    for (auto const& child : node.children()) {
        lastEvent = std::make_shared<GameEvent>(lastEvent,
            child.attribute("value").as_int(),
            child.attribute("effect").as_string(),
            (std::string_view)child.attribute("strategy").as_string());
    }
   nextEvent = lastEvent;
}

GameEvent::GameEvent(std::shared_ptr<GameEvent> nextEvent, int value, std::string effect, std::string_view eventstrategie) {
    this->nextEvent = nextEvent;
    this->value = value;
    this->effect = effect;
    this->eventstrategie = EventStrategyFactory::create(eventstrategie);
}