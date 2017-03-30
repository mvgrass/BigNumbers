#include "reference.h"
#include "ui_reference.h"

Reference::Reference( QPushButton* button,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reference), b(button)
{
    ui->setupUi(this);
}

Reference::~Reference()
{
    delete ui;
}

void Reference::on_pushButton_clicked()
{
    this->close();
}

void Reference::closeEvent(QCloseEvent *ev)
{
    b->setEnabled(true);
    QDialog::closeEvent(ev);
}
