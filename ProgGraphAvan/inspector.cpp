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

    transform->hide();
    shape->hide();
    material->hide();

    // Connect
    connect(uiTransform->spinBox_TranslationX,  SIGNAL(editingFinished()),          this,   SLOT(on_spinBox_PX_changed()));
    connect(uiTransform->spinBox_TranslationY,  SIGNAL(editingFinished()),          this,   SLOT(on_spinBox_PY_changed()));
    connect(uiTransform->spinBox_TranslationZ,  SIGNAL(editingFinished()),          this,   SLOT(on_spinBox_PZ_changed()));
    connect(uiTransform->spinBox_RotationX,     SIGNAL(editingFinished()),          this,   SLOT(on_spinBox_Angle_changed()));
    connect(uiTransform->spinBox_ScaleX,        SIGNAL(editingFinished()),          this,   SLOT(on_spinBox_SX_changed()));
    connect(uiTransform->spinBox_ScaleY,        SIGNAL(editingFinished()),          this,   SLOT(on_spinBox_SY_changed()));
    connect(uiShape->shapeBoxType,              SIGNAL(currentIndexChanged(int)),   this,   SLOT(on_comboBox_Shape_changed(int)));
    connect(uiMaterial->spinBoxThickness,       SIGNAL(editingFinished()),          this,   SLOT(on_spinBox_StrokeThickness_changed()));
    connect(uiMaterial->comboBoxStyle,          SIGNAL(currentIndexChanged(int)),   this,   SLOT(on_comboBox_StrokeStyle_changed(int)));
    connect(uiMaterial->pushButtonFillColor,    SIGNAL(clicked()),                  this,   SLOT(on_pushButton_FillColor_changed()));
    connect(uiMaterial->pushButtonStrokeColor,  SIGNAL(clicked()),                  this,   SLOT(on_pushButton_StrokeColor_changed()));
    connect(uiTransform->lineEditName,          SIGNAL(editingFinished()),          this,   SLOT(on_name_changed()));
}

Inspector::~Inspector()
{
    delete uiTransform;
}

void Inspector::OnEntityChanged(GameObject* go, bool blockUpdate)
{
    this->blockUpdate = blockUpdate;
    if (go != nullptr)
    {
        selectedGO = go;
        // ===================== Load info =====================
        uiTransform->spinBox_TranslationX->setValue(go->transform.position[0]);
        uiTransform->spinBox_TranslationY->setValue(go->transform.position[1]);
        uiTransform->spinBox_TranslationZ->setValue(go->transform.position[2]);
        uiTransform->spinBox_RotationX->setValue(go->transform.angle);
        uiTransform->spinBox_ScaleX->setValue(go->transform.scale[0]);
        uiTransform->spinBox_ScaleY->setValue(go->transform.scale[1]);
        uiShape->shapeBoxType->setCurrentIndex(go->sprite.GetTypeIndex());
        uiMaterial->spinBoxThickness->setValue(go->sprite.strokeThickness);
        uiMaterial->comboBoxStyle->setCurrentIndex(go->sprite.GetStrokeTypeIndex());
        uiTransform->lineEditName->setText(go->name);
        GameObjectChangedName(selectedGO->GetId(),selectedGO->name);

        transform->show();
        shape->show();
        material->show();
    }
    else
    {
        transform->hide();
        shape->hide();
        material->hide();
    }
    this->blockUpdate = false;
}

void Inspector::on_spinBox_PX_changed()
{
    if (uiTransform->spinBox_TranslationX->value() == selectedGO->transform.position[0])
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->transform.position[0] = uiTransform->spinBox_TranslationX->value();
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_spinBox_PY_changed()
{
    if (uiTransform->spinBox_TranslationY->value() == selectedGO->transform.position[1])
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->transform.position[1] = uiTransform->spinBox_TranslationY->value();
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_spinBox_PZ_changed()
{
    if (uiTransform->spinBox_TranslationZ->value() == selectedGO->transform.position[2])
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->transform.position[2] = uiTransform->spinBox_TranslationZ->value();
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_spinBox_Angle_changed()
{
    if (uiTransform->spinBox_RotationX->value() == selectedGO->transform.angle)
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->transform.angle = uiTransform->spinBox_RotationX->value();
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_spinBox_SX_changed()
{
    if (uiTransform->spinBox_ScaleX->value() == selectedGO->transform.scale[0])
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->transform.scale[0] = uiTransform->spinBox_ScaleX->value();
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_spinBox_SY_changed()
{
    if (uiTransform->spinBox_ScaleY->value() == selectedGO->transform.scale[1])
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->transform.scale[1] = uiTransform->spinBox_ScaleY->value();
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_comboBox_Shape_changed(int num)
{
    if (num == selectedGO->sprite.GetTypeIndex())
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->sprite.SetTypeIndex(num);
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_spinBox_StrokeThickness_changed()
{
    if (uiMaterial->spinBoxThickness->value() == selectedGO->sprite.strokeThickness)
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->sprite.strokeThickness = uiMaterial->spinBoxThickness->value();
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_comboBox_StrokeStyle_changed(int num)
{
    if (num == selectedGO->sprite.GetStrokeTypeIndex())
        return; // If we dont modify the object don't update it
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->sprite.SettrokeTypeIndex(num);
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_pushButton_FillColor_changed()
{
    if (selectedGO != nullptr && !blockUpdate)
    {
        QColor color = QColorDialog::getColor(selectedGO->sprite.fillColor, this, "Choose Color");
        selectedGO->sprite.fillColor = color;
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_pushButton_StrokeColor_changed()
{
    if (selectedGO != nullptr && !blockUpdate)
    {
        QColor color = QColorDialog::getColor(selectedGO->sprite.strokeColor, this, "Choose Color");
        selectedGO->sprite.strokeColor = color;
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}

void Inspector::on_name_changed()
{
    if (selectedGO != nullptr && !blockUpdate)
    {
        selectedGO->name = uiTransform->lineEditName->text();
        GameObjectChangedName(selectedGO->GetId(),selectedGO->name);
        UpdateScene();
        GameObjectModified(selectedGO);
    }
}
