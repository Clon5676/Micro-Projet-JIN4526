
#ifndef MICRO_PROJET_JIN4526_FOOD_H
#define MICRO_PROJET_JIN4526_FOOD_H
#include "Resources.h"
#include <string>

class Food : public Resources {
public:
    Food(int quantity = 0, const std::string& sprite = "") : Resources(quantity, sprite) {}
};

#endif //MICRO_PROJET_JIN4526_FOOD_H
