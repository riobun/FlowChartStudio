#ifndef ITEM_H
#define ITEM_H

#include <QStandardItem>
#include <QString>

#include "ItemType.h"

class Graph;

class Item : public QStandardItem
{
public:
    Item(::ItemType type, const QString& path);
    ~Item();

    ::ItemType itemType() const { return _type; }
    const QString& path() const { return _path; }
    Graph* graph() const { return _graph; }
    const QString& name() const { return _name; }
    void rename(const QString& newName);
    void setPath(const QString& path) { _path = path; }

private:
    ::ItemType _type;
    QString _path;
    Graph* _graph;
    QString _name;
};

#endif // ITEM_H
