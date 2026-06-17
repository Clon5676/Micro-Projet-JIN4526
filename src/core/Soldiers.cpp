#include "Soldiers.h"

int Soldiers::action(int nbsoldiers) {
    if (usePeople(nbsoldiers)) {
        int damage = static_cast<int>(nbsoldiers * strength * moral);
        damage = applyRandomVariation(damage);

        moral -= 0.1;
        if (moral <= 0) {
            moral = 0;
        }
        return damage;
    }
    return 0;
}

int Soldiers::attack(int nbsoldiers) {
    return action(nbsoldiers);
}

int Soldiers::getMaxRecruitable(const Food& food, const Materials& materials) const {
    const int foodCost = 15;
    const int materialsCost = 15;
    const int maxByFood = food.getQuantity() / foodCost;
    const int maxByMaterials = materials.getQuantity() / materialsCost;

    if (maxByFood < maxByMaterials) {
        return maxByFood;
    }
    return maxByMaterials;
}

bool Soldiers::recruit(Food& food, Materials& materials, int amount) {
    const int foodCost = 15;
    const int materialsCost = 15;

    if (amount <= 0 || getMaxRecruitable(food, materials) < amount) {
        return false;
    }

    food.spend(foodCost * amount);
    materials.spend(materialsCost * amount);
    addPeople(amount);
    return true;
}
