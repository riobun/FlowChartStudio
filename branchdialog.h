#ifndef BRANCHDIALOG_H
#define BRANCHDIALOG_H

#include <QDialog>

class Text;
class QLabel;
class QLineEdit;
class QCompleter;
class QDialogButtonBox;

class BranchDialog : public QDialog
{
    Q_OBJECT

public:
    BranchDialog(Text* text);
    QString getBranch() const;

private:
    Text* text;
    QLabel* branchLabel;
    QLabel* functionLabel;
    QLineEdit* branchEdit;
    QLineEdit* functionEdit;
    QCompleter* branchCompleter;
    QDialogButtonBox* buttonBox;
};

#endif // BRANCHDIALOG_H
