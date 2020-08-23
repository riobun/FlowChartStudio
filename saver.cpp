#include <QModelIndex>
#include "item.h"
#include "scene.h"
#include "saver.h"

void Saver::AddNewProject(const QString& path)
{

}

void Saver::AddNewFile(const QString& path)
{

}

void Saver::Save(Item* item)
{
    auto index = item->index();
    auto scene = item->scene();
    auto graph = scene->graph;
    auto path = item->path();
    auto type = item->itemType();
    if (type == ItemType::File)
    {

    }
    else if (type == ItemType::Project)
    {

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
