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
#include <QApplication>
#include <QDir>

QJsonDocument read(const QString& path)
{
    QFile loadFile(path);
    loadFile.open(QIODevice::ReadOnly);
    QByteArray allData = loadFile.readAll();
    loadFile.close();
    QJsonParseError json_error;
    return QJsonDocument(QJsonDocument::fromJson(allData, &json_error));
}

void write(const QString& path, const QJsonDocument& doc)
{
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

QJsonArray serializeFolder(Item* item)
{
    QJsonArray files;
    for (auto i = 0; i < item->rowCount(); i++)
    {
        auto child = static_cast<Item*>(item->child(i));
        auto type = child->itemType();
        QJsonObject jsonItem;
        if (type == ItemType::File)
        {
            jsonItem.insert("kind", "file");
            jsonItem.insert("path", child->path());
        }
        else if (type == ItemType::Folder)
        {
            jsonItem.insert("kind", "folder");
            jsonItem.insert("name", child->name());
            jsonItem.insert("files", serializeFolder(child));
        }
        files.append(jsonItem);
    }
    return files;
}

QList<QStandardItem*> deserializeFolder(QJsonArray folder)
{
    QList<QStandardItem*> items;
    for (auto i = 0; i < folder.count(); i++)
    {
        auto jsonItem = folder.at(i).toObject();
        auto kind = jsonItem.value("kind").toString();
        Item* item;
        if (kind == "file")
        {
            auto path = jsonItem.value("path").toString();
            item = new Item(ItemType::File, path);
        }
        else if (kind == "folder")
        {
            auto name = jsonItem.value("name").toString();
            auto files = jsonItem.value("files").toArray();
            item = new Item(ItemType::Folder, name);
            item->appendRows(deserializeFolder(files));
        }
        items.append(item);
    }
    return items;
}

void Saver::AddNewProject(const QString& path)
{
    QJsonObject project;
    QJsonArray root;
    project.insert("root", root);
    QJsonDocument doc;
    doc.setObject(project);
    write(path, doc);
}

void Saver::AddNewFile(const QString& path)
{
    QJsonArray elements;
    QJsonDocument doc;
    doc.setArray(elements);
    write(path, doc);
}

void Saver::Save(Item* item)
{
    auto index = item->index();
    auto name = item->name();
    auto path = item->path();
    auto type = item->itemType();
    QJsonDocument doc;
    if (type == ItemType::File)
    {
        auto graph = item->graph();

        QJsonObject qso;
        QJsonObject gqso;
        gqso.insert("FilePath",path);
        gqso.insert("Name",item->name());
        gqso.insert("Graph",QJsonValue(graph->get_JsonObject()));
        qso.insert("Flie",gqso);

        QJsonDocument doc;
        doc.setObject(qso);
        QFile file(item->path());
        qDebug() << path;
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
        QJsonObject project;
        project.insert("root", serializeFolder(item));
        doc.setObject(project);
        write(path + "/" + name + ".pr", doc);
    }
}

void Saver::SaveAs(Item* item, const QString& path)
{

}

Item* Saver::Open(const QString& path)
{
    Item* item;
    auto doc = read(path);
    if (path.endsWith(".pr"))
    {
        item = new Item(ItemType::Project, path);
        auto project = doc.object();
        auto root = project.value("root").toArray();
        item->appendRows(deserializeFolder(root));
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
