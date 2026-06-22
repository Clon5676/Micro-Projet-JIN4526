#ifndef MICRO_PROJET_JIN4526_RESOURCECOMPONENT_H
#define MICRO_PROJET_JIN4526_RESOURCECOMPONENT_H

#include <string>

class ResourceComponent {
public:
    virtual ~ResourceComponent() = default;

    virtual std::string getName() const = 0;
    virtual int getQuantity() const = 0;
    virtual void setQuantity(int newQuantity) = 0;
    virtual void addQuantity(int amount) = 0;
    virtual bool spend(int amount) = 0;
};

#endif //MICRO_PROJET_JIN4526_RESOURCECOMPONENT_H
