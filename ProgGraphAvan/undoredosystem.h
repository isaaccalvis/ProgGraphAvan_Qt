#ifndef UNDOREDOSYSTEM_H
#define UNDOREDOSYSTEM_H

#include <vector>
#include "gameobject.h"

#include "inspector.h"

#define BUCKET_SIZE 5

class SceneWidget;

class RecoveryGameObject
{
public:
    RecoveryGameObject();
    ~RecoveryGameObject();

public:
    GameObject copy_gameObject;
    GameObject* original_gameObject = nullptr;

public:
    bool isUsed = false;
};

class UndoRedoSystem
{
public:
    UndoRedoSystem();
    UndoRedoSystem(SceneWidget* scene);
    ~UndoRedoSystem();

    void AddGameObject(GameObject* go);
    void GoBack();
    void GoFront();

private:
    int FindPlace();
    void PrintBucket();

private:
    std::vector<RecoveryGameObject*> recoveryBucket;
    unsigned int actualIndex = 0;

public:
    SceneWidget* scene = nullptr;
};

#endif // UNDOREDOSYSTEM_H
