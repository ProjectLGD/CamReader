#pragma once

#include <iostream>
#include <cmath>

#include "Gene.hpp"

using namespace std;

class Vec3 : public Gene {
public:
    int x = 0;
    int y = 0;
    int z = 0;

    Vec3();
    Vec3(int x, int y, int z);
    ~Vec3();

    float get_distance(Vec3 target);


    friend ostream& operator<< (ostream & out, const Vec3 &data);
    friend Vec3 operator+(const Vec3 &t, const Vec3 &o);
    friend Vec3 operator-(const Vec3 &t, const Vec3 &o);


    friend bool operator<(const Vec3 &l, const Vec3 &r);
    friend bool operator!=(const Vec3 &l, const Vec3 &r);
    friend bool operator==(const Vec3 &l, const Vec3 &r);
    friend bool operator>(const Vec3 &l, const Vec3 &r);
    friend bool operator>=(const Vec3 &l, const Vec3 &r);
    friend bool operator<=(const Vec3 &l, const Vec3 &r);
private:

};
