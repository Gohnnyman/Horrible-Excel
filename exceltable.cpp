#include "exceltable.h"
#include <QScriptEngine>
#include <QScriptable>
#include <QHash>
#include <QHashIterator>
#include <QMessageBox>
#include "calculator.h"
#include "filemanager.h"

ExcelTable::ExcelTable(QObject *parent) : QAbstractTableModel(parent)
{
}

int ExcelTable::rowCount(const QModelIndex &) const
{
    return rows;
}

int ExcelTable::columnCount(const QModelIndex &) const
{
    return columns;
}

QString ExcelTable::calculate(QString str) const
{
    if(!str.size() || str[0] != '=') return str;
    str = str.toUpper();
    str.remove(0, 1);

    str.replace("MMAX", "Calculator.mmax");
    str.replace("MMIN", "Calculator.mmin");

    str.replace("MAX", "Calculator.max");
    str.replace("MIN", "Calculator.min");

    str.replace("=", "==", Qt::CaseInsensitive);

    str.replace("NOT", "!", Qt::CaseInsensitive);

    str.replace("TRUE", "true", Qt::CaseInsensitive);
    str.replace("FALSE", "false", Qt::CaseInsensitive);

    str.replace(QRegExp("([A-Z]+\\d+)"), "Calculator.link(\"\\1\")");


//    QScriptEngine engine;
    Calculator *calculator = new Calculator(this);
    QScriptValue objectValue = calculator->engine->newQObject(calculator);
    QScriptValue result;

    calculator->engine->globalObject().setProperty("Calculator", objectValue);

    QScriptSyntaxCheckResult checker = calculator->engine->checkSyntax(str);

    result = calculator->engine->evaluate(str);

    if(calculator->engine->hasUncaughtException())
    {
        if(checker.state() == QScriptSyntaxCheckResult::Error)
            return QString("%1:%2 %3").arg(checker.errorLineNumber()).arg(checker.errorColumnNumber())
                    .arg(calculator->engine->uncaughtException().toString());
        else
            return calculator->engine->uncaughtException().toString();
    }

    str = calculator->engine->evaluate(str).toString();
    return str;
}

QString ExcelTable::getCurrentEditText()
{
    return currentEditText;
}

void ExcelTable::setCurrentEditText(QString line)
{
    currentEditText = line;
    emit textEditChanged(line);
}

QVariant ExcelTable::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return calculate(cells[index].text);
    case Qt::EditRole:
        return cells[index].text;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> ExcelTable::roleNames() const
{
    return {{Qt::DisplayRole, "cellText"},
        {Qt::EditRole, "rawCellText"}};
}

void ExcelTable::saveToCell(int row, int column, const QString string)
{
    if(string.size() > 0)
    {
        cells[index(row, column)].text = string;
    }
}

QString ExcelTable::getCellText(int row, int column) const
{
    return calculate(cells[index(row, column)].text);
}

QModelIndex ExcelTable::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QStringList ExcelTable::prepareForSave()
{
    QStringList tmp;

    QHash<QModelIndex, Cell>::const_iterator i = cells.constBegin();
    while (i != cells.constEnd()) {
        if(i.value().text != "") tmp.push_back(QString("%1;%2;%3").arg(i.key().row()).arg(i.key().column()).arg(i.value().text));
        ++i;
    }
    return tmp;
}

void ExcelTable::saveFile()
{
    FileManager fileManager;
    fileManager.save(prepareForSave());
}

void ExcelTable::openFile()
{
    try
    {
        FileManager fileManager;
        QStringList stringList = fileManager.open();
        QStringList tmp;
        QString text;
        int row, column;
        if(stringList.size() == 0) return;
        QHash <QModelIndex, Cell> tmpCells;
        for(const auto& it: stringList)
        {
            tmp = it.split(";", Qt::SkipEmptyParts);
            if(tmp.size() != 3) throw std::exception();
            row = tmp[0].toInt();
            column = tmp[1].toInt();
            text = tmp[2];
            tmpCells[index(row, column)].text = text;
        }
        cells.clear();
        cells = std::move(tmpCells);
        emit dataChanged(index(0,0), index(rows, columns));
    }  catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Помилка відкриття файлу");
        msgBox.exec();
    }
}

QStringList ExcelTable::getHeader() const
{
    QStringList lst;
    QString current = "A";
    for(int i = 0; i < columns; ++i)
    {
        lst.append(current);
        for(int j = current.size() - 1; j >= 0; --j)
        {
            current[j] = current[j].unicode() + 1;
            if(current[j] == 91)
            {
                current[j] = 65;
                if(j == 0)
                {
                    current.push_front(64);
                    j++;
                }
            } else
            {
                break;
            }
        }
    }
    return lst;
}

void ExcelTable::addColumn()
{
    columns++;
}

void ExcelTable::addRow()
{
    rows++;
}

void ExcelTable::removeColumn()
{
    columns--;
    for(int i = 0; i < rows; ++i)
    {
        cells[index(i, columns)].text = "";
    }
}

void ExcelTable::removeRow()
{
    rows--;
    for(int i = 0; i < columns; ++i)
    {
        cells[index(rows, i)].text = "";
    }
}


void ExcelTable::selectCell(int row, int column)
{
    qDebug() << "Selected " << row << ' ' << column;
    lastSelectedCell = &cells[index(row, column)];
}

QString ExcelTable::getLastCellText()
{
    return QString("%1").arg(lastSelectedCell->text);
}

void ExcelTable::saveLastCellText()
{
    if(lastSelectedCell != nullptr) lastSelectedCell->text = currentEditText;
    emit dataChanged(index(0,0), index(rows, columns));
}
