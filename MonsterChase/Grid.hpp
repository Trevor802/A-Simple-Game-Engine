//
//  Grid.hpp
//  GhostChaser
//
//  Created by Trevor Alex on 9/8/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include "Vector2D.hpp"

class Grid{
public:
    Grid(){};
    Grid(const int x, const int y, const int width, const int height) : x(x), y(y), width(width), height(height), origin(Vector2D(x, y)), size(Vector2D(width, height)){};
    ~Grid();
    int x, y, width, height;
    Vector2D origin, size;
    Vector2D move(const Vector2D& start, const Vector2D& offset);
};

#endif /* Grid_hpp */
