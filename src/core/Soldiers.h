
#ifndef MICRO_PROJET_JIN4526_SOLDIER_H
#define MICRO_PROJET_JIN4526_SOLDIER_H
#include "Manpower.h"
#include <string>

class Soldiers : public Manpower {
    double damage;

    public:
    Soldiers(int quantity, std::string sprite, int available, int health, double moral, double damage)
        : Manpower(quantity, sprite, available, health, moral), damage(damage) {};
    Soldiers() = default;
    void action() override;
};

#endif //MICRO_PROJET_JIN4526_SOLDIER_H
