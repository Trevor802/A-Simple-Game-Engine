//
//  MonsterController.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#pragma once
#include "MonsterController.hpp"
#include "Vector2D.hpp"
#include "SmartPtr.h"
#include "PhysicsComponent.h"

void MonsterController::Update(float DeltaTime){
    Vector2D dir = getMovingDirection();
    auto physicsComponent = gameObject->GetComponent<PhysicsComponent>();
    if (physicsComponent) {
        physicsComponent->AddForce(dir * 1000.0f);
    }
}

Vector2D MonsterController::getMovingDirection()
{
    Vector2D dir;
    switch (m_MovingStrategy) {
    case MovingStrategy::ChaseTarget:
        dir = m_Target->GetPosition() - gameObject->GetPosition();
        dir.Normalize();
        break;
    case MovingStrategy::Random:
        dir = Vector2D::RandDir();
        break;
    case MovingStrategy::Patrol:
        if (gameObject->GetPosition().x > 200.0f)
            dir = -1;
        else if (gameObject->GetPosition().x < 160.0f)
            dir = 1;
        break;
    case MovingStrategy::Invalid:
        throw invalid_argument("Invalid enum");
        break;
    default:
        break;
    }
    return dir;
}

