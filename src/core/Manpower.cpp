#include "Manpower.h"
#include "Peasents.h"
#include "Soldiers.h"

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
    available += toRest;

    if (available < 0) {
        available = 0;
    }

    if (feed) {
        moral += 0.5;
    }
    feed = false;
    toRest = 0;
}
