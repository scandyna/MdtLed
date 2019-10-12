
#include "Mdt/Led.h"
#include <QtTest/QtTest>
#include <QApplication>

void MdtLedTestPackage::runled()
{
  Mdt::Led led;

  led->show();

  QTest::qWait(100);
}

/*
 * Main
 */

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  MdtLedTestPackage test;

  return QTest::qExec(&test, argc, argv);
}
