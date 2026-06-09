
#ifndef MICRO_PROJET_JIN4526_EVENT_H
#define MICRO_PROJET_JIN4526_EVENT_H

#include <string>
#include <vector>

class Event {
    std::vector<std::string> eventList;

public:
    Event(std::string fichier);
    Event() = default;
    std::string activate(int day) const;
};

#endif //MICRO_PROJET_JIN4526_EVENT_H
