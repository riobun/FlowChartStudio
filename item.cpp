#include "mainwindow.h"
#include "item.h"
#include "ui_mainwindow.h"

Item::Item(::ItemType type, const QString& path) : _type(type), _path(path),
    _graph(new Graph())
{
    auto pathParts = path.split('/');
    auto length = pathParts.length();
    auto fileName = pathParts[length - 1];
    auto nameParts = fileName.split('.');
    _name = nameParts[0];
    setText(_name);
    QIcon icon;
    switch (type)
    {
    case ::ItemType::File: icon = QIcon(":/images/file.png"); break;
    case ::ItemType::Folder: icon = QIcon(":/images/filefolder.png"); break;
    case ::ItemType::Project: icon = QIcon(":/images/project.png"); break;
    }
    setIcon(icon);
    if (type == ::ItemType::File)
    {

    }
    else if (type == ::ItemType::Project)
    {
        _path = pathParts[0];
        for (auto i = 1; i < length - 1; i++)
        {
            auto pathPart = pathParts[i];
            _path += "/" + pathPart;
        }
    }
}

Item::~Item()
{
    delete _graph;
}

void Item::rename(const QString &newName)
{
}
