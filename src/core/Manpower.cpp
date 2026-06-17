#include "Manpower.h"
#include "Peasents.h"
#include "Soldiers.h"

#include <algorithm>
#include <random>

int Manpower::applyRandomVariation(int baseValue) const {
    if (baseValue <= 0) {
        return 1;
    }

    static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());
    std::uniform_real_distribution<double> distribution(0.8, 1.2);

    const int variedValue = static_cast<int>(baseValue * distribution(generator));
    return std::max(1, variedValue);
}

void Manpower::addPeople(int amount) {
    if (amount <= 0) {
        return;
    }

    quantity += amount;
    available += amount;
}

bool Manpower::usePeople(int amount) {
    if (amount < 0 || available < amount) {
        return false;
    }

    available -= amount;
    return true;
}

void Manpower::rest() {
    available = quantity;

    if (feed) {
        moral += 0.5;
        if (moral > 2.0) {
            moral = 2.0;
        }
    }
    feed = false;
}
