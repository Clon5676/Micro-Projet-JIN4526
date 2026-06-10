#include "Peasents.h"
#include <cmath>

int Peasents::action(int nbpeasents) {
    if (usePeople(nbpeasents)) {
        int resources = std::round(nbpeasents * moral * productivity);
        moral -= 0.1;
        if (moral <= 0) {
            moral = 0;
        }
        productivity += 0.1;
        return resources;
    }
    return 0;
}