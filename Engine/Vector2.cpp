//
//  Vector2D.cpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#define _USE_MATH_DEFINES

#include "Vector2.hpp"
#include <math.h>

bool Vector2::InArray(const Vector2 array[], const int size, const Vector2 v){
    for(int i = 0; i < size; i++){
        if (array[i] == v){
            return true;
        }
    }
    return false;
}

Vector2 Vector2::RandInArea(const float width, const float height){
    return Vector2((float)rand() / (float)RAND_MAX * width, (float)rand() / (float)RAND_MAX * height);
}

Vector2 Vector2::RandDir(){
    Vector2 v;
    double r = (double)rand() / RAND_MAX;
    v.x = (float)cos(2 * M_PI * r);
    v.y = (float)sin(2 * M_PI * r);
    return v;
}

Vector2 Vector2::Clamp(const Vector2& a, const Vector2& min_v, const Vector2& max_v) {
    Vector2 v = a;
    if (a.x < min_v.x)
        v.x = min_v.x;
    else if (a.x >= max_v.x)
        v.x = max_v.x - 1;
    if (a.y < min_v.y)
        v.y = min_v.y;
    else if (a.y >= max_v.y)
        v.y = max_v.y - 1;
    return v;
}

float Vector2::Dot(const Vector2& i_lhs, const Vector2& i_rhs)
{
    return i_lhs.x * i_rhs.x + i_lhs.y * i_rhs.y;
}

bool Vector2::clamp(const Vector2& min_v, const Vector2& max_v){
    if (x >= min_v.x && x < max_v.x && y >= min_v.y && y < max_v.y)
        return false;
    if (x < min_v.x)
        x = min_v.x;
    else if (x >= max_v.x)
        x = max_v.x - 1;
    if (y < min_v.y)
        y = min_v.y;
    else if (y >= max_v.y)
        y = max_v.y - 1;
    return true;
}

std::ostream& operator<<(std::ostream& o, const Vector2 v) {
    o << "x: " << v.x << " y: " << v.y;
    return o;
}
