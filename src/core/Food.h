
#ifndef MICRO_PROJET_JIN4526_FOOD_H
#define MICRO_PROJET_JIN4526_FOOD_H
#include "Resources.h"

class Food : public Resources {

    public:
    explicit Food(int quantity) : Resources(quantity, "Food") {};
    Food() = default;
    ~Food() = default;
};

#endif //MICRO_PROJET_JIN4526_FOOD_H
