#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../database.hpp"
#include <thread>

TEST_CASE("Insert and Get", "[basic]") {
    Database db;
    REQUIRE(db.insert("key1", "value1") == true);
    auto res = db.get("key1");
    REQUIRE(res.has_value());
    REQUIRE(res.value() == "value1");
}

TEST_CASE("Duplicate Insert", "[basic]") {
    Database db;
    REQUIRE(db.insert("key1", "value1") == true);
    REQUIRE(db.insert("key1", "another") == false);
}

TEST_CASE("Get Non-Existent Key", "[error]") {
    Database db;
    auto res = db.get("nope");
    REQUIRE(!res.has_value());
}

TEST_CASE("Update Existing and Non-Existent", "[update]") {
    Database db;
    REQUIRE(db.insert("key1", "value1") == true);
    REQUIRE(db.update("key1", "updated") == true);
    REQUIRE(db.get("key1").value() == "updated");
    REQUIRE(db.update("nope", "value") == false);
}

TEST_CASE("Remove Existing and Non-Existent", "[remove]") {
    Database db;
    REQUIRE(db.insert("key1", "value1") == true);
    REQUIRE(db.remove("key1") == true);
    REQUIRE(!db.get("key1").has_value());
    REQUIRE(db.remove("key1") == false);
}

TEST_CASE("Invalid Input Handling", "[validation]") {
    Database db;
    REQUIRE(db.insert("", "value") == false);
    REQUIRE(db.insert("key", "") == false);
    REQUIRE(db.update("", "value") == false);
    REQUIRE(db.update("key", "") == false);
    REQUIRE(db.remove("") == false);
    auto res = db.get("");
    REQUIRE(!res.has_value());
}

TEST_CASE("Sequential Operations", "[sequence]") {
    Database db;
    REQUIRE(db.insert("a", "1") == true);
    REQUIRE(db.insert("b", "2") == true);
    REQUIRE(db.get("a").value() == "1");
    REQUIRE(db.remove("a") == true);
    REQUIRE(!db.get("a").has_value());
    REQUIRE(db.get("b").value() == "2");
    REQUIRE(db.update("b", "3") == true);
    REQUIRE(db.get("b").value() == "3");
}

TEST_CASE("Concurrent Inserts and Gets", "[concurrency]") {
    Database db;
    std::thread t1([&](){ db.insert("k1", "v1"); });
    std::thread t2([&](){ db.insert("k2", "v2"); });
    t1.join();
    t2.join();
    REQUIRE(db.get("k1").value() == "v1");
    REQUIRE(db.get("k2").value() == "v2");
}
