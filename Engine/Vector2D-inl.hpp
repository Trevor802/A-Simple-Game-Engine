//
//  Vector2D-inl.hpp
//  Engine
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#ifndef Vector2D_inl_hpp
#define Vector2D_inl_hpp

inline bool Vector2D::operator==(const Vector2D& a) const {
    return (this->x == a.x && this->y == a.y);
}

inline Vector2D Vector2D::operator+(const Vector2D& a) const {
    return Vector2D{this->x+a.x, this->y+a.y};
}

inline Vector2D Vector2D::operator-(const Vector2D& a) const {
    return Vector2D{this->x-a.x, this->y-a.y};
}

inline Vector2D& Vector2D::operator+=(const Vector2D& a){
    this->x = x+a.x;
    this->y = y+a.y;
    return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& a){
    this->x = x-a.x;
    this->y = y-a.y;
    return *this;
}

#endif /* Vector2D_inl_hpp */
