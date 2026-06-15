#include "DialogueScene.h"

#include <iostream>

void DialogueScene::loadSprites() {
    const std::vector<std::string> spriteFiles = {
        "resources/Sprites/CyranoDeBergerac.png",
        "resources/Sprites/SoldatEspagnol.png",
        "resources/Sprites/SoldatFrancais.png",
        "resources/Sprites/Peasant.png"
    };

    spriteTextures.clear();

    for (const std::string& fileName : spriteFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(fileName)) {
            std::cerr << "Could not load sprite: " << fileName << std::endl;
        }
        spriteTextures.push_back(texture);
    }

    spriteGroups.clear();
    spriteGroups.push_back({"heroes", {0}});
    spriteGroups.push_back({"enemySoldiers", {1}});
    spriteGroups.push_back({"frenchSoldiers", {2}});
    spriteGroups.push_back({"battle", {1, 2}});
    spriteGroups.push_back({"peasants", {3}});
}

void DialogueScene::clearActors() {
    activeSpriteGroups.clear();
}

void DialogueScene::showActor(const std::string& groupName, Side side) {
    const int groupIndex = findGroupIndex(groupName);
    if (groupIndex >= 0) {
        activeSpriteGroups[side] = groupIndex;
    }
}

void DialogueScene::setSpeakers(const std::string& leftName, const std::string& rightName) {
    leftSpeaker = leftName;
    rightSpeaker = rightName;
}

void DialogueScene::setDialogue(const std::string& leftText, const std::string& rightText) {
    leftSpeech = leftText;
    rightSpeech = rightText;
}

void DialogueScene::draw(sf::RenderWindow& window, const sf::Font& font) {
    drawActors(window);
    drawMessages(window, font);
}

void DialogueScene::drawPrompt(sf::RenderWindow& window, const sf::Font& font, const std::string& text) {
    drawMessageBubble(window, font, leftSpeaker, text, Side::Left, 840.f);
}

void DialogueScene::drawPromptControls(sf::RenderWindow& window, const sf::Font& font) {
    const sf::Vector2u windowSize = window.getSize();
    const float chatX = static_cast<float>(windowSize.x) * 0.30f;

    sf::Text controls(font, "Enter: confirm    Backspace: erase    Escape: cancel", 18);
    controls.setPosition({chatX, static_cast<float>(windowSize.y) - 38.f});
    controls.setFillColor(sf::Color(235, 238, 242));
    window.draw(controls);
}

int DialogueScene::findGroupIndex(const std::string& groupName) const {
    for (std::size_t i = 0; i < spriteGroups.size(); i++) {
        if (spriteGroups[i].name == groupName) {
            return static_cast<int>(i);
        }
    }

    std::cerr << "Unknown sprite group: " << groupName << std::endl;
    return -1;
}

float DialogueScene::getActorX(Side side, const sf::Vector2u& windowSize) const {
    if (side == Side::Left) {
        return 65.f;
    }

    return static_cast<float>(windowSize.x) - 285.f;
}

std::vector<std::string> DialogueScene::wrapText(const std::string& text, std::size_t maxLineLength) const {
    std::vector<std::string> lines;
    std::string currentLine;
    std::string currentWord;

    for (char character : text) {
        if (character == ' ') {
            if (currentLine.size() + currentWord.size() + 1 > maxLineLength && !currentLine.empty()) {
                lines.push_back(currentLine);
                currentLine = currentWord;
            } else {
                if (!currentLine.empty()) {
                    currentLine += " ";
                }
                currentLine += currentWord;
            }
            currentWord.clear();
        } else {
            currentWord += character;
        }
    }

    if (!currentWord.empty()) {
        if (currentLine.size() + currentWord.size() + 1 > maxLineLength && !currentLine.empty()) {
            lines.push_back(currentLine);
            currentLine = currentWord;
        } else {
            if (!currentLine.empty()) {
                currentLine += " ";
            }
            currentLine += currentWord;
        }
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}

void DialogueScene::drawActors(sf::RenderWindow& window) {
    const sf::Vector2u windowSize = window.getSize();

    for (const auto& actor : activeSpriteGroups) {
        const int groupIndex = actor.second;
        if (groupIndex < 0 || groupIndex >= static_cast<int>(spriteGroups.size())) {
            continue;
        }

        const SpriteGroup& group = spriteGroups[groupIndex];
        const float spacing = 120.f;

        for (std::size_t i = 0; i < group.textureIndexes.size(); i++) {
            const int textureIndex = group.textureIndexes[i];
            if (textureIndex < 0 || textureIndex >= static_cast<int>(spriteTextures.size())) {
                continue;
            }

            sf::Sprite sprite(spriteTextures[textureIndex]);
            sprite.setPosition({getActorX(actor.first, windowSize) + spacing * static_cast<float>(i), 650.f});

            const sf::Vector2u textureSize = spriteTextures[textureIndex].getSize();
            if (textureSize.x > 0 && textureSize.y > 0) {
                const float wantedHeight = 300.f;
                const float scale = wantedHeight / static_cast<float>(textureSize.y);
                sprite.setScale({scale, scale});
            }

            window.draw(sprite);
        }
    }
}

void DialogueScene::drawMessages(sf::RenderWindow& window, const sf::Font& font) {
    drawMessageBubble(window, font, leftSpeaker, leftSpeech, Side::Left, 665.f);
    drawMessageBubble(window, font, rightSpeaker, rightSpeech, Side::Right, 760.f);
}

void DialogueScene::drawMessageBubble(sf::RenderWindow& window, const sf::Font& font, const std::string& speaker,
                                      const std::string& text, Side side, float y) {
    if (text.empty()) {
        return;
    }

    const sf::Vector2u windowSize = window.getSize();
    const float chatX = static_cast<float>(windowSize.x) * 0.30f;
    const float chatWidth = static_cast<float>(windowSize.x) * 0.40f;
    const float bubbleWidth = chatWidth * 0.78f;
    const float bubbleX = side == Side::Left ? chatX : chatX + chatWidth - bubbleWidth;
    const std::vector<std::string> lines = wrapText(text, 38);
    const float bubbleHeight = 48.f + 24.f * static_cast<float>(lines.size());

    sf::RectangleShape bubble({bubbleWidth, bubbleHeight});
    bubble.setPosition({bubbleX, y});
    bubble.setFillColor(side == Side::Left ? sf::Color(232, 232, 237) : sf::Color(232, 232, 237));
    bubble.setOutlineThickness(0.f);
    window.draw(bubble);

    sf::Text speakerText(font, speaker, 16);
    speakerText.setPosition({bubbleX + 18.f, y + 10.f});
    speakerText.setFillColor(side == Side::Left ? sf::Color(20, 20, 25) : sf::Color::Black);
    window.draw(speakerText);

    for (std::size_t i = 0; i < lines.size(); i++) {
        sf::Text lineText(font, lines[i], 18);
        lineText.setPosition({bubbleX + 18.f, y + 36.f + 24.f * static_cast<float>(i)});
        lineText.setFillColor(side == Side::Left ? sf::Color(20, 20, 25) : sf::Color::Black);
        window.draw(lineText);
    }
}
