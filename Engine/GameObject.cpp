//
//  Actor.cpp
//  Engine
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject(void){
    
}

GameObject::~GameObject() {
    
}

void GameObject::Update(float DeltaTime) {
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->get()->Update(DeltaTime);
	}
}
