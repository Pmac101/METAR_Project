/** @file mainwindow.h
 *  @brief logbook header file
 *
 *  header file containing functions and variables used with the MainWindow widget
 *
 *  @author patrick mccormick
 *  @bug no known bugs
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logbook.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// LO1. Design and implement a class.
//
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /** @brief [event] UI creation
     *
     *  constructs MainWindow widget
     *
     *  @param parent   the new parent to become a window
     *
     *  @return void
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    /** @brief [signal] retrieves API info
     *
     *   when button is pressed, a request is sent to API and the retrieved data is then displayed in MainWindow widget
     *
     *  @return void
     */
    void on_pushButton_clicked();


    /** @brief [signal] opens logbook
     *
     *   when button is pressed, the logbook window is opened
     *
     *  @return void
     */
    void on_pushButton_2_clicked();

// LO6. Use object-oriented encapsulation mechanisms such as interfaces and private members.
private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString answer;

    /** @brief breaks up raw metar into sections
     *
     *   takes the raw metar string and breakes it into sections that are individually displayed within the MainWindow widget
     *
     *   @param rawMetar    the entire metar string
     *
     *  @return void
     */
    void metarConversion(QString rawMetar);
};
#endif // MAINWINDOW_H
