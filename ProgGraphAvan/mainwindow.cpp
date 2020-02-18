#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_inspector.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , uiMainWindow(new Ui::MainWindow)
    , uiInspector(new Ui::Inspector)
    //, uiRendering(new Ui::Rendering)
{
    qDebug("Creating Window\n");
    uiMainWindow->setupUi(this);

    // Create rendering widget

    // Add Inspector
    QWidget* inspectorWidget = new QWidget();
    uiInspector->setupUi(inspectorWidget);
    uiMainWindow->DockWindowInspector->setWidget(inspectorWidget);

    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowProject->toggleViewAction());
    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowHierarchy->toggleViewAction());
    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowInspector->toggleViewAction());
    uiMainWindow->menuView->addAction(uiMainWindow->DockWindowRendering->toggleViewAction());

    connect(uiMainWindow->actionSave, SIGNAL(triggered()), this, SLOT(OnSaveClicked()));
    connect(uiMainWindow->actionOpen, SIGNAL(triggered()), this, SLOT(OnOpenClicked()));

}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiInspector;
    //delete uiRendering;
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
