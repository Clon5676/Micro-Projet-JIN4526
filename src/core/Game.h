
#ifndef MICRO_PROJET_JIN4526_GAME_H
#define MICRO_PROJET_JIN4526_GAME_H
#include "Event.h"
#include "Food.h"
#include "Materials.h"
#include "Peasent.h"
#include "Soldier.h"

class Game {
    Food food;
    Materials materials;
    Soldier soldier;
    Peasent peasent;
    Event event;

    public:
    Game();
    void init();
    void run();

};

#endif //MICRO_PROJET_JIN4526_GAME_H
