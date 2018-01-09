#include "Rocket.h"

Rocket::Rocket(DNA<Vec3> dna) : Citizen<Vec3>(dna, Vec3(0,0,0)){
}

Rocket::Rocket(DNA<Vec3> dna, Vec3 start_pos) : Citizen<Vec3>(dna, start_pos){
	//cout << "Initializing rocket at " << start_pos << endl;

}

Rocket::~Rocket() {
}


float Rocket::fitness_calculate(Vec3 target) {
    float distance = start.get_distance(target);
    // cout << "Current pos " << pos << endl;
    // cout << "Target " << target << endl;
    // cout << "Distance in rocket to t is " << distance << endl;
    fitness = 0.8f * (1.0f / (distance+1)) + 0.2f * (1.0f / (steps_taken+1));
    return fitness;
}

void Rocket::run(Vec3 target, unsigned int current_dna) {
    // move according to the Vec3's in DNA.
    vector<Vec3> genes = dna.gene_get();
    // cout << "Startpos is " << pos << endl;
    // cout << "[---------------]" << endl;
    // cout << "Adding " << genes.at(i) << " to current " << pos << endl;
    if (!done && !failed) {
        // cout << "Adding pos" << endl;
        start = start + genes.at(current_dna);
        steps_taken = current_dna;
        if (start.get_distance(target) < 5) { // if withing 5 pixels.
            done = true;
            // cout << "Rocket reached target pos at " << pos << " in " << steps_taken << " steps" << endl;
        }
        // TODO: add checks for failed.
    } else {
        // rocket has either reached target or failed in doing so.
    }
    // cout << "Ended up at " << pos << endl;
    // cout << "----" << endl;
    // cout << "Final pos --------" << pos << endl;
    if (current_dna == genes.size() -1) {
        // cout << "Drawing" << endl;
        Rect r(Point(start.x - 2, start.y - 2), Point(start.x + 2, start.y + 2));
        // cout << r << endl;
        rectangle(Singleton<Mat>::getInstance(), r, Scalar(0, 255, 0), CV_FILLED);
        imshow("Running", Singleton<Mat>::getInstance());
        //waitKey(1);
    }
}


ostream& operator<< (ostream & out, const Rocket &data) {
    out << "Citizen " << data.start << " steps " << data.steps_taken << flush;
    return out;
}
