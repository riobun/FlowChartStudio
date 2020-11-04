#ifndef ITEM_H
#define ITEM_H

#include <QStandardItem>
#include <QString>

#include "ItemType.h"

class Scene;
class Graph;
class QWidget;

class Item : public QStandardItem
{
public:
    Item(::ItemType type, const QString& path);
    ~Item();

    ::ItemType itemType() const { return _type; }
    const QString& path() const { return _path; }
    Scene* scene() const { return _scene; }
    Graph* graph() const;
    QWidget* tab() const { return _tab; }
    const QString& name() const { return _name; }
    bool rename(const QString& newName);
    void setPath(const QString& path) { _path = path; }
    void setTab(QWidget* tab) { _tab = tab; }

private:
    ::ItemType _type;
    QString _path;
    Scene* _scene;
    QString _name;
    QWidget* _tab = nullptr;
};

#endif // ITEM_H
