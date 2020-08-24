#include <QModelIndex>
#include "item.h"
#include "scene.h"
#include "saver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>
#include <QVariant>
#include<QApplication>
void Saver::AddNewProject(const QString& path)
{

}

void Saver::AddNewFile(const QString& path)
{

}

void Saver::Save(Item* item)
{
    auto index = item->index();
    auto path = item->path();
    auto type = item->itemType();
    if (type == ItemType::File)
    {
        auto graph = item->graph();

        QJsonArray graphArray;
        QJsonObject qso;

        graphArray.append(graph->get_JsonObject());

        QJsonObject gqso;
        gqso.insert("FilePath",path);
        gqso.insert("GraphID",graph->GetID());
        graphArray.append(gqso);
        qso.insert("Flie",QJsonValue(graphArray));

        QJsonDocument doc;
        doc.setObject(qso);
        QFile file(QApplication::applicationDirPath()+item->path());
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "File open failed!";
        }
        else
        {
            qDebug() <<"File open successfully!";
        }
             file.write(doc.toJson(QJsonDocument::Indented));
             file.close();
    }
    else if (type == ItemType::Project)
    {
        auto name = item->name();
        QJsonObject qso;
        QJsonArray FileArray;
        QJsonObject gqso;

        FileArray.append(name);
        FileArray.append(path);
        gqso.insert("GraphID",item->graph()->GetID());
        FileArray.append(gqso);
        qso.insert("Project",QJsonValue(FileArray));

        QJsonDocument doc;
        doc.setObject(qso);
        QFile file(QApplication::applicationDirPath()+item->path());
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "File open failed!";
        }
        else
        {
            qDebug() <<"File open successfully!";
        }
             file.write(doc.toJson(QJsonDocument::Indented));
             file.close();
    }
}

void Saver::SaveAs(Item* item, const QString& path)
{

}

Item* Saver::Open(const QString& path)
{
    Item* item;
    if (path.endsWith(".pr"))
    {
        item = new Item(ItemType::Project, path);
    }
    else if (path.endsWith(".gr"))
    {
        item = new Item(ItemType::File, path);
    }
    return item;
}

void Saver::Rename(const QString& oldPath, const QString& newName)
{

}
