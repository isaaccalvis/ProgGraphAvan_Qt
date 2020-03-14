#include "undoredosystem.h"

// =================    Recovery GameObject class   =================

RecoveryGameObject::RecoveryGameObject()
{
    isUsed = false;
}

RecoveryGameObject::~RecoveryGameObject()
{

}

// =================        UndoRedoSystem          =================

UndoRedoSystem::UndoRedoSystem()
{
    recoveryBucket.resize(BUCKET_SIZE);
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        recoveryBucket[i] = new RecoveryGameObject();
    }
}

UndoRedoSystem::~UndoRedoSystem()
{
    recoveryBucket.clear();
}

void UndoRedoSystem::AddGameObject(GameObject* go)
{
    if (go != nullptr)
    {
        int position = FindPlace();
        // Copy Game Object
        recoveryBucket[position]->original_gameObject = go;
        recoveryBucket[position]->copy_gameObject = *go;

        // Comprobacions
        int *FillColorBlue;
        recoveryBucket[position]->copy_gameObject.sprite.fillColor.getRgb(nullptr,nullptr,FillColorBlue,nullptr);
        qDebug("Index = %i, TransformZ = %d, Shape = %i, ColorFillB = %i",
               position,
               recoveryBucket[position]->copy_gameObject.transform.position[2],
               recoveryBucket[position]->copy_gameObject.sprite.GetStrokeTypeIndex(),
               *FillColorBlue);
    }
}

int UndoRedoSystem::FindPlace()
{
    int position = -1;
    for (int i = 0; i < recoveryBucket.size(); i++)
    {
        if (!recoveryBucket[i]->isUsed)
        {
            position = i;
            break;
        }
    }
    if (position == -1) // In this case vector is full
    {
        // Clear last element
        delete recoveryBucket[0];
        recoveryBucket[0] = new RecoveryGameObject();
        // Move all elements
        for (int i = 1; i < BUCKET_SIZE; i++)
        {
            recoveryBucket[i] = recoveryBucket[i - 1];
        }
        // Return last position
        position = BUCKET_SIZE - 1;
    }
    return position;
}
