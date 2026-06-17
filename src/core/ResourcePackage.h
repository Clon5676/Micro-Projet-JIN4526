#ifndef MICRO_PROJET_JIN4526_RESOURCEPACKAGE_H
#define MICRO_PROJET_JIN4526_RESOURCEPACKAGE_H

#include "ResourceComponent.h"

#include <string>
#include <vector>

class ResourcePackage : public ResourceComponent {
    std::string name;
    std::vector<ResourceComponent*> children;

public:
    explicit ResourcePackage(const std::string& packageName = "Package");

    void add(ResourceComponent& resource);
    void clear();

    std::string getName() const override;
    int getQuantity() const override;
    void setQuantity(int newQuantity) override;
    void addQuantity(int amount) override;
    bool spend(int amount) override;
};

#endif //MICRO_PROJET_JIN4526_RESOURCEPACKAGE_H
