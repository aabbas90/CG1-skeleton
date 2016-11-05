#include "triangle.h"
#include "infiniteplane.h"

namespace rt
{
	Triangle::Triangle(Point vertices[3], CoordMapper * texMapper, Material * material)
	{
		this->v1 = vertices[0];
		this->v2 = vertices[1];
		this->v3 = vertices[2];
		this->texMapper = texMapper;
		this->material = material;
	}

	Triangle::Triangle(const Point & v1, const Point & v2, const Point & v3, CoordMapper * texMapper, Material * material)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
		this->texMapper = texMapper;
		this->material = material;
	}

	Intersection Triangle::intersect(const Ray & ray, float previousBestDistance) const
	{
		Vector v1v2 = v2 - v1;
		Vector v1v3 = v3 - v1;
		Vector normalVector = cross(v1v2, v1v3);
		float fullArea = normalVector.length() / 2;

		InfinitePlane plane = InfinitePlane(v1, normalVector, texMapper, material);
		Intersection intersectionObject = plane.intersect(ray, previousBestDistance);

		if (intersectionObject)
		{
			Point p = intersectionObject.hitPoint();


			Vector v3v2 = v3 - v2;
			Vector pv2 = p - v2;

			Vector v3v2pNormal = cross(v3v2, pv2);
			float u = (v3v2pNormal.length() / 2) / fullArea;
			if (dot(normalVector, v3v2pNormal) < 0)
				return Intersection();

			Vector v1v3 = v1 - v3;
			Vector pv3 = p - v3;
			Vector v1v3pNormal = cross(v1v3, pv3);
			float v = (v1v3pNormal.length() / 2) / fullArea;
			if (dot(normalVector, v1v3pNormal) < 0)
				return Intersection();

			intersectionObject.SetLocalIntersectingPoint(u * v1 + v * v2 + (1 - u - v) * v3);
		}

		return intersectionObject;
	}

	float Triangle::getArea() const
	{
		Vector v1v2 = v2 - v1;
		Vector v1v3 = v3 - v1;
		Vector normalVector = cross(v1v2, v1v3);
		return normalVector.length() / 2;
	}
}