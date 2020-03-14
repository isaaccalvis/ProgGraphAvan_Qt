#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class Hierarchy;
class Inspector;
class SceneWidget;

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
    void OnCloseClicked();

private:
    Ui::MainWindow *uiMainWindow = nullptr;

    Hierarchy* hierarchy = nullptr;
    Inspector* inspector = nullptr;
    SceneWidget* scene = nullptr;
};
#endif // MAINWINDOW_H
