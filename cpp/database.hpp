
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

    /**
     * @brief Dodaje novi par ključ-vrijednost u bazu.
     * @param key   Neprazan jedinstveni ključ.
     * @param value Neprazan pridruženi podatak.
     * @return true ako je unos uspio; false ako ključ već postoji ili je ulaz neispravan.
     */
    bool insert(const std::string& key, const std::string& value);

    /**
     * @brief Vraća vrijednost za zadani ključ.
     * @param key Neprazan ključ.
     * @return Optional s vrijednošću ako nađe; std::nullopt ako ne nađe ili je ključ neispravan.
     */
    std::optional<std::string> get(const std::string& key) const;

    /**
     * @brief Ažurira postojeći ključ novom vrijednošću.
     * @param key       Ključ koji se ažurira.
     * @param new_value Nova neprazna vrijednost.
     * @return true ako je ažuriranje uspjelo; false ako ključ ne postoji ili je ulaz neispravan.
     */
    bool update(const std::string& key, const std::string& new_value);

    /**
     * @brief Briše par ključ-vrijednost iz baze.
     * @param key Neprazan ključ.
     * @return true ako je brisanje uspjelo; false ako ključ ne postoji ili je neispravan.
     */
    bool remove(const std::string& key);

private:
    mutable std::shared_mutex                     mutex_;  ///< Štiti pristup data_ mapi.
    std::unordered_map<std::string, std::string>  data_;    ///< Interna pohrana podataka.

    /**
     * @brief Provjera valjanosti stringa (trenutno samo neprazan).
     * @param s String koji se provjerava.
     * @return true ako nije prazan.
     */
    static bool isValid(const std::string& s) {
        return !s.empty();
    }
};

#endif // DATABASE_HPP
