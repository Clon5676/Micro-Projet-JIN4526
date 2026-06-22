#include "ResourcePackage.h"

ResourcePackage::ResourcePackage(const std::string& packageName) : name(packageName) {
}

void ResourcePackage::add(ResourceComponent& resource) {
    children.push_back(&resource);
}

void ResourcePackage::clear() {
    children.clear();
}

std::string ResourcePackage::getName() const {
    return name;
}

int ResourcePackage::getQuantity() const {
    int total = 0;
    for (const ResourceComponent* child : children) {
        total += child->getQuantity();
    }
    return total;
}

void ResourcePackage::setQuantity(int newQuantity) {
    if (children.empty()) {
        return;
    }

    children.front()->setQuantity(newQuantity);
}

void ResourcePackage::addQuantity(int amount) {
    if (children.empty()) {
        return;
    }

    children.front()->addQuantity(amount);
}

bool ResourcePackage::spend(int amount) {
    if (amount < 0 || getQuantity() < amount) {
        return false;
    }

    int remaining = amount;
    for (ResourceComponent* child : children) {
        const int childQuantity = child->getQuantity();
        if (childQuantity >= remaining) {
            child->spend(remaining);
            return true;
        }

        child->spend(childQuantity);
        remaining -= childQuantity;
    }

    return true;
}
