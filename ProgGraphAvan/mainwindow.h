#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inspector.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class Inspector;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnSaveClicked();
    void OnOpenClicked();

private:
    Ui::MainWindow *uiMainWindow = nullptr;
    Ui::Inspector *uiInspector = nullptr;
};
#endif // MAINWINDOW_H
