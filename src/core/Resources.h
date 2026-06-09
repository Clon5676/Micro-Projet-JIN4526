
#ifndef MICRO_PROJET_JIN4526_RESOURCES_H
#define MICRO_PROJET_JIN4526_RESOURCES_H

#include <string>

class Resources {
protected:
    int quantity;
    std::string sprite;

public:
    Resources(int startQuantity, const std::string spriteName) : quantity(startQuantity), sprite(spriteName) {};
    Resources() = default;

    int getQuantity() const {return quantity;}
    const std::string& getSprite() const {return sprite;}

    void setQuantity(int newQuantity) {quantity = newQuantity; if (quantity < 0) {quantity = 0;} }
    void addQuantity(int amount) {quantity += amount;}
    bool spend(int amount) {if (amount < 0 || quantity < amount) {return false;} quantity -= amount; return true;}

};

#endif //MICRO_PROJET_JIN4526_RESOURCES_H
