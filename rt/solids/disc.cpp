#include "disc.h"
#include "infiniteplane.h"
namespace rt
{
	Disc::Disc(const Point & center, const Vector & normal, float radius, CoordMapper * texMapper, Material * material)
	{
		this->center = center;
		this->normal = normal;
		this->radius = radius;
		this->texMapper = texMapper;
		this->material = material;
	}

	Intersection Disc::intersect(const Ray & ray, float previousBestDistance) const
	{
		InfinitePlane plane = InfinitePlane(center, normal, texMapper, material);
		Intersection planeInt = plane.intersect(ray, previousBestDistance);
		
		if (planeInt)
		{
			Point intersectionPoint = planeInt.hitPoint();
			float distance2FromCentre = Vector(center - intersectionPoint).lensqr();

			if (distance2FromCentre < radius * radius)
			{
				return planeInt;
			}
		}

		return Intersection();
	}

	float Disc::getArea() const
	{
		return pi * radius * radius;
	}
}