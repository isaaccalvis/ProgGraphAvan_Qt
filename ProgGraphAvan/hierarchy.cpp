#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->button_AddEntity, SIGNAL(clicked()), this, SLOT(OnAddEntityClick()));
    connect(ui->button_RemoveEntity, SIGNAL(clicked()), this, SLOT(OnRemoveEntityClick()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(OnListElementClicked(int)));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::OnAddEntityClick()
{
    ui->listWidget->addItem("Entity");
    emit entityCreated(maxId);
    maxId++;
}

void Hierarchy::OnRemoveEntityClick()
{
    int current = ui->listWidget->currentRow();
    ui->listWidget->takeItem(current);
    emit entityDestroy(current);
    maxId--;
}

void Hierarchy::OnListElementClicked(int currentRow)
{
    selectedId = currentRow;
    qInfo("%i", selectedId);
    emit entitySelected(selectedId);
}
