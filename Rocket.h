#pragma once

#include "stdafx.h"

class Rocket : public Citizen<Vec3> {
public:
    bool failed = false;

    unsigned int steps_taken = 0;

    Rocket(DNA<Vec3> dna);
	Rocket(DNA<Vec3> dna, Vec3 start_pos);
    ~Rocket();

    void run(Vec3 target, unsigned int current_dna);
    float fitness_calculate(Vec3 target);


    friend ostream& operator<< (ostream & out, const Rocket &data);
};
