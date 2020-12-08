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
    resize(500, 200);
    auto scene = static_cast<Scene*>(text->scene());
    auto& dictionary = scene->branchDictionary;
    auto& branches = scene->branches;
    branchLabel = new QLabel("Branch");
    functionLabel = new QLabel("Function");
    englishLabel = new QLabel("English");
    branchEdit = new QLineEdit;
    auto oldText = text->branch;
    branchEdit->setText(oldText);
    QStringList list;
    for (auto i = dictionary.begin(); i != dictionary.end(); i++)
    {
        list << i.key();
    }
    branchCompleter = new QCompleter(list);
    branchEdit->setCompleter(branchCompleter);
    functionEdit = new QLineEdit;
    functionEdit->setReadOnly(true);
    englishEdit = new QLineEdit;
    englishEdit->setReadOnly(true);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(branchEdit, &QLineEdit::textChanged, [&](const QString& newText)
    {
        if (dictionary.contains(newText))
        {
            auto english = dictionary[newText];
            englishEdit->setText(english);
            if (branches.contains(english)) functionEdit->setText(branches[english]);
            else functionEdit->setText("");
        }
        else
        {
            englishEdit->setText("");
            functionEdit->setText("");
        }
    });
    if (dictionary.contains(oldText))
    {
        auto english = dictionary[oldText];
        englishEdit->setText(english);
        if (branches.contains(english)) functionEdit->setText(branches[english]);
    }
    auto layout = new QGridLayout;
    layout->addWidget(branchLabel, 0, 0);
    layout->addWidget(branchEdit, 1, 0);
    layout->addWidget(englishLabel, 2, 0);
    layout->addWidget(englishEdit, 3, 0);
    layout->addWidget(functionLabel, 4, 0);
    layout->addWidget(functionEdit, 5, 0);
    layout->addWidget(buttonBox, 6, 0);
    setLayout(layout);
    setWindowTitle("编辑branch");
}

QString BranchDialog::getBranch() const
{
    return branchEdit->text();
}
