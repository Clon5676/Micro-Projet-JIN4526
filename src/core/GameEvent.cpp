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

int GameEvent::countEvents() const {
    int count = 1;
    std::shared_ptr<GameEvent> currentEvent = nextEvent;

    while (currentEvent != nullptr) {
        count++;
        currentEvent = currentEvent->nextEvent;
    }

    return count;
}

std::shared_ptr<GameEvent> GameEvent::getEventAt(int index) {
    if (index <= 0) {
        return std::make_shared<GameEvent>(*this);
    }

    std::shared_ptr<GameEvent> currentEvent = nextEvent;
    int currentIndex = 1;

    while (currentEvent != nullptr && currentIndex < index) {
        currentEvent = currentEvent->nextEvent;
        currentIndex++;
    }

    if (currentEvent == nullptr) {
        return std::make_shared<GameEvent>(*this);
    }

    return currentEvent;
}
