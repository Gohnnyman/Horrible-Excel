#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include "exceltable.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(FirsText, BasicOperations) {
  ExcelTable exceltable;
  int argc;
  char **argv = nullptr;
  QApplication app(argc, argv);

  EXPECT_EQ("true", exceltable.calculate("=1 + 1 = 2").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=1 + 1 + 2 = 4").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=1 * 1 / 1 = 1").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=(1 * 5) / (3 - 1) = 2.5").toStdString());
}


TEST(FirsText, MaxAndMin) {
  ExcelTable exceltable;
  int argc;
  char **argv = nullptr;
  QApplication app(argc, argv);

  EXPECT_EQ("true", exceltable.calculate("=max(1, 2) = 2").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=min(-2, 5) = -2").toStdString());
  EXPECT_EQ("Error: Wrong number of arguments", exceltable.calculate("=min(1, 2, 3) = 1").toStdString());
}

TEST(FirsText, MmaxAndMmin) {
  ExcelTable exceltable;
  int argc;
  char **argv = nullptr;
  QApplication app(argc, argv);

  EXPECT_EQ("true", exceltable.calculate("=mmax(1, 2, 3, 4, 5) = 5").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=mmin(10, -2, 5, 3, 3) = -2").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=mmax(1 * 2 + 3, 1 + 2 * 3, 1 + 2 + 3) = 7").toStdString());
}

TEST(FirsText, CompareOperations) {
  ExcelTable exceltable;
  int argc;
  char **argv = nullptr;
  QApplication app(argc, argv);

  EXPECT_EQ("false", exceltable.calculate("=1 * 3 < 3").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=1 * 2 < 4").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=228 > 3").toStdString());
}

TEST(FirsText, NotOperator) {
  ExcelTable exceltable;
  int argc;
  char **argv = nullptr;
  QApplication app(argc, argv);

  EXPECT_EQ("false", exceltable.calculate("=0").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=1").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=not 0").toStdString());
}

TEST(FirsText, LinksTest) {
  ExcelTable exceltable;
  int argc;
  char **argv = nullptr;
  QApplication app(argc, argv);

  exceltable.saveToCell(0, 0, "1");
  exceltable.saveToCell(0, 1, "2");
  exceltable.saveToCell(0, 2, "3");

  EXPECT_EQ("true", exceltable.calculate("=mmax(A0, B0, C0) = 3").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=(A0 + B0) = 3").toStdString());
  EXPECT_EQ("true", exceltable.calculate("=not(A0 - 1)").toStdString());
}


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    ExcelTable exceltable;

    engine.rootContext()->setContextProperty("ExcelTable", &exceltable);

    engine.load(url);

    return app.exec();
}
