#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include <QLabel>
#include <QPropertyAnimation>
#include <QComboBox>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QScrollArea>

#include "reference.h"

#include "natural.h"
#include "integer.h"
#include "rational.h"
#include "polinom.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_NatButton_clicked();

    void on_IntButton_clicked();

    void on_RatButton_clicked();

    void on_PolButton_clicked();

    void on_reference_clicked();

private:
    Ui::MainWindow *ui;

    enum {None, Nat, Int, Rat, Pol} state;

    QList<QPushButton*> ButtonsList;
    QList<QTextEdit*> EditsList;
    QList<QLabel*> LabelsList;
    QList<QComboBox*>BoxesList;
    QList<QLayout*>LayoutsList;
    QList<QSpacerItem*>SpacersList;


    QList<QComboBox*>BoxesListA;
    QList<QLineEdit*> LineEditsListA;
    QList<QLabel*> LabelsListA;
    QList<QTextEdit*> EditsListA;

    QList<QComboBox*>BoxesListB;
    QList<QLineEdit*> LineEditsListB;
    QList<QLabel*> LabelsListB;
    QList<QTextEdit*> EditsListB;

    QScrollArea* ApolArea = nullptr;
    QScrollArea* BpolArea = nullptr;
    QWidget* ApolWidg = nullptr;
    QWidget* BpolWidg = nullptr;
    int ApolCounter = 1;
    int BpolCounter = 1;

    bool validation(QString &);

    void drawAnimation(QWidget *);

    void delWidgets();

    void printNatural(const Natural&,QTextEdit&);

    void printInteger(Integer&,QTextEdit&);

    void printRational(Rational&,QTextEdit&);

    void printPolinom(Polinom&);

    void printIncorrect();
};

#endif // MAINWINDOW_H
