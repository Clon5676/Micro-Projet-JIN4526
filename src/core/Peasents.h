
#ifndef MICRO_PROJET_JIN4526_PEASENT_H
#define MICRO_PROJET_JIN4526_PEASENT_H
#include "Manpower.h"
#include <string>

class Peasents : public Manpower {
    double productivity;

public:
    Peasents(int quantity, const std::string& sprite, int available, int health, double moral, double productivity)
        : Manpower(quantity, sprite, available, health, moral), productivity(productivity) {}
    Peasents() = default;

    int action(int nbpeasents) override;
    int farm(int nbpeasents);
    int mine(int nbpeasents);
    double getProductivity() {return productivity;};
};

#endif //MICRO_PROJET_JIN4526_PEASENT_H
