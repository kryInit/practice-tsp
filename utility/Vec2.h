#ifndef VEC2_H
#define VEC2_H

#include <iostream>

struct Vec2 {
    int x, y;

    bool operator<( const Vec2& another ) const {
        return x == another.x ? y < another.y : x < another.x;
    }
    bool operator==( const Vec2& another ) const {
        return x == another.x && y == another.y;
    }
    bool operator!=( const Vec2& another ) const {
        return x != another.x || y != another.y;
    }

    Vec2() : x(0.), y(0.) {};
    Vec2(int _x, int _y) {x = _x, y = _y; }


    friend std::ostream &operator<<(std::ostream &out, const Vec2 &v) {
        out << '(' << v.x << "," << v.y << ')';
        return out;
    }
};

#endif
