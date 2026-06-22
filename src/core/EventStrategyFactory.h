
#ifndef MICRO_PROJET_JIN4526_EVENTSTRATEGYFACTORY_H
#define MICRO_PROJET_JIN4526_EVENTSTRATEGYFACTORY_H
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "EventStrategy.h"

class EventStrategyFactory {

    public:
    using EventStrategies_create = std::function<std::shared_ptr<EventStrategy>()>;

    static bool register_class_name(std::string_view class_name, EventStrategies_create const& event_strategies_create) {
        if (!get_name2create_methods().contains(class_name)) {
        std::cout << class_name << " registered\n";
        get_name2create_methods()[class_name] = event_strategies_create;
        return true;

    }
        std::cerr << "ERROR : " << class_name << " registered\n";
        return false;
    }

    static std::shared_ptr<EventStrategy> create(std::string_view class_name) {
        return get_name2create_methods().contains(class_name)
                   ? get_name2create_methods()[class_name]()
                   : nullptr;
    }

private:
    static std::map<std::string_view, EventStrategies_create>& get_name2create_methods() {
        static std::map<std::string_view, EventStrategies_create> name2create;
        return name2create;
    }

};

#endif //MICRO_PROJET_JIN4526_EVENTSTRATEGYFACTORY_H
