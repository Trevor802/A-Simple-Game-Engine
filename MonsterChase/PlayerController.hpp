//
//  IPlayerController.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#ifndef IPlayerController_hpp
#define IPlayerController_hpp

#include "IActorController.hpp"
#include "Grid.hpp"

class PlayerController : public IActorController{
public:
    PlayerController(const Grid& i_Grid) { m_Grid = i_Grid; }
    ~PlayerController();
    void SetActor(GameObject* i_Actor) override { m_Player = i_Actor; }
    bool Update(float DeltaTime) override;
    
private:
    GameObject* m_Player;
    Grid m_Grid;
};

#endif /* IPlayerController_hpp */
