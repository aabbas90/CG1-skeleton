#include "castingdist.h"
#include <core/vector.h>
#include <rt/intersection.h>

namespace rt
{
	float MAX_DIST2 = 10000000;

	RayCastingDistIntegrator::RayCastingDistIntegrator(World * world, const RGBColor & nearColor, float nearDist, const RGBColor & farColor, float farDist)
	{
		this->world = world;
		this->nearColor = nearColor;
		this->nearDist = nearDist;
		this->farColor = farColor;
		this->farDist = farDist;
	}

	RGBColor RayCastingDistIntegrator::getRadiance(const Ray & ray) const
	{
		Intersection intersection = this->world->scene->intersect(ray, MAX_DIST2);
		RGBColor colorValue = RGBColor(0, 0, 0);
		if (intersection)
		{
			colorValue = (intersection.distance - nearDist) * farColor / (farDist - nearDist) + (farDist - intersection.distance) * nearColor / (farDist - nearDist);
			colorValue = colorValue * abs(dot(intersection.normal(), ray.d));
		}
		return colorValue;
	}
}
