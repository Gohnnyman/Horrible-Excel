#include "calculator.h"
#include "exceltable.h"
#include <QDebug>
#include <QtMath>


QScriptValue Calculator::mmax()
{
    if(argumentCount() == 0)
        return context()->throwError("Wrong number of arguments");

    double max = context()->argument(0).toNumber();
    for(int i = 1; i < argumentCount(); ++i)
    {
        max = std::max(max, context()->argument(i).toNumber());
    }
    return max;
}

QScriptValue Calculator::mmin()
{
    if(argumentCount() == 0)
        return context()->throwError("Wrong number of arguments");

    double min = context()->argument(0).toNumber();
    for(int i = 1; i < argumentCount(); ++i)
    {
        min = std::min(min, context()->argument(i).toNumber());
    }
    return min;
}

QScriptValue Calculator::max()
{
    if(argumentCount() > 2)
        return context()->throwError("Wrong number of arguments");

    return std::max(context()->argument(0).toNumber(), context()->argument(1).toNumber());
}

QScriptValue Calculator::min()
{
    if(argumentCount() > 2)
        return context()->throwError("Wrong number of arguments");

    return std::min(context()->argument(0).toNumber(), context()->argument(1).toNumber());
}

QScriptValue Calculator::link()
{
    QString str = context()->argument(0).toString();
    QRegExp rowRx("\\d+");
    QRegExp columnRx("[A-Z]+");
    rowRx.indexIn(str);
    columnRx.indexIn(str);

    QString rowStr = str.right(rowRx.matchedLength());
    QString columnStr = str.left(columnRx.matchedLength());

    int column = 0;

    for(int i = 0; i < columnStr.size(); ++i)
    {
        column += (columnStr[columnStr.size() - 1 - i].unicode() - 65) * qPow(26, i);
    }
    QString tmp = parentTable->getCellText(rowStr.toInt(), column);
    bool isOk;
    int ans = tmp.toInt(&isOk);

    if(isOk) return ans;
    else return engine->evaluate(tmp);
}

Calculator::Calculator(const ExcelTable* table) : parentTable(table)
{
    engine = new QScriptEngine();
}
