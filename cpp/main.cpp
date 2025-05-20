#include <iostream>
#include "database.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./main <command> <key> [value]\n";
        return 1;
    }

    std::string command = argv[1];
    std::string key = argv[2];
    std::string value = (argc > 3) ? argv[3] : "";

    Database db;

    if (command == "insert") {
        bool success = db.insert(key, value);
        std::cout << (success ? "OK" : "Key already exists") << std::endl;
    } else if (command == "get") {
        auto result = db.get(key);
        std::cout << ((result == "") ? result : "nista") << std::endl;
    } else if (command == "update") {
        bool success = db.update(key, value);
        std::cout << (success ? "Updated" : "Key not found") << std::endl;
    } else if (command == "delete") {
        bool success = db.remove(key);
        std::cout << (success ? "Deleted" : "Key not found") << std::endl;
    } else {
        std::cout << "Unknown command" << std::endl;
    }

    return 0;
}
