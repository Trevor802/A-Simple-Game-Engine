//
//  Actor.cpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#pragma once
#include "GameObject.hpp"

GameObject::GameObject(void){
    
}

GameObject::~GameObject() {
	Release();

}

void GameObject::Update(float DeltaTime) {
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		(*it)->Update(DeltaTime);
	}
}

void GameObject::Release() {
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		(*it)->Release();
	}
}
