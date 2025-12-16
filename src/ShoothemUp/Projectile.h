#pragma once
#include "Rectangle.h"
#include "Circle.h"

class Projectile : public Rectangle
{
    public:
        int Damage;
        float Speed;
        Vector2f Position;

        Projectile(int width, int height);
};