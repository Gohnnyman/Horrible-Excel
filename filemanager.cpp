#include "filemanager.h"
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

FileManager::FileManager(QObject *parent) : QWidget()
{

}

void FileManager::save(QStringList data)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Зберегти",
                                                    QDir::currentPath() + "/table.xcl",
                                                    tr("Horrible excel (*.xcl)"));
    if(fileName == "") return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(const auto& it: data)
    {
        out << it << '\n';
    }

}

QStringList FileManager::open()
{
    QStringList stringList;
    try
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Відкрити horrible excel", QDir::currentPath(), "Horrible excel (*.xcl)");
        if(fileName == "") return stringList;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return stringList;

        QTextStream in(&file);
        while (!in.atEnd()) {
            stringList.append(in.readLine());
        }
    }
    catch(std::exception e)
    {
        QMessageBox msgBox;
        msgBox.setText("Помилка відкриття файлу");
        msgBox.exec();
    }
    return stringList;
}


