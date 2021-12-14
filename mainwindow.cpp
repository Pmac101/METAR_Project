/** @file logbook.h
 *  @brief logbook header file
 *
 *  header file containing functions and variables used the logbook widget
 *
 *  @author patrick mccormick
 *  @bug no known bugs
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logbook.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QString>
#include <QTableView>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager();
    QObject::connect(manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply *reply) {
                if (reply->error()) {
                    qDebug() << reply->errorString();
                    return;
                }
                answer = reply->readAll();
                ui->label_14->setText(answer.QString::mid(10, answer.size()-25));
                metarConversion(answer);
            }
        );
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // works
{
    QString airportID = ui->lineEdit->text();

    if (airportID.contains(QRegularExpression("[^a-zA-Z]"))){

        QMessageBox errorBox;
        errorBox.warning(this, "Invalid Input", "You must enter a proper ICAO airport identifier consisting of 4 letters.");
    }

    else if (airportID.length() != 4){
        QMessageBox errorBox;
        errorBox.warning(this, "Invalid Input", "You must enter 4 letters.");
    }

    else {
        request.setUrl(QUrl("https://api.checkwx.com/metar/" + airportID + "?x-api-key=429d0470f1b747b4b9de564ff9"));
        manager->get(request);
    }
}


void MainWindow::metarConversion(QString rawMetar)
{

    QList<QString> metarVector;
    QString weatherData = "";
    QString word = " ";

    // LO7. Define and use iterators and other operations on aggregates, including operations that take functions as arguments.
    for (auto x : rawMetar) {
        if (x == ' ') {
            metarVector.push_back(word);
            if (word == "RMK") {
                break;
            }
            else {
                word = "";
            }
        }
        else {
            word = word + x;
        }
    }

    int vecSize = metarVector.size();

    // LO7. Define and use iterators and other operations on aggregates, including operations that take functions as arguments.
    for (int i = 4; i < (vecSize - 3); i++) {
        weatherData.append(metarVector[i]+ " ");
    }

    QString time = metarVector.at(1);
    ui->label_8->setText(time);

    QString windDirectionSpeed =  metarVector.at(2).QString::mid(0,3) + "@" +  metarVector.at(2).QString::mid(3,4);
    ui->label_9->setText(windDirectionSpeed);

    QString visibility = metarVector.at(3);
    ui->label_10->setText(visibility);

    ui->label_11->setText(weatherData);

    QString tempDew = metarVector.at(vecSize-3);
    ui->label_12->setText(tempDew);

    QString altimeter = metarVector.at(vecSize-2).QString::mid(1,2) + "." + metarVector.at(vecSize-2).QString::mid(3,2);
    ui->label_13->setText(altimeter);
}

void MainWindow::on_pushButton_2_clicked() // works
{
    logbook user_logbook;
    user_logbook.setModal(true);
    user_logbook.exec();
}
