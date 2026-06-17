#include "MaterialsEventStrategy.h"

void MaterialsEventStrategy::activateEvent(Game* game, int amount) {
    if (amount > 0) {
        game->getMaterials()->addQuantity(amount);
        return;
    }
    else if (game->getMaterials()->spend(amount * (-1))) {
        return;
    }
    int quantity = game->getMaterials()->getQuantity();
    game->getMaterials()->setQuantity(0);
    return;
}