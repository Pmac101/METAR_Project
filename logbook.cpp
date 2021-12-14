/** @file logbook.cpp
 *  @brief logbook implementation file
 *
 *  contains the creation of a table widget and functions to create/edit an existing xml file
 *
 *  @author patrick mccormick
 *  @bug override of ~logbook() triggers warning
 */

#include "logbook.h"
#include "ui_logbook.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QtCore>
#include <QtXml>


logbook::logbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logbook)
{
    ui->setupUi(this);

    // Setup tableWidget
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList{"Date","Aircraft","Departure","Destination","Total Time"});
    ui->tableWidget->setSelectionBehavior(QTableView::SelectRows);
}


logbook::~logbook()
{
    delete ui;
}

// LO1a. At least one class in a header file with non-trivial methods implemented in a cpp file
// overrides logbook::~logbook() function above
void QDialog::closeEvent(QCloseEvent *logbook)
{
    logbook->ignore();
    QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Confirm", "Are you sure you want to close the logbook? Any unsaved data will be lost.", QMessageBox::Yes | QMessageBox::No);

    if(confirmation == QMessageBox::Yes)
    {
        logbook->accept();

    }

}

void logbook::on_pushButton_2_clicked()
{
    QString xmlFilePath = QFileDialog::getOpenFileName(this, "open file");

    QDomDocument document;
    QFile file(xmlFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return;
    }
    else
    {
        if (!document.setContent(&file))
        {
            qDebug() << "Failed to load file";
            return;
        }

        file.close();
    }

    QDomElement root = document.firstChildElement();

    loadFile(root, "Flight", "Name");
    qDebug() << "File loaded successfully";

    QDomNodeList flights = root.elementsByTagName("Flight");
    QDomNodeList dates = root.elementsByTagName("Date");
    QDomNodeList airplanes = root.elementsByTagName("Aircraft");
    QDomNodeList departures = root.elementsByTagName("Departure");
    QDomNodeList destinations = root.elementsByTagName("Destination");
    QDomNodeList times = root.elementsByTagName("Time");

    for(int i = 0; i < flights.count(); i++)
        {
            QDomNode flightNode = flights.at(i);
            QDomNode dateNode = dates.at(i);
            QDomNode airplaneNode = airplanes.at(i);
            QDomNode departureNode = departures.at(i);
            QDomNode destinationNode = destinations.at(i);
            QDomNode timeNode = times.at(i);

            if(flightNode.isElement())
            {
                QDomElement dateElement = dateNode.toElement();
                QDomElement airplaneElement = airplaneNode.toElement();
                QDomElement departureElement = departureNode.toElement();
                QDomElement destinationElement = destinationNode.toElement();
                QDomElement timeElement = timeNode.toElement();

                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(dateElement.attribute("Name")));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(airplaneElement.attribute("Name")));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(departureElement.attribute("Name")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(destinationElement.attribute("Name")));
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(timeElement.attribute("Name")));
            }
        }
}


void logbook::on_pushButton_4_clicked()
{
    QString date = ui->lineEdit->text();
    QString aircraft = ui->lineEdit_2->text();
    QString departure = ui->lineEdit_3->text();
    QString destination = ui->lineEdit_4->text();
    QString time = ui->lineEdit_5->text();

    if (date.isEmpty() || aircraft.isEmpty() || departure.isEmpty() || destination.isEmpty() || time.isEmpty())
    {
        QMessageBox::information(this, "Empty Field", "All fields must be filled in before you can add an entry.");
        return;
    }

    const int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row,0,new QTableWidgetItem(date));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(aircraft));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(departure));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(destination));
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(time));

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}


void logbook::on_pushButton_5_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}


void logbook::on_pushButton_6_clicked()
{
    QDomDocument document;

    QDomElement root = document.createElement("Flights");

    document.appendChild(root);

     // Adding more elements
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QDomElement flights = document.createElement("Flight");
        flights.setAttribute("Name", "Flight Entry " + QString::number(i));
        flights.setAttribute("ID", QString::number(i));
        root.appendChild(flights);

        QDomElement date = document.createElement("Date");
        date.setAttribute("Name", ui->tableWidget->item(i,0)->text());
        flights.appendChild(date);

        QDomElement aircraft = document.createElement("Aircraft");
        aircraft.setAttribute("Name", ui->tableWidget->item(i,1)->text());
        flights.appendChild(aircraft);

        QDomElement departure = document.createElement("Departure");
        departure.setAttribute("Name", ui->tableWidget->item(i,2)->text());
        flights.appendChild(departure);

        QDomElement destination = document.createElement("Destination");
        destination.setAttribute("Name", ui->tableWidget->item(i,3)->text());
        flights.appendChild(destination);

        QDomElement time = document.createElement("Time");
        time.setAttribute("Name", ui->tableWidget->item(i,4)->text());
        flights.appendChild(time);
    }

        // Writing to a file
        QString userFileName = QFileDialog::getSaveFileName(this, tr("Save as"),QString(), tr("xml (*.xml)"));
        QFile file(userFileName);

        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Open the file for writing failed";
        }
        else
        {
            QTextStream stream(&file);
            stream << document.toString();
            file.close();
            qDebug() << "Writing is done";
        }
}

void logbook::loadFile(QDomElement root, QString tag, QString att)
{
    QDomNodeList nodes = root.elementsByTagName(tag);

    qDebug() << "# nodes = " << nodes.count();

    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);

        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.attribute(att);
        }
    }
}
