#ifndef __LX__COLOR_H
#define __LX__COLOR_H

namespace lx
{

// RGB color with premultiplied alpha

class Color
{
    public:
        Color(unsigned int premultipliedRGBA)
        {
            _uint = premultipliedRGBA;
        }

        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255)
        {
            _uint =
                ((unsigned int)(alpha) << 24) |
                ((unsigned int)(r * alpha / 255) << 16) |
                ((unsigned int)(g * alpha / 255) <<  8) |
                ((unsigned int)(b * alpha / 255));
        }

        unsigned int uint() const { return _uint; }



        static const Color black;
        static const Color white;
        static const Color red;
        static const Color green;
        static const Color blue;
        static const Color transparent;


    private:
        unsigned int _uint;
};


}

#endif
