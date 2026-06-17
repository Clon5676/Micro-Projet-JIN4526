#include "Game.h"

void Game::updateDay() {
    dialogueScene.clearActors();
    day++;
    peasent.rest();
    soldiers.rest();

    if (day % 3 == 0) {
        materials.addQuantity(10);
        message = event.activate(day) + " You found 10 materials."; // here example of how to put message with something else
    } else {
		message = event.activate(day); // here it calls the events that are set to happen on this day, if any
    }
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
    showConversation("heroes", "peasants", "Cyrano", "Peasant",
        "The quarry answers us.", "We brought back " + std::to_string(gainedMaterials) + " materials.");
}

void Game::recruitPeasant() {
    if (peasent.recruit(food)) {
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Welcome. Your hands will help the village.", "I am ready to work.");
    } else {
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Can another peasant join us?", "Not yet. We need more food.");
    }
}

void Game::recruitSoldiers() {
    if (soldiers.getMaxRecruitable(food, materials) <= 0) {
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
        showConversation("frenchSoldiers", "heroes", "Soldier", "Cyrano",
            "Stand ready, soldiers.", std::to_string(people) + " of us join the ranks.");
    } else {
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

    showConversation("frenchSoldiers", "enemySoldiers", "Soldier", "Enemy",
        "Strike with courage!", "We received " + std::to_string(damage) + " damage.");
}

void Game::feedPeople() {
    const int neededFood = peasent.getQuantity() + soldiers.getQuantity();
    if (food.spend(neededFood)) {
        peasent.feeded();
        soldiers.feeded();
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Tonight, everyone eats.", "Morale will rise after rest.");
    } else {
        showConversation("heroes", "peasants", "Cyrano", "Peasant",
            "Can we feed everyone?", "No. The stores are too low.");
    }
}
