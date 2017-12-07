#include "Rocket.h"

Rocket::Rocket(DNA<Vec3> dna) : Citizen<Vec3>(dna){
    this->pos = Vec3(0,0,0);
}

Rocket::~Rocket() {

}

// void Rocket::update(Vec3 target, unsigned int current_dna) {
//     cout << "update rocket" << endl;
//     Vec3 current_gene = dna.gene_get().at(current_dna);
//     // TODO: add more checks.
//
//     // check if we have reached the target.
//     if (!failed && !reached) {
//         if (pos.get_distance(target) < 5) {
//             // we're there!
//             cout << "Rocket reached target at pos " << pos << endl;
//             reached = true;
//         } else {
//             // apply current_gene to our pos.
//             pos = pos + current_gene;
//         }
//     }
// }

float Rocket::fitness_calculate(Vec3 target) {
    float distance = pos.get_distance(target);
    // cout << "Current pos " << pos << endl;
    // cout << "Target " << target << endl;
    // cout << "Distance in rocket to t is " << distance << endl;
    fitness = 1.0f / (distance+1);
    return fitness;
}

void Rocket::run(Vec3 target) {
    // move according to the Vec3's in DNA.
    (void) target;
    vector<Vec3> genes = dna.gene_get();
    // cout << "Startpos is " << pos << endl;
    // cout << "[---------------]" << endl;
    for (size_t i = 0; i < genes.size(); i++) {
        // cout << "Adding " << genes.at(i) << " to current " << pos << endl;
        pos = pos + genes.at(i);
        // cout << "Ended up at " << pos << endl;
        // cout << "----" << endl;
    }
    // cout << "Final pos --------" << pos << endl;
}


ostream& operator<< (ostream & out, const Rocket &data) {
    out << "Rocket " << data.pos << flush;
    return out;
}
