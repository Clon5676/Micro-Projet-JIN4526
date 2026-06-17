#ifndef MICRO_PROJET_JIN4526_GAME_H
#define MICRO_PROJET_JIN4526_GAME_H
#include "DialogueScene.h"
#include "Event.h"
#include "Food.h"
#include "Materials.h"
#include "Peasents.h"
#include "ResourcePackage.h"
#include "Soldiers.h"

#include <SFML/Graphics.hpp>
#include <string>

class Game {
private:
    enum class ManpowerAction { None, Farm, Mine, Attack, RecruitSoldiers };

    sf::RenderWindow window;
    sf::Font font;
    DialogueScene dialogueScene;

    Food food;
    Materials materials;
    ResourcePackage stockpile;
    Soldiers soldiers;
    Peasents peasent;
    Event event;

    int day;
    int enemyHealth;
    std::string message;
    ManpowerAction pendingAction;
    std::string manpowerInput;

public:
    Game();
    void init();
    void run();
    void pause();
    void chooseEvent(const sf::Event& currentEvent);

private:
    void updateDay();
    void draw();
    void drawText(const std::string& text, float x, float y, unsigned int 
        = 22);
    void drawManpowerPopup();
    void startManpowerChoice(ManpowerAction action);
    void confirmManpowerChoice();
    void cancelManpowerChoice();
    void handleManpowerInput(const sf::Event& currentEvent);
    int getPendingActionMaxPeople() const;
    std::string getPendingActionName() const;
    void showConversation(const std::string& leftActor, const std::string& rightActor,
                          const std::string& leftSpeaker, const std::string& rightSpeaker,
                          const std::string& leftText, const std::string& rightText);
    void farm();
    void farmWithPeople(int people);
    void mine();
    void mineWithPeople(int people);
    void recruitPeasant();
    void recruitSoldiers();
    void recruitSoldiersWithPeople(int people);
    void attack();
    void attackWithPeople(int people);
    void feedPeople();

};

#endif //MICRO_PROJET_JIN4526_GAME_H
