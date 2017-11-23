#pragma once

#include "Vector3D.h"
#include <vector>

struct Plane {
    Plane(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    Plane(const Vector3D& point, const Vector3D& normal);
    Plane(double a, double  b, double c, double d);
    explicit Plane(const std::vector<Vector3D>& points);

    double distanceFrom(const Vector3D& point) const;
    Vector3D projectionOf(const Vector3D& point) const;

    double A, B, C, D;
    Vector3D N;
};

std::ostream& operator<<(std::ostream& out, const Plane& plane);
