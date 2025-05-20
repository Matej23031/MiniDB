// database.cpp
#include "database.hpp"
#include <iostream>

bool Database::insert(const std::string& key, const std::string& value) {
    if (!isValid(key) || !isValid(value)) {
        std::cerr << "[ERROR] insert(): invalid key or value\n";
        return false;
    }
    std::unique_lock lock(mutex_);
    auto [it, ok] = data_.emplace(key, value);
    if (!ok) {
        std::cerr << "[WARN ] insert(): key '" << key << "' already exists\n";
    }
    return ok;
}

std::optional<std::string> Database::get(const std::string& key) const {
    if (!isValid(key)) {
        std::cerr << "[ERROR] get(): invalid key\n";
        return std::nullopt;
    }
    std::shared_lock lock(mutex_);
    auto it = data_.find(key);
    if (it == data_.end()) {
        std::cerr << "[INFO ] get(): key '" << key << "' not found\n";
        return std::nullopt;
    }
    return it->second;
}

bool Database::update(const std::string& key, const std::string& new_value) {
    if (!isValid(key) || !isValid(new_value)) {
        std::cerr << "[ERROR] update(): invalid key or value\n";
        return false;
    }
    std::unique_lock lock(mutex_);
    auto it = data_.find(key);
    if (it == data_.end()) {
        std::cerr << "[WARN ] update(): key '" << key << "' not found\n";
        return false;
    }
    it->second = new_value;
    return true;
}

bool Database::remove(const std::string& key) {
    if (!isValid(key)) {
        std::cerr << "[ERROR] remove(): invalid key\n";
        return false;
    }
    std::unique_lock lock(mutex_);
    auto count = data_.erase(key);
    if (count == 0) {
        std::cerr << "[WARN ] remove(): key '" << key << "' not found\n";
    }
    return count > 0;
}
