
#ifndef MICRO_PROJET_JIN4526_EVENT_H
#define MICRO_PROJET_JIN4526_EVENT_H

#include <memory>
#include <string>

#include "EventStrategy.h"
#include "pugixml.hpp"

class EventStrategy;

class GameEvent{
    std::shared_ptr<GameEvent> nextEvent;
    int value;
    std::string effect;
    std::shared_ptr<EventStrategy> eventstrategie;

public:
    GameEvent(pugi::xml_node node);
    GameEvent(std::shared_ptr<GameEvent> nextEvent, int value, std::string effect, std::string_view eventstrategie);
    GameEvent(int value, std::string effect, std::string_view eventstrategie);
    GameEvent() = default;
    std::shared_ptr<GameEvent> getNextEvent() { return nextEvent;}
    int getValue() { return value;}
    std::string getEffect() { return effect;}
    std::shared_ptr<EventStrategy> getEventStrategie() { return eventstrategie;}
    int countEvents() const;
    std::shared_ptr<GameEvent> getEventAt(int index);
};

#endif //MICRO_PROJET_JIN4526_EVENT_H
