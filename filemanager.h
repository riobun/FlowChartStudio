#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

class MainWindow;
class QStandardItemModel;
namespace Ui { class MainWindow; }

class FileManager : public QObject
{
    Q_OBJECT

public:
    FileManager(QObject *parent = nullptr);

    QStandardItemModel* model;

private:


private:
    MainWindow* window() const;
    Ui::MainWindow* ui() const;

    void newProject();
    void openProject();
};

#endif // FILEMANAGER_H
