#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>
#include<QLabel>
#include<QcheckBox>
#include<QLineEdit>
#include<QTableWidget>
#include<QTextEdit>
#include<QDialogButtonBox>
#include<QPushButton>
#include <QComboBox>
#include<text.h>


class DetailsDialog : public QDialog
{
    Q_OBJECT

public:
    DetailsDialog(QString sc,const QString &title="文本编辑框", QWidget *parent=0);
    void changcon(QString sc);
public slots:
    void verify() ;
    void pressbutton();
    void rc_onchange(int ac);
    void nc_onchange(int bc);
public:
    //QList<QPair<QString, QString> > orderItems();
    QString senderName() const;
    QString senderContent() const;
    QString senderLogic() const;
private:
    //void setupItemsTable();
    QPushButton* addB;
    QComboBox* relationC;
    QComboBox* notC;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *contentLabel;
    QTextEdit *contentEdit;
    QTextEdit *logicEdit;
    QDialogButtonBox *buttonBox;
    QString a;
    QString b;
    QString con;
    //QString relationitem;
    //int size;


};

#endif // TEXTDIALOG_H
