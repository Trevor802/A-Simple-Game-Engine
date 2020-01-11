//
//  MonsterController.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#pragma once
#include "IActorController.hpp"
#include "Monster.hpp"
#include "Grid.hpp"

enum MovingStrategy{
    ChasePlayer, Random
};

class MonsterController : public IActorController{
public:
    MonsterController(const Grid& i_Grid, const MovingStrategy& i_MovingStrategy = MovingStrategy::Random) : m_Grid(i_Grid), m_MovingStrategy(i_MovingStrategy){};
    ~MonsterController();
    void SetActor(GameObject *i_pActor) override;
    void SetTarget(GameObject* i_pPlayer) { m_pPlayer = i_pPlayer; }
    bool Update() override;
    Monster* GetMonster() const { return m_pMonster; }
    
private:
    Grid m_Grid;
    Monster *m_pMonster;
    GameObject* m_pPlayer;
    MovingStrategy m_MovingStrategy = MovingStrategy::Random;
    
    Vector2D chasingPlayerDirection() const;
    Vector2D randomMovingDirection() const;
};
