#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "Plane.h"

using namespace std;

vector<Vector3D> readPointsFromFile(const string& filename) {
    Vector3D p;
    vector<Vector3D> points;
    for (ifstream planeFile(filename, ios::in); planeFile >> p;) {
        points.push_back(p);
    }
    return points;
}

struct PointAndDistanceFromPlane {
    Vector3D point;
    double distanceFromPlane;
};

ostream& operator<<(ostream& out, const PointAndDistanceFromPlane& rhs) {
    return out << rhs.point.x << ", " << rhs.point.y << ", " << rhs.point.z << ", " << rhs.distanceFromPlane;
}

struct DistanceComparator {
    bool operator()(const PointAndDistanceFromPlane& lhs, const PointAndDistanceFromPlane& rhs) {
        return lhs.distanceFromPlane < rhs.distanceFromPlane;
    }
};

int main() {
    try {
        Plane plane(readPointsFromFile("data/PlanePoints.csv"));

        ofstream projectionsFile("data/Projections.csv", ios::out);

        std::set<PointAndDistanceFromPlane, DistanceComparator> sortedPoints;
        for (auto& p: readPointsFromFile("data/Points.csv")) {
            Vector3D projection = plane.projectionOf(p);
            double distance = length(projection - p);
            sortedPoints.emplace(PointAndDistanceFromPlane{projection, distance});
            projectionsFile << projection << endl;
        }

        ofstream orderedProjectionsFile("data/OrderedProjections.csv", ios::out);
        for (auto& p : sortedPoints) {
            orderedProjectionsFile << p << endl;
        }

        return 0;
    } catch (std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}