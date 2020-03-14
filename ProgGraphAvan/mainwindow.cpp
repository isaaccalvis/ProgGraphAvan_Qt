#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "scenewidget.h"
#include "undoredosystem.h"
#include <QMessageBox>
#include <QStyle>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    setStyleSheet("background-color:lightGray");


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

    // Close/Save/Load/Undo/Redo Options
    connect(uiMainWindow->actionSave, SIGNAL(triggered()), scene, SLOT(WriteJsonScene()));
    connect(uiMainWindow->actionOpen, SIGNAL(triggered()), scene, SLOT(ReadJsonScene()));
    connect(uiMainWindow->actionClose, SIGNAL(triggered()), this, SLOT(OnCloseClicked()));
    connect(uiMainWindow->actionUndo, SIGNAL(triggered()), this, SLOT(OnUndoClicked()));
    connect(uiMainWindow->actionRedo, SIGNAL(triggered()), this, SLOT(OnRedoClicked()));
    connect(uiMainWindow->actionUndo, SIGNAL(triggered()), scene, SLOT(OnUndo()));
    connect(uiMainWindow->actionRedo, SIGNAL(triggered()), scene, SLOT(OnRedo()));

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
    // Connect Scene with Hierarchy
    connect(scene, SIGNAL(GenerateEmptyGameObject()), hierarchy, SLOT(OnAddEntityClick()));
    connect(scene, SIGNAL(GameObjectChangedName(int, QString&)), hierarchy, SLOT(OnNameChanged(int, QString&)));
    // Connect Inspector with Scene ==> UndoRedoSystem
    connect(inspector, SIGNAL(GameObjectModified(GameObject*)), scene, SLOT(GameObjectModified(GameObject*)));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

void MainWindow::OnCloseClicked()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "Confirmation Exit", "Are you sure you want to exit?");
    if (button == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

void MainWindow::OnUndoClicked()
{

}

void MainWindow::OnRedoClicked()
{

}
