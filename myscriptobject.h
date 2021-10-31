#ifndef MYSCRIPTOBJECT_H
#define MYSCRIPTOBJECT_H

#include <QObject>
#include <QScriptEngine>
#include <QScriptable>

class popa: public QObject, protected QScriptable
{
    Q_OBJECT
public slots:
    void doSomething()
    {
      context()->throwError("Threw an error from a slot");
    }
    QString doSomethingElse()
    {
      return qscriptvalue_cast<QString>("argumentCount()");
    }
};

#endif // MYSCRIPTOBJECT_H
