#include <rt/textures/perlin.h>
#include <core/point.h>
#include <core/interpolate.h>
#include <core/scalar.h>

namespace rt 
{

    /* returns a value in range -1 to 1 */
    float noise(int x, int y, int z) 
    {
        int n = x + y * 57 + z * 997;
        n = (n<<13) ^ n;
        return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }
 

    PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
        :white(white), black(black) {}

    void PerlinTexture::addOctave(float amplitude, float frequency)
    {

    }
    RGBColor PerlinTexture::getColor(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    RGBColor PerlinTexture::getColorDX(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    RGBColor PerlinTexture::getColorDY(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }


}
