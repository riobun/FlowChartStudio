#include <QMessageBox>
#include "mainwindow.h"
#include "item.h"
#include "ui_mainwindow.h"

Item::Item(::ItemType type, const QString& path, bool setId) : _type(type), _path(path),
    _scene(nullptr)
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
        _scene = new Scene(setId);
        _scene->setSceneRect(QRectF(0,0,5000,5000));
        _scene->item = this;
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
    if (_tab)
    {
        auto window = MainWindow::instance();
        if (window)
        {
            auto tabWidget = window->getUi()->tabWidget;
            auto index = tabWidget->indexOf(_tab);
            tabWidget->removeTab(index);
        }
    }
    if (_scene) delete _scene;
}

Graph* Item::graph() const
{
    return _scene->graph;
}

bool Item::rename(const QString &newName)
{
    if (itemType() == ::ItemType::Project)
    {
        if (!QFile::rename(path() + "/" + name() + ".pr", path() + "/" + newName + ".pr"))
        {
            return false;
        }
    }
    else if (itemType() == ::ItemType::File)
    {
        auto pathParts = path().split('/');
        auto path = pathParts[0];
        for (auto i = 1; i < pathParts.length() - 1; i++)
        {
            auto pathPart = pathParts[i];
            path += "/" + pathPart;
        }
        auto newPath = path + "/" + newName + ".gr";
        if (!QFile::rename(path + "/" + name() + ".gr", newPath))
        {
            return false;
        }
        _path = newPath;
    }

    _name = newName;
    return true;
}

QString Item::logicPath()
{
    auto project = MainWindow::instance()->RootItem();
    QString path = name();
    auto item = this->parent();
    while (item != project)
    {
        auto myItem = static_cast<Item*>(item);
        path = myItem->name() + "/" + path;
        item = item->parent();
    }
    path = project->name() + "/" + path;
    return path;
}
