
#ifndef MICRO_PROJET_JIN4526_GAME_H
#define MICRO_PROJET_JIN4526_GAME_H
#include "Event.h"
#include "Food.h"
#include "Materials.h"
#include "Peasent.h"
#include "Soldier.h"

#include <SFML/Graphics.hpp>
#include <string>

class Game {
    sf::RenderWindow window;
    sf::Font font;

    Food food;
    Materials materials;
    Soldier soldier;
    Peasent peasent;
    Event event;

    int day;
    int enemyHealth;
    std::string message;

public:
    Game();
    void init();
    void run();
    void pause();
    void chooseEvent(const sf::Event& currentEvent);

private:
    void updateDay();
    void draw();
    void drawText(const std::string& text, float x, float y, unsigned int size = 22);
    void farm();
    void mine();
    void recruitPeasant();
    void recruitSoldier();
    void attack();
    void feedPeople();

};

#endif //MICRO_PROJET_JIN4526_GAME_H
