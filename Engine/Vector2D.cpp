//
//  Vector2D.cpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include "Vector2D.hpp"

bool Vector2D::InArray(const Vector2D array[], const int size, const Vector2D v){
    for(int i = 0; i < size; i++){
        if (array[i] == v){
            return true;
        }
    }
    return false;
}

Vector2D Vector2D::RandInArea(const int width, const int height){
    return Vector2D(rand() % width, rand() % height);
}

Vector2D Vector2D::RandDir(){
    Vector2D v;
    if (rand() < RAND_MAX / 2){
        if (rand() < RAND_MAX / 2){
            v.x = -1;
        }
        else{
            v.x = 1;
        }
    }
    else{
        if (rand() < RAND_MAX / 2){
            v.y = -1;
        }
        else{
            v.y = 1;
        }
    }
    return v;
}

Vector2D Vector2D::Clamp(const Vector2D& a, const Vector2D& min_v, const Vector2D& max_v) {
    Vector2D v = a;
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

bool Vector2D::clamp(const Vector2D& min_v, const Vector2D& max_v){
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

std::ostream& operator<<(std::ostream& o, const Vector2D v) {
    o << "x: " << v.x << " y: " << v.y;
    return o;
}
