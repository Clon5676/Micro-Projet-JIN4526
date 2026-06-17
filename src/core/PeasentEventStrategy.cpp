#include "PeasentEventStrategy.h"

#include "Game.h"

void PeasentEventStrategy::activateEvent(Game* game, int amount) {
    if (amount > 0) {
        game->getPeasents()->addQuantity(amount);
        return;
    }
    else if (game->getPeasents()->spend(amount * (-1))) {
        return;
    }
    game->getPeasents()->setQuantity(0);
}
