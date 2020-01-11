//
//  ActorManager.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//
#pragma once
#include <string>
#include "Vector2D.hpp"
#include "Monster.hpp"
#include "Grid.hpp"
#include "MonsterController.hpp"

#define MAX_MONSTERS 50

#define DEATH_TURNS 5
using namespace std;

class MonsterManager{
public:
    MonsterManager(const string name, const int initCount, const Grid& grid);
    ~MonsterManager();
    void update();
    Monster* spawn(const Vector2D& pos);
    Monster* spawn(const Vector2D& pos, const string name);
    void SetPlayer(GameObject* i_pPlayer);
private:
    void destroy(const int index);
    int actorsCount;
    string name;
    MonsterController** m_Controllers = new MonsterController*[MAX_MONSTERS]();
    Grid grid;
    GameObject* m_pPlayer;
};

