#include "Manpower.h"
#include "Peasent.h"
#include "Soldier.h"

Resources::Resources(int startQuantity, const std::string& spriteName)
    : quantity(startQuantity), sprite(spriteName) {
}

int Resources::getQuantity() const {
    return quantity;
}

const std::string& Resources::getSprite() const {
    return sprite;
}

void Resources::setQuantity(int newQuantity) {
    quantity = newQuantity;
    if (quantity < 0) {
        quantity = 0;
    }
}

void Resources::addQuantity(int amount) {
    setQuantity(quantity + amount);
}

bool Resources::spend(int amount) {
    if (amount < 0 || quantity < amount) {
        return false;
    }

    quantity -= amount;
    return true;
}

Manpower::Manpower(int quantity, const std::string& sprite, int available, int health, double moral)
    : Resources(quantity, sprite), available(available), health(health), moral(moral) {
}

int Manpower::getAvailable() const {
    return available;
}

int Manpower::getHealth() const {
    return health;
}

double Manpower::getMoral() const {
    return moral;
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
}

int Peasent::recolte() const {
    return static_cast<int>(getAvailable() * productivity * moral);
}

void Peasent::action() {
    rest();
}

double Soldier::battle() const {
    return getAvailable() * damage * moral;
}

void Soldier::action() {
    rest();
}
