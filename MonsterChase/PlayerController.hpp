//
//  IPlayerController.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once
#include "BaseComponent.h"
#include "Vector2D.hpp"

class PlayerController : public BaseComponent{
public:
    PlayerController() : BaseComponent() {};
    void Update(float DeltaTime) override;
    inline void SetInput(Vector2D i_Input) { m_Input = i_Input; }

private:
    Vector2D m_Input;
};

