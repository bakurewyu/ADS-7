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
    Car* start = first;
    Car* current = start;
    if (!current->light)
        current->light = true;
    int count = 1;
    current = current->next;
    countOp++;
    while (true) {
        if (current->light) {
            current->light = false;
            for (int i = 0; i < count; ++i) {
                current = current->prev;
                countOp++;
            }
            if (!current->light) {
                return count;
            }
            current = current->next;
            countOp++;
            count = 1;
        } else { 
            current = current->next;
            countOp++;
            count++;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
