#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "s_transform.h"
#include "s_sprite.h"

class GameObject
{
public:
    GameObject();
    GameObject(int num);

public:
    S_Transform transform;
    S_Sprite sprite;

    int GetId() const;
    void SetId(int id);

private:
    int num = -1;

public:
    QString name = "Entity";
};

#endif // GAMEOBJECT_H
