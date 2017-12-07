#pragma once

#include <iostream>
#include "DNA.hpp"
#include "Citizen.hpp"

using namespace std;

template <class T, class R>
class Population {
    typedef vector<R>(*dna_gen_func)(uint64_t vector_size, uint64_t dna_size);
private:
    T target; // our target, T. The population wants to be as close as possible to target.
    float mutation_rate; // how often mutations occur.
    uint64_t population_size; // The size of the
    vector<R> popu; // current population filled with DNA
    vector<R> mating_pool; // the pool used when making new generation
    bool finished = false; // not in use yet
    int perfect_score = 1; // not in use yet.
    uint64_t generation = 0; // current generation
    dna_gen_func gen_func = nullptr; // thefunction to use to generate random data, as inside this class, T is still unknown.

public:
    Population(T target, float mutation_rate, uint64_t population_size, uint64_t dna_size, dna_gen_func func) {

        this->target = target;
        this->mutation_rate = mutation_rate;
        this->population_size = population_size;
        this->gen_func = func;

        // fill population with DNA.
        // TODO: remove hardcoded value;
        // Generate random DNA, so we're generating 100 DNA<T>'s of size 100;
        vector<R> random_dna = dna_generate(population_size, dna_size);
        for (size_t i = 0; i < random_dna.size(); i++) {
            R dna = random_dna.at(i);
            popu.push_back(dna); // this copies the dna to popu
        }

        // fitness_calculate();
    }

    Population(const Population<T, R> *p) {
        this->target = p->target;
        this->mutation_rate = p->mutation_rate;
        this->population_size = p->population_size;
        this->gen_func = p->gen_func;

        this->popu = p->popu;
    }

    void fitness_calculate() {
        for (size_t i = 0; i < popu.size(); i++) {
            // These have to be pointers otherwise we're not accesing the actual DNA inside the vec.
            R *citizen = &popu.at(i);
            citizen->run(target);
            // cout << "Dna fitness is " << dna->fitness_get();
            // dna->fitness_calculate(target);
            citizen->fitness_calculate(target);
            // cout << "Fitness is " << endl;
            // cout << citizen->fitness << endl;
            // cout << " and now it is " << dna->fitness_get() << endl;
        }
    }

    void natural_selection() {
        mating_pool.clear();

        // Find max fitness.
        float fitness_max = 0.0f;
        for (size_t i = 0; i < popu.size(); i++) {
            R *cit = &popu.at(i);
            // cout << "Dna fitness " << dna->fitness_get() << endl;
            if (cit->fitness > fitness_max) {
                fitness_max = cit->fitness;
            }
        }

        // cout << "Fitness max is " << fitness_max << endl;

        for (size_t i = 0; i < popu.size(); i++) {
            R *cit = &popu.at(i);

            // So, what we're going to do next is, find the most fit DNA's fitness.
            // If the DNA is more fit, it should be added to our mating pool more often.
            // Else, it should be added less.

            // So for example, a piece of DNA with a fitness of 1 should be added 10 times.
            // A piece of DNA with a fitness of 0.1 should be added only one time.
            unsigned int count = 0;
            cit->fitness_normalize(fitness_max);
            float fitness_current = cit->fitness;
            count = (unsigned int)(10 * fitness_current);
            // cout << "Adding fitness of " << fitness_current << "\t" << count << " times to mating_pool" << endl;
            for (size_t j = 0; j < count; j++) {
                mating_pool.push_back(*cit);
            }
        }
        // cout << "Mating pool size: " << mating_pool.size() << endl;
    }

    void generate() {
        // Refill the population with children from the mating pool.

        // This verifies we're actually replacing the value in popu.
        // popu.at(0).print();

        // cout << "Mating pool consists of " << mating_pool.size() << " potential mates" << endl;
        // for (size_t i = 0; i < mating_pool.size(); i++) {
        //     mating_pool.at(i).print();
        // }

        for (size_t i = 0; i < popu.size(); i++) {
            // Get parents
            DNA<T> partner1 = mating_pool.at(rand() % (mating_pool.size() - 1)).dna;
            DNA<T> partner2 = mating_pool.at(rand() % (mating_pool.size() - 1)).dna;

            // Make new child
            DNA<T> child = partner1.crossover(&partner2);

            // cout << "Turning partner 1 and partner 2 into child" << endl;
            // partner1.print();
            // partner2.print();
            // child.print();

            vector<T> random_values = dna_generate(1, child.gene_size()).at(0).dna.gene_get();
            child.mutate(mutation_rate, random_values);

            // add child to population as new citizen.
            // TODO: Check if we shouldn't pas pos
            popu.at(i) = R(child);
        }
        // fitness_calculate(); // don't forget to calculate fitness so that all our new children are fit =D
        // If they're the same, that's not good.
        // popu.at(0).print();
        generation++;
    }

    DNA<T> compute_most_fit() {
        // fitness_calculate();
        float fitness_max = 0.0f;
        size_t index = 0;
        for (size_t i = 0; i < popu.size(); i++) {
            R *cit = &popu.at(i);
            float fitness_current = cit->fitness;
            // cout << "Current fitness " << fitness_current << endl;
            if (fitness_current > fitness_max) {
                fitness_max = fitness_current;
                index = i;
            }
        }
        cout << "The most fit DNA is index " << index << " with a fitness of " << fitness_max << endl;
        cout << "Pos is " << popu.at(index) << endl;
        cout << "Distance is " << popu.at(index).pos.get_distance(target) << endl;
        return popu.at(index).dna;
    }

    vector<R> dna_generate(uint64_t vector_amount, uint64_t dna_amount) {
        return gen_func(vector_amount, dna_amount);
    }

    vector<R> get_dna() {
        return popu;
    }

    void run() {
        for (size_t i = 0; i < popu.size(); i++) {
            // for citz
            popu.at(i).run(target);
        }
    }

    void print() {
        cout << "Population consisting of the following variables" << endl;
        cout << "Target:\t\t\t" << target << endl;
        cout << "Mutation rate:\t\t" << mutation_rate << endl;
        cout << "Population size:\t" << population_size << endl;
        cout << "Generation:\t\t" << generation << endl;
        cout << "End of population" << endl;
        cout << endl;
    }

    bool operator==(const Population<T, R> &other) const {
        return (this->generation == other.generation) && (this->popu == other.popu);
    }
};
