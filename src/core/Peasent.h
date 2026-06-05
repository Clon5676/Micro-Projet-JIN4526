
#ifndef MICRO_PROJET_JIN4526_PEASENT_H
#define MICRO_PROJET_JIN4526_PEASENT_H
#include "Manpower.h"
#include <string>

class Peasent : public Manpower {
    double productivity;

    public:
    Peasent(double productivity, int available, int health, double moral, int quantity, std::string sprite) : productivity(productivity), available(available), health(health), moral(moral), quantity(quantity), sprite(sprite) {};
    void recolt();
    void action() override;
};

#endif //MICRO_PROJET_JIN4526_PEASENT_H
