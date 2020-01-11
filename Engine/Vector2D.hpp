//
//  Vector2D.hpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once
#include <iostream>

class Vector2D {
public:
    float x;
    float y;
    
    Vector2D(float x=0, float y=0):x(x),y(y)
    {
        
    }
    
    inline Vector2D operator+(const Vector2D& a) const;
    
    inline Vector2D& operator+=(const Vector2D& a);
    
    inline Vector2D operator-(const Vector2D& a) const;
    
    inline Vector2D& operator-=(const Vector2D& a);
    
    inline Vector2D operator*(const float a) const;

    inline Vector2D& operator*=(const float a);

    inline bool operator==(const Vector2D& a) const;
    
    static bool InArray(const Vector2D array[], const int size, const Vector2D v);
    
    static Vector2D RandInArea(const float width, const float height);
    
    static Vector2D RandDir();
    
    static Vector2D Clamp(const Vector2D& a, const Vector2D& min_v, const Vector2D& max_v);
    
    bool clamp(const Vector2D& min_v, const Vector2D& max_v);
    
    friend std::ostream& operator<<(std::ostream& o, const Vector2D v);
};

#include "Vector2D-inl.hpp"
