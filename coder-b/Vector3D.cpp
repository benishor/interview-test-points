#include "Vector3D.h"

Vector3D::Vector3D() : x(0), y(0), z(0) {};

Vector3D::Vector3D(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_) {
}

Vector3D operator*(const Vector3D& a, double b) {
    return {a.x * b, a.y * b, a.z * b};
}

Vector3D operator/(const Vector3D& a, double b) {
    return {a.x / b, a.y / b, a.z / b};
}

Vector3D operator-(const Vector3D& a, const Vector3D& b) {
    return {b.x - a.x, b.y - a.y, b.z - a.z};
}

Vector3D operator+(const Vector3D& a, const Vector3D& b) {
    return {b.x + a.x, b.y + a.y, b.z + a.z};
}

Vector3D operator*(const Vector3D& a, const Vector3D& b) {
    double x = a.y * b.z - b.y * a.z;
    double y = a.z * b.x - b.z * a.x;
    double z = a.x * b.y - b.x * a.y;
    return {x, y, z};
}

double dot(const Vector3D& a, const Vector3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double length(const Vector3D& a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vector3D normalize(const Vector3D& a) {
    double len = length(a);
    return len > 0.000001 ?
           a / len :
           a;
}

std::istream& operator>>(std::istream& in, Vector3D& rhs) {
    char comma;
    return in >> rhs.x >> comma >> rhs.y >> comma >> rhs.z;
}

std::ostream& operator<<(std::ostream& out, const Vector3D& rhs) {
    return out << rhs.x << ", " << rhs.y << ", " << rhs.z;
}

Vector3D& Vector3D::operator=(const Vector3D& a) {
    x = a.x;
    y = a.y;
    z = a.z;
    return *this;
}

