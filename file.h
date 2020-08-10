#ifndef FILE_H
#define FILE_H

#include <QObject>

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QObject *parent = nullptr);

signals:

};

#endif // FILE_H
