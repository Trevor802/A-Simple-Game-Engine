//
//  IPlayerController.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 12/23/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include "PlayerController.hpp"
#include <iostream>
#include <conio.h>

bool PlayerController::Update(float DeltaTime) {
    int input = _getch();
    Vector2D move;
    cout << "\n";
    if (input == 'q'){
        return false;
    }
    else{
        if (input == 'w'){
            move = m_Grid.move(m_Player->GetPosition(), Vector2D(0, 1));
        }
        else if (input == 's'){
            move = m_Grid.move(m_Player->GetPosition(), Vector2D(0, -1));
        }
        else if (input == 'a'){
            move = m_Grid.move(m_Player->GetPosition(), Vector2D(-1, 0));
        }
        else if (input == 'd'){
            move = m_Grid.move(m_Player->GetPosition(), Vector2D(1, 0));
        }
        cout << "Hero's position: " << m_Player->SetPosition(move) << endl;
    }
    return true;
}

PlayerController::~PlayerController(){
    
}
