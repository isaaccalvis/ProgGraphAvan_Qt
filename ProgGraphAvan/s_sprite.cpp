#include "s_sprite.h"

S_Sprite::S_Sprite()
{

}

int S_Sprite::GetTypeIndex() const
{
    return (int)type;
}

void S_Sprite::SetTypeIndex(int num)
{
    type = (SHAPE_TYPE)num;
}
