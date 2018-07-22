#include "point.h"
#include <algorithm>
#include "vector.h"
#include "float4.h"

namespace rt
{
	Point Point::operator+(const Point & b) const
	{
		return Point(this->x + b.x, this->y + b.y, this->z + b.z);
	}

	Vector Point::operator-(const Point & b) const
	{
		return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
	}

	bool Point::operator==(const Point & b) const
	{
		return (this->x == b.x && this->y == b.y && this->z == b.z) ? 1 : 0;
	}

	bool Point::operator!=(const Point & b) const
	{
		return (this->x != b.x || this->y != b.y || this->z != b.z) ? 1 : 0;
	}

	Point operator*(float scalar, const Point & b)
	{
		return Point(b.x * scalar, b.y * scalar, b.z * scalar);
	}

	Point operator*(const Point & a, float scalar)
	{
		return scalar * a;
	}

	Point min(const Point & a, const Point & b)
	{
		float minX = std::fminf(a.x, b.x);
		float minY = std::fminf(a.y, b.y);
		float minZ = std::fminf(a.z, b.z);

		return Point(minX, minY, minZ);
	}

	Point max(const Point & a, const Point & b)
	{
		return Point(a.x > b.x ? a.x : b.x,
					 a.y > b.y ? a.y : b.y,
					 a.z > b.z ? a.z : b.z);
	}

	std::ostream& operator<<(std::ostream& os, const Point& pt)
	{
	    os << "POINT x:" << pt.x << " y:" << pt.y << " z:" << pt.z;
	    return os;
	}

	Point::Point(const Float4& f4)
	{
		if(f4.w != 0.0f)
		{
			this->x = f4.x / f4.w;
			this->y = f4.y / f4.w;
			this->z = f4.z / f4.w;
		}
		else
		{
			this->x = f4.x;
			this->y = f4.y;
			this->z = f4.z;
		}
	}
}

