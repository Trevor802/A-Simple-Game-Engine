//
//  Actor.hpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once

#include <string>
#include "Vector2D.hpp"

using namespace std;
class Actor{
public:
    Actor(void);
    Actor(Vector2D position, const string name) : m_Position(position), name(name), active(true){};
    virtual ~Actor();
    string name;
    bool active;
    
private:
    Vector2D m_Position;
    
public:
    Vector2D GetPosition() const { return m_Position; }
    Vector2D SetPosition(const Vector2D& i_Position) {
        m_Position = i_Position;
        return m_Position;
    }
    Vector2D Move(const Vector2D& i_Move){
        m_Position += i_Move;
        return m_Position;
    }
};


