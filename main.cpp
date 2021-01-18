#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "splashscreen.h"
#include "autosavethread.h"
#include "navigationbutton.h"

#include <QGridLayout>

MainWindow* point_w = nullptr;

QMainWindow* firstWindow;
MainWindow* mainWindow;


void showSplashScreen(QApplication& app);
void showNavigationWindow();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoSaveThread autoSaveThread;
    autoSaveThread.start();
    MainWindow window;
    mainWindow = &window;
    /*MainWindow w;
    point_w = &w;
    showSplashScreen(a);
    w.show();*/
//    mainWindow->show();
//    mainWindow->hide();
    showNavigationWindow();

    auto returnCode = a.exec();
    autoSaveThread.terminate ();
    return returnCode;
}

void showSplashScreen(QApplication& app)
{
    SplashScreen splashScreen;
    splashScreen.showScreen(app);
}

void showNavigationWindow()
{
    firstWindow = new QMainWindow();
    firstWindow->setWindowTitle("自主决策系统图形化配置软件");
    auto centralWidget = new QWidget(firstWindow);
    centralWidget->setObjectName("centralWidget");
    centralWidget->setStyleSheet(
        "QPushButton {"
            "background-color: qlineargradient("
                "x1: 0, y1: 0,"
                "x2: 1, y2: 1,"
                "stop: 0 white,"
                "stop: 1 #87CEFA"
            ");"
            "border: 4px solid black;"
        "}"
        "QPushButton:hover {"
            "background-color: qlineargradient("
                "x1: 0, y1: 0,"
                "x2: 1, y2: 1,"
                "stop: 0 white,"
                "stop: 1 #DEC674"
            ");"
        "}"
        "#centralWidget { border-image: url(:/images/technology_blue.jpg); }"
    );
    auto layout = new QGridLayout(centralWidget);
    auto container = new QWidget(centralWidget);
    container->setFixedSize(1080, 700);
    layout->addWidget(container, 1, 0);
    auto label = new QLabel("一键导航", container);
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(0, 0, 1080, 200);
    label->setFont(QFont("微软雅黑", 30));
    label->setStyleSheet("color: white");
    auto newModelButton = new NavigationButton(container);
    newModelButton->setGeometry(10, 260, 300, 200);
    newModelButton->setStyleSheet("border-image:url(:/images/new_model.png)");
    QObject::connect(newModelButton, &QPushButton::clicked, []()
    {
        firstWindow->hide();
        mainWindow->closeProject();
        mainWindow->show();
        mainWindow->newModel();
    });
    auto editModelButton = new NavigationButton(container);
    editModelButton->setGeometry(390, 260, 300, 200);
    editModelButton->setStyleSheet("border-image:url(:/images/edit_model.png)");
    QObject::connect(editModelButton, &QPushButton::clicked, []()
    {
        firstWindow->hide();
        mainWindow->closeProject();
        mainWindow->show();
        mainWindow->editModel();
    });
    auto verifyModelButton = new NavigationButton(container);
    verifyModelButton->setGeometry(770, 260, 300, 200);
    verifyModelButton->setStyleSheet("border-image:url(:/images/verify_model.png)");
    QObject::connect(verifyModelButton, &QPushButton::clicked, []()
    {
        // mainWindow->show();
        mainWindow->editModel();
        if (mainWindow->verifyModel())
        {
            QMessageBox::information(firstWindow, "提示", "验证通过");
        }
        else
        {
            firstWindow->hide();
            mainWindow->closeProject();
            mainWindow->show();
            mainWindow->initializePosition();
        }
    });
    auto importButton = new NavigationButton(container);
    importButton->setGeometry(10, 490, 300, 200);
    importButton->setStyleSheet("border-image:url(:/images/import_data.png)");
    QObject::connect(importButton, &QPushButton::clicked, []()
    {
        //window->close();
        //mainWindow->show();
        mainWindow->editModel();
        mainWindow->importBranches();
        mainWindow->importNodeDictionary();
        mainWindow->importBranchDictionary();
        QMessageBox::information(firstWindow, "提示", "导入结束");
    });
    auto generateButton = new NavigationButton(container);
    generateButton->setGeometry(390, 490, 300, 200);
    generateButton->setStyleSheet("border-image:url(:/images/generate_data.png)");
    QObject::connect(generateButton, &QPushButton::clicked, []()
    {
        //window->close();
        //mainWindow->show();
        mainWindow->editModel();
        if (mainWindow->verifyModel())
        {
            mainWindow->exportCsv(false);
            QMessageBox::information(firstWindow, "提示", "生成成功");
        }
        else
        {
            QMessageBox::information(firstWindow, "提示", "该模型存在问题");
            firstWindow->hide();
            mainWindow->closeProject();
            mainWindow->show();
            mainWindow->initializePosition();
        }
    });
    auto exportButton = new NavigationButton(container);
    exportButton->setGeometry(770, 490, 300, 200);
    exportButton->setStyleSheet("border-image:url(:/images/export_data.png)");
    QObject::connect(exportButton, &QPushButton::clicked, []()
    {
        // window->close();
        //mainWindow->show();
        mainWindow->editModel();
        if (mainWindow->verifyModel())
        {
            mainWindow->exportCsv(false);
            QMessageBox::information(firstWindow, "提示", "生成成功");
        }
        else
        {
            QMessageBox::information(firstWindow, "提示", "该模型存在问题");
            firstWindow->hide();
            mainWindow->closeProject();
            mainWindow->show();
            mainWindow->initializePosition();
        }
    });
    firstWindow->setCentralWidget(centralWidget);
    firstWindow->showMaximized();
}
