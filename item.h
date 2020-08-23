#ifndef ITEM_H
#define ITEM_H

#include <QStandardItem>
#include <QString>

#include "ItemType.h"

class Scene;

class Item : public QStandardItem
{
public:
    Item(::ItemType type, const QString& path);
    ::ItemType itemType() const { return _type; }
    const QString& path() const { return _path; }
    Scene* scene() const;
    const QString& name() const { return _name; }
    void rename(const QString& newName);
    void setPath(const QString& path) { _path = path; }

private:
    ::ItemType _type;
    QString _path;
    Scene* _scene;
    QString _name;
};

#endif // ITEM_H
