
#ifndef MICRO_PROJET_JIN4526_MANPOWER_H
#define MICRO_PROJET_JIN4526_MANPOWER_H

#include "Resources.h"
#include <string>

class Manpower : public Resources {
protected:
    int available;
    int health;
    double moral;
    bool feed;

public:
    Manpower(int quantity, const std::string sprite, int available, int health, double moral) : Resources(quantity, sprite), available(available), health(health), moral(moral), feed(false) {};
    virtual ~Manpower() = default;
    Manpower() = default;

    int getAvailable() const {return available;}
    int getHealth() const {return health;}
    double getMoral() const {return moral;}

    void addPeople(int amount);
    bool usePeople(int amount);
    void rest();
    void feeded() {feed = true;}

    virtual int action(int nbmanpower) = 0;
};

#endif //MICRO_PROJET_JIN4526_MANPOWER_H
