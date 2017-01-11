#include <rt/primmod/bmap.h>
#include <rt/coordmappers/tmapper.h>
#include <rt/coordmappers/world.h>
#include <core/float4.h>


namespace rt
{
	BumpMapper::BumpMapper(Triangle * base, Texture * bumpmap, const Point & bv1, const Point & bv2, const Point & bv3, float vscale)
	{
		baseT = base;
		bMap = bumpmap;
		vScale = vscale;
		baseT->texMapper = new TriangleMapper(bv1, bv2, bv3);
		this->bv1 = bv1;
		this->bv2 = bv2;
		this->bv3 = bv3;

		
		//Compute how the texture base vectors ex,ey map to world space wx,wy.
		//worldX = //TODO

	}
	BBox BumpMapper::getBounds() const
	{
		return baseT->getBounds();
	}
	Intersection BumpMapper::intersect(const Ray & ray, float previousBestDistance) const
	{
		Intersection triangleInt = baseT->intersect(ray, previousBestDistance);
		
		if (triangleInt)
		{
			Point texturePoint = baseT->texMapper->getCoords(triangleInt);
			// gradient at the given texture coordinates
			float DX = bMap->getColorDX(texturePoint).grayscale();
			
			float DY = bMap->getColorDY(texturePoint).grayscale();
			
			//TODO, initialized to dummy values
			Vector worldX = Vector(1.0f, 0.0f, 0.0f);
			Vector worldY = Vector(0.0f, 1.0f, 0.0f);
			
			//perturb the normal in world space
			triangleInt.setNormal(triangleInt.normal() + DX * worldX + DY * worldY);	
		}
		return triangleInt;
	}
	void BumpMapper::setMaterial(Material * m)
	{
		baseT->setMaterial(m);
	}
	void BumpMapper::setCoordMapper(CoordMapper * cm)
	{
		baseT->setCoordMapper(cm);
	}
}
