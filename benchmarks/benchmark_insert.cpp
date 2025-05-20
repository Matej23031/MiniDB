
#include <iostream>
#include <chrono>
#include "database.hpp"

int main(int argc, char* argv[]) {
    int N = 1000000;
    if (argc > 1) {
        try {
            N = std::stoi(argv[1]);
        } catch (...) {
            std::cerr << "Invalid argument, using default N=1000000\n";
        }
    }

    Database db;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        db.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Inserted " << N << " entries in "
              << duration.count() << " seconds ("
              << (duration.count() * 1000.0 / N)
              << " ms per insert)\n";

    return 0;
}
