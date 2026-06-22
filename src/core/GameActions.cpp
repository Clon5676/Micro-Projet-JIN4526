#include "Game.h"
#include <random>
#include <sstream>
#include "pugixml.hpp"
#include "EventStrategy.h"

void Game::updateDay() {
    day++;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, this->event->countEvents() - 1);

    std::shared_ptr<GameEvent> event = this->event->getEventAt(distrib(gen));

    event->getEventStrategie()->activateEvent(this, event->getValue());

    message = event->getEffect();

    peasent.rest();
    soldiers.rest();
}

void Game::showConversation(const std::string& leftActor, const std::string& rightActor,
                            const std::string& leftSpeaker, const std::string& rightSpeaker,
                            const std::string& leftText, const std::string& rightText) {
    dialogueScene.clearActors();
    dialogueScene.showActor(leftActor, DialogueScene::Side::Left);
    dialogueScene.showActor(rightActor, DialogueScene::Side::Right);
    dialogueScene.setSpeakers(leftSpeaker, rightSpeaker);
    dialogueScene.setDialogue(leftText, rightText);
}

void Game::farm() {
    showConversation("heroes", "peasants", "Cyrano", "Peasant",
        "Friend, how many peasants can we send to the fields?", "");
    startManpowerChoice(ManpowerAction::Farm);
}

void Game::farmWithPeople(int people) {
    const int gainedFood = peasent.farm(people);
    food.addQuantity(gainedFood);
    message = "Peasants produced " + std::to_string(gainedFood) + " food.";
    showConversation("heroes", "peasants", "Cyrano", "Peasant",
        "Excellent work in the fields.", "We gathered " + std::to_string(gainedFood) + " food.");
}

void Game::mine() {
    showConversation("heroes", "peasants", "Cyrano", "Peasant",
        "How many peasants shall go to the quarry?", "");
    startManpowerChoice(ManpowerAction::Mine);
}

void Game::mineWithPeople(int people) {
    const int gainedMaterials = peasent.mine(people);
    materials.addQuantity(gainedMaterials);
    message = "Peasants produced " + std::to_string(gainedMaterials) + " materials.";
    showConversation("heroes", "peasants", "Cyrano", "Peasant",
        "The quarry answers us.", "We brought back " + std::to_string(gainedMaterials) + " materials.");
}

void Game::recruitPeasant() {
    if (peasent.recruit(food)) {
        message = "A new peasant joined your village.";
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Welcome. Your hands will help the village.", "I am ready to work.");
    } else {
        message = "Not enough food to recruit a peasant.";
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Can another peasant join us?", "Not yet. We need more food.");
    }
}

void Game::recruitSoldiers() {
    if (soldiers.getMaxRecruitable(food, materials) <= 0) {
        message = "Need 15 food and 15 materials to recruit soldiers.";
        showConversation("frenchSoldiers", "heroes", "Soldier", "Cyrano",
            "Can we raise new soldiers?", "No. We lack food or materials.");
        return;
    }

    showConversation("frenchSoldiers", "heroes", "Soldier", "Cyrano",
        "Captain, how many soldiers can we train?", "");
    startManpowerChoice(ManpowerAction::RecruitSoldiers);
}

void Game::recruitSoldiersWithPeople(int people) {
    if (soldiers.recruit(food, materials, people)) {
        message = std::to_string(people) + " new soldiers are ready.";
        showConversation("frenchSoldiers", "heroes", "Soldier", "Cyrano",
            "Stand ready, soldiers.", std::to_string(people) + " of us join the ranks.");
    } else {
        message = "Not enough resources to recruit soldiers.";
        showConversation("frenchSoldiers", "heroes", "Soldier", "Cyrano",
            "Can we train that many?", "No. We need more food or materials.");
    }
}

void Game::attack() {
    showConversation("frenchSoldiers", "enemySoldiers", "Soldier", "Enemy",
        "How many soldiers shall charge?", "");
    startManpowerChoice(ManpowerAction::Attack);
}

void Game::attackWithPeople(int people) {
    const int damage = soldiers.attack(people);
    enemyHealth -= damage;
    if (enemyHealth < 0) {
        enemyHealth = 0;
    }

    message = "Your soldiers dealt " + std::to_string(damage) + " damage.";
    showConversation("frenchSoldiers", "enemySoldiers", "Soldier", "Enemy",
        "Strike with courage!", "We received " + std::to_string(damage) + " damage.");
}

void Game::feedPeople() {
    const int neededFood = peasent.getQuantity() + soldiers.getQuantity();
    if (food.spend(neededFood)) {
        peasent.feeded();
        soldiers.feeded();
        message = "Everyone ate. You spent " + std::to_string(neededFood) + " food.";
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Tonight, everyone eats.", "Morale will rise after rest.");
    } else {
        message = "Not enough food. Need more to feed everyone";
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Can we feed everyone?", "No. The stores are too low.");
    }
}
