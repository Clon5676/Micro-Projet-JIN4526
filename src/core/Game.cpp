#include "Game.h"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {
std::string formatMorale(double morale) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << morale;
    return stream.str();
}
}

Game::Game(){

    window = sf::RenderWindow(sf::VideoMode({1300, 1000}), "Resource Kingdom");
    day = 1;
    enemyHealth = 1000;
    pendingAction = ManpowerAction::None;
    gameOver = false;

    pugi::xml_document doc;
    if (auto result = doc.load_file("resources/init.xml"); !result) {
        std::cerr << "Could not open file init.xml because " << result.description() << std::endl;
    }

    pugi::xml_node game = doc.child("Game");
    pugi::xml_node foodNode = game.child("Food");
    pugi::xml_node materialsNode = game.child("Materials");
    pugi::xml_node peasantsNode = game.child("Peasents");
    pugi::xml_node soldiersNode = game.child("Soldiers");
    pugi::xml_node eventsNode = game.child("Events");

    food = Food(foodNode.attribute("quantity").as_int());
    materials = Materials(materialsNode.attribute("quantity").as_int());
    stockpile = ResourcePackage("Stockpile");
    stockpile.add(food);
    stockpile.add(materials);
    soldiers = Soldiers(soldiersNode.attribute("quantity").as_int(),
        soldiersNode.attribute("sprite").as_string(),
        soldiersNode.attribute("available").as_int(),
        soldiersNode.attribute("health").as_int(),
        soldiersNode.attribute("moral").as_double(),
        soldiersNode.attribute("strength").as_double());
    peasent = Peasents(peasantsNode.attribute("quantity").as_int(),
        peasantsNode.attribute("sprite").as_string(),
        peasantsNode.attribute("available").as_int(),
        peasantsNode.attribute("health").as_int(),
        peasantsNode.attribute("moral").as_double(),
        peasantsNode.attribute("productivity").as_double());
    event = std::make_shared<GameEvent>(eventsNode);

    init();
}

void Game::init() {
    window.setFramerateLimit(60);
    if (!font.openFromFile("resources/Font/arial.ttf")) {
        message = "Font not found, but the game is running.";
    }

    dialogueScene.loadSprites();
    dialogueScene.setSpeakers("Cyrano", "");
    dialogueScene.setDialogue("What shall we do today?", "");
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

void Game::draw() {
    checkLossCondition();

    window.clear(sf::Color(30, 35, 42));

    drawText("Resource Kingdom", 40, 30, 36);
    drawText("Day " + std::to_string(day), 40, 85, 24);

    drawText("Food: " + std::to_string(food.getQuantity()), 70, 155);
    drawText("Materials: " + std::to_string(materials.getQuantity()), 70, 195);
    drawText("Stockpile total: " + std::to_string(stockpile.getQuantity()), 70, 235);
    drawText("Peasants: " + std::to_string(peasent.getQuantity()) + " available: " + std::to_string(peasent.getAvailable()), 70, 275);
    drawText("Soldiers: " + std::to_string(soldiers.getQuantity()) + " available: " + std::to_string(soldiers.getAvailable()), 70, 315);
    drawText("Peasant morale: " + formatMorale(peasent.getMoral()), 70, 355);
    drawText("Soldier morale: " + formatMorale(soldiers.getMoral()), 70, 395);
    drawText("Enemy castle health: " + std::to_string(enemyHealth), 70, 435);

    drawText("F: farm food", 620, 155);
    drawText("M: mine materials", 620, 195);
    drawText("P: recruit peasant (20 food)", 620, 235);
    drawText("S: recruit soldiers (15 food, 15 materials)", 620, 275);
    drawText("A: attack castle", 620, 315);
    drawText("Space: feed people", 620, 355);
    drawText("N: next day", 620, 395);

    dialogueScene.draw(window, font);
    drawText(message, 70, 635, 20);

    if (pendingAction != ManpowerAction::None) {
        drawManpowerPopup();
    }

    if (gameOver) {
        drawGameOverPopup();
    }

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

void Game::checkLossCondition() {
    if (gameOver) {
        return;
    }

    if (peasent.getQuantity() <= 0 || soldiers.getQuantity() <= 0) {
        gameOver = true;
        pendingAction = ManpowerAction::None;
        manpowerInput = "";
        message = "The siege has failed.";
    }
}

void Game::drawGameOverPopup() {
    sf::RectangleShape overlay({1300.f, 1000.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 145));
    window.draw(overlay);

    sf::RectangleShape popup({900.f, 280.f});
    popup.setPosition({200.f, 350.f});
    popup.setFillColor(sf::Color(53, 38, 44));
    popup.setOutlineColor(sf::Color(210, 78, 78));
    popup.setOutlineThickness(4.f);
    window.draw(popup);

    drawText("It seems you ran out of people to keep the siege,", 245, 390, 25);
    drawText("The spanish army is victorious!", 245, 445, 30);
    drawText("And more importantly, you will never see Roxane again!", 245, 505, 25);
    drawText("Press Escape to exit", 245, 565, 20);
}
