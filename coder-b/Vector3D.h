#pragma once

#include <cmath>
#include <istream>
#include <ostream>

struct Vector3D {
    Vector3D();
    Vector3D(double x_, double y_, double z);
    Vector3D& operator=(const Vector3D& a);


    double x, y, z;
};

Vector3D operator*(const Vector3D& a, double b);
Vector3D operator/(const Vector3D& a, double b);
Vector3D operator-(const Vector3D& a, const Vector3D& b);
Vector3D operator+(const Vector3D& a, const Vector3D& b);
Vector3D operator*(const Vector3D& a, const Vector3D& b);
double dot(const Vector3D& a, const Vector3D& b);
double length(const Vector3D& a);
Vector3D normalize(const Vector3D& a);
std::istream& operator>>(std::istream& in, Vector3D& rhs);
std::ostream& operator<<(std::ostream& out, const Vector3D& rhs);