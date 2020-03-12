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

    // Connect
    connect(uiTransform->spinBox_TranslationX,  SIGNAL(valueChanged(double)),       this, SLOT(on_spinBox_PX_changed(double)));
    connect(uiTransform->spinBox_TranslationY,  SIGNAL(valueChanged(double)),       this, SLOT(on_spinBox_PY_changed(double)));
    connect(uiTransform->spinBox_TranslationZ,  SIGNAL(valueChanged(double)),       this, SLOT(on_spinBox_PZ_changed(double)));
    connect(uiTransform->spinBox_RotationX,     SIGNAL(valueChanged(double)),       this, SLOT(on_spinBox_Angle_changed(double)));
    connect(uiTransform->spinBox_ScaleX,        SIGNAL(valueChanged(double)),       this, SLOT(on_spinBox_SX_changed(double)));
    connect(uiTransform->spinBox_ScaleY,        SIGNAL(valueChanged(double)),       this, SLOT(on_spinBox_SY_changed(double)));
    connect(uiShape->shapeBoxType,              SIGNAL(currentIndexChanged(int)),   this, SLOT(on_comboBox_Shape_changed(int)));
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

void Inspector::on_spinBox_PX_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.position[0] = num;
        UpdateScene();
    }
}

void Inspector::on_spinBox_PY_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.position[1] = num;
        UpdateScene();
    }
}

void Inspector::on_spinBox_PZ_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.position[2] = num;
        UpdateScene();
    }
}

void Inspector::on_spinBox_Angle_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.angle = num;
        UpdateScene();
    }
}

void Inspector::on_spinBox_SX_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.scale[0] = num;
        UpdateScene();
    }
}

void Inspector::on_spinBox_SY_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.scale[1] = num;
        UpdateScene();
    }
}

void Inspector::on_comboBox_Shape_changed(int num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->sprite.SetTypeIndex(num);
        UpdateScene();
    }
}
