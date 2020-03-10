#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QWidget>
#include <list>
#include "gameobject.h"

class SceneWidget : public QWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget* parent = nullptr);
    ~SceneWidget();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    GameObject* CreateGameObject();
    void DeleteGameObject(GameObject* go);

private:
    void paintEvent(QPaintEvent* event) override;
    std::list<GameObject*> gameObjects;
    GameObject* selectedGO = nullptr;
};

#endif // SCENEWIDGET_H
