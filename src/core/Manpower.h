
#ifndef MICRO_PROJET_JIN4526_MANPOWER_H
#define MICRO_PROJET_JIN4526_MANPOWER_H
#include "Resources.h"
#include <string>

class Manpower : public Resources {
  int available;
  int health;
  double moral;

public:
  Manpower(int health, double moral, int available, int quantity, std::string sprite) : quantity(quantity), sprite(sprite), available(available), health(health), moral(moral) {};
  virtual action() = 0;
};

#endif //MICRO_PROJET_JIN4526_MANPOWER_H
