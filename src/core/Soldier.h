
#ifndef MICRO_PROJET_JIN4526_SOLDIER_H
#define MICRO_PROJET_JIN4526_SOLDIER_H
#include "Manpower.h"
#include <string>

class Soldier : public Manpower {
    double damage;

public:
    Soldier(double damage = 1.0, int available = 0, int health = 100, double moral = 1.0, int quantity = 0, const std::string& sprite = "")
        : Manpower(quantity, sprite, available, health, moral), damage(damage) {}

    double battle() const;
    void action() override;
};

#endif //MICRO_PROJET_JIN4526_SOLDIER_H
