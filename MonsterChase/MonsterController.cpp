//
//  MonsterController.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include "MonsterController.hpp"
#include <iostream>

void MonsterController::SetActor(GameObject *i_Actor){
    m_pMonster = dynamic_cast<Monster*>(i_Actor);
}

bool MonsterController::Update(){
    if (!m_pMonster->active) return false;
    Vector2D dir;
    switch (m_MovingStrategy) {
        case MovingStrategy::ChasePlayer:
            dir = chasingPlayerDirection();
            break;
        default:
            dir = randomMovingDirection();
            break;
    }
    m_pMonster->SetPosition(m_Grid.move(m_pMonster->GetPosition(), dir));
    m_pMonster->consumeTurn();
    cout << m_pMonster->name << " moves to " << m_pMonster->GetPosition() << endl;
    return true;
}

MonsterController::~MonsterController(){
    delete m_pMonster;
}

Vector2D MonsterController::chasingPlayerDirection() const {
    Vector2D direction = m_pPlayer->GetPosition() - m_pMonster->GetPosition();
    if (direction.x != 0 && direction.y != 0){
        if (rand() % 2){
            direction.y = 0;
        }else{
            direction.x = 0;
        }
    }
    direction.clamp(Vector2D(-1, -1), Vector2D(2, 2));
    return direction;
}

Vector2D MonsterController::randomMovingDirection() const {
    return Vector2D::RandDir();
}
