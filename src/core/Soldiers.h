
#ifndef MICRO_PROJET_JIN4526_SOLDIER_H
#define MICRO_PROJET_JIN4526_SOLDIER_H
#include "Manpower.h"
#include <string>

class Soldiers : public Manpower {
    double strength;

    public:
    Soldiers(int quantity, std::string sprite, int available, int health, double moral, double strength)
        : Manpower(quantity, sprite, available, health, moral), strength(strength) {};
    Soldiers() = default;
    int action(int nbsoldiers) override;
    int attack(int nbsoldiers);
    double getStrenght() { return strength; }
};

#endif //MICRO_PROJET_JIN4526_SOLDIER_H
