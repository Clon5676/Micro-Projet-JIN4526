#ifndef MICRO_PROJET_JIN4526_GAME_H
#define MICRO_PROJET_JIN4526_GAME_H
#include "Event.h"
#include "Food.h"
#include "Materials.h"
#include "Peasents.h"
#include "Soldiers.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

class Game {
public:
    enum class Side { Left, Center, Right };

private:
    enum class ManpowerAction { None, Farm, Mine, Attack };

    struct SpriteGroup {
        std::string name;
        std::vector<int> textureIndexes;
        sf::Vector2f position;
    };

    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::Texture> spriteTextures;
    std::vector<SpriteGroup> spriteGroups;

    Food food;
    Materials materials;
    Soldiers soldiers;
    Peasents peasent;
    Event event;

    int day;
    int enemyHealth;
    std::string message;
    bool showSprites;
    //int activeSpriteGroup;
    ManpowerAction pendingAction;
    std::string manpowerInput;

    std::map<Side, int> activeSpriteGroups;

public:
    Game();
    void init();
    void run();
    void pause();
    void chooseEvent(const sf::Event& currentEvent);
    void showSpriteGroup(const std::string& groupName, Side side = Side::Center);

private:
    void updateDay();
    void draw();
    void drawText(const std::string& text, float x, float y, unsigned int size = 22);
    void drawManpowerPopup();
    void startManpowerChoice(ManpowerAction action);
    void confirmManpowerChoice();
    void cancelManpowerChoice();
    void handleManpowerInput(const sf::Event& currentEvent);
    int getPendingActionMaxPeople() const;
    std::string getPendingActionName() const;
    void loadSprites();
    void drawSprites();
    void farm();
    void farmWithPeople(int people);
    void mine();
    void mineWithPeople(int people);
    void recruitPeasant();
    void recruitSoldiers();
    void attack();
    void attackWithPeople(int people);
    void feedPeople();

};

#endif //MICRO_PROJET_JIN4526_GAME_H
