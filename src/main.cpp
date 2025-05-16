// Copyright 2022 NNTU-CS
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "train.h"

void testTrain(int n, int mode, int& steps, int64_t& micros) {
    Train train;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < n; ++i) {
        bool light = false;
        if (mode == 1) light = true;
        else if (mode == 2) light = dis(gen);
        train.addCar(light);
    }

    auto start = std::chrono::high_resolution_clock::now();
    int len = train.getLength();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<
        std::chrono::microseconds>(end - start);
    micros = duration.count();
    steps = train.getOpCount();
}

int main() {
    std::cout << "Длина,Режим,Шаги,Время(микросекунда)" <<
        std::endl;

    for (int n = 10; n <= 100; n += 10) {
        for (int mode = 0; mode <= 2; ++mode) {
            int steps;
            int64_t micros;
            testTrain(n, mode, steps, micros);
            std::cout << n << "," << mode << "," <<
                steps << "," << micros << std::endl;
        }
    }

    return 0;
}
