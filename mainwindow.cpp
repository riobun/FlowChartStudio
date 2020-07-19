#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QToolBox>
#include <QPushButton>
//#include <QLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*    auto toolBox = new QToolBox();
    auto pButton1 = new QPushButton("One");
    auto widget = new QWidget();
    auto aLayout = new QGridLayout();
    aLayout->addWidget(pButton1);
    widget->setLayout(aLayout);
    toolBox->addItem(widget, "sddf");

    auto scene = new QGraphicsScene(centralWidget());

    auto view = new QGraphicsView(scene, centralWidget());

    auto layout = new QHBoxLayout(centralWidget());
    layout->addWidget(toolBox);
    layout->addWidget(view);
    centralWidget()->setLayout(layout);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

