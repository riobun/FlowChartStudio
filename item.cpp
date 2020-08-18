#include "item.h"

Item::Item(::ItemType type, const QString& path) : _type(type), _path(path), _scene(nullptr)
{
    auto pathParts = path.split('/');
    auto length = pathParts.length();
    auto fileName = pathParts[length - 1];
    auto nameParts = fileName.split('.');
    auto name = nameParts[0];
    setText(name);
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
}
