#pragma once

#include <iostream>

using namespace std;

template <class T>
class Citizen {
public:
    DNA<T> dna;

    float fitness = 0;

    Citizen(DNA<T> dna) {
        this->dna = dna;
    }

    virtual float fitness_calculate(T target) {
        cerr << "Calculting fitness in citizen" << endl;
        (void) target;
        return 0.0f;
    }

    virtual float fitness_normalize(float max) {
        fitness /= max;
        return fitness;
    }

    virtual void run(T target) {
        cerr << "Running citizen, are you sure this is supposed to happen?" << endl;
        (void) target;
    }

};
