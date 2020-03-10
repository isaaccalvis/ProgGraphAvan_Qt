#include "gameobject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(int num)
{
    this->num = num;
}

int GameObject::GetId() const
{
    return num;
}

void GameObject::SetId(int id)
{
    num = id;
}
