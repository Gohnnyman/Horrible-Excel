#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QWidget>

class FileManager : public QWidget
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    void save(QStringList data);
    QStringList open();
signals:



};

#endif // FILEMANAGER_H
