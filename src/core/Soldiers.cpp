#include "Soldiers.h"

void Soldiers::action() {
    int dead =  getAvailable() * damage * moral;
}
