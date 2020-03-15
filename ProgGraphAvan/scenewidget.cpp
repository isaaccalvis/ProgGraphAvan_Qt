#include "scenewidget.h"
#include <QPainter>
#include <vector>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>

SceneWidget::SceneWidget(QWidget* parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    undoRedoSystem = new UndoRedoSystem(this);
}

SceneWidget::~SceneWidget()
{
    // TODO: Clean GameObjects list
    delete undoRedoSystem;
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
        QTransform transform = painter.transform();
        transform.translate(goOrdered[i]->transform.position[0],goOrdered[i]->transform.position[1]);
        painter.setTransform(transform);
        painter.rotate(goOrdered[i]->transform.angle);

        int x = goOrdered[i]->transform.position[0];
        int y = goOrdered[i]->transform.position[1];
        int w = goOrdered[i]->transform.scale[0];
        int h = goOrdered[i]->transform.scale[1];
        QRect rect(0,0,w,h);
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

void SceneWidget::ReadJsonScene()
{
    bool ok;
    QString text = QInputDialog::getText(0, "Input dialog",
                                         "File Name (add extension!):", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        QString val;
        QFile readFile;
        readFile.setFileName(text);
        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox message;
            message.setText("Couldn't find this file");
            message.exec();
        }
        val = readFile.readAll();
        readFile.close();

        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray array(doc.array());
        for (int i = 0; i < array.size(); i++)
        {
            GenerateEmptyGameObject();
            GameObject* go = gameObjects.back();
            QJsonValue value(array[i]);

            go->name = QString(value.toObject().value("Name").toString());
            go->transform.position[0] = value.toObject().value("T_PosX").toDouble();
            go->transform.position[1] = value.toObject().value("T_PosY").toDouble();
            go->transform.position[2] = value.toObject().value("T_PosZ").toDouble();
            go->transform.angle = value.toObject().value("Angle").toDouble();
            go->transform.scale[0] = value.toObject().value("T_ScaleX").toDouble();
            go->transform.scale[1] = value.toObject().value("T_ScaleY").toDouble();

            go->sprite.SetTypeIndex(value.toObject().value("S_Shape").toInt());
            go->sprite.strokeThickness = value.toObject().value("S_strokeThickness").toInt();
            go->sprite.SettrokeTypeIndex(value.toObject().value("S_strokeStyle").toInt());

            go->sprite.fillColor = QColor(value.toObject().value("S_fillColorR").toInt(),
                    value.toObject().value("S_fillColorG").toInt(),
                    value.toObject().value("S_fillColorB").toInt(),
                    value.toObject().value("S_fillColorA").toInt());
            go->sprite.strokeColor = QColor(value.toObject().value("S_strokeColorR").toInt(),
                    value.toObject().value("S_strokeColorG").toInt(),
                    value.toObject().value("S_strokeColorB").toInt(),
                    value.toObject().value("S_strokeColorA").toInt());

            GameObjectChangedName(go->GetId(), go->name);
        }
        update();
    }
    else
    {
        QMessageBox message;
        message.setText("Name is empty or a problem occurred at read name file");
        message.exec();
    }
}

void SceneWidget::WriteJsonScene()
{
    bool ok;
    QString text = QInputDialog::getText(0, "Input dialog",
                                         "File Name (add extension!):", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        QJsonArray array;
        for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
        {
            QJsonObject go;
            go.insert("Name", (*it)->name);
            go.insert("T_PosX", (*it)->transform.position[0]);
            go.insert("T_PosY", (*it)->transform.position[1]);
            go.insert("T_PosZ", (*it)->transform.position[2]);
            go.insert("T_Angle", (*it)->transform.angle);
            go.insert("T_ScaleX", (*it)->transform.scale[0]);
            go.insert("T_ScaleY", (*it)->transform.scale[1]);
            go.insert("S_Shape", (*it)->sprite.GetTypeIndex());
            int rgba[4];
            go.insert("S_strokeThickness", (*it)->sprite.strokeThickness);
            go.insert("S_strokeStyle", (*it)->sprite.strokeStyle);
            (*it)->sprite.strokeColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
            go.insert("S_strokeColorR", rgba[0]);
            go.insert("S_strokeColorG", rgba[1]);
            go.insert("S_strokeColorB", rgba[2]);
            go.insert("S_strokeColorA", rgba[3]);
            (*it)->sprite.fillColor.getRgb(&rgba[0],&rgba[1],&rgba[2],&rgba[3]);
            go.insert("S_fillColorR", rgba[0]);
            go.insert("S_fillColorG", rgba[1]);
            go.insert("S_fillColorB", rgba[2]);
            go.insert("S_fillColorA", rgba[3]);

            array.push_back(go);
        }
        QJsonDocument doc(array);
        QFile saveFile(text);
        saveFile.open(QIODevice::WriteOnly);
        saveFile.write(doc.toJson());
        saveFile.close();
    }
    else
    {
        QMessageBox message;
        message.setText("Name is empty or a problem occurred at read name file");
        message.exec();
    }
}

void SceneWidget::GameObjectModified(GameObject* go)
{
    undoRedoSystem->AddGameObject(go);
    qDebug("GameObjectModified");
}

void SceneWidget::OnUndo()
{
    undoRedoSystem->GoBack();
}

void SceneWidget::OnRedo()
{
    undoRedoSystem->GoFront();
}
