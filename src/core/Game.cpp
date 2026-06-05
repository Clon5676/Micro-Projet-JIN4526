#include "Game.h"

Game::Game(pugi::xml_node node) {
    food = Food(node.child("Food"));
    materials = Materials(node.child("Materials"));
    soldiers = Soldiers(node.child("Soldiers"));
    peasent = Peasent(node.child("Peasent"));
    event = Event(node.child("Event"));
}