#ifndef __LX__RECT_H
#define __LX__RECT_H

#include "Point.h"
#include "Size.h"

namespace lx
{

class Rect
{
    public:
        Rect(): origin(0, 0), size(0, 0) { }
        Rect(const Point& origin, const Size& size): origin(origin), size(size) { }
        Rect(int x, int y, int w, int h): origin(x, y), size(w, h) { }

        Point origin;
        Size size;

        int x() const { return origin.x; }
        int y() const { return origin.y; }
        int w() const { return size.w; }
        int h() const { return size.h; }

        const Point bottomRight() const { return origin + size.toPoint(); }


        Rect operator + (const Point& offset) const
        {
            return Rect(origin + offset, size);
        }

        Rect operator - (const Point& offset) const
        {
            return Rect(origin - offset, size);
        }

        bool operator == (const Rect& other) const
        {
            return origin == other.origin && size == other.size;
        }

        bool operator != (const Rect& other) const
        {
            return origin != other.origin || size != other.size;
        }


        Rect combine(const Rect& other) const
        {
            Point br = bottomRight();
            Point br2 = other.bottomRight();

            Point neworigin = origin;

            if (neworigin.x > other.origin.x) neworigin.x = other.origin.x;
            if (neworigin.y > other.origin.y) neworigin.y = other.origin.y;

            if (br.x < br2.x) br.x = br2.x;
            if (br.y < br2.y) br.y = br2.y;

            return Rect(neworigin, Size(br.x - neworigin.x, br.y - neworigin.y));
        }

        bool intersects(const Rect& other) const
        {
            if (origin.x + size.w <= other.origin.x) return false;
            if (origin.x >= other.origin.x + other.size.w) return false;
            if (origin.y + size.h <= other.origin.y) return false;
            if (origin.y >= other.origin.y + other.size.h) return false;
            return true;
        }

        Rect intersect(const Rect& other) const
        {
            Point br = bottomRight();
            Point br2 = other.bottomRight();

            Point neworigin = origin;

            if (neworigin.x < other.origin.x) neworigin.x = other.origin.x;
            if (neworigin.y < other.origin.y) neworigin.y = other.origin.y;

            if (br.x > br2.x) br.x = br2.x;
            if (br.y > br2.y) br.y = br2.y;

            return Rect(neworigin,  Size(br.x - neworigin.x, br.y - neworigin.y));
        }


        bool contains(const Point& point) const
        {
            return (origin.x <= point.x) && (origin.y <= point.y) && (origin.x + size.w > point.x) && (origin.y + size.h > point.y);
        }



        void print() const
        {
            printf("Rect([%d,%d], [%d,%d])\n", origin.x, origin.y, size.w, size.h);
        }
};

}

#endif
