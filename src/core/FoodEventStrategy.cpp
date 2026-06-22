#include "FoodEventStrategy.h"

#include "Game.h"

void FoodEventStrategy::activateEvent(Game* game, int amount) {
    if (amount > 0) {
        game->getFood()->addQuantity(amount);
        return;
    }
    else if (game->getFood()->spend(amount * (-1))) {
        return;
    }
    int quantity = game->getFood()->getQuantity();
    game->getFood()->setQuantity(0);
    return;
}
