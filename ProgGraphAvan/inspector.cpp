#include "inspector.h"
#include "ui_Transform.h"
#include "ui_shape.h"
#include "ui_material.h"
#include <QVBoxLayout>

Inspector::Inspector(QWidget* parent) : QWidget(parent)
{
    uiTransform = new Ui::Transform();
    uiShape = new Ui::Shape();
    uiMaterial = new Ui::Material();

    // Create Widgets
    // Transform
    transform = new QWidget();
    uiTransform->setupUi(transform);
    // Shape
    shape = new QWidget();
    uiShape->setupUi(shape);
    // Material
    material = new QWidget();
    uiMaterial->setupUi(material);
    // Create, fill & set layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(transform);
    layout->addWidget(shape);
    layout->addWidget(material);

    QSpacerItem* spacerItem = new QSpacerItem(1,1, QSizePolicy::Expanding,QSizePolicy::Expanding);
    layout->addSpacerItem(spacerItem);

    setLayout(layout);
}

Inspector::~Inspector()
{
    delete uiTransform;
}

void Inspector::OnEntityChanged(GameObject* go)
{
    //shape->show();
    //material->show();
    selectedGO = go;
    // ===================== Load info =====================
        // Transform
    uiTransform->spinBox_TranslationX->setValue(go->transform.position[0]);
    uiTransform->spinBox_TranslationY->setValue(go->transform.position[1]);
    uiTransform->spinBox_TranslationZ->setValue(go->transform.position[2]);

    uiTransform->spinBox_RotationX->setValue(go->transform.angle);
    uiTransform->spinBox_RotationY->setValue(go->transform.angle);
    uiTransform->spinBox_RotationZ->setValue(go->transform.angle);

    uiTransform->spinBox_ScaleX->setValue(go->transform.scale[0]);
    uiTransform->spinBox_ScaleY->setValue(go->transform.scale[1]);
    uiTransform->spinBox_ScaleZ->setValue(go->transform.scale[1]); // No tinc ScaleZ !!

        // Shape
    uiShape->shapeBoxType->setCurrentIndex(go->sprite.GetTypeIndex());

        // Material
    //uiMaterial->spinBoxThickness->setValue();
    //uiMaterial->comboBoxStyle->setCurrentIndex();
}
