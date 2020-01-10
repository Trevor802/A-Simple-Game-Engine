//
//  ActorManager.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include "MonsterManager.hpp"

Monster* MonsterManager::spawn(const Vector2D& pos) {
    return spawn(pos, this->name + "_" + to_string(actorsCount));
}

Monster* MonsterManager::spawn(const Vector2D& pos, const string name) {
    if (actorsCount + 1 > MAX_MONSTERS) return nullptr;
    Monster* monster = new Monster(pos, name, DEATH_TURNS);
    MonsterController* monsterController = new MonsterController(grid, MovingStrategy::ChasePlayer);
    monsterController->SetActor(monster);
    if (m_pPlayer){
        monsterController->SetTarget(m_pPlayer);
    }
    m_Controllers[actorsCount] = monsterController;
    actorsCount++;
    cout << "Spawned " << monster->name << " at " << monster->GetPosition() << endl;
    return monster;
}

MonsterManager::~MonsterManager() {
    for (int i = 0; i < MAX_MONSTERS; i++) {
        delete m_Controllers[i];
    }
    delete [] m_Controllers;
}

MonsterManager::MonsterManager(const string name, const int initCount, const Grid& grid) {
    this->name = name;
    this->grid = grid;
    actorsCount = initCount;
    for (int i = 0; i < initCount; i++) {
        Monster* pMonster = new Monster(grid.origin + Vector2D::RandInArea(grid.width, grid.height),
                                   name + "_" + to_string(i), DEATH_TURNS);
        m_Controllers[i] = new MonsterController(grid, MovingStrategy::Random);
        m_Controllers[i]->SetActor(pMonster);
    }
}

void MonsterManager::update() {
    // Move monsters
    for (int i = 0; i < actorsCount; i++) {
        m_Controllers[i]->Update();
    };
    // Create monsters
    Vector2D* grids = new Vector2D[this->grid.width * this->grid.height];
    int overlappingCount = 0;
    for (int i = 0; i < actorsCount - 1; i++) {
        for (int j = i + 1; j < actorsCount; j++) {
            if (m_Controllers[i]->GetMonster()->GetPosition() == m_Controllers[j]->GetMonster()->GetPosition()){
                overlappingCount++;
            }
        }
    }
    delete[] grids;
    for (int i = 0; i < overlappingCount; i++){
        spawn(grid.origin + Vector2D::RandInArea(grid.width, grid.height));
    }
}

void MonsterManager::SetPlayer(Actor *i_pPlayer){
    m_pPlayer = i_pPlayer;
    for (int i = 0; i < actorsCount; i++) {
        m_Controllers[i]->SetTarget(i_pPlayer);
    }
}
