#include "EnemyHealthEventStrategy.h"

#include "Game.h"

void EnemyHealthEventStrategy::activateEvent(Game* game, int amount) {
    int enemyHealth = game->getEnemyHealth();
    if (amount > 0) {
        game->setEnemyHealth(enemyHealth + amount);
        return;
    }
    else if (amount * -1 < enemyHealth) {
        game->setEnemyHealth(enemyHealth + amount);
        return;
    }
    game->setEnemyHealth(0);
}
