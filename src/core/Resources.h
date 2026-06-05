
#ifndef MICRO_PROJET_JIN4526_RESOURCES_H
#define MICRO_PROJET_JIN4526_RESOURCES_H

#include <string>

class Resources {
    int quantity;
    std::string sprite;

    public:
    Resources(int quantity, std::string sprite) : quantity(quantity), sprite(sprite) {};
    void setQuantity(int quantity) {this.quantity += quantity;}

};

#endif //MICRO_PROJET_JIN4526_RESOURCES_H
