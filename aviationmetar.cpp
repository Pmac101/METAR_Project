#include "aviationmetar.h"
#include "ui_aviationmetar.h"

AviationMetar::AviationMetar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AviationMetar)
{
    ui->setupUi(this);
}

AviationMetar::~AviationMetar()
{
    delete ui;
}

// ---------------------------------------------------------------------------

