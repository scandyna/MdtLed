#include "LedTest.h"
#include "Mdt/Led.h"
#include <QtTest/QtTest>
#include <QApplication>

void LedTest::sandbox()
{
}

/*
 * Main
 */

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  LedTest test;

  return QTest::qExec(&test, argc, argv);
}
