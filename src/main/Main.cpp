int main() {
    pugi::xml_document doc;
    if (auto result = doc.load_file("resources/init.xml"); !result) {
        std::cerr << "Could not open file init.xml because " << result.description() << std::endl;
        return 1;
    }

    Game::Game(doc.child("Game"));
}
