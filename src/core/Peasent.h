
#ifndef MICRO_PROJET_JIN4526_PEASENT_H
#define MICRO_PROJET_JIN4526_PEASENT_H
#include "Manpower.h"
#include <string>

class Peasent : public Manpower {
    double productivity;

public:
    Peasent(double productivity = 1.0, int available = 0, int health = 100, double moral = 1.0, int quantity = 0, const std::string& sprite = "")
        : Manpower(quantity, sprite, available, health, moral), productivity(productivity) {}

    int recolte() const;
    void action() override;
};

#endif //MICRO_PROJET_JIN4526_PEASENT_H
