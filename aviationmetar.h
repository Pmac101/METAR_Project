#ifndef AVIATIONMETAR_H
#define AVIATIONMETAR_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class AviationMetar; }
QT_END_NAMESPACE

class AviationMetar : public QMainWindow
{
    Q_OBJECT

public:
    AviationMetar(QWidget *parent = nullptr);
    ~AviationMetar();

private slots:

private:
    QNetworkAccessManager m_manager;
    Ui::AviationMetar *ui;
};
#endif // AVIATIONMETAR_H
