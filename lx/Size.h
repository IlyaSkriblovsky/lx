#ifndef __LX__SIZE_H
#define __LX__SIZE_H

#include "Point.h"

namespace lx
{

class Size
{
    public:
        Size(): w(0), h(0) { }

        Size(int w, int h): w(w), h(h) { }

        int w;
        int h;

        Point toPoint() const { return Point(w, h); }


        bool operator == (const Size& other) const
        {
            return w == other.w && h == other.h;
        }

        bool operator != (const Size& other) const
        {
            return w != other.w || h != other.h;
        }


        Size swapped() const
        {
            return Size(h, w);
        }




        void print() const
        {
            printf("Size(%d, %d)\n", w, h);
        }
};

}

#endif
