
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <unordered_map>
#include <optional>
#include <shared_mutex>

/**
 * @brief Dretveno-sigurna memorijska baza ključ-vrijednost.
 *
 * Koristi shared_mutex za:
 *   - paralelno čitanje više dretvi
 *   - ekskluzivno pisanje u jednoj dretvi
 */
class Database {
public:
    Database() = default;
    ~Database() = default;

    bool insert(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool update(const std::string& key, const std::string& new_value);
    bool remove(const std::string& key);

private:
    mutable std::shared_mutex                     mutex_; 
    std::unordered_map<std::string, std::string>  data_;   

    static bool isValid(const std::string& s) {
        return !s.empty();
    }
};

#endif 
