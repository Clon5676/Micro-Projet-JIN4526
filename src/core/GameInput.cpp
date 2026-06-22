#include "Game.h"

void Game::chooseEvent(const sf::Event& currentEvent) {
    const auto* keyPressed = currentEvent.getIf<sf::Event::KeyPressed>();
    if (gameOver) {
        if (keyPressed != nullptr && keyPressed->code == sf::Keyboard::Key::Escape) {
            window.close();
        }
        return;
    }

    if (pendingAction != ManpowerAction::None) {
        handleManpowerInput(currentEvent);
        return;
    }

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
    }
}

void Game::drawManpowerPopup() {
    const int maxPeople = getPendingActionMaxPeople();
    const std::string prompt = getPendingActionName() + ": how many? Available "
        + std::to_string(maxPeople) + ". Number: " + manpowerInput;

    dialogueScene.drawPrompt(window, font, prompt);
    dialogueScene.drawPromptControls(window, font);
}

void Game::startManpowerChoice(ManpowerAction action) {
    pendingAction = action;
    manpowerInput = "";
    //message = "Type a number and press Enter.";
}

void Game::confirmManpowerChoice() {
    if (manpowerInput.empty()) {
        //message = "Please type a number first.";
        return;
    }

    const int people = std::stoi(manpowerInput);
    const int maxPeople = getPendingActionMaxPeople();

    if (people <= 0) {
        //message = "You must send at least 1 person.";
        return;
    }

    if (people > maxPeople) {
        //message = "You only have " + std::to_string(maxPeople) + " available.";
        return;
    }

    const ManpowerAction actionToRun = pendingAction;
    pendingAction = ManpowerAction::None;
    manpowerInput = "";

    if (actionToRun == ManpowerAction::Farm) {
        farmWithPeople(people);
    } else if (actionToRun == ManpowerAction::Mine) {
        mineWithPeople(people);
    } else if (actionToRun == ManpowerAction::Attack) {
        attackWithPeople(people);
    } else if (actionToRun == ManpowerAction::RecruitSoldiers) {
        recruitSoldiersWithPeople(people);
    }
}

void Game::cancelManpowerChoice() {
    pendingAction = ManpowerAction::None;
    manpowerInput = "";
    //message = "Action cancelled.";
}

void Game::handleManpowerInput(const sf::Event& currentEvent) {
    const auto* keyPressed = currentEvent.getIf<sf::Event::KeyPressed>();
    if (keyPressed != nullptr) {
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            confirmManpowerChoice();
        } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
            cancelManpowerChoice();
        } else if (keyPressed->code == sf::Keyboard::Key::Backspace && !manpowerInput.empty()) {
            manpowerInput.pop_back();
        }
        return;
    }

    const auto* textEntered = currentEvent.getIf<sf::Event::TextEntered>();
    if (textEntered == nullptr) {
        return;
    }

    if (textEntered->unicode >= '0' && textEntered->unicode <= '9' && manpowerInput.size() < 3) {
        manpowerInput += static_cast<char>(textEntered->unicode);
    }
}

int Game::getPendingActionMaxPeople() const {
    if (pendingAction == ManpowerAction::Attack) {
        return soldiers.getAvailable();
    }

    if (pendingAction == ManpowerAction::RecruitSoldiers) {
        return soldiers.getMaxRecruitable(food, materials);
    }

    if (pendingAction == ManpowerAction::Farm || pendingAction == ManpowerAction::Mine) {
        return peasent.getAvailable();
    }

    return 0;
}

std::string Game::getPendingActionName() const {
    if (pendingAction == ManpowerAction::Farm) {
        return "Farm";
    }

    if (pendingAction == ManpowerAction::Mine) {
        return "Mine";
    }

    if (pendingAction == ManpowerAction::Attack) {
        return "Attack";
    }

    if (pendingAction == ManpowerAction::RecruitSoldiers) {
        return "Recruit soldiers";
    }

    return "";
}
