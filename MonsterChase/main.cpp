//
//  main.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 8/27/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <string>

#include "MonsterManager.hpp"
#include "Grid.hpp"
#include "PlayerController.hpp"

#define GRID_WIDTH 5
#define GRID_HEIGHT 5
using namespace std;


char * getName(){
    char temp[50];
    cin >> temp;
    char *pn = new char[strlen(temp) + 1];
    strcpy(pn, temp);
    return pn;
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(0));
    Grid grid = Grid(0, 0, GRID_WIDTH, GRID_HEIGHT);
    MonsterManager* monsterManager = new MonsterManager("Monster", 0, grid);
    cout << "Input initial monster numbers: ";
    int initMonster;
    cin >> initMonster;
    while (initMonster < 0 || initMonster > MAX_MONSTERS) {
        cout << "Invalid Number. Input initial monster numbers: ";
        cin >> initMonster;
    }
    for (int i = 0; i < initMonster; i++) {
        cout << "Input Monster " + to_string(i) + "'s Name: ";
        monsterManager->spawn(Vector2D::RandInArea(grid.width, grid.height), getName());
    }
    cout << "Input Player's Name: ";
    Actor* hero = new Actor(Vector2D(3, 4), getName());
    PlayerController* playerController = new PlayerController(grid);
    playerController->SetActor(hero);
    monsterManager->SetPlayer(hero);
    // loop
    bool update = true;
    while (update) {
        cout << "updating" << endl;
        update = playerController->Update();
        if (update){
            monsterManager->update();
        }
    };
    delete hero;
    delete monsterManager;
    delete playerController;
    return 0;
}
