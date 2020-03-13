#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "scenewidget.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , uiMainWindow(new Ui::MainWindow)
{
    qDebug("Creating Window\n");
    uiMainWindow->setupUi(this);

    // Hierarchy
    hierarchy = new Hierarchy();
    uiMainWindow->DockWindowHierarchy->setWidget(hierarchy);

    // Inspector
    inspector = new Inspector();
    uiMainWindow->DockWindowInspector->setWidget(inspector);

    // Scene
    scene = new SceneWidget();
    QBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addWidget(scene);
    uiMainWindow->centralwidget->setLayout(centralLayout);

    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowProject->toggleViewAction());
    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowHierarchy->toggleViewAction());
    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowInspector->toggleViewAction());
    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowRendering->toggleViewAction());

    connect(uiMainWindow->actionSave, SIGNAL(triggered()), this, SLOT(OnSaveClicked()));
    connect(uiMainWindow->actionOpen, SIGNAL(triggered()), this, SLOT(OnOpenClicked()));

    // Connect Hierachy (Create/Delete/Modified) with Scene
    connect(hierarchy, SIGNAL(entityCreated(int)), scene, SLOT(CreateGameObject(int)));
    connect(hierarchy, SIGNAL(entityDestroy(int)), scene, SLOT(DeleteGameObject(int)));
    connect(hierarchy, SIGNAL(entitySelected(int)), scene, SLOT(ChangeSelectedGameObject(int)));

    // Connect Scene (Modified) with Inspector
    connect(scene, SIGNAL(GameObjectSelected(GameObject*)),inspector, SLOT(OnEntityChanged(GameObject*)));

    // Connect Inspector (Update) with Scene
    connect(inspector, SIGNAL(UpdateScene()), scene, SLOT(update()));

    // Connect Inspector with Hierarchy
    connect(inspector, SIGNAL(GameObjectChangedName(int, QString&)), hierarchy, SLOT(OnNameChanged(int, QString&)));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

void MainWindow::OnSaveClicked()
{

}

void MainWindow::OnOpenClicked()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "1...", "2...");
    if (button == QMessageBox::Yes)
    {
        qDebug("Yes");
    }
    else
    {
        qDebug("No");
    }
}
