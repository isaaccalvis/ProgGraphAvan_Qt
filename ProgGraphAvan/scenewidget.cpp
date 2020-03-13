#include "scenewidget.h"
#include <QPainter>
#include <vector>

SceneWidget::SceneWidget(QWidget* parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

SceneWidget::~SceneWidget()
{
    // TODO: Clean GameObjects list
}

QSize SceneWidget::sizeHint() const
{
    return QSize(256,256);
}

QSize SceneWidget::minimumSizeHint() const
{
    return QSize(64,64);
}

void SceneWidget::CreateGameObject(int num)
{
    GameObject* newGO = new GameObject(num);
    gameObjects.push_back(newGO);
    update();
}

void SceneWidget::DeleteGameObject(int num)
{
    bool deleted = false;
    for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
    {
        if (!deleted)
        {
            if ((*it)->GetId() == num)
            {
                if ((*it)->GetId() == gameObjects.size()-1)
                {
                    gameObjects.erase(it);
                    deleted = true;
                    break;
                }
                else
                {
                    it = gameObjects.erase(it);
                    (*it)->SetId((*it)->GetId() - 1);
                    deleted = true;
                }
            }
        }
        else
        {
            (*it)->SetId((*it)->GetId() - 1);
        }
    }
    update();
}

void SceneWidget::ChangeSelectedGameObject(int num)
{
    GameObject* go = nullptr;
    for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
    {
        if ((*it)->GetId() == num)
        {
            go = (*it);
            break;
        }
    }
    GameObjectSelected(go);
}

void SceneWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(Qt::blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    brush.setColor(Qt::white);
    pen.setWidth(4);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);

    std::vector<GameObject*> goOrdered;
    goOrdered.resize(gameObjects.size());
    // Create vector
    int i = 0;
    for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
    {
        goOrdered[i] = (*it);
        i++;
    }
    // Order Vector
    for (int i = 1; i < goOrdered.size(); i++)
    {
        if (i > 0)
        {
            if (goOrdered[i]->transform.position[2] < goOrdered[i-1]->transform.position[2])
            {
                GameObject* aux = goOrdered[i];
                goOrdered[i] = goOrdered[i - 1];
                goOrdered[i-1] = aux;
                i--;
                i--;
            }
        }
    }

    for (int i = 0; i < goOrdered.size(); i++)
    {
        brush.setColor(goOrdered[i]->sprite.fillColor);
        pen.setColor(goOrdered[i]->sprite.strokeColor);
        pen.setWidth(goOrdered[i]->sprite.strokeThickness);

        switch(goOrdered[i]->sprite.strokeStyle)
        {
        case STROKE_STYLE::SOLID:
            pen.setStyle(Qt::PenStyle::SolidLine);
            break;
        case STROKE_STYLE::DASHED:
            pen.setStyle(Qt::PenStyle::DashLine);
            break;
        }

        painter.setBrush(brush);
        painter.setPen(pen);

        int x = goOrdered[i]->transform.position[0];
        int y = goOrdered[i]->transform.position[1];
        int w = goOrdered[i]->transform.scale[0];
        int h = goOrdered[i]->transform.scale[1];
        QRect rect(x,y,w,h);
        switch(goOrdered[i]->sprite.type)
        {
        case SHAPE_TYPE::CIRCLE:
            painter.drawRect(rect);
            break;
        case SHAPE_TYPE::QUAD:
            painter.drawEllipse(rect);
            break;
        }
    }
}
