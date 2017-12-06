#pragma once

#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>
#include <limits>

using namespace std;

template <class T>
class DNA {
private:
    // The genes of this DNA. Can contain any object.
    vector<T> genes;

    // The fitness of this particular DNA.
    // Will only be accurate after calling the fitness function.
    float fitness = 0.0f;

public:

    DNA() {

    }

    DNA(const DNA<T> *genes) {
        cout << "Copy constructor called" << endl;
        for (auto m : genes) {
            gene_add(m);
        }
        fitness = genes->fitness;
    }

    ~DNA() {
        // cout << "Deconstructor DNA called" << endl;
    }

    // Crosses two DNA's into a new one.
    DNA<T> crossover(DNA<T> *other) {
        uint64_t size_self = this->gene_size();
        uint64_t size_other = other->gene_size();
		uint64_t size_big;	//Size of the biggest vector

		DNA<T> *set_big;	//Keep track of which vector is the biggest
		DNA<T> new_dna;

        // Decide on the smallest size we're going to use for both vectors.
        // This ensures that we don't go over the limits of a vector.
		// Additionally the biggest vector is determined
        uint64_t size_to_use;
        if (size_self > size_other) {
            size_to_use = size_other;
			set_big = this;
        } else {
            size_to_use = size_self;
			set_big = other;
        }
		size_big = set_big->gene_size();

        // Find a midpoint that fits within the smallest size of the vectors.
        size_t midpoint = (rand() % size_to_use);
        // Sometimes we pick from this first, sometimes we pick from other first
        size_t order = rand() % 2;

        // From 0 to midpoint, pick a gene.
        for (size_t i = 0; i < midpoint; i++) {
            if (order) {
                new_dna.gene_add(this->genes.at(i));
            } else {
                new_dna.gene_add(other->genes.at(i));
            }

        }
        // From midpoint to the smallest vector size, pick the others
        for (size_t i = midpoint; i < size_to_use; i++) {
            if (order) {
                new_dna.gene_add(other->genes.at(i));
            } else {
                new_dna.gene_add(this->genes.at(i));
            }
        }

		//Determine (randomly) how much of the leftover values should be added
		if (size_big != size_to_use)
		{
			uint64_t size_differential = (rand() % (size_big - size_to_use));

			for (size_t i = size_to_use; i < (size_to_use + size_differential); i++)
			{
				new_dna.gene_add(set_big->genes.at(i));
			}

		}

        return new_dna;
    }

    // Mutates the genes using mutation_rate with values provided by random_values.
    void mutate(float mutation_rate, vector<T> random_values) {
        for (size_t i = 0; i < genes.size(); i++) {
            float random = (rand() / (float)RAND_MAX);
            if (random < mutation_rate) {
                genes.at(i) = random_values.at(rand() % random_values.size());
            }
        }
    }

    // Calculates the fitness for this particular DNA.
    void fitness_calculate(T target) {
        // NOTE: Make sure that fitness_calculate always returns a float > 0.

        float distance_max;
        float distance_min;

        if (genes.size() > 1) {
            // Calculate the distance to T for every gene.
            distance_max = genes.at(0).get_distance(target);
            distance_min = genes.at(0).get_distance(target);
            for (size_t i = 1; i < genes.size(); i++) {
                T current = genes.at(i);
                // We can not use abs() because T is not guaranteed to be float or int etc.
                T distance_current;
                // Work around abs() not supporting much more than default datatypes.
                if (current > target) {
                    distance_current = current - target;
                } else {
                    distance_current = target - current;
                }
                if (distance_current.get_distance(target) > distance_max) {
                    distance_max = distance_current.get_distance(target);
                }
                if (distance_current.get_distance(target) < distance_min) {
                    distance_min = distance_current.get_distance(target);
                }
            }
        } else if (genes.size() == 1) {
            distance_max = genes.at(0).get_distance(target);
            distance_min = genes.at(0).get_distance(target);
        } else {
            cerr << "Genes.size() is 0, should not happen boi." << endl;
            exit(1);
        }

        float distance_between_min_max = distance_max - distance_min;

        // cout << "Max and min are " << distance_max << " " << distance_min << endl;

        // The worst case scenario is distance_max, the best is distance_min being 0.
        // The closer distance_max is to distance_min, the more fit this DNA is.

        // Fitness is more dependant on distance_min than distance_between_min_max right now.
        // Distance_min is 70% of the fitness and distance_between_min_maxis only 30%, so the closer to the target,
        // the fitter it is. And the closer all values are to the target, the fitter it is. (Unless distance_min is large)
        // cout << genes.at(0) << endl;
        // cout << "Dis min " << distance_min << endl;
        // cout << "Dis amx " << distance_max << endl;
        // TODO: check if fitness works well.
        fitness = 0.7f * (1/(distance_min + 1)) + 0.3f * (1/(distance_between_min_max + 1));
        // cerr << "Kill me" << endl;
        // cout << fitness << endl;
        // exit(1);
    }

    float fitness_get() {
        return fitness;
    }

    void gene_add(T gene) {
        genes.push_back(gene);
    }

    vector<T> gene_get() {
        return genes;
    }

    uint64_t gene_size() {
        return genes.size();
    }

    void print() {
        cout << "DNA consisting of the following genes." << endl;
        size_t i = 0;
        for (auto &g : genes) {
            cout << g << "\t";
            i++;
            if (i == 10) {
                i = 0;
                cout << endl;
            }
        }
        cout << endl;
        cout << "It's fitness is " << fitness << endl;
        cout << "End of DNA" << endl;
        cout << endl;
    }

    bool operator==(const DNA<T> &other) const {
        return this->genes == other.genes;
    }

};
