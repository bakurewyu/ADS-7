// Copyright 2022 NNTU-CS
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "train.h"

void testTrain(int n, int mode, int& steps, long long& micros) {
    Train train;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < n; ++i) {
        bool light;
        if (mode == 0) light = false; // все выключены
        else if (mode == 1) light = true; // все включены
        else light = dis(gen); // случайно!!!!
        train.addCar(light);
    }

    auto start = std::chrono::high_resolution_clock::now();
    int len = train.getLength();
    auto end = std::chrono::high_resolution_clock::now();

    steps = train.getOpCount();
    micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    std::cout << "Длина,Режим,Шаги,Время(микросекунда)" << std::endl;

    for (int n = 10; n <= 100; n += 10) {
        for (int mode = 0; mode <= 2; ++mode) {
            int steps;
            long long micros;
            testTrain(n, mode, steps, micros);
            std::cout << n << "," << mode << "," << steps << "," << micros << std::endl;
        }
    }

    return 0;
}
