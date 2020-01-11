//
//  IActorController.hpp
//  Engine
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#pragma once
#include <stdio.h>
#include "GameObject.hpp"

class IActorController{
public:
    virtual void SetActor(GameObject* i_Actor) = 0;
    virtual bool Update() = 0;
};

