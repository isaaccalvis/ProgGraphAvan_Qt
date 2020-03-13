#ifndef S_SPRITE_H
#define S_SPRITE_H

#include <QColor>

enum SHAPE_TYPE
{
    CIRCLE,
    QUAD
};

enum STROKE_STYLE
{
    SOLID,
    DASHED
};

class S_Sprite
{
public:
    S_Sprite();

    int GetTypeIndex() const;
    void SetTypeIndex(int num);

    int GetStrokeTypeIndex() const;
    void SettrokeTypeIndex(int num);

public:
    // Shape
    SHAPE_TYPE type = CIRCLE;
    // Material
    int strokeThickness = 1;
    QColor strokeColor = Qt::white;
    STROKE_STYLE strokeStyle = STROKE_STYLE::SOLID;
    QColor fillColor = Qt::white;

};

#endif // S_SPRITE_H
