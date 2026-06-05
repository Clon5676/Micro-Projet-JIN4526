
#ifndef MICRO_PROJET_JIN4526_SOLDIER_H
#define MICRO_PROJET_JIN4526_SOLDIER_H
#include "Manpower.h"
#include <string>

class Soldiers : public Manpower {
    double damage;

    public:
    Soldiers(double damage, int available, int health, double moral, int quantity, std::string sprite) : damage(damage), available(available), health(health), moral(moral), quantity(quantity), sprite(sprite) {};
    void battle();
    void action() override;
};

#endif //MICRO_PROJET_JIN4526_SOLDIER_H
