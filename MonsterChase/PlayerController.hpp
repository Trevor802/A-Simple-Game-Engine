//
//  IPlayerController.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once
#include "BaseComponent.h"
#include "Vector2.hpp"

class PlayerController : public BaseComponent{
public:
    void Update(float DeltaTime) override;
    inline void SetInput(Vector2 i_Input) { m_Input = i_Input; }

private:
    Vector2 m_Input;
};

