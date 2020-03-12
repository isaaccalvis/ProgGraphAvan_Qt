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
    shape->show();
    material->show();
}
