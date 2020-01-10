//
//  Grid.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#include "Grid.hpp"

Grid::~Grid(){
    
}

Vector2D Grid::move(const Vector2D& start, const Vector2D& offset){
    return Vector2D::Clamp(start+offset, origin, origin+size);
}
