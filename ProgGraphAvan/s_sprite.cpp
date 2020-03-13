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

int S_Sprite::GetStrokeTypeIndex() const
{
    return (int)strokeStyle;
}

void S_Sprite::SettrokeTypeIndex(int num)
{
    strokeStyle = (STROKE_STYLE)num;
}
