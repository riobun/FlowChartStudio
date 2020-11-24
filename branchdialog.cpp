#include <QLabel>
#include <QLineEdit>
#include <QCompleter>
#include <QDialogButtonBox>
#include <QGridLayout>
#include "branchdialog.h"
#include "text.h"
#include "scene.h"

BranchDialog::BranchDialog(Text* text) : text(text)
{
    auto& branches = static_cast<Scene*>(text->scene())->branches;
    branchLabel = new QLabel("Branch");
    functionLabel = new QLabel("Function");
    branchEdit = new QLineEdit;
    auto oldText = text->branch;
    branchEdit->setText(oldText);
    QStringList list;
    for (auto i = branches.begin(); i != branches.end(); i++)
    {
        list << i.key();
    }
    branchCompleter = new QCompleter(list);
    branchEdit->setCompleter(branchCompleter);
    functionEdit = new QLineEdit;
    functionEdit->setEnabled(false);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(branchEdit, &QLineEdit::textChanged, [&](const QString& newText)
    {
        if (branches.contains(newText)) functionEdit->setText(branches[newText]);
    });
    if (branches.contains(oldText)) functionEdit->setText(branches[oldText]);
    auto layout = new QGridLayout;
    layout->addWidget(branchLabel, 0, 0);
    layout->addWidget(branchEdit, 1, 0);
    layout->addWidget(functionLabel, 2, 0);
    layout->addWidget(functionEdit, 3, 0);
    layout->addWidget(buttonBox, 4, 0);
    setLayout(layout);
    setWindowTitle("编辑branch");
}

QString BranchDialog::getBranch() const
{
    return branchEdit->text();
}
