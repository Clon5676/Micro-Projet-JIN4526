#include "Soldiers.h"

int Soldiers::action(int nbsoldiers) {
    if (usePeople(nbsoldiers)) {
        int damage =  nbsoldiers * strength * moral;

        moral -= 0.1;
        if (moral <= 0) {
            moral = 0;
        }
        return damage;
    }
    return 0;
}

int Soldiers::attack(int nbsoldiers) {
    return action(nbsoldiers);
}
