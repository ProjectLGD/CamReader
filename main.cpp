#define EXIT_OK 0
#define EXIT_ERR 1

#include "stdafx.h"

unsigned int max_x = 10;
unsigned int max_y = 10;


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

int main(int argc, char** argv) {
    (void) argc; // unused
    (void) argv; // unused
    cout << endl;
    srand((unsigned)time(nullptr));

    cout << boolalpha; // remember this one

    cout << "How often should we run?" << endl;
    // cin >> to_run;
	VidReader reader;
	while (true)
	{
		Mat snapshot;
		vector<DOT> pos;
		while (true)
		{
			pos = reader.getPositions(snapshot);
			
			imshow("snapslet", snapshot);
			waitKey(1);

			if (pos[0].pt != pos[1].pt)
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

		cout << "Red and blue" << endl;
		cout << redv << "\t" << bluev << endl;

		unsigned int to_run = 30;

		unsigned int size = 25;
		float delta = bluev.get_distance(redv);
		unsigned int dna_size = (delta/max_x)*3;
		cout << "DNA size is " << dna_size << " pixel distance is " << delta << endl;
		Population<Vec3, Rocket> pop(redv, bluev, 0.001f, size, dna_size, generate_data);
		cout << "Iterating "<< to_run <<" times to evolve population" << endl;
		char temp;

		for (size_t count = 1; count <= to_run; count++) {
		    cout << "\r";
		    cout << "Population " << count << flush;
		    // continue on with the next generation.
		    pop.fitness_calculate();
		    pop.natural_selection();
		    pop.compute_most_fit();
		    pop.generate(); // generates an entirely new population without any fitness.
            Rect r(Point(bluev.x - 2, bluev.y - 2), Point(bluev.x + 2, bluev.y + 2));
            rectangle(Singleton<Mat>::getInstance(), r, Scalar(255, 0, 0, 255), CV_FILLED);
            Rect r2(Point(redv.x - 2, redv.y - 2), Point(redv.x + 2, redv.y + 2));
            rectangle(Singleton<Mat>::getInstance(), r2, Scalar(0, 0, 255, 255), CV_FILLED);

            imshow("Running", Singleton<Mat>::getInstance());
            waitKey(500);

		    // cin >> temp;
           // Singleton<Mat>::getInstance() = Mat::zeros(640, 480, CV_8UC3);
			Singleton<Mat>::getInstance() = snapshot.clone();

		}
        cin >> temp;
		cout << endl;

		// pop.compute_most_fit().print();

		pop.print();


	}

	cout << Singleton<Mat>::getInstance() << endl;


    //// TODO: Get these from camera.
    //DOT red;
    //red.color = RED;
    //red.pt = Point(121, 248);

    //DOT blue;
    //blue.color = BLUE;
    //blue.pt = Point(50, 100);

    //Vec3 bluev(blue.pt.x, blue.pt.y, 0);
    //Vec3 redv(red.pt.x - bluev.x, red.pt.y - bluev.y, 0);

    //cout << "Red and blue" << endl;
    //cout << redv << "\t" << bluev << endl;

    //Population<Vec3, Rocket> pop(redv, 0.01f, size, dna_size, generate_data);
    //cout << "Iterating "<< to_run <<" times to evolve population" << endl;
    //char temp;

    //for (size_t count = 1; count <= to_run; count++) {
    //    cout << "\r";
    //    cout << "Population " << count << flush;
    //    // continue on with the next generation.
    //    pop.fitness_calculate();
    //    pop.natural_selection();
    //    pop.compute_most_fit();
    //    pop.generate(); // generates an entirely new population without any fitness.
    //    cin >> temp;
    //}
    //cout << endl;

    //// pop.compute_most_fit().print();

    //pop.print();

    return EXIT_OK;
}
