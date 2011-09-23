#ifndef __LX__POINT_H
#define __LX__POINT_H

#include <cstdio>

namespace lx
{


class Point
{
    public:
        Point(): x(0), y(0) { }
        Point(int x, int y): x(x), y(y) { }

        int x;
        int y;


        Point operator + (const Point& other) const
        {
            return Point(x + other.x, y + other.y);
        }

        Point& operator += (const Point& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }


        Point operator - (const Point& other) const
        {
            return Point(x - other.x, y - other.y);
        }

        Point& operator -= (const Point& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }


        bool operator == (const Point& other) const
        {
            return x == other.x && y == other.y;
        }



        void print() const
        {
            printf("Point(%d, %d)\n", x, y);
        }
};


}

#endif
