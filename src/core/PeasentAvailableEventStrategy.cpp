#include "PeasentAvailableEventStrategy.h"

void PeasentAvailableEventStrategy::activateEvent(Game* game, int amount) {
    int available = game->getPeasents()->getAvailable();
    if (amount < available) {
        game->getPeasents()->setAvailable(available - amount);
        return;
    }
    game->getPeasents()->setAvailable(0);
}