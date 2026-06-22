#include "SoldierAvailableEventStrategy.h"

void SoldierAvailableEventStrategy::activateEvent(Game* game, int amount) {
    game->getSoldiers()->setToRest(amount);
}