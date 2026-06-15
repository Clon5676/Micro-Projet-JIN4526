#ifndef MICRO_PROJET_JIN4526_DIALOGUESCENE_H
#define MICRO_PROJET_JIN4526_DIALOGUESCENE_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

class DialogueScene {
public:
    enum class Side { Left, Right };

    void loadSprites();
    void clearActors();
    void showActor(const std::string& groupName, Side side);
    void setSpeakers(const std::string& leftName, const std::string& rightName);
    void setDialogue(const std::string& leftText, const std::string& rightText);

    void draw(sf::RenderWindow& window, const sf::Font& font);
    void drawPrompt(sf::RenderWindow& window, const sf::Font& font, const std::string& text);
    void drawPromptControls(sf::RenderWindow& window, const sf::Font& font);

private:
    struct SpriteGroup {
        std::string name;
        std::vector<int> textureIndexes;
    };

    std::vector<sf::Texture> spriteTextures;
    std::vector<SpriteGroup> spriteGroups;
    std::map<Side, int> activeSpriteGroups;

    std::string leftSpeaker;
    std::string rightSpeaker;
    std::string leftSpeech;
    std::string rightSpeech;

    int findGroupIndex(const std::string& groupName) const;
    float getActorX(Side side, const sf::Vector2u& windowSize) const;
    std::vector<std::string> wrapText(const std::string& text, std::size_t maxLineLength) const;
    void drawActors(sf::RenderWindow& window);
    void drawMessages(sf::RenderWindow& window, const sf::Font& font);
    void drawMessageBubble(sf::RenderWindow& window, const sf::Font& font, const std::string& speaker,
                           const std::string& text, Side side, float y);
};

#endif //MICRO_PROJET_JIN4526_DIALOGUESCENE_H
