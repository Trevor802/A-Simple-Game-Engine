#include "Vector2.hpp"
//
//  Vector2D-inl.hpp
//  Engine
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#ifndef Vector2_inl_hpp
#define Vector2_inl_hpp

inline char* Vector2::ToString() const 
{
    char buffer[32];
    sprintf_s(buffer, 32, "x:%f,y:%f\n", x, y);
    return buffer;
}

inline bool Vector2::IsZero(float i_val) const
{
    return Engine::Numeric::AreEqual(i_val, 0, FLT_EPSILON);
}

inline bool Vector2::operator==(const Vector2& a) const {
    return (this->x == a.x && this->y == a.y);
}

inline float Vector2::Magnitude() const
{
    return sqrt(x * x + y * y);
}

inline float Vector2::SqrMagnitude() const 
{
    return x * x + y * y;
}

inline Vector2 Vector2::Normalize() const
{
    return Vector2( IsZero(x) ? 0 : x / Magnitude(), IsZero(y) ? 0 : y / Magnitude());
}

inline Vector2 Vector2::Clamp(float MaxMagnitude) const
{
    if (Magnitude() > MaxMagnitude)
        return Normalize() * MaxMagnitude;
    return *this;
}

inline Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

inline Vector2 Vector2::operator+(const Vector2& a) const {
    return Vector2{this->x+a.x, this->y+a.y};
}

inline Vector2 Vector2::operator-(const Vector2& a) const {
    return Vector2{this->x-a.x, this->y-a.y};
}

inline Vector2& Vector2::operator+=(const Vector2& a){
    this->x = x+a.x;
    this->y = y+a.y;
    return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& a){
    this->x = x-a.x;
    this->y = y-a.y;
    return *this;
}

inline Vector2 Vector2::operator*(const float a) const {
    return Vector2{ this->x * a, this->y * a };
}

inline Vector2& Vector2::operator*=(const float a) {
    this->x = x * a;
    this->y = y * a;
    return *this;
}

inline Vector2 Vector2::operator/(const float a) const {
    return Vector2{ this->x / a, this->y / a };
}

inline Vector2& Vector2::operator/=(const float a) {
    this->x = x / a;
    this->y = y / a;
    return *this;
}

inline GLib::Point2D Vector2::ToPoint2D() const {
    return GLib::Point2D{ this->x, this->y };
}

#endif /* Vector2_inl_hpp */
