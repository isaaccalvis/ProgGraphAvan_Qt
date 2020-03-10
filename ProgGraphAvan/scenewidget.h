#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QWidget>

class SceneWidget : public QWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    void paintEvent(QPaintEvent* event) override;
};

#endif // SCENEWIDGET_H
