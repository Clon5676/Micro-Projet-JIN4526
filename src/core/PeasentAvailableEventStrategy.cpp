#include "PeasentAvailableEventStrategy.h"

void PeasentAvailableEventStrategy::activateEvent(Game* game, int amount) {
    game->getPeasents()->setToRest(amount);
}