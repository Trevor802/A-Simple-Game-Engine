//
//  IPlayerController.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once
#include "PlayerController.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.h"

void PlayerController::Update(float DeltaTime) {
    auto physicsComponent = gameObject->GetComponent<PhysicsComponent>();
    if (physicsComponent) {
        physicsComponent->AddForce(m_Input * 5000.0f);
    }
}
