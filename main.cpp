/** @file main.cpp
 *  @brief main implementation file
 *
 *  main program file. opens MainWindow widget
 *
 *  @author patrick mccormick
 *  @bug no known bugs
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
