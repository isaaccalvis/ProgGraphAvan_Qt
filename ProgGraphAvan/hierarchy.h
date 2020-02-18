#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

namespace Ui {
class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

signals:
    void entitySelected(int entityId);

public slots:
    void OnAddEntityClick();
    void OnRemoveEntityClick();
    void OnListElementClicked(int currentRow);

private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
