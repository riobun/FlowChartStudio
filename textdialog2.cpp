#include<textdialog2.h>
#include<idpool.h>
#include<QGridLayout>
#include<QMessageBox>
#include <QCompleter>
#include "mainwindow.h"


DetailsDialog2::DetailsDialog2(QString ID_,QString con,const QString &title, QWidget *parent)
    : QDialog(MainWindow::instance())
{
    resize(500, 200);
    IDLabel = new QLabel(tr("ID:"));
    contentLabel = new QLabel(tr("描述:"));
    contentLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    IDEdit = new QLineEdit;
    contentEdit = new QLineEdit;
    englishLabel = new QLabel("English");
    englishEdit = new QLineEdit;
    englishEdit->setReadOnly(true);
    QStringList list;
    auto& dictionary = MainWindow::instance()->scene()->nodeDictionary;
    for (auto i = dictionary.begin(); i != dictionary.end(); i++)
    {
        list << i.key();
    }
    contentCompleter = new QCompleter(list);
    contentEdit->setCompleter(contentCompleter);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DetailsDialog2::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DetailsDialog2::reject);
    connect(contentEdit, &QLineEdit::textChanged, [&](const QString& newText)
    {
        if (dictionary.contains(newText)) englishEdit->setText(dictionary[newText]);
        else englishEdit->setText("");
    });
    if (dictionary.contains(con)) englishEdit->setText(dictionary[con]);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(IDLabel, 0, 0);
    mainLayout->addWidget(IDEdit, 1, 0);

    mainLayout->addWidget(contentLabel, 2, 0);
    mainLayout->addWidget(contentEdit, 3,0);
    mainLayout->addWidget(englishLabel, 4, 0);
    mainLayout->addWidget(englishEdit, 5, 0);
    mainLayout->addWidget(buttonBox, 6, 0);
    setLayout(mainLayout);

    setWindowTitle(title);
    content=con;
    ID=ID_;
    contentEdit->setText(content);
    IDEdit->setText(ID);
}


QString DetailsDialog2::senderID() const
{
    return ID;
}

QString DetailsDialog2::senderContent() const
{
    return contentEdit->text();
}


void DetailsDialog2::verify()
{
    QString str;
    str.append(IDEdit->text());
   // str.chop(1);
    if(str==ID){
        accept();
        return;
    }
    else{
       isID2=isNorm(str);
        if(isID2==true){
         isID=isRepeat(MainWindow::instance()->graph(), str);
        }
    }
    if (!isID && !contentEdit->text().isEmpty()&&isID2) {
        Node* node;
        int oldNodeId = CStringHexToInt(ID);
        foreach (auto currentNode, MainWindow::instance()->graph()->getNodes())
        {
            if (currentNode->getNodeId() == oldNodeId)
            {
                node = currentNode;
            }
        }
        node->changesId(str);
        ID=str;
        accept();
        return;
    }
    else if(!isID2){
        QMessageBox::StandardButton answer;
        answer = QMessageBox::warning(this, tr("修改后的ID不合法"),
            tr("修改后的ID格式不正确\n"
               "应以0x为开头的16进制\n"
               "是否放弃修改?"),
            QMessageBox::Yes | QMessageBox::No);

        if (answer == QMessageBox::Yes)
            accept();
        //else
            //reject();
    }

    else if(isID){
        QMessageBox::StandardButton answer;
        answer = QMessageBox::warning(this, tr("修改后的ID不合法"),
            tr("修改后的ID与已有ID重复\n"
               "是否放弃修改?"),
            QMessageBox::Yes | QMessageBox::No);

        if (answer == QMessageBox::Yes)
            accept();
       // else
           // reject();

    }
    else if(contentEdit->text().isEmpty()){
    QMessageBox::StandardButton answer;
    answer = QMessageBox::warning(this, tr("文本框没有描述部分"),
        tr("没有编辑描述部分的文本框会被自动删除\n"
           "是否添加描述?"),
        QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::No)
        reject();
   // else
        //accept();
    }
}

