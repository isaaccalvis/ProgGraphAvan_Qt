#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , uiMainWindow(new Ui::MainWindow)
    //, uiRendering(new Ui::Rendering)
{
    qDebug("Creating Window\n");
    uiMainWindow->setupUi(this);

    // Create rendering widget
    QWidget* renderingWidget = new QWidget();
    //uiRendering->setupUi(renderingWidget);
    renderingWidget->show();
    uiMainWindow->DockWindowRendering->setWidget(renderingWidget);
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    //delete uiRendering;
}
