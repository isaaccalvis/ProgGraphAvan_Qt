#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "ui_Transform.h"
#include "ui_shape.h"
#include "ui_material.h"
#include "gameobject.h"

namespace Ui {
class Transform;
class Shape;
class Material;
}

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();

public slots:
    void OnEntityChanged(GameObject* go);

private:
    Ui::Transform* uiTransform = nullptr;
    Ui::Shape* uiShape = nullptr;
    Ui::Material* uiMaterial = nullptr;

    QWidget* transform = nullptr;
    QWidget* shape = nullptr;
    QWidget* material = nullptr;

    GameObject* selectedGO = nullptr;
};

#endif // INSPECTOR_H
