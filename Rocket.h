#pragma once

#include "stdafx.h"

class Rocket : public Citizen<Vec3> {
public:
    Vec3 pos;

    bool reached = false;
    bool failed = false;

    Rocket(DNA<Vec3> dna);
    ~Rocket();

    void run(Vec3 target);
    float fitness_calculate(Vec3 target);


    friend ostream& operator<< (ostream & out, const Rocket &data);
};
