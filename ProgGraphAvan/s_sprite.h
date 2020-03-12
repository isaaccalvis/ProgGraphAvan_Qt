#ifndef S_SPRITE_H
#define S_SPRITE_H


enum SHAPE_TYPE
{
    CIRCLE,
    QUAD
};

class S_Sprite
{
public:
    S_Sprite();

    int GetTypeIndex() const;
    void SetTypeIndex(int num);

public:
    SHAPE_TYPE type = CIRCLE;
};

#endif // S_SPRITE_H
