#ifndef SAVER_H
#define SAVER_H

class QString;
class Item;

class Saver
{
public:
    static void AddNewProject(const QString& path);
    static void AddNewFile(const QString& path, Item* item);
    static void Save(Item* item);
    static void SaveProject(Item* item);
    static void SaveAs(Item* item, const QString& path);
    static Item* Open(const QString& path);
    static void Rename(const QString& oldPath, const QString& newName);
    static void AddRelation();
    static void ClearRelation();
};

#endif // SAVER_H
