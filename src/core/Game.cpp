#include "Game.h"

#include <sstream>

Event::Event()
    : eventList({"A calm day begins.", "Travelers bring news from nearby farms.", "The enemy castle is quiet today."}) {
}

std::string Event::activate(int day) const {
    const int eventIndex = day % static_cast<int>(eventList.size());
    return eventList[eventIndex];
}

Game::Game()
    : window(sf::VideoMode({1000, 700}), "Resource Kingdom"),
      food(100, "FoodSprite.png"),
      materials(80, "MaterialsSprite.png"),
      soldier(2.0, 8, 100, 1.0, 8, "SoldierSprite.png"),
      peasent(1.5, 15, 100, 1.0, 15, "PeasentSprite.png"),
      day(1),
      enemyHealth(120),
      message("Welcome! Choose an action with the keyboard.") {
    init();
}

void Game::init() {
    window.setFramerateLimit(60);

    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        message = "Font not found, but the game is running.";
    }
}

void Game::run() {
    while (window.isOpen()) {
        while (const std::optional<sf::Event> currentEvent = window.pollEvent()) {
            if (currentEvent->is<sf::Event::Closed>()) {
                window.close();
            } else {
                chooseEvent(*currentEvent);
            }
        }

        draw();
    }
}

void Game::pause() {
    message = "Pause is planned. For now, press Escape to quit.";
}

void Game::chooseEvent(const sf::Event& currentEvent) {
    const auto* keyPressed = currentEvent.getIf<sf::Event::KeyPressed>();
    if (keyPressed == nullptr) {
        return;
    }

    if (keyPressed->code == sf::Keyboard::Key::Escape) {
        window.close();
    } else if (keyPressed->code == sf::Keyboard::Key::F) {
        farm();
    } else if (keyPressed->code == sf::Keyboard::Key::M) {
        mine();
    } else if (keyPressed->code == sf::Keyboard::Key::P) {
        recruitPeasant();
    } else if (keyPressed->code == sf::Keyboard::Key::S) {
        recruitSoldier();
    } else if (keyPressed->code == sf::Keyboard::Key::A) {
        attack();
    } else if (keyPressed->code == sf::Keyboard::Key::N) {
        updateDay();
    } else if (keyPressed->code == sf::Keyboard::Key::Space) {
        feedPeople();
    }
}

void Game::updateDay() {
    day++;
    peasent.action();
    soldier.action();
    feedPeople();

    if (day % 3 == 0) {
        materials.addQuantity(10);
        message = event.activate(day) + " You found 10 materials.";
    } else {
        message = event.activate(day);
    }
}

void Game::draw() {
    window.clear(sf::Color(30, 35, 42));

    drawText("Resource Kingdom", 40, 30, 36);
    drawText("Day " + std::to_string(day), 40, 85, 24);

    drawText("Food: " + std::to_string(food.getQuantity()), 70, 155);
    drawText("Materials: " + std::to_string(materials.getQuantity()), 70, 195);
    drawText("Peasants: " + std::to_string(peasent.getQuantity()) + " available: " + std::to_string(peasent.getAvailable()), 70, 235);
    drawText("Soldiers: " + std::to_string(soldier.getQuantity()) + " available: " + std::to_string(soldier.getAvailable()), 70, 275);
    drawText("Enemy castle health: " + std::to_string(enemyHealth), 70, 315);

    drawText("F: farm food", 620, 155);
    drawText("M: mine materials", 620, 195);
    drawText("P: recruit peasant (20 food)", 620, 235);
    drawText("S: recruit soldier (15 food, 15 materials)", 620, 275);
    drawText("A: attack castle", 620, 315);
    drawText("Space: feed people", 620, 355);
    drawText("N: next day", 620, 395);

    drawText(message, 70, 560, 20);

    if (enemyHealth <= 0) {
        drawText("Victory! The enemy castle has fallen.", 270, 480, 30);
    }

    window.display();
}

void Game::drawText(const std::string& text, float x, float y, unsigned int size) {
    if (font.getInfo().family.empty()) {
        return;
    }

    sf::Text drawableText(font, text, size);
    drawableText.setPosition({x, y});
    drawableText.setFillColor(sf::Color(235, 238, 242));
    window.draw(drawableText);
}

void Game::farm() {
    const int gainedFood = peasent.recolte();
    food.addQuantity(gainedFood);
    peasent.usePeople(peasent.getAvailable());
    message = "Peasants produced " + std::to_string(gainedFood) + " food.";
}

void Game::mine() {
    const int gainedMaterials = peasent.getAvailable();
    materials.addQuantity(gainedMaterials);
    peasent.usePeople(peasent.getAvailable());
    message = "Peasants produced " + std::to_string(gainedMaterials) + " materials.";
}

void Game::recruitPeasant() {
    if (food.spend(20)) {
        peasent.addPeople(1);
        message = "A new peasant joined your village.";
    } else {
        message = "Not enough food to recruit a peasant.";
    }
}

void Game::recruitSoldier() {
    if (food.getQuantity() < 15 || materials.getQuantity() < 15) {
        message = "Need 15 food and 15 materials to recruit a soldier.";
        return;
    }

    food.spend(15);
    materials.spend(15);
    soldier.addPeople(1);
    message = "A new soldier is ready.";
}

void Game::attack() {
    const int damage = static_cast<int>(soldier.battle());
    enemyHealth -= damage;
    if (enemyHealth < 0) {
        enemyHealth = 0;
    }

    soldier.usePeople(soldier.getAvailable());
    message = "Your soldiers dealt " + std::to_string(damage) + " damage.";
}

void Game::feedPeople() {
    const int neededFood = peasent.getQuantity() + soldier.getQuantity();
    if (food.spend(neededFood)) {
        message = "Everyone ate. You spent " + std::to_string(neededFood) + " food.";
    } else {
        message = "Not enough food. Morale system will be added next.";
    }
}
