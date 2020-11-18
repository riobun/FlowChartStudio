#include <QModelIndex>
#include "item.h"
#include "scene.h"
#include "saver.h"
#include "arrow.h"
#include "groupaction.h"
#include "changeelementaction.h"
#include "arrownode.h"
#include "mainwindow.h"
#include "subgraphnode.h"
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
#include <QMetaEnum>

QMap<SubgraphNode*, int> relations;

void Saver::ClearRelation()
{
    relations.clear();
}

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
            jsonItem.insert("items", serializeFolder(child));
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
            item = Saver::Open(path);
        }
        else if (kind == "folder")
        {
            auto name = jsonItem.value("name").toString();
            auto files = jsonItem.value("items").toArray();
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

void checkExisting(Item* item, const QString& path, Item* newItem)
{
    for (auto i = 0; i < item->rowCount(); i++)
    {
        auto child = static_cast<Item*>(item->child(i));
        if (child->itemType() == ItemType::File)
        {
            if (child->path() == path && child != newItem)
            {
                child->parent()->removeRow(i);
            }
        }
        else checkExisting(child, path, newItem);
    }
}

void Saver::AddNewFile(const QString& path, Item* item)
{
/*    QJsonObject graph;
    QJsonDocument doc;
    QJsonArray nodes;
    graph.insert("nodes", nodes);
    QJsonArray arrows;
    graph.insert("arrows", arrows);
    QJsonArray texts;
    graph.insert("texts", texts);
    doc.setObject(graph);
    write(path, doc);*/
    auto rootItem = MainWindow::instance()->RootItem();
    checkExisting(rootItem, path, item);
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
        QJsonObject graphJson;
        graphJson.insert("id", graph->GetID());
        QJsonArray nodesJson;
        foreach (auto node, graph->getNodes())
        {
            QJsonObject nodeJson;
            auto shape = node->getShape();
            nodeJson.insert("id", node->GetID());
            nodeJson.insert("shape", getShapeString(shape));
            nodeJson.insert("x", node->GetLocation().x());
            nodeJson.insert("y", node->GetLocation().y());
            nodeJson.insert("width", node->GetWidth());
            nodeJson.insert("height", node->GetHeight());
            auto backgroundColor = node->GetBackgroundColor();
            auto backgroundColorString = QString("%1 %2 %3").arg(backgroundColor.red())
                    .arg(backgroundColor.green()).arg(backgroundColor.blue());
            nodeJson.insert("backgroundColor", backgroundColorString);
            auto frameColor = node->GetFrameColor();
            auto frameColorString = QString("%1 %2 %3").arg(frameColor.red())
                    .arg(frameColor.green()).arg(frameColor.blue());
            nodeJson.insert("frameColor", frameColorString);
            nodeJson.insert("thickness", node->GetThickness());
            if (shape == ElementShape::SubGraph)
            {
                auto relationGraph = ((SubgraphNode*)node)->relatedGraph;
                if (relationGraph)
                {
                    nodeJson.insert("relation", relationGraph->GetID());
                }
            }
            nodesJson.append(nodeJson);
        }
        graphJson.insert("nodes", nodesJson);
        QJsonArray arrowsJson;
        foreach (auto arrow, graph->getArrows())
        {
            QJsonObject arrowJson;
            arrowJson.insert("id", arrow->GetID());
            arrowJson.insert("type", arrow->getType());
            arrowJson.insert("from", arrow->startItem()->GetNode()->GetID());
            arrowJson.insert("to", arrow->endItem()->GetNode()->GetID());
            auto color = arrow->getColor();
            auto colorString = QString("%1 %2 %3").arg(color.red())
                    .arg(color.green()).arg(color.blue());
            arrowJson.insert("color", colorString);
            arrowJson.insert("size", arrow->getSize());
            arrowJson.insert("haveEnd", arrow->HaveEnd);
            QJsonArray arrowListJson;
            auto arrowList = arrow->arrowlist;
            foreach (auto carrow, arrowList)
            {
                arrowListJson.append(carrow->GetID());
            }
            arrowJson.insert("list", arrowListJson);

            arrowsJson.append(arrowJson);
        }
        graphJson.insert("arrows", arrowsJson);
        QJsonArray textsJson;
        foreach (auto text, graph->getTexts())
        {
            QJsonObject textJson;
            textJson.insert("id", text->getId());
            auto font = text->get_text_font();
            auto fontString = QString("%1 %2 %3 %4").arg(font.family())
                    .arg(font.pointSizeF()).arg(font.bold()).arg(font.italic());
            textJson.insert("font", fontString);
            auto color = text->get_text_color();
            auto colorString = QString("%1 %2 %3").arg(color.red())
                    .arg(color.green()).arg(color.blue());
            textJson.insert("color", colorString);
            textJson.insert("x", text->get_text_location().x());
            textJson.insert("y", text->get_text_location().y());
            textJson.insert("logic", text->get_text_logic());
            textJson.insert("input", text->getInput());
            if (text->parent) textJson.insert("parent", text->parent->GetID());
            else textJson.insert("parent", -1);
            textJson.insert("content", text->get_text_content());
            textsJson.append(textJson);
        }
        graphJson.insert("texts", textsJson);
        doc.setObject(graphJson);
        write(path, doc);
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
        item = new Item(ItemType::File, path, false);
        auto graph = item->graph();
        auto scene = item->scene();
        auto doc = read(path);
        auto graphJson = doc.object();
        graph->GraphElement::setId(graphJson.value("id").toInt());
        graph->setId();
        auto nodesJson = graphJson.value("nodes").toArray();
        foreach (auto nodeJsonValue, nodesJson)
        {
            auto nodeJson = nodeJsonValue.toObject();
            auto id = nodeJson.value("id").toInt();
            auto shape = parseShape(nodeJson.value("shape").toString());
            auto location = QPoint(nodeJson.value("x").toVariant().toReal(),
                                   nodeJson.value("y").toVariant().toReal());
            auto width = nodeJson.value("width").toVariant().toReal();
            auto height = nodeJson.value("height").toVariant().toReal();
            auto backgroundColorParts = nodeJson.value("backgroundColor").toString().split(" ");
            QColor backgroundColor(backgroundColorParts[0].toInt(),
                    backgroundColorParts[1].toInt(), backgroundColorParts[2].toInt());
            auto frameColorParts = nodeJson.value("frameColor").toString().split(" ");
            QColor frameColor(frameColorParts[0].toInt(),
                    frameColorParts[1].toInt(), frameColorParts[2].toInt());
            auto thickness = nodeJson.value("thickness").toVariant().toReal();
            Node* node = Node::create(shape, location, width, height);
            node->setId(id);
            node->SetBackgroundColor(backgroundColor);
            node->SetFrameColor(frameColor);
            node->SetThickness(thickness);
            if (shape == ElementShape::SubGraph)
            {
                auto relationId = nodeJson.value("relation").toInt();
                relations.insert((SubgraphNode*)node, relationId);
            }
            ChangeElementAction(node, shape, true, scene).Do();
        }
        auto arrowJson = graphJson.value("arrows").toArray();
        QMap<Arrow*, QJsonArray> arrowMap;
        foreach (auto arrowJsonValue, arrowJson)
        {
            auto arrowJson = arrowJsonValue.toObject();
            auto id = arrowJson.value("id").toInt();
            auto type = arrowJson.value("type").toInt();
            auto from = arrowJson.value("from").toInt();
            auto to = arrowJson.value("to").toInt();
            auto colorParts = arrowJson.value("color").toString().split(" ");
            QColor color(colorParts[0].toInt(),
                    colorParts[1].toInt(), colorParts[2].toInt());
            auto size = arrowJson.value("size").toInt();
            auto haveEnd = arrowJson.value("haveEnd").toInt();
            auto fromItem = graph->getNodes()[from]->getNodeItem();
            auto toItem = graph->getNodes()[to]->getNodeItem();
            auto arrow = new Arrow(fromItem, toItem, haveEnd);
            arrowMap.insert(arrow, arrowJson.value("list").toArray());
            arrow->setId(id);
            arrow->setType(type);
            arrow->setArrowColor(color);
            arrow->setSize(size);
            ChangeElementAction(arrow, ElementShape::Arrow, true, scene).Do();
        }
        QMapIterator<Arrow*, QJsonArray> i(arrowMap);
        while (i.hasNext())
        {
            auto pair = i.next();
            auto arrow = pair.key();
            auto jsonArray = pair.value();
            foreach (auto jsonValue, jsonArray)
            {
                auto arrowId = jsonValue.toInt();
                auto carrow = graph->getArrows()[arrowId];
                arrow->arrowlist.append(carrow);
            }
        }
        auto textsJson = graphJson.value("texts").toArray();
        foreach (auto textJsonValue, textsJson)
        {
            auto textJson = textJsonValue.toObject();
            auto id = textJson.value("id").toString();
            QPointF location(textJson.value("x").toVariant().toReal(),
                             textJson.value("y").toVariant().toReal());
            auto logic = textJson.value("logic").toString();
            auto input = textJson.value("input").toString();
            auto parent = textJson.value("parent").toInt();
            auto fontParts = textJson.value("font").toString().split(" ");
            QFont font(fontParts[0], fontParts[1].toInt(), fontParts[2] == "true",
                    fontParts[3] == "true");
            auto colorParts = textJson.value("color").toString().split(" ");
            QColor color(colorParts[0].toInt(),
                    colorParts[1].toInt(), colorParts[2].toInt());
            auto content = textJson.value("content").toString();
            auto parentNode = parent == -1 ? nullptr : graph->getNodes()[parent];
            Text* text;
            if (parentNode)
            {
                QString temp="0x";
                temp+= QString::number(parentNode->GetID(),16);
                auto position = parentNode->GetLocation() + location - parentNode->GetLocation();
                text = new Text(position, parentNode, temp, true);
            }
            else text = new Text(location);
            if (id != "") text->change_ID(id);
            if (parentNode)
            {
                auto parentShape = parentNode->getShape();
                if (input != "" && parentShape != ElementShape::InnerInput && parentShape != ElementShape::InnerOutput)
                {
                    text->change_input(input);
                }
            }
            text->change_content(content);
            text->reset_font(font);
            text->reset_color(color);
            text->change_logic(logic);
            ChangeElementAction(text, ElementShape::Text, true, scene).Do();
        }
        scene->isChanged = false;
    }
    return item;
}

void Saver::Rename(const QString& oldPath, const QString& newName)
{

}

void Saver::AddRelation()
{
    QMapIterator<SubgraphNode*, int> i(relations);
    while (i.hasNext())
    {
        auto pair = i.next();
        auto node = pair.key();
        auto id = pair.value();
        if (Graph::graphs.contains(id))
        {
            auto graph = Graph::graphs[id];
            node->relatedGraph = graph;
            graph->AddRelatedNode(node);
        }
    }
}
