
#ifndef MICRO_PROJET_JIN4526_EVENTSTRATEGY_H
#define MICRO_PROJET_JIN4526_EVENTSTRATEGY_H
#include "Game.h"

class Game;

class EventStrategy {
    public:
    virtual void activateEvent(Game* game, int amount) = 0;
};

#endif //MICRO_PROJET_JIN4526_EVENTSTRATEGY_H
