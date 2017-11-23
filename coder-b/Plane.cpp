#include "Plane.h"

Plane::Plane(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
    Vector3D ab = b - a;
    Vector3D ac = c - a;
    N = normalize(ab * ac);
    A = N.x;
    B = N.y;
    C = N.z;
    D = -(A * a.x + B * a.y + C * a.z);
}

Plane::Plane(const Vector3D& point, const Vector3D& normal) {
    N = normal;
    A = N.x;
    B = N.y;
    C = N.z;
    D = -(A * point.x + B * point.y + C * point.z);
}

Plane::Plane(const std::vector<Vector3D>& points)
        : Plane(points.at(0), points.at(1), points.at(2)) {
}

double Plane::distanceFrom(const Vector3D& point) const {
    Plane newPlane(point, N);
    return fabs(newPlane.D - D);
}

Vector3D Plane::projectionOf(const Vector3D& point) const {
    Plane newPlane(point, N);
    double distance = newPlane.D - D;
    return point + (N * distance);
}

Plane::Plane(double a, double b, double c, double d) {
    A = a; B = b; C = c; D = d;
    N = Vector3D(a, b, c);
}

std::ostream& operator<<(std::ostream& out, const Plane& plane) {
    return out << "{A: " << plane.A << ", B: " << plane.B << ", C: " << plane.C << ", D: " << plane.D << "}";
}
