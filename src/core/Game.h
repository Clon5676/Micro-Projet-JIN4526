
#ifndef MICRO_PROJET_JIN4526_GAME_H
#define MICRO_PROJET_JIN4526_GAME_H
#include "Event.h"
#include "Food.h"
#include "Materials.h"
#include "Peasent.h"
#include "Soldiers.h"
#include "pugixml.hpp"

class Game {
    Food food;
    Materials materials;
    Soldiers soldiers;
    Peasent peasent;
    Event event;

    public:
    Game(pugi::xml_node node);
    void init();
    void run();

};

#endif //MICRO_PROJET_JIN4526_GAME_H
