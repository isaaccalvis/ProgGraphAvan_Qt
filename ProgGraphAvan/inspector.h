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

signals:
    void UpdateScene();
    void GameObjectChangedName(int row, QString& name);
    void GameObjectModified(GameObject* go);

public slots:
    void OnEntityChanged(GameObject* go, bool blockUpdate = false);

    // Input Slots
    void on_spinBox_PX_changed();                   // Position
    void on_spinBox_PY_changed();
    void on_spinBox_PZ_changed();
    void on_spinBox_Angle_changed();              // Angle
    void on_spinBox_SX_changed();                 // Scale
    void on_spinBox_SY_changed();
    void on_comboBox_Shape_changed(int num);                // Shape
    void on_spinBox_StrokeThickness_changed();    // Material
    void on_comboBox_StrokeStyle_changed(int num);
    void on_pushButton_FillColor_changed();
    void on_pushButton_StrokeColor_changed();
    void on_name_changed();

private:
    Ui::Transform* uiTransform = nullptr;
    Ui::Shape* uiShape = nullptr;
    Ui::Material* uiMaterial = nullptr;

    QWidget* transform = nullptr;
    QWidget* shape = nullptr;
    QWidget* material = nullptr;

    GameObject* selectedGO = nullptr;

    bool blockUpdate = false;
};

#endif // INSPECTOR_H
