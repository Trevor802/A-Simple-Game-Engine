//
//  Monster.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 9/9/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#ifndef Monster_hpp
#define Monster_hpp

#include "GameObject.hpp"

class Monster : public GameObject {
public:
    Monster(void){};
    Monster(const Vector2& position, const string name, const int deathTurn);
    void consumeTurn();
    void setTurn(const int turn);
    int getTurn() const;
private:
    int deathTurn;
};

#endif /* Monster_hpp */
