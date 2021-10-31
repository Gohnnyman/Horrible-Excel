#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QObject>
#include <QScriptEngine>
#include <QScriptable>

class ExcelTable;

class Calculator: public QObject, protected QScriptable
{
    Q_OBJECT
    const ExcelTable* parentTable;
public:
    Calculator(const ExcelTable* table);
public slots:
    QScriptValue mmax();
    QScriptValue mmin();
    QScriptValue max();
    QScriptValue min();
    QScriptValue link();
};

#endif // CALCULATOR_H
