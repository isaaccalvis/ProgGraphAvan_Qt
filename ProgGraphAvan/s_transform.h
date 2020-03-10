#ifndef S_TRANSFORM_H
#define S_TRANSFORM_H


class S_Transform
{
public:
    S_Transform();

public:
    float position[3] = {0.,0.,0.};
    float angle = 0.0f;
    float scale[2] = {1.,1.};
};

#endif // S_TRANSFORM_H
