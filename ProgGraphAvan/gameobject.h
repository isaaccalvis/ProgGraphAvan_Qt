#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "s_transform.h"
#include "s_sprite.h"

class GameObject
{
public:
    GameObject();

public:
    S_Transform transform;
    S_Sprite sprite;

private:
    int num = -1;
};

#endif // GAMEOBJECT_H
