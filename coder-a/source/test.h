#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace test
{
//! A simple 3D point in space
struct Point
{
	float x, y, z;

	Point() {}
	Point(float newX, float newY, float newZ)
		: x(newX)
		, y(newY)
		, z(newZ)
	{}

	Point crossProduct(const Point& other)
	{
		return Point(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	float dotProduct(const Point& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	void normalize()
	{
		float m = x * x + y * y + z * z;

		if (m <= 0.00001f)
		{
			x = y = z = 0.0f;
			return;
		}

		m = sqrtf(m);
		x /= m;
		y /= m;
		z /= m;
	}

	float getDistance(const Point& to) const
	{
		float xx = x - to.x;
		float yy = y - to.y;
		float zz = z - to.z;
		const float epsilonValue = 0.00001f;

		xx = xx * xx + yy * yy + zz * zz;

		if (xx <= epsilonValue)
		{
			return 0.0f;
		}

		return sqrtf(xx);
	}

	Point operator - (const Point& other) const
	{
		return Point(x - other.x, y - other.y, z - other.z);
	}

	Point operator * (float value) const
	{
		return Point(x * value, y * value, z * value);
	}
};

//! A projected point on a plane
struct ProjectedPoint
{
	Point point; //<< projected point
	float distanceToOriginalPoint = 0.0f;
};

//! A simple plane, defined by 3 points in space
struct Plane
{
	Point points[3];
	Point origin;
	Point normal;
	float a = 0, b = 0, c = 0, d = 0;

	void computeCoefficients()
	{
		Point edge = points[2] - points[0];
		normal = edge.crossProduct(points[1] - points[0]);

		normal.normalize();
		origin = points[0];
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(a * origin.x + b * origin.y + c * origin.z);
	}

	Point projectPoint(const Point& point) const
	{
		return point - normal * (point - origin).dotProduct(normal);
	}
};

typedef std::vector<Point> PointArray;
typedef std::vector<ProjectedPoint> ProjectedPointArray;

//! Point processor class
class PointProcessor
{
public:
	//! The save to file points mode
	enum class SavePointsMode
	{
		LocationOnly, //<< save only the xyz location of the points
		LocationAndDistance //<< save xyz location along with the distance from original points to projected points
	};

	PointProcessor() {}
	//! create this class and its data directly from points file and plane definition file
	PointProcessor(const std::string& pointsFilename, const std::string& planeFilename);
	//! load the 3D points from a csv text file containing a list of 3 float values for each point
	//! \return true if loading was successful
	bool loadPoints(const std::string& pointsFilename);
	//! load the plane definition from a csv text file containing plane's 3D coordinates
	//! \return true if loading was successful
	bool loadPlane(const std::string& planeFilename);
	//! save the projected points to a csv file as a list of 3 float values for each point
	bool saveProjectedPoints(const std::string& filename, SavePointsMode mode);
	//! compute the projected points from the original ones
	void computeProjectedPoints();
	//! sort the projected points
	void sortProjectedPoints();
	//! clear all the data
	void clearData();

protected:
	Plane plane;
	PointArray points;
	ProjectedPointArray projectedPoints;
};

}