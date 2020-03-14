#ifndef UNDOREDOSYSTEM_H
#define UNDOREDOSYSTEM_H

#include <vector>
#include "gameobject.h"

#define BUCKET_SIZE 5

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
    ~UndoRedoSystem();

public:
    void AddGameObject(GameObject* go);
    void GoBack();
    void GoFront();

private:
    int FindPlace();
    void PrintBucket(int position);

private:
    std::vector<RecoveryGameObject*> recoveryBucket;
    unsigned int actualIndex = 0;
};

#endif // UNDOREDOSYSTEM_H
