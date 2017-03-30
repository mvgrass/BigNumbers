#ifndef REFERENCE_H
#define REFERENCE_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class Reference;
}

class Reference : public QDialog
{
    Q_OBJECT

public:
    explicit Reference(QPushButton* button,QWidget* parent = 0);
    ~Reference();

private slots:
    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Reference *ui;
    QPushButton *b;
};

#endif // REFERENCE_H
