#define EXIT_OK 0
#define EXIT_ERR 1

#include "stdafx.h"

unsigned int max_x = 10;
unsigned int max_y = 10;

unsigned int width = 640;
unsigned int height = 480;

using namespace std::chrono;

vector<Rocket> generate_data(uint64_t vector_size, uint64_t dna_size) {
    vector<Rocket> vec;
    for (size_t i = 0; i < vector_size; i++) {
        DNA<Vec3> dna;
        for (size_t j = 0; j < dna_size; j++) {
            int x = rand() % (max_x*2) - max_x; // also generate negative numbers.
            int y = rand() % (max_x*2) - max_x;
            // int y = 0;
            int z = 0;
            dna.gene_add(Vec3(x, y, z));
        }
        // add this to a citizen.
        Rocket cit(dna);
        vec.push_back(cit);
    }

    return vec;
}

void plot_rocket_path(Rocket &rock, Vec3 &bluev, Vec3 &redv, Mat &snapshot) {
    Singleton<Mat>::getInstance() = snapshot.clone();
    Rect r(Point(bluev.x - 2, bluev.y - 2), Point(bluev.x + 2, bluev.y + 2));
    rectangle(Singleton<Mat>::getInstance(), r, Scalar(255, 0, 0, 255), CV_FILLED);
    Rect r2(Point(redv.x - 2, redv.y - 2), Point(redv.x + 2, redv.y + 2));
    rectangle(Singleton<Mat>::getInstance(), r2, Scalar(0, 0, 255, 255), CV_FILLED);
    imshow("Running", Singleton<Mat>::getInstance());
    for (size_t i = 0; i < rock.dna.gene_size(); i++) {
        rock.run(bluev, i);
        Rect re(Point(rock.start.x - 2, rock.start.y - 2), Point(rock.start.x + 2, rock.start.y + 2));
        rectangle(Singleton<Mat>::getInstance(), re, Scalar(255, 255, 0), CV_FILLED);
        imshow("Running", Singleton<Mat>::getInstance());
        waitKey(50);
    }
}

typedef pair<pair<Vec3, Vec3>, Rocket> ENTRY;

vector<ENTRY> entries;

ENTRY make_entry(Vec3 start, Vec3 target, Rocket path) {
    return make_pair(make_pair(start, target), path);
}

void pathfind() {
    cout << "IMPLEMENT ME " << endl;
}

int do_actual_learning(Vec3 bluev, Vec3 redv, Mat &snapshot) {
    unsigned int to_run = 30;

    unsigned int size = 25;
    float delta = bluev.get_distance(redv);
    unsigned int dna_size = (delta/max_x)*3;
    Population<Vec3, Rocket> pop(redv, bluev, 0.01f, size, dna_size, generate_data);
    uint64_t start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for (size_t count = 1; count <= to_run; count++) {
        cout << "\r";
        cout << "Population " << count << flush;
        // continue on with the next generation.
        pop.fitness_calculate();
        pop.natural_selection();
        Rocket rocket = pop.compute_most_fit();
        pop.generate(); // generates an entirely new population without any fitness.

        Rect r(Point(bluev.x - 2, bluev.y - 2), Point(bluev.x + 2, bluev.y + 2));
        rectangle(Singleton<Mat>::getInstance(), r, Scalar(255, 0, 0, 255), CV_FILLED);
        Rect r2(Point(redv.x - 2, redv.y - 2), Point(redv.x + 2, redv.y + 2));
        rectangle(Singleton<Mat>::getInstance(), r2, Scalar(0, 0, 255, 255), CV_FILLED);
        imshow("Running", Singleton<Mat>::getInstance());

        if (pop.is_finished()) {
            cout << endl;
            uint64_t now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            cout << "Population finished." << endl;
            cout << "Most fit Citizen is " << rocket << endl;
            cout << "Time taken to find this Citizen is " << (float)(now - start_time)/1000.0f << "s" << endl;
            entries.push_back(make_entry(bluev, redv, rocket));
            Rocket r_new(rocket.dna, bluev);
            plot_rocket_path(r_new, bluev, redv, snapshot);
            return 1;
        }

        char key = waitKey(500);
        if (key == 'p') {
            cout << endl;
            cout << "The current most fit Citizen is " << rocket << endl;
            Rocket r_new(rocket.dna, bluev);
            plot_rocket_path(r_new, bluev, redv, snapshot);
        }
        if (key == 27) {
            return 27;
        }
        Singleton<Mat>::getInstance() = snapshot.clone();

    }
    Rocket rocket = pop.compute_most_fit();

    if (!pop.is_finished()) {
        cout << endl;
        uint64_t now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout << "Population finished but has not reached goal." << endl;
        cout << "Most fit Citizen is " << rocket << endl;
        cout << "Time taken to find this Citizen is " << (float)(now - start_time)/1000.0f << "s" << endl;
        Rocket r_new(rocket.dna, bluev);
        plot_rocket_path(r_new, bluev, redv, snapshot);
    }
    return 0;
}

void hardcoded_learning() {

    vector<pair<Point, Point>> pairs;

    for (size_t i = 0; i < 100; i++) {
        Point red(rand() % width, rand() % height);
        Point blue(rand() % width, rand() % height);
        pairs.push_back(make_pair(blue, red));
    }

    for (size_t i = 0; i < pairs.size(); i++)
	{

        Mat snapshot = Mat::zeros( Size(640, 480), CV_8UC3);

        Singleton<Mat>::getInstance() = snapshot.clone();

        DOT red;
        DOT blue;
        red.pt = pairs[i].second;
        blue.pt = pairs[i].first;

		Vec3 bluev(blue.pt.x, blue.pt.y, 0);
		Vec3 redv(red.pt.x , red.pt.y , 0);

        int retval = do_actual_learning(bluev, redv, snapshot);
        if (retval == 27) {
            break;
        }

        //cin >> temp
		cout << endl;
		// pop.print();

	}

}

void learn() {
	VidReader reader;
    while (true)
	{
		Mat snapshot;
		vector<DOT> pos;
        Point zero_pt(0,0);
		while (true)
		{
			pos = reader.getPositions(snapshot);

			imshow("Snapshot", snapshot);
			waitKey(1);
			if (pos[0].pt != zero_pt && pos[1].pt != zero_pt && pos[0].pt != pos[1].pt)
				break;
		}

        Singleton<Mat>::getInstance() = snapshot.clone();

        DOT red;
        DOT blue;
        // red.pt = Point(100, 200);
        // blue.pt = Point(50, 50);


        for (DOT d : pos)
        {
            std::cout << "Point " << d.pt.x << "-" << d.pt.y << " " << d.color << std::endl;
            if (d.color == RED)
                red = d;
            else
                blue = d;
        }

		Vec3 bluev(blue.pt.x, blue.pt.y, 0);
		Vec3 redv(red.pt.x , red.pt.y , 0);

        int retval = do_actual_learning(bluev, redv, snapshot);
        if (retval == 27) {
            break;
        }

	}

}

int main(int argc, char** argv) {
    (void) argc; // unused
    (void) argv; // unused
    cout << endl;
    srand((unsigned)time(nullptr));

    cout << boolalpha; // remember this one

    char key;
    while(true) {
        cout << "Please press a key to select your desired action." << endl;
        cout << "l : Learn based on random data provided by the camera." << endl;
        cout << "t : Try finding the correct path based on the stored data." << endl;
        cout << "h : Learn based on hardcoded points." << endl;
        cout << "q : Quit." << endl;
        cin >> key;

        switch (key) {
            case 'l':
                cout << "Learn" << endl;
                learn();
                break;
            case 't':
                cout << "Try pathfinding" << endl;
                pathfind();
                break;
            case 'h':
                cout << "Hardcoded learning" << endl;
                hardcoded_learning();
                break;
            case 'q':
                return EXIT_OK;
        }
    }

    return EXIT_OK;
}
