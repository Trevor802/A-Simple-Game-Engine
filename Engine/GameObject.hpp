//
//  GameObject.hpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once

#include <string>
#include "Vector2D.hpp"
#include <vector>
#include "BaseComponent.h"
using namespace std;

class GameObject{
public:
    GameObject(void);
    GameObject(Vector2D position, const string name) : m_Position(position), name(name), active(true){};
    virtual ~GameObject();
    virtual void Update();
    string name;
    bool active;
    
private:
    Vector2D m_Position;
    vector<unique_ptr<BaseComponent>> m_Components;
    
public:
    Vector2D GetPosition() const { return m_Position; };
    Vector2D SetPosition(const Vector2D& i_Position) {
        m_Position = i_Position;
        return m_Position;
    };
    Vector2D Move(const Vector2D& i_Move) {
        m_Position += i_Move;
        return m_Position;
    };
    template <typename T>
    inline T* AddComponent(T* i_pComponent);
};

#include "GameObject-inl.h"