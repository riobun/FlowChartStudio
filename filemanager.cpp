#include <QAction>

#include "filemanager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "item.h"
#include "saver.h"

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    auto ui = this->ui();
    // 初始化文件树形结构 model
    {
        model = new QStandardItemModel(ui->treeView);
        ui->treeView->setModel(model);
        model->setHorizontalHeaderLabels(QStringList()<<"项目管理");
    }
    //connect(ui->newProjectAction, &QAction::triggered, this, &FileManager::newProject);
    //connect(ui->openProjectAction, &QAction::triggered, this, &FileManager::openProject);
}

MainWindow* FileManager::window() const
{
    return static_cast<MainWindow*>(parent());
}

Ui::MainWindow* FileManager::ui() const
{
    return window()->getUi();
}

void FileManager::newProject()
{
    auto path = QFileDialog::getSaveFileName(window(), "新建项目文件", QString(), "项目文件(*.pr)");
    if (path != QString())
    {
        auto item = new Item(ItemType::Project, path);
        model->appendRow(item);
        Saver::AddNewProject(path);
    }
}

void FileManager::openProject()
{
    auto path = QFileDialog::getOpenFileName(window(), "打开项目", QString(), "项目文件(*.pr)");
    if (path != QString())
    {
        auto item = Saver::Open(path);
        model->clear();
        model->appendRow(item);
    }
}
