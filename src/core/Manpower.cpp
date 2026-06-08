include "Manpower.h"
#include <sstream>
#include <iostream>


Manpower::Manpower(const pugi::xml_node& node)
    : label(node.attribute("label").as_string()),
    x(node.attribute("x").as_double()),
    y(node.attribute("y").as_double()) {
    //cout << (this->x) << (this->y) << endl;
}
