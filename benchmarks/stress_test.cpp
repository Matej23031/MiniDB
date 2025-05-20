// stress_test.cpp
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "database.hpp"

void worker(Database& db, int start, int count) {
    for (int i = 0; i < count; ++i) {
        db.insert("key" + std::to_string(start + i), "value" + std::to_string(start + i));
    }
}

int main(int argc, char* argv[]) {
    int threads = std::thread::hardware_concurrency();
    int total = 1000000;

    if (argc > 1) {
        try { threads = std::stoi(argv[1]); } catch (...) {}
    }
    if (argc > 2) {
        try { total = std::stoi(argv[2]); } catch (...) {}
    }

    if (threads < 1) threads = 1;
    int per_thread = total / threads;

    Database db;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> workers;
    workers.reserve(threads);
    for (int i = 0; i < threads; ++i) {
        workers.emplace_back(worker, std::ref(db), i * per_thread, per_thread);
    }
    for (auto& t : workers) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Inserted " << (per_thread * threads)
              << " entries using " << threads << " threads in "
              << duration.count() << " seconds ("
              << (duration.count() * 1000.0 / (per_thread * threads))
              << " ms per insert)\n";

    return 0;
}
