#include "intersection.h"
#include <core/assert.h>
#include <iostream>

namespace rt
{
	Intersection Intersection::failure()
	{
		return Intersection();
	}

	Intersection::Intersection(float distance, const Ray & ray, const Solid * solid, const Vector & normal)
	{
		this->distance = distance;

		// Normally the distance should always be positive!
		if (distance < 0)
		{
			std::cout << "Intersection distance less than zero!";
			throw;
		}

		this->ray = ray;
		this->solid = solid;
		this->normalVector = normal;
		this->intersectionPoint = ray.getPoint(distance);
		foundIntersection = true;
	}

	Point Intersection::hitPoint() const
	{
		return intersectionPoint;
	}

	Vector Intersection::normal() const
	{
		return normalVector;
	}

	Point Intersection::local() const
	{
		NOT_IMPLEMENTED;
	}

	Intersection::operator bool()
	{
		return foundIntersection;
	}
}
