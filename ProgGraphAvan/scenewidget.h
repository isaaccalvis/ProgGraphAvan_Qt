#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QWidget>
#include <list>
#include "gameobject.h"
#include "undoredosystem.h"

class SceneWidget : public QWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget* parent = nullptr);
    ~SceneWidget();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    void GameObjectSelected(GameObject* go);
    void GenerateEmptyGameObject(); // Amb això genero un game object al final de la llista que el fare servir per carregar escenes des de json (TODO: treure aixo)
    void GameObjectChangedName(int row, QString& name);

public slots:
    void CreateGameObject(int num);
    void DeleteGameObject(int num);
    void ChangeSelectedGameObject(int num);
    void ReadJsonScene();
    void WriteJsonScene();
    void GameObjectModified(GameObject* go);
    void OnUndo();
    void OnRedo();

public:
    UndoRedoSystem* undoRedoSystem = nullptr;

private:
    void paintEvent(QPaintEvent* event) override;
    std::list<GameObject*> gameObjects;
    GameObject* selectedGO = nullptr;
};

#endif // SCENEWIDGET_H
