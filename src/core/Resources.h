
#ifndef MICRO_PROJET_JIN4526_RESOURCES_H
#define MICRO_PROJET_JIN4526_RESOURCES_H

#include <string>

class Resources {
protected:
    int quantity;
    std::string sprite;

public:
    Resources(int startQuantity = 0, const std::string& spriteName = "");

    int getQuantity() const;
    const std::string& getSprite() const;

    void setQuantity(int newQuantity);
    void addQuantity(int amount);
    bool spend(int amount);

};

#endif //MICRO_PROJET_JIN4526_RESOURCES_H
