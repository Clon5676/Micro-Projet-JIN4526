#include "Peasents.h"

void Peasents::action() {
    int newfood =  static_cast<int>(getAvailable() * productivity * moral);
}
