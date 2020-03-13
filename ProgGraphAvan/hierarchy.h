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
    void entityCreated(int entityId);
    void entitySelected(int entityId);
    void entityDestroy(int entityId);

public slots:
    void OnAddEntityClick();
    void OnRemoveEntityClick();
    void OnListElementClicked(int currentRow);
    void OnNameChanged(int row, QString& name);

private:
    Ui::Hierarchy *ui;
    int selectedId = -1;
    unsigned int maxId = 0;
};

#endif // HIERARCHY_H
