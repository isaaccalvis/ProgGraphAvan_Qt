#include "undoredosystem.h"
#include "scenewidget.h"

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

UndoRedoSystem::UndoRedoSystem(SceneWidget* scene)
{
    recoveryBucket.resize(BUCKET_SIZE);
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        recoveryBucket[i] = new RecoveryGameObject();
    }
    this->scene = scene;
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
        actualIndex = position;
        // Copy Game Object
        recoveryBucket[position]->original_gameObject = go;

        recoveryBucket[position]->copy_gameObject.name = go->name;
        recoveryBucket[position]->copy_gameObject.SetId(go->GetId());

        recoveryBucket[position]->copy_gameObject.transform.position[0] = go->transform.position[0];
        recoveryBucket[position]->copy_gameObject.transform.position[1] = go->transform.position[1];
        recoveryBucket[position]->copy_gameObject.transform.position[2] = go->transform.position[2];
        recoveryBucket[position]->copy_gameObject.transform.angle = go->transform.angle;
        recoveryBucket[position]->copy_gameObject.transform.scale[0] = go->transform.scale[0];
        recoveryBucket[position]->copy_gameObject.transform.scale[1] = go->transform.scale[1];

        recoveryBucket[position]->copy_gameObject.sprite.SetTypeIndex(go->sprite.GetTypeIndex());
        recoveryBucket[position]->copy_gameObject.sprite.SettrokeTypeIndex(go->sprite.GetStrokeTypeIndex());
        recoveryBucket[position]->copy_gameObject.sprite.strokeThickness = go->sprite.strokeThickness;


        int rgba[4];
        go->sprite.fillColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
        recoveryBucket[position]->copy_gameObject.sprite.fillColor.setRgb(rgba[0],rgba[1],rgba[2],rgba[3]);
        go->sprite.strokeColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
        recoveryBucket[position]->copy_gameObject.sprite.strokeColor.setRgb(rgba[0],rgba[1],rgba[2],rgba[3]);

        // Comprobacions
        PrintBucket();
    }
}

void UndoRedoSystem::GoBack()
{
    if (!lastWasBack || actualIndex == (BUCKET_SIZE -1))
    {
        recoveryBucket[actualIndex]->wentBack = true;
        lastWasBack = true;
        if (actualIndex > 0)
            actualIndex--;
    }

    if (recoveryBucket[actualIndex]->original_gameObject != nullptr)    // Not have been removed
    {
        recoveryBucket[actualIndex]->original_gameObject->name = recoveryBucket[actualIndex]->copy_gameObject.name;
        recoveryBucket[actualIndex]->original_gameObject->SetId(recoveryBucket[actualIndex]->copy_gameObject.GetId());
        recoveryBucket[actualIndex]->original_gameObject->transform.position[0] =   recoveryBucket[actualIndex]->copy_gameObject.transform.position[0];
        recoveryBucket[actualIndex]->original_gameObject->transform.position[1] =   recoveryBucket[actualIndex]->copy_gameObject.transform.position[1];
        recoveryBucket[actualIndex]->original_gameObject->transform.position[2] =   recoveryBucket[actualIndex]->copy_gameObject.transform.position[2];
        recoveryBucket[actualIndex]->original_gameObject->transform.angle =         recoveryBucket[actualIndex]->copy_gameObject.transform.angle;
        recoveryBucket[actualIndex]->original_gameObject->transform.scale[0] =      recoveryBucket[actualIndex]->copy_gameObject.transform.scale[0];
        recoveryBucket[actualIndex]->original_gameObject->transform.scale[1] =      recoveryBucket[actualIndex]->copy_gameObject.transform.scale[1];

        recoveryBucket[actualIndex]->original_gameObject->sprite.SetTypeIndex(recoveryBucket[actualIndex]->copy_gameObject.sprite.GetTypeIndex());
        recoveryBucket[actualIndex]->original_gameObject->sprite.SettrokeTypeIndex(recoveryBucket[actualIndex]->copy_gameObject.sprite.GetStrokeTypeIndex());
        recoveryBucket[actualIndex]->original_gameObject->sprite.strokeThickness = recoveryBucket[actualIndex]->copy_gameObject.sprite.strokeThickness;

        int rgba[4];
        recoveryBucket[actualIndex]->copy_gameObject.sprite.fillColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
        recoveryBucket[actualIndex]->original_gameObject->sprite.fillColor.setRgb(rgba[0],rgba[1],rgba[2],rgba[3]);
        recoveryBucket[actualIndex]->copy_gameObject.sprite.strokeColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
        recoveryBucket[actualIndex]->original_gameObject->sprite.strokeColor.setRgb(rgba[0],rgba[1],rgba[2],rgba[3]);
    }
    else    // Have been removed
    {

    }

    recoveryBucket[actualIndex]->wentBack = true;

    scene->update();
    if (scene->wInspector != nullptr)
        scene->wInspector->OnEntityChanged(recoveryBucket[actualIndex]->original_gameObject, true);

    if (actualIndex > 0)
        actualIndex--;
}

void UndoRedoSystem::GoFront()
{
    if (lastWasBack)
    {
        if (actualIndex == 0)
        {
            if (actualIndex < BUCKET_SIZE-1)
                actualIndex += 1;
            else
                return;
        }
        else
        {
            if (actualIndex < BUCKET_SIZE-2)
                actualIndex += 2;
            else
                return;
        }
    }
    else
    {
        if (actualIndex < BUCKET_SIZE-1)
            actualIndex += 1;
        else
            return;
    }
    lastWasBack = false;

    if (recoveryBucket[actualIndex]->original_gameObject != nullptr && recoveryBucket[actualIndex]->wentBack)    // Not have been removed
    {
        recoveryBucket[actualIndex]->original_gameObject->name = recoveryBucket[actualIndex]->copy_gameObject.name;
        recoveryBucket[actualIndex]->original_gameObject->SetId(recoveryBucket[actualIndex]->copy_gameObject.GetId());
        recoveryBucket[actualIndex]->original_gameObject->transform.position[0] =   recoveryBucket[actualIndex]->copy_gameObject.transform.position[0];
        recoveryBucket[actualIndex]->original_gameObject->transform.position[1] =   recoveryBucket[actualIndex]->copy_gameObject.transform.position[1];
        recoveryBucket[actualIndex]->original_gameObject->transform.position[2] =   recoveryBucket[actualIndex]->copy_gameObject.transform.position[2];
        recoveryBucket[actualIndex]->original_gameObject->transform.angle =         recoveryBucket[actualIndex]->copy_gameObject.transform.angle;
        recoveryBucket[actualIndex]->original_gameObject->transform.scale[0] =      recoveryBucket[actualIndex]->copy_gameObject.transform.scale[0];
        recoveryBucket[actualIndex]->original_gameObject->transform.scale[1] =      recoveryBucket[actualIndex]->copy_gameObject.transform.scale[1];

        recoveryBucket[actualIndex]->original_gameObject->sprite.SetTypeIndex(recoveryBucket[actualIndex]->copy_gameObject.sprite.GetTypeIndex());
        recoveryBucket[actualIndex]->original_gameObject->sprite.SettrokeTypeIndex(recoveryBucket[actualIndex]->copy_gameObject.sprite.GetStrokeTypeIndex());
        recoveryBucket[actualIndex]->original_gameObject->sprite.strokeThickness = recoveryBucket[actualIndex]->copy_gameObject.sprite.strokeThickness;

        int rgba[4];
        recoveryBucket[actualIndex]->copy_gameObject.sprite.fillColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
        recoveryBucket[actualIndex]->original_gameObject->sprite.fillColor.setRgb(rgba[0],rgba[1],rgba[2],rgba[3]);
        recoveryBucket[actualIndex]->copy_gameObject.sprite.strokeColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
        recoveryBucket[actualIndex]->original_gameObject->sprite.strokeColor.setRgb(rgba[0],rgba[1],rgba[2],rgba[3]);

        scene->update();
        if (scene->wInspector != nullptr)
            scene->wInspector->OnEntityChanged(recoveryBucket[actualIndex]->original_gameObject, true);
    }
    else    // Have been removed
    {

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
        std::vector<RecoveryGameObject*> aux;
        aux.resize(BUCKET_SIZE);
        for (int i = 0; i < BUCKET_SIZE; i++)
        {
            aux[i] = recoveryBucket[i];
        }
        for (int i = 0; i < BUCKET_SIZE-1; i++)
        {
            recoveryBucket[i] = aux[i+1];
        }
        recoveryBucket[BUCKET_SIZE-1] = aux[0];
        position = BUCKET_SIZE - 1;
    }
    return position;
}

void UndoRedoSystem::PrintBucket()
{
    qDebug("==== OpenBucket ====");
    for (int i = 0; i < recoveryBucket.size(); i++)
    {
    qDebug("Index = %i, Name: %s, Id: %i, TransformX: %.2f, TransformY: %.2f, TransformZ = %.2f, Angle: %.2f, ScaleX: %.2f, ScaleY: %.2f, Shape = %i, Stroke = %i S_Thickness %i",
           i,
           recoveryBucket[i]->copy_gameObject.name.toStdString().c_str(),
           recoveryBucket[i]->copy_gameObject.GetId(),
           recoveryBucket[i]->copy_gameObject.transform.position[0],
           recoveryBucket[i]->copy_gameObject.transform.position[1],
           recoveryBucket[i]->copy_gameObject.transform.position[2],
           recoveryBucket[i]->copy_gameObject.transform.angle,
           recoveryBucket[i]->copy_gameObject.transform.scale[0],
           recoveryBucket[i]->copy_gameObject.transform.scale[1],
           recoveryBucket[i]->copy_gameObject.sprite.GetTypeIndex(),
           recoveryBucket[i]->copy_gameObject.sprite.GetStrokeTypeIndex(),
           recoveryBucket[i]->copy_gameObject.sprite.strokeThickness
        );
    int rgba[4];
    int rgba2[4];
    recoveryBucket[i]->copy_gameObject.sprite.fillColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
    recoveryBucket[i]->copy_gameObject.sprite.strokeColor.getRgb(&rgba2[0],&rgba2[1],&rgba2[2],&rgba2[3]);

    qDebug("\t Fill R: %i, G: %i, B: %i, A: %i :::: Stroke R: %i, G: %i, B: %i, A: %i",
           rgba[0],rgba[1],rgba[2],rgba[3], rgba2[0],rgba2[1],rgba2[2],rgba2[3]);
    }
    qDebug("==== CloseBucket ====");
}
