#include "inspector.h"
#include "ui_Transform.h"
#include "ui_shape.h"
#include "ui_material.h"
#include <QVBoxLayout>
#include <QColor>
#include <QColorDialog>

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
    connect(uiMaterial->spinBoxThickness,       SIGNAL(valueChanged(int)),          this, SLOT(on_spinBox_StrokeThickness_changed(int)));
    connect(uiMaterial->comboBoxStyle,          SIGNAL(currentIndexChanged(int)),   this, SLOT(on_comboBox_StrokeStyle_changed(int)));
    connect(uiMaterial->pushButtonFillColor,    SIGNAL(clicked()),                  this, SLOT(on_pushButton_FillColor_changed()));
    connect(uiMaterial->pushButtonStrokeColor,  SIGNAL(clicked()),                  this, SLOT(on_pushButton_StrokeColor_changed()));
    connect(uiTransform->lineEditName,          SIGNAL(editingFinished()),          this, SLOT(on_name_changed()));
}

Inspector::~Inspector()
{
    delete uiTransform;
}

void Inspector::OnEntityChanged(GameObject* go)
{
    if (go != nullptr)
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
        uiTransform->spinBox_ScaleX->setValue(go->transform.scale[0]);
        uiTransform->spinBox_ScaleY->setValue(go->transform.scale[1]);

            // Shape
        uiShape->shapeBoxType->setCurrentIndex(go->sprite.GetTypeIndex());

            // Material
        uiMaterial->spinBoxThickness->setValue(go->sprite.strokeThickness);
        uiMaterial->comboBoxStyle->setCurrentIndex(go->sprite.GetStrokeTypeIndex());

            // Name (Transform)
        uiTransform->lineEditName->setText(go->name);
    }
}

void Inspector::on_spinBox_PX_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.position[0] = num;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_spinBox_PY_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.position[1] = num;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_spinBox_PZ_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.position[2] = num;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_spinBox_Angle_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.angle = num;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_spinBox_SX_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.scale[0] = num;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_spinBox_SY_changed(double num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->transform.scale[1] = num;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_comboBox_Shape_changed(int num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->sprite.SetTypeIndex(num);
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_spinBox_StrokeThickness_changed(int num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->sprite.strokeThickness = num;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_comboBox_StrokeStyle_changed(int num)
{
    if (selectedGO != nullptr)
    {
        selectedGO->sprite.SettrokeTypeIndex(num);
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_pushButton_FillColor_changed()
{
    if (selectedGO != nullptr)
    {
        QColor color = QColorDialog::getColor(selectedGO->sprite.fillColor, this, "Choose Color");
        selectedGO->sprite.fillColor = color;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_pushButton_StrokeColor_changed()
{
    if (selectedGO != nullptr)
    {
        QColor color = QColorDialog::getColor(selectedGO->sprite.strokeColor, this, "Choose Color");
        selectedGO->sprite.strokeColor = color;
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}

void Inspector::on_name_changed()
{
    if (selectedGO != nullptr)
    {
        selectedGO->name = uiTransform->lineEditName->text();
        GameObjectChangedName(selectedGO->GetId(),selectedGO->name);
        GameObjectModified(selectedGO);
        UpdateScene();
    }
}
