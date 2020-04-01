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
#include "TransformComponent.h"
#include "SmartPtr.h"
#include <math.h>

using namespace std;

class GameObject{
public:
    GameObject(void);
    GameObject(Vector2 position, const string name);
    virtual ~GameObject();
    virtual void Release();
    virtual void Update(float DeltaTime);
    string name;
    bool active;
    StrongPtr<TransformComponent> transform;
    friend class TransformComponent;
    
private:
    vector<StrongPtr<BaseComponent>> m_Components;
    
public:
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