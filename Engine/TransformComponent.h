#pragma once
#define _USE_MATH_DEFINES
#include "BaseComponent.h"
#include "Vector2.hpp"
#include <math.h>
class TransformComponent :
	public BaseComponent
{
public:
    TransformComponent(Vector2 i_position) : m_Position(i_position) {}
    Vector2 GetPosition() const { return m_Position; };
    Vector2 SetPosition(const Vector2& i_Position) {
        m_Position = i_Position;
        return m_Position;
    };
    inline void SetRotation(float i_degree) { m_RotRadians = i_degree * (float)M_PI / 180.f; }
    inline float GetRotRad() const { return m_RotRadians; }
    inline float GetRotDeg() const { return m_RotRadians * 180.f / (float)M_PI; }
    Vector2 Move(const Vector2& i_Move) {
        m_Position += i_Move;
        return m_Position;
    };
private:
    Vector2 m_Position;
    float m_RotRadians;
};

