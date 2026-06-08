
#ifndef MICRO_PROJET_JIN4526_MANPOWER_H
#define MICRO_PROJET_JIN4526_MANPOWER_H

#include "Resources.h"
#include <string>

class Manpower : public Resources {
protected:
    int available;
    int health;
    double moral;

public:
    Manpower(int quantity = 0, const std::string& sprite = "", int available = 0, int health = 100, double moral = 1.0);
    virtual ~Manpower() = default;

    int getAvailable() const;
    int getHealth() const;
    double getMoral() const;

    void addPeople(int amount);
    bool usePeople(int amount);
    void rest();

    virtual void action() = 0;
};

#endif //MICRO_PROJET_JIN4526_MANPOWER_H
