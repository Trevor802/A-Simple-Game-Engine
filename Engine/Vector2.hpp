//
//  Vector2.hpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once
#include <iostream>
#include <math.h>
#include <assert.h>
#include "Numeric.h"
#include "BasicTypes.h"

class Vector2 {
public:
    float x;
    float y;
    
    Vector2(float x=0, float y=0):x(x),y(y)
    {
        assert(!isnan(x));
        assert(!isnan(y));
    }
    
    inline Vector2 operator-() const;

    inline Vector2 operator+(const Vector2& a) const;
    
    inline Vector2& operator+=(const Vector2& a);
    
    inline Vector2 operator-(const Vector2& a) const;
    
    inline Vector2& operator-=(const Vector2& a);
    
    inline Vector2 operator*(const float a) const;

    inline Vector2& operator*=(const float a);

    inline Vector2 operator/(const float a) const;

    inline Vector2& operator/=(const float a);

    inline bool operator==(const Vector2& a) const;

    inline float Magnitude() const;

    inline float SqrMagnitude() const;

    const float DotProduct(const Vector2& i_rhs) const;

    inline Vector2 Normalize() const;

    inline char* ToString() const;

    inline bool IsZero(float i_val) const;

    inline Vector2 Clamp(float MaxMagnitude) const;

    inline GLib::Point2D ToPoint2D() const;
    
    static bool InArray(const Vector2 array[], const int size, const Vector2 v);
    
    static Vector2 RandInArea(const float width, const float height);
    
    static Vector2 RandDir();
    
    static Vector2 Clamp(const Vector2& a, const Vector2& min_v, const Vector2& max_v);

    static float Dot(const Vector2& i_lhs, const Vector2& i_rhs);
    
    bool clamp(const Vector2& min_v, const Vector2& max_v);

    friend Vector2 operator*(const float i_scalar, const Vector2& i_vec);

    friend std::ostream& operator<<(std::ostream& o, const Vector2 v);
};

inline Vector2 operator*(const float i_scalar, const Vector2& i_vec) {
    return Vector2(i_scalar * i_vec.x, i_scalar * i_vec.y);
}
#include "Vector2-inl.hpp"
