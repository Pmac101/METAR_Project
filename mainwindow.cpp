#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>


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
    QString airportID = ui->lineEdit->text(); // need to add code to check for proper text input format so program does not crash
    request.setUrl(QUrl("https://api.checkwx.com/metar/" + airportID + "?x-api-key=429d0470f1b747b4b9de564ff9"));
    manager->get(request);
}


void MainWindow::metarConversion(QString rawMetar) //works
{

    QList<QString> metarVector;
    QString weatherData = "";
    QString word = " ";



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
