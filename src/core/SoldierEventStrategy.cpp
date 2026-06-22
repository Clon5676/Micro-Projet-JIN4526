#include "SoldierEventStrategy.h"

#include "Game.h"

void SoldierEventStrategy::activateEvent(Game* game, int amount) {
    if (amount > 0) {
        game->getSoldiers()->addQuantity(amount);
        return;
    }
    else if (game->getSoldiers()->spend(amount * (-1))) {
        return;
    }
    game->getSoldiers()->setQuantity(0);
}
