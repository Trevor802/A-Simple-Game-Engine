//
//  GameObject.hpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once

#define _USE_MATH_DEFINES

#include <string>
#include "Vector2.hpp"
#include <vector>
#include "BaseComponent.h"
#include "SmartPtr.h"
#include <math.h>

using namespace std;

class GameObject{
public:
    GameObject(void);
    GameObject(Vector2 position, const string name) : m_Position(position), name(name), active(true){};
    virtual ~GameObject();
    virtual void Release();
    virtual void Update(float DeltaTime);
    string name;
    bool active;
    
private:
    Vector2 m_Position;
    float m_RotRadians;
    vector<StrongPtr<BaseComponent>> m_Components;
    
public:
    Vector2 GetPosition() const { return m_Position; };
    Vector2 SetPosition(const Vector2& i_Position) {
        m_Position = i_Position;
        return m_Position;
    };
    inline void SetRotation(float i_degree) { m_RotRadians = i_degree * (float)M_PI / 180.f; }
    inline float GetRotRad() const { return m_RotRadians; }
    inline float GetRotDeg() const { return m_RotRadians * 180.f / (float)M_PI; }
    Vector2 Move(const Vector2& i_Move) {
        m_Position += i_Move;
        return m_Position;
    };
    template <typename T>
    inline StrongPtr<T> AddComponent(StrongPtr<T>& i_pComponent);

    template <typename T>
    StrongPtr<T> GetComponent();
    template <typename T>
    bool HasComponent();

    // self weak reference
    WeakPtr<GameObject> self;
};

#include "GameObject-inl.h"
#include "GameObject-tmpl.h"