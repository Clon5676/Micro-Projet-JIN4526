#include "Event.h"
#include "SFML/Window/Event.hpp"

#include <fstream>
#include <iostream>
#include <string>

Event::Event(std::string fichier) {

    std::ifstream file(fichier);

      if (!file.is_open()) {
          std::cerr << "Erreur: impossible d'ouvrir le fichier!" << std::endl;
      }

      std::string line;
      while (std::getline(file, line)) {
          eventList.push_back(line);
      }

      file.close();
}

std::string Event::activate(int day) const {
    const int eventIndex = day % static_cast<int>(eventList.size());
    return eventList[eventIndex];
}
