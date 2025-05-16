// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() {
    first = nullptr;
    countOp = 0;
}

Train::~Train() {
    if (!first) return;

    Car* current = first->next;
    while (current != first) {
        Car* temp = current;
        current = current->next;
        delete temp;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        newCar->next = newCar->prev = newCar;
        first = newCar;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) throw std::logic_error("Поезд то пустой блин!");

    Car* current = first;
    int steps = 1;
    current->light = true;

    current = current->next;
    countOp++;

    while (!current->light) {
        countOp++;
        steps++;
        current = current->next;
    }

    return steps;
}

int Train::getOpCount() {
    return countOp;
}
