
#ifndef MICRO_PROJET_JIN4526_MATERIALS_H
#define MICRO_PROJET_JIN4526_MATERIALS_H

#include "Resources.h"
#include <string>

class Materials : public Resources {
public:
    Materials(int quantity = 0, const std::string& sprite = "") : Resources(quantity, sprite) {}
};

#endif //MICRO_PROJET_JIN4526_MATERIALS_H
