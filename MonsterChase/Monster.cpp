//
//  Monster.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 9/9/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include "Monster.hpp"
#include <iostream>

Monster::Monster(const Vector2D& position, const string name, const int deathTurn) : GameObject(position, name){
    this->deathTurn = deathTurn;
    this->active = true;
}

void Monster::consumeTurn(){
    if (this->deathTurn-- <= 0){
        this->active = false;
        cout << "Destroyed " + name << endl;
    }
}

void Monster::setTurn(const int turn){
    deathTurn = turn;
}

int Monster::getTurn() const {
    return deathTurn;
}
