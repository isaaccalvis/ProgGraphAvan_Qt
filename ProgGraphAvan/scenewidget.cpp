#include "scenewidget.h"
#include <QPainter>

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
        qDebug("New %i", (*it)->GetId());
    }
}

void SceneWidget::paintEvent(QPaintEvent* event)
{
        qDebug("painting");
        QColor blueColor = QColor::fromRgb(127,190,220);
        QColor whiteColor = QColor::fromRgb(255,255,255);
        QColor blackColor = QColor::fromRgb(0,0,0);

        QPainter painter(this);
        QBrush brush;
        QPen pen;

        brush.setColor(blueColor);
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        pen.setStyle(Qt::PenStyle::NoPen);
        painter.setBrush(brush);
        painter.setPen(pen);

        //painter.drawRect(rect());

        brush.setColor(whiteColor);
        pen.setWidth(4);
        pen.setColor(blackColor);
        pen.setStyle(Qt::PenStyle::DashLine);
        painter.setBrush(brush);
        painter.setBrush(brush);
        painter.setPen(pen);

        // Draw circle
        /*
        int r = 64;
        int w = r * 2;
        int h = r * 2;
        int x = rect().width() / 2 - r;
        int y = rect().height() / 2 - r;
        QRect circleRect(x,y,w,h);
        painter.drawEllipse(circleRect);
        */
        for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
        {
            /*
            int x = (*it)->transform.position[0];
            int y = (*it)->transform.position[1];
            int w = (*it)->transform.scale[0];
            int h = (*it)->transform.scale[1];
            QRect circleRect(x,y,w,h);
            painter.drawEllipse(circleRect);
            */
            int r = 64;
            int w = r * 2;
            int h = r * 2;
            int x = rect().width() / 2 - r;
            int y = rect().height() / 2 - r;
            QRect circleRect(x,y,w,h);
            painter.drawEllipse(circleRect);
        }
}
