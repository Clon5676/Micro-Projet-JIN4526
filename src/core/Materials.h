
#ifndef MICRO_PROJET_JIN4526_MATERIALS_H
#define MICRO_PROJET_JIN4526_MATERIALS_H

#include "Resources.h"

class Materials : public Resources {
public:
    explicit Materials(int quantity) : Resources(quantity, "Materials") {}
    Materials() = default;
};

#endif //MICRO_PROJET_JIN4526_MATERIALS_H
