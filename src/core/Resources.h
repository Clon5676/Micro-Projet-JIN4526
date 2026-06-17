
#ifndef MICRO_PROJET_JIN4526_RESOURCES_H
#define MICRO_PROJET_JIN4526_RESOURCES_H

#include "ResourceComponent.h"

#include <string>

class Resources : public ResourceComponent {
protected:
    int quantity;
    std::string name;

public:
    Resources(int startQuantity, const std::string resourceName = "Resource");
    Resources() = default;

    std::string getName() const override;
    int getQuantity() const override;

    void setQuantity(int newQuantity) override;
    void addQuantity(int amount) override;
    bool spend(int amount) override;

};

#endif //MICRO_PROJET_JIN4526_RESOURCES_H
