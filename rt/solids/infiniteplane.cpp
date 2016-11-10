#include "infiniteplane.h"
#include<core/assert.h>
#include<rt/bbox.h>

namespace rt
{
	InfinitePlane::InfinitePlane(const Point & origin, const Vector & normal, CoordMapper * texMapper, Material * material)
	{
		this->origin = origin;
		this->normal = normal;
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox InfinitePlane::getBounds() const
	{
		NOT_IMPLEMENTED;
	}

	Intersection InfinitePlane::intersect(const Ray & ray, float previousBestDistance) const
	{
		float denom = dot(normal, ray.d);
		if (std::abs(denom) > 1e-6) 
		{
			float currentDistance = dot(origin - ray.o, normal) / denom;
			if (currentDistance < previousBestDistance && currentDistance > 0)
			{
				Intersection intersect = Intersection(currentDistance, ray, this, normal);
				intersect.SetLocalIntersectingPoint((ray.getPoint(currentDistance) - origin));
				return intersect;
			}
		}

		return Intersection();
	}

	Point InfinitePlane::sample() const
	{
		NOT_IMPLEMENTED;
	}

	float InfinitePlane::getArea() const
	{
		return FLT_MAX;
	}
}