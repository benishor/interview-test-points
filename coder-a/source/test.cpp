#include "test.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace test;

PointProcessor::PointProcessor(const std::string& pointsFilename, const std::string& planeFilename)
{
	if (!loadPoints(pointsFilename))
	{
		cerr << "Error while loading points filename: " << pointsFilename << endl;
		return;
	}

	if (!loadPlane(planeFilename))
	{
		cerr << "Error while loading plane points filename: " << planeFilename << endl;
	}
}

bool PointProcessor::loadPoints(const std::string& pointsFilename)
{
	ifstream file;
	Point pt;
	char delim;

	file.open(pointsFilename);

	if (!file.is_open())
		return false;

	while (!file.eof())
	{
		file >> pt.x; file >> delim;
		file >> pt.y; file >> delim;
		file >> pt.z;
		
		if (!file.good())
			break;

		points.push_back(pt);
	}

	cout << "Loaded " << points.size() << " points" << endl;

	return true;
}

bool PointProcessor::loadPlane(const std::string& planeFilename)
{
	ifstream file;
	Point pt;
	char delim;
	int currentPointIndex = 0;

	file.open(planeFilename);

	if (!file.is_open())
		return false;

	while (!file.eof() && currentPointIndex < 3)
	{
		file >> pt.x; file >> delim;
		file >> pt.y; file >> delim;
		file >> pt.z;

		if (!file.good())
			break;

		plane.points[currentPointIndex++] = pt;
	}

	cout << "Loaded " << currentPointIndex << " plane points" << endl;

	plane.computeCoefficients();

	return true;
}

bool PointProcessor::saveProjectedPoints(const std::string& filename, SavePointsMode mode)
{
	ofstream file;

	file.open(filename);

	if (!file.is_open())
		return false;

	for (auto& pt : projectedPoints)
	{
		file << pt.point.x << "," << pt.point.y << "," << pt.point.z;

		if (mode == SavePointsMode::LocationAndDistance)
		{
			file << "," << pt.distanceToOriginalPoint;
		}

		file << std::endl;
	}

	cout << "Saved " << projectedPoints.size() << " points" << endl;

	return true;
}

void PointProcessor::computeProjectedPoints()
{
	// make room for the projected points array
	projectedPoints.resize(points.size());

	for (size_t i = 0, iCount = points.size(); i < iCount; i++)
	{
		auto& pt = points[i];
		auto& projPt = projectedPoints[i];
		
		projPt.point = plane.projectPoint(pt);
		projPt.distanceToOriginalPoint = projPt.point.getDistance(pt);
	}
}

void PointProcessor::sortProjectedPoints()
{
	auto sorterPred = [](const ProjectedPoint& a, const ProjectedPoint& b)
	{
		return a.distanceToOriginalPoint < b.distanceToOriginalPoint;
	};

	std::sort(projectedPoints.begin(), projectedPoints.end(), sorterPred);
}

void PointProcessor::clearData()
{
	points.clear();
	projectedPoints.clear();
}

int main(int argc, char** argv)
{
	std::string pointsFilename = "../../input_data/Points.csv";
	std::string planeFilename = "../../input_data/PlanePoints.csv";
	std::string projectedPointsFilename = "../../output_data/Projections.csv";
	std::string orderedPointsFilename = "../../output_data/OrderedProjections.csv";

	if (argc == 3)
	{
		pointsFilename = argv[1];
		planeFilename = argv[2];
		cout << "User provided filenames." << endl;
	}
	else if (argc == 2)
	{
		pointsFilename = argv[1];
		cout << "User provided points filename." << endl;
	}

	cout << "Processing points filename: " << pointsFilename <<  endl;
	cout << "Processing plane filename: " << planeFilename << endl;

	PointProcessor processor(pointsFilename, planeFilename);

	processor.computeProjectedPoints();
	processor.saveProjectedPoints(projectedPointsFilename, PointProcessor::SavePointsMode::LocationOnly);
	processor.sortProjectedPoints();
	processor.saveProjectedPoints(orderedPointsFilename, PointProcessor::SavePointsMode::LocationAndDistance);

	return 0;
}