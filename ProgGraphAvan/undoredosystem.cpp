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
        //recoveryBucket[position]->copy_gameObject.transform.position[0] = go->transform.position[0];
        //recoveryBucket[position]->copy_gameObject.transform.position[1] = go->transform.position[1];
        //recoveryBucket[position]->copy_gameObject.transform.position[2] = go->transform.position[2];


        // Comprobacions
        int *FillColorBlue;
        recoveryBucket[position]->copy_gameObject.sprite.fillColor.getRgb(nullptr,nullptr,FillColorBlue,nullptr);
        qDebug("Index = %i, TransformZ = %f, Shape = %i, ColorFillB = %i",
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
            recoveryBucket[position]->isUsed = true;
            break;
        }
    }
    if (position == -1) // In this case vector is full
    {
        RecoveryGameObject* firstAux = recoveryBucket[0];
        // Move all elements
        for (int i = 1; i < BUCKET_SIZE; i++)
        {
            recoveryBucket[i] = recoveryBucket[i - 1];
        }
        // Return last position
        recoveryBucket[BUCKET_SIZE - 1] = firstAux;
        position = BUCKET_SIZE - 1;
    }
    return position;
}
