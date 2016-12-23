#include <rt/textures/imagetex.h>
#include <math.h>
#include <core/point.h>
#include <utility>  


namespace rt
{
    ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
    :image(image), bh(bh), i(i){}
    ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
    :bh(bh), i(i)
    {
        this->image.readPNG(filename);
    }
    std::pair <float,float> ImageTexture::getTextureCoordinates(const Point& coord) const
    {
        //Border Handling
        //Lattice Coordinates TODO: apply + BIG_POINT hack?
        int lu = floor(coord.x);
        int lv = floor(coord.y);

        //Fractional Coordinates
        float fu = coord.x - lu;
        float fv = coord.y - lv;

        switch(bh)
        {
            case REPEAT:
                        //let fractional coordinates be as is 
                        break;
            case MIRROR:
                        if(abs(lu) %2 == 1)
                            fu = 1 - fu;
                        if(abs(lv) %2 == 1)
                            fv = 1 - fv;
                        break;
            case CLAMP:
                        //clamp u to [0,1]
                        if(coord.x < 0) fu = 0;
                        else if(coord.x >= 1) fu = 1;
                        else fu = coord.x;

                        //clamp v to [0,1]
                        if(coord.y < 0) fv = 0;
                        else if(coord.y >= 1) fv = 1;
                        else fv = coord.y;
                        break;
        }
        return std::pair <float,float>(fu, fv);
    }
    RGBColor ImageTexture::getColor(const Point& coord)
    {
        auto tutv = getTextureCoordinates(coord);
        float tu = tutv.first;
        float tv = tutv.second;

        // Interpolation 
        float resU = image.width();
        float resV = image.width();

        //Local Coordinates 
        float u, v;
        
        //lattice coordinates
        float lu, lv;

        //Fractional Coordinates
        float fu, fv;

        switch(i)
        {
            case NEAREST:
                        //Local Coordinates #TODO pixel centered already?
                        u = tu * resU;
                        v = tv * resV;
                        
                        //lattice coordinates
                        lu = std::fmin(floor(u), resU - 1);
                        lv = std::fmin(floor(v), resV - 1);
                        return image(lu, lv);
            case BILINEAR:
                        //Local Coordinates #TODO node centered already?
                        u = tu * (resU - 1);
                        v = tv * (resV - 1);

                        //Fractional Coordinates
                        fu = u - floor(u);
                        fv = v - floor(v);
                        return (   (1 - fu) * (1 - fv) * image(floor(u), floor(v))
                                + ((1 - fu) * (    fv) * image(floor(u), floor(v) + 1 ))
                                + ((    fu) * (1 - fv) * image(floor(u) + 1, floor(v) ))
                                + ((    fu) * (    fv) * image(floor(u) + 1, floor(v) + 1 )));
        }
    }
    RGBColor ImageTexture::getColorDX(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    RGBColor ImageTexture::getColorDY(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
}