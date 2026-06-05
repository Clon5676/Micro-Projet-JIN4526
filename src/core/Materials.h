
#ifndef MICRO_PROJET_JIN4526_MATERIALS_H
#define MICRO_PROJET_JIN4526_MATERIALS_H

#include "Resources.h"
#include <string>

class Materials : public Resources {
    public:
    Materials(int quantity, std::string sprite) : quantity(quantity), sprite(sprite) {};
};

#endif //MICRO_PROJET_JIN4526_MATERIALS_H
