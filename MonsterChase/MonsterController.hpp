//
//  MonsterController.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#pragma once
#include "BaseComponent.h"
#include "GameObject.hpp"
#include "SmartPtr.h"
#include "Vector2D.hpp"
#include "json.hpp"

enum MovingStrategy{
    ChaseTarget, 
    Random, 
    Patrol,
    Invalid = -1
};

NLOHMANN_JSON_SERIALIZE_ENUM(MovingStrategy, {
    {ChaseTarget, "ChaseTarget"},
    {Random, "Random"},
    {Patrol, "Patrol"},
    {Invalid, nullptr}
})

class MonsterController : public BaseComponent{
public:
    MonsterController(MovingStrategy i_MovingStrategy = MovingStrategy::Random) : BaseComponent() { 
        m_MovingStrategy = i_MovingStrategy; };
    void Update(float DeltaTime) override;
    inline void SetMovingStrategy(MovingStrategy i_MovingStrategy) { m_MovingStrategy = i_MovingStrategy; }
    inline void SetTarget(StrongPtr<GameObject> i_Target) { m_Target = i_Target; }

private:
    Vector2D getMovingDirection();
    MovingStrategy m_MovingStrategy = MovingStrategy::Random;
    WeakPtr<GameObject> m_Target;
};
