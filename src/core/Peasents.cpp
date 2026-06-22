#include "Peasents.h"
#include <cmath>

int Peasents::action(int nbpeasents) {
    if (usePeople(nbpeasents)) {
        int resources = static_cast<int>(std::round(nbpeasents * moral * productivity));
        resources = applyRandomVariation(resources);
        moral -= 0.1;
        if (moral <= 0) {
            moral = 0;
        }
        productivity += 0.1;
        return resources;
    }
    return 0;
}

int Peasents::farm(int nbpeasents) {
    return action(nbpeasents);
}

int Peasents::mine(int nbpeasents) {
    return action(nbpeasents);
}

bool Peasents::recruit(Food& food) {
    const int foodCost = 20;
    if (!food.spend(foodCost)) {
        return false;
    }

    addPeople(1);
    return true;
}
