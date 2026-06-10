#include "Game.h"

#include <iostream>
#include <sstream>

#include "pugixml.hpp"

std::string Event::activate(int day) const {
    const int eventIndex = day % static_cast<int>(eventList.size());
    return eventList[eventIndex];
}

Game::Game(){

    window = sf::RenderWindow(sf::VideoMode({1000, 700}), "Resource Kingdom");
    day = 1;
    enemyHealth = 120;
    message = "Welcome! Choose an action with the keyboard.";
    showSprites = false;
    activeSpriteGroup = -1;

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

    food = Food(foodNode.attribute("quantity").as_int(), foodNode.attribute("sprite").as_string());
    materials = Materials(materialsNode.attribute("quantity").as_int(), materialsNode.attribute("sprite").as_string());
    soldiers = Soldiers(soldiersNode.attribute("quantity").as_int(),
        soldiersNode.attribute("sprite").as_string(),
        soldiersNode.attribute("available").as_int(),
        soldiersNode.attribute("health").as_int(),
        soldiersNode.attribute("moral").as_double(),
        soldiersNode.attribute("damage").as_double());
    peasent = Peasents(peasantsNode.attribute("quantity").as_int(),
        peasantsNode.attribute("sprite").as_string(),
        peasantsNode.attribute("available").as_int(),
        peasantsNode.attribute("health").as_int(),
        peasantsNode.attribute("moral").as_double(),
        peasantsNode.attribute("productivity").as_double());
    event = Event(eventsNode.attribute("eventList").as_string());

    init();
}

void Game::init() {
    window.setFramerateLimit(60);

    if (!font.openFromFile("resources/Font/arial.ttf")) {
        message = "Font not found, but the game is running.";
    }

    loadSprites();
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
        recruitSoldiers();
    } else if (keyPressed->code == sf::Keyboard::Key::A) {
        attack();
    } else if (keyPressed->code == sf::Keyboard::Key::N) {
        updateDay();
    } else if (keyPressed->code == sf::Keyboard::Key::Space) {
        feedPeople();
    } else if (keyPressed->code == sf::Keyboard::Key::L) {
        showSprites = !showSprites;
        if (showSprites) {
            if (activeSpriteGroup == -1) {
                showSpriteGroup("heroes", Side::Left);
            }
            message = "Sprites are now visible.";
        } else {
            message = "Sprites are now hidden.";
        }
    }
}

void Game::updateDay() {
    day++;
    peasent.action();
    soldiers.action();
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
    drawText("Soldiers: " + std::to_string(soldiers.getQuantity()) + " available: " + std::to_string(soldiers.getAvailable()), 70, 275);
    drawText("Enemy castle health: " + std::to_string(enemyHealth), 70, 315);

    drawText("F: farm food", 620, 155);
    drawText("M: mine materials", 620, 195);
    drawText("P: recruit peasant (20 food)", 620, 235);
    drawText("S: recruit soldiers (15 food, 15 materials)", 620, 275);
    drawText("A: attack castle", 620, 315);
    drawText("Space: feed people", 620, 355);
    drawText("N: next day", 620, 395);
    drawText("L: show/hide sprites", 620, 435);

    if (showSprites) {
        drawSprites();
    }

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

void Game::loadSprites() {
    const std::vector<std::string> spriteFiles = {
        "resources/Sprites/CyranoDeBergerac.png",
        "resources/Sprites/SoldatEspagnol.png",
        "resources/Sprites/SoldatFrancais.png"
    };

    spriteTextures.clear();

    for (const std::string& fileName : spriteFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(fileName)) {
            std::cerr << "Could not load sprite: " << fileName << std::endl;
        }

        spriteTextures.push_back(texture);
    }

    const sf::Vector2f spawnPosition = {360.f, 375.f};

    spriteGroups.clear();
    spriteGroups.push_back({"heroes", {0}, spawnPosition});
    spriteGroups.push_back({"enemySoldiers", {1}, spawnPosition});
    spriteGroups.push_back({"frenchSoldiers", {2}, spawnPosition});
    spriteGroups.push_back({"battle", {1, 2}, spawnPosition});
}

void Game::drawSprites() {
    if (activeSpriteGroup < 0 || activeSpriteGroup >= static_cast<int>(spriteGroups.size())) {
        return;
    }

    const SpriteGroup& group = spriteGroups[activeSpriteGroup];
    const float spacing = 130.f;

    for (std::size_t i = 0; i < group.textureIndexes.size(); i++) {
        const int textureIndex = group.textureIndexes[i];
        if (textureIndex < 0 || textureIndex >= static_cast<int>(spriteTextures.size())) {
            continue;
        }

        sf::Sprite sprite(spriteTextures[textureIndex]);
        sprite.setPosition({group.position.x + spacing * static_cast<float>(i), group.position.y});

        const sf::Vector2u textureSize = spriteTextures[textureIndex].getSize();
        if (textureSize.x > 0 && textureSize.y > 0) {
            const float wantedHeight = 140.f;
            const float scale = wantedHeight / static_cast<float>(textureSize.y);
            sprite.setScale({scale, scale});
        }

        window.draw(sprite);
    }
}

void Game::showSpriteGroup(const std::string& groupName, Side side) {
    float x = 360.f; // Default Center
    if (side == Side::Left) {
        x = 100.f;
    } else if (side == Side::Right) {
        x = 700.f;
    }

    for (std::size_t i = 0; i < spriteGroups.size(); i++) {
        if (spriteGroups[i].name == groupName) {
            spriteGroups[i].position.x = x;
            activeSpriteGroup = static_cast<int>(i);
            showSprites = true;
            return;
        }
    }

    std::cerr << "Unknown sprite group: " << groupName << std::endl;
}

void Game::farm() {
    showSpriteGroup("heroes", Side::Left);
    // const int gainedFood = peasent.recolte();
    // food.addQuantity(gainedFood);
    // peasent.usePeople(peasent.getAvailable());
    // message = "Peasants produced " + std::to_string(gainedFood) + " food.";
}

void Game::mine() {
    showSpriteGroup("heroes", Side::Left);
    const int gainedMaterials = peasent.getAvailable();
    materials.addQuantity(gainedMaterials);
    peasent.usePeople(peasent.getAvailable());
    message = "Peasants produced " + std::to_string(gainedMaterials) + " materials.";
}

void Game::recruitPeasant() {
    showSpriteGroup("heroes", Side::Left);
    if (food.spend(20)) {
        peasent.addPeople(1);
        message = "A new peasant joined your village.";
    } else {
        message = "Not enough food to recruit a peasant.";
    }
}

void Game::recruitSoldiers() {
    showSpriteGroup("frenchSoldiers", Side::Left);
    if (food.getQuantity() < 15 || materials.getQuantity() < 15) {
        message = "Need 15 food and 15 materials to recruit a soldiers.";
        return;
    }

    food.spend(15);
    materials.spend(15);
    soldiers.addPeople(1);
    message = "A new soldier is ready.";
}

void Game::attack() {
    showSpriteGroup("battle", Side::Center);
    // const int damage = static_cast<int>(soldiers.battle());
    // enemyHealth -= damage;
    // if (enemyHealth < 0) {
    //     enemyHealth = 0;
    // }
    //
    // soldiers.usePeople(soldiers.getAvailable());
    // message = "Your soldiers dealt " + std::to_string(damage) + " damage.";
}

void Game::feedPeople() {
    const int neededFood = peasent.getQuantity() + soldiers.getQuantity();
    if (food.spend(neededFood)) {
        message = "Everyone ate. You spent " + std::to_string(neededFood) + " food.";
    } else {
        message = "Not enough food. Morale system will be added next.";
    }
}
