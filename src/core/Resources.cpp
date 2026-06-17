#include "Resources.h"

Resources::Resources(int startQuantity, const std::string spriteName, const std::string resourceName)
    : quantity(startQuantity), sprite(spriteName), name(resourceName) {
}

std::string Resources::getName() const {
    return name;
}

int Resources::getQuantity() const {
    return quantity;
}

void Resources::setQuantity(int newQuantity) {
    quantity = newQuantity;
    if (quantity < 0) {
        quantity = 0;
    }
}

void Resources::addQuantity(int amount) {
    quantity += amount;
    if (quantity < 0) {
        quantity = 0;
    }
}

bool Resources::spend(int amount) {
    if (amount < 0 || quantity < amount) {
        return false;
    }

    quantity -= amount;
    return true;
}
