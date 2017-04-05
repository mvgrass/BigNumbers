#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    state = None;
}

MainWindow::~MainWindow()
{
    delWidgets();
    delete ui;
}

void MainWindow::on_NatButton_clicked()
{
    if(state == Nat)
        return;

    state = Nat;

    delWidgets();

    QLabel* Alab= new QLabel(this);
    Alab->setText("Введите число A");
    LabelsList.append(Alab);
    ui->horizontalLayout->addWidget(Alab);

    QTextEdit* A = new QTextEdit(this);
    A->setText("0");
    EditsList.append(A);
    ui->horizontalLayout->addWidget(A);

    QLabel* Blab= new QLabel(this);
    Blab->setText("Введите число B");
    LabelsList.append(Blab);
    ui->horizontalLayout->addWidget(Blab);

    QTextEdit* B = new QTextEdit(this);
    B->setText("0");
    EditsList.append(B);
    ui->horizontalLayout->addWidget(B);

    QLabel* Anslab= new QLabel(this);
    Anslab->setText("Ответ");
    LabelsList.append(Anslab);
    ui->horizontalLayout->addWidget(Anslab);

    QTextEdit* ans = new QTextEdit(this);
    EditsList.append(ans);
    ui->horizontalLayout->addWidget(ans);

    QPushButton* plusOneA = new QPushButton(this);
    plusOneA->setText("A + 1");
    ButtonsList.append(plusOneA);
    ui->verticalLayout_3->addWidget(plusOneA);

    QPushButton* plusOneB = new QPushButton(this);
    plusOneB->setText("B + 1");
    ButtonsList.append(plusOneB);
    ui->verticalLayout_3->addWidget(plusOneB);

    QPushButton* plus = new QPushButton(this);
    plus->setText("A + B");
    ButtonsList.append(plus);
    ui->verticalLayout_3->addWidget(plus);

    QPushButton* AminusB = new QPushButton(this);
    AminusB->setText("|A - B|");
    ButtonsList.append(AminusB);
    ui->verticalLayout_3->addWidget(AminusB);


    QPushButton* multiply = new QPushButton(this);
    multiply->setText("A * B");
    ButtonsList.append(multiply);
    ui->verticalLayout_3->addWidget(multiply);

    QPushButton* gcd = new QPushButton(this);
    gcd->setText("НОД");
    ButtonsList.append(gcd);
    ui->verticalLayout_3->addWidget(gcd);

    QPushButton* lcm = new QPushButton(this);
    lcm->setText("НОК");
    ButtonsList.append(lcm);
    ui->verticalLayout_3->addWidget(lcm);


    plusOneA->show();

    plusOneB->show();

    plus->show();

    AminusB->show();

    multiply->show();

    gcd->show();

    lcm->show();

    Alab->show();

    A->setFixedHeight(3*ui->NatButton->height());
    A->show();

    Blab->show();

    B->setFixedHeight(3*ui->NatButton->height());
    B->show();

    Anslab->show();

    ans->setFixedHeight(3*ui->NatButton->height());
    ans->show();

    drawAnimation(plusOneA);
    drawAnimation(plusOneB);
    drawAnimation(plus);
    drawAnimation(AminusB);
    drawAnimation(multiply);
    drawAnimation(gcd);
    drawAnimation(lcm);
    drawAnimation(A);
    drawAnimation(B);
    drawAnimation(ans);

    connect(plusOneA,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");
        bool flag = validation(A);

        if(flag){
            Natural a(std::string(A.toLocal8Bit().constData()));

            a = a.ADD_1N_N();

            printNatural(a,*this->EditsList[0]);
        }else
            this->EditsList[2]->setText("Некорректные данные");
    });

    connect(plusOneB,&QPushButton::clicked,[=](){
        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool flag = validation(B);
        if(flag){
            Natural b(std::string(B.toLocal8Bit().constData()));

            b = b.ADD_1N_N();

            printNatural(b,*this->EditsList[1]);
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(plus,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");
        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        if(f1&&f2){
            Natural* a = new Natural(std::string(A.toLocal8Bit().constData()));
            Natural* b = new Natural(std::string(B.toLocal8Bit().constData()));

            Natural* c = new Natural(a->ADD_NN_N(*b));

            printNatural(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(AminusB,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");
        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        if(f1&&f2){
            Natural* a = new Natural(std::string(A.toLocal8Bit().constData()));
            Natural* b = new Natural(std::string(B.toLocal8Bit().constData()));

            Natural* c = new Natural(a->SUB_NN_N(*b));

            printNatural(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(multiply,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");
        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        if(f1&&f2){
            Natural* a = new Natural(std::string(A.toLocal8Bit().constData()));
            Natural* b = new Natural(std::string(B.toLocal8Bit().constData()));

            Natural* c = new Natural(a->MUL_NN_N(*b));

            printNatural(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(gcd,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");
        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        if(f1&&f2){
            Natural* a = new Natural(std::string(A.toLocal8Bit().constData()));
            Natural* b = new Natural(std::string(B.toLocal8Bit().constData()));

            Natural* c = new Natural(a->GCF_NN_N(*b));

            printNatural(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(lcm,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");
        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        if(f1&&f2){
            Natural* a = new Natural(std::string(A.toLocal8Bit().constData()));
            Natural* b = new Natural(std::string(B.toLocal8Bit().constData()));

            Natural* c = new Natural(a->LCM_NN_N(*b));

            printNatural(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

}

void MainWindow::on_IntButton_clicked()
{
    if(state == Int)
        return;

    state = Int;

    delWidgets();

    QLabel* Alab= new QLabel(this);
    Alab->setText("Введите число A");
    LabelsList.append(Alab);
    ui->horizontalLayout->addWidget(Alab);

    QComboBox* sign1 = new QComboBox(this);
    sign1->addItem("+");
    sign1->addItem("-");
    BoxesList.append(sign1);
    ui->horizontalLayout->addWidget(sign1);

    QTextEdit* A = new QTextEdit(this);
    A->setText("0");
    EditsList.append(A);
    ui->horizontalLayout->addWidget(A);

    QLabel* Blab= new QLabel(this);
    Blab->setText("Введите число B");
    LabelsList.append(Blab);
    ui->horizontalLayout->addWidget(Blab);

    QComboBox* sign2 = new QComboBox(this);
    sign2->addItem("+");
    sign2->addItem("-");
    BoxesList.append(sign2);
    ui->horizontalLayout->addWidget(sign2);

    QTextEdit* B = new QTextEdit(this);
    B->setText("0");
    EditsList.append(B);
    ui->horizontalLayout->addWidget(B);

    QLabel* Anslab= new QLabel(this);
    Anslab->setText("Ответ");
    LabelsList.append(Anslab);
    ui->horizontalLayout->addWidget(Anslab);

    QTextEdit* ans = new QTextEdit(this);
    EditsList.append(ans);
    ui->horizontalLayout->addWidget(ans);

    QPushButton* plus = new QPushButton(this);
    plus->setText("A + B");
    ButtonsList.append(plus);
    ui->verticalLayout_3->addWidget(plus);

    QPushButton* minus = new QPushButton(this);
    minus->setText("A - B");
    ButtonsList.append(minus);
    ui->verticalLayout_3->addWidget(minus);

    QPushButton* multiply = new QPushButton(this);
    multiply->setText("A * B");
    ButtonsList.append(multiply);
    ui->verticalLayout_3->addWidget(multiply);

    QPushButton* div = new QPushButton(this);
    div->setText("A div B");
    ButtonsList.append(div);
    ui->verticalLayout_3->addWidget(div);

    QPushButton* mod = new QPushButton(this);
    mod->setText("A mod B");
    ButtonsList.append(mod);
    ui->verticalLayout_3->addWidget(mod);

    plus->show();

    minus->show();

    multiply->show();

    div->show();

    mod->show();

    Alab->show();

    sign1->show();
    sign1->setFixedHeight(ui->NatButton->height());
    sign1->setFixedWidth(1.5*ui->NatButton->height());

    A->setFixedHeight(3*ui->NatButton->height());
    A->show();

    Blab->show();

    sign2->show();
    sign2->setFixedHeight(ui->NatButton->height());
    sign2->setFixedWidth(1.5*ui->NatButton->height());

    B->setFixedHeight(3*ui->NatButton->height());
    B->show();

    Anslab->show();

    ans->setFixedHeight(3*ui->NatButton->height());
    ans->show();

    drawAnimation(plus);
    drawAnimation(minus);
    drawAnimation(multiply);
    drawAnimation(div);
    drawAnimation(mod);
    drawAnimation(A);
    drawAnimation(B);
    drawAnimation(ans);

    connect(plus,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");

        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        A = BoxesList[0]->currentText()+A;
        B = BoxesList[1]->currentText()+B;

        if(f1&&f2){
            Integer* a = new Integer(std::string(A.toLocal8Bit().constData()));
            Integer* b = new Integer(std::string(B.toLocal8Bit().constData()));

            Integer* c = new Integer(a->ADD_ZZ_Z(*b));

            printInteger(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(minus,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");

        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        A = BoxesList[0]->currentText()+A;
        B = BoxesList[1]->currentText()+B;

        if(f1&&f2){
            Integer* a = new Integer(std::string(A.toLocal8Bit().constData()));
            Integer* b = new Integer(std::string(B.toLocal8Bit().constData()));

            Integer* c = new Integer(a->SUB_ZZ_Z(*b));

            printInteger(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(multiply,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");

        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        A = BoxesList[0]->currentText()+A;
        B = BoxesList[1]->currentText()+B;

        if(f1&&f2){
            Integer* a = new Integer(std::string(A.toLocal8Bit().constData()));
            Integer* b = new Integer(std::string(B.toLocal8Bit().constData()));

            Integer* c = new Integer(a->MUL_ZZ_Z(*b));

            printInteger(*c,*this->EditsList[2]);

            delete a;
            delete b;
            delete c;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(div,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");

        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        A = BoxesList[0]->currentText()+A;
        B = BoxesList[1]->currentText()+B;

        if(f1&&f2){
            Integer* a = new Integer(std::string(A.toLocal8Bit().constData()));
            Integer* b = new Integer(std::string(B.toLocal8Bit().constData()));

            int sign = b->POZ_Z_D();
            if(sign==2){
                Integer* c = new Integer(a->DIV_ZZ_Z(b->TRANS_Z_N()));

                printInteger(*c,*this->EditsList[2]);

                delete c;
            }else if(sign == 1){
                Integer* c = new Integer(a->DIV_ZZ_Z(b->ABS_Z_N()).MUL_ZM_Z());

                printInteger(*c,*this->EditsList[2]);

                delete c;
            }
            else
               this->EditsList[2]->setText("Деление на 0 невозможно");

            delete a;
            delete b;
        }else
            EditsList[2]->setText("Некорректные данные");
    });

    connect(mod,&QPushButton::clicked,[=](){
        QString A = this->EditsList[0]->toPlainText();
        A.replace("\n","");

        QString B = this->EditsList[1]->toPlainText();
        B.replace("\n","");

        bool f1 = validation(A);
        bool f2 = validation(B);

        A = BoxesList[0]->currentText()+A;
        B = BoxesList[1]->currentText()+B;

        if(f1&&f2){
            Integer* a = new Integer(std::string(A.toLocal8Bit().constData()));
            Integer* b = new Integer(std::string(B.toLocal8Bit().constData()));

            int sign = b->POZ_Z_D();
            if(sign==2){
                Integer* c = new Integer(a->MOD_ZZ_Z(b->TRANS_Z_N()));

                printInteger(*c,*this->EditsList[2]);

                delete c;
            }else if(sign == 1){
                Integer* c = new Integer(a->MOD_ZZ_Z(b->TRANS_Z_N()));

                printInteger(*c,*this->EditsList[2]);

                delete c;
            }
            else
                this->EditsList[2]->setText("Деление на 0 невозможно");

            delete a;
            delete b;
        }else
            EditsList[2]->setText("Некорректные данные");
    });
}

void MainWindow::on_RatButton_clicked()
{
    if(state == Rat)
        return;

    state = Rat;

    delWidgets();

    QLabel* Alab= new QLabel(this);
    Alab->setText("Введите число A");
    LabelsList.append(Alab);
    ui->horizontalLayout->addWidget(Alab);

    QComboBox* sign1 = new QComboBox(this);
    sign1->addItem("+");
    sign1->addItem("-");
    BoxesList.append(sign1);
    ui->horizontalLayout->addWidget(sign1);

    QVBoxLayout* ALayout = new QVBoxLayout();
    ALayout->setContentsMargins(0,200,0,200);
    LayoutsList.append(ALayout);

    QTextEdit* ANum = new QTextEdit(this);
    ANum->setText("0");
    EditsList.append(ANum);
    ALayout->addWidget(ANum);


    QTextEdit* ADenum = new QTextEdit(this);
    ADenum->setText("1");
    EditsList.append(ADenum);
    ALayout->addWidget(ADenum);

    ui->horizontalLayout->addLayout(ALayout);

    QLabel* Blab= new QLabel(this);
    Blab->setText("Введите число B");
    LabelsList.append(Blab);
    ui->horizontalLayout->addWidget(Blab);

    QComboBox* sign2 = new QComboBox(this);
    sign2->addItem("+");
    sign2->addItem("-");
    BoxesList.append(sign2);
    ui->horizontalLayout->addWidget(sign2);

    QVBoxLayout* BLayout = new QVBoxLayout();
    BLayout->setContentsMargins(0,200,0,200);
    LayoutsList.append(BLayout);


    QTextEdit* BNum = new QTextEdit(this);
    BNum->setText("0");
    EditsList.append(BNum);
    BLayout->addWidget(BNum);


    QTextEdit* BDenum = new QTextEdit(this);
    BDenum->setText("1");
    EditsList.append(BDenum);
    BLayout->addWidget(BDenum);

    ui->horizontalLayout->addLayout(BLayout);


    QLabel* Anslab= new QLabel(this);
    Anslab->setText("Ответ");
    LabelsList.append(Anslab);
    ui->horizontalLayout->addWidget(Anslab);

    QTextEdit* ans = new QTextEdit(this);
    EditsList.append(ans);
    ui->horizontalLayout->addWidget(ans);

    QPushButton* plus = new QPushButton(this);
    plus->setText("A + B");
    ButtonsList.append(plus);
    ui->verticalLayout_3->addWidget(plus);

    QPushButton* minus = new QPushButton(this);
    minus->setText("A - B");
    ButtonsList.append(minus);
    ui->verticalLayout_3->addWidget(minus);

    QPushButton* multiply = new QPushButton(this);
    multiply->setText("A * B");
    ButtonsList.append(multiply);
    ui->verticalLayout_3->addWidget(multiply);

    QPushButton* div = new QPushButton(this);
    div->setText("A / B");
    ButtonsList.append(div);
    ui->verticalLayout_3->addWidget(div);

    plus->show();

    minus->show();

    multiply->show();

    div->show();

    Alab->show();

    sign1->show();
    sign1->setFixedHeight(ui->NatButton->height());
    sign1->setFixedWidth(1.5*ui->NatButton->height());

    ANum->setFixedHeight(3*ui->NatButton->height());
    ANum->show();

    ADenum->setFixedHeight(3*ui->NatButton->height());
    ADenum->show();

    Blab->show();

    sign2->show();
    sign2->setFixedHeight(ui->NatButton->height());
    sign2->setFixedWidth(1.5*ui->NatButton->height());

    BNum->setFixedHeight(3*ui->NatButton->height());
    BNum->show();

    BDenum->setFixedHeight(3*ui->NatButton->height());
    BDenum->show();

    Anslab->show();

    ans->setFixedHeight(3*ui->NatButton->height());
    ans->show();

    drawAnimation(plus);
    drawAnimation(minus);
    drawAnimation(multiply);
    drawAnimation(div);
    drawAnimation(ANum);
    drawAnimation(ADenum);
    drawAnimation(BNum);
    drawAnimation(BDenum);
    drawAnimation(ans);

    connect(plus,&QPushButton::clicked,[=](){
        QString ANum = this->EditsList[0]->toPlainText();
        ANum.replace("\n","");

        QString ADenum = this->EditsList[1]->toPlainText();
        ADenum.replace("\n","");

        QString BNum = this->EditsList[2]->toPlainText();
        BNum.replace("\n","");

        QString BDenum = this->EditsList[3]->toPlainText();
        BDenum.replace("\n","");

        bool f1 = validation(ANum);
        bool f2 = validation(ADenum);
        bool f3 = validation(BNum);
        bool f4 = validation(BDenum);

        ANum = BoxesList[0]->currentText()+ANum;
        BNum = BoxesList[1]->currentText()+BNum;

        if(f1&&f2&&f3&&f4){
            Integer aNum(std::string(ANum.toLocal8Bit().constData()));
            Integer bNum(std::string(BNum.toLocal8Bit().constData()));

            Natural aDenum(std::string(ADenum.toLocal8Bit().constData()));
            Natural bDenum(std::string(BDenum.toLocal8Bit().constData()));

            Rational* a = new Rational(aNum,aDenum);
            Rational* b = new Rational(bNum,bDenum);

            if(aDenum.NZER_N_B()&&bDenum.NZER_N_B()){
                Rational* c = new Rational(a->ADD_QQ_Q(*b));

                printRational(*c,*this->EditsList[4]);

                delete c;
            }else
                this->EditsList[4]->setText("Знаменатель не должен быть равен 0");

            delete a;
            delete b;
        }else
            EditsList[4]->setText("Некорректные данные");
    });

    connect(minus,&QPushButton::clicked,[=](){
        QString ANum = this->EditsList[0]->toPlainText();
        ANum.replace("\n","");

        QString ADenum = this->EditsList[1]->toPlainText();
        ADenum.replace("\n","");

        QString BNum = this->EditsList[2]->toPlainText();
        BNum.replace("\n","");

        QString BDenum = this->EditsList[3]->toPlainText();
        BDenum.replace("\n","");

        bool f1 = validation(ANum);
        bool f2 = validation(ADenum);
        bool f3 = validation(BNum);
        bool f4 = validation(BDenum);

        ANum = BoxesList[0]->currentText()+ANum;
        BNum = BoxesList[1]->currentText()+BNum;

        if(f1&&f2&&f3&&f4){
            Integer aNum(std::string(ANum.toLocal8Bit().constData()));
            Integer bNum(std::string(BNum.toLocal8Bit().constData()));

            Natural aDenum(std::string(ADenum.toLocal8Bit().constData()));
            Natural bDenum(std::string(BDenum.toLocal8Bit().constData()));

            Rational* a = new Rational(aNum,aDenum);
            Rational* b = new Rational(bNum,bDenum);

            if(aDenum.NZER_N_B()&&bDenum.NZER_N_B()){
                Rational* c = new Rational(a->SUB_QQ_Q(*b));

                printRational(*c,*this->EditsList[4]);

                delete c;
            }else
                this->EditsList[4]->setText("Знаменатель не должен быть равен 0");

            delete a;
            delete b;
        }else
            EditsList[4]->setText("Некорректные данные");
    });

    connect(multiply,&QPushButton::clicked,[=](){
        QString ANum = this->EditsList[0]->toPlainText();
        ANum.replace("\n","");

        QString ADenum = this->EditsList[1]->toPlainText();
        ADenum.replace("\n","");

        QString BNum = this->EditsList[2]->toPlainText();
        BNum.replace("\n","");

        QString BDenum = this->EditsList[3]->toPlainText();
        BDenum.replace("\n","");

        bool f1 = validation(ANum);
        bool f2 = validation(ADenum);
        bool f3 = validation(BNum);
        bool f4 = validation(BDenum);

        ANum = BoxesList[0]->currentText()+ANum;
        BNum = BoxesList[1]->currentText()+BNum;

        if(f1&&f2&&f3&&f4){
            Integer aNum(std::string(ANum.toLocal8Bit().constData()));
            Integer bNum(std::string(BNum.toLocal8Bit().constData()));

            Natural aDenum(std::string(ADenum.toLocal8Bit().constData()));
            Natural bDenum(std::string(BDenum.toLocal8Bit().constData()));

            Rational* a = new Rational(aNum,aDenum);
            Rational* b = new Rational(bNum,bDenum);

            if(aDenum.NZER_N_B()&&bDenum.NZER_N_B()){
                Rational* c = new Rational(a->MUL_QQ_Q(*b));

                printRational(*c,*this->EditsList[4]);

                delete c;
            }else
                this->EditsList[4]->setText("Знаменаталь не должен быть равен 0");

            delete a;
            delete b;
        }else
            EditsList[4]->setText("Некорректные данные");
    });

    connect(div,&QPushButton::clicked,[=](){
        QString ANum = this->EditsList[0]->toPlainText();
        ANum.replace("\n","");

        QString ADenum = this->EditsList[1]->toPlainText();
        ADenum.replace("\n","");

        QString BNum = this->EditsList[2]->toPlainText();
        BNum.replace("\n","");

        QString BDenum = this->EditsList[3]->toPlainText();
        BDenum.replace("\n","");

        bool f1 = validation(ANum);
        bool f2 = validation(ADenum);
        bool f3 = validation(BNum);
        bool f4 = validation(BDenum);

        ANum = BoxesList[0]->currentText()+ANum;
        BNum = BoxesList[1]->currentText()+BNum;

        if(f1&&f2&&f3&&f4){
            Integer aNum(std::string(ANum.toLocal8Bit().constData()));
            Integer bNum(std::string(BNum.toLocal8Bit().constData()));

            Natural aDenum(std::string(ADenum.toLocal8Bit().constData()));
            Natural bDenum(std::string(BDenum.toLocal8Bit().constData()));

            Rational* a = new Rational(aNum,aDenum);
            Rational* b = new Rational(bNum,bDenum);

            if(aDenum.NZER_N_B()&&bDenum.NZER_N_B()&&bNum.POZ_Z_D()!=0){
                Rational* c = new Rational(a->DIV_QQ_Q(*b));

                printRational(*c,*this->EditsList[4]);

                delete c;
            }else if(!aDenum.NZER_N_B()||!bDenum.NZER_N_B())
                this->EditsList[4]->setText("Знаменатель не должен быть равен 0");
            else
                this->EditsList[4]->setText("Число \"B\" должно быть отлично от 0");

            delete a;
            delete b;
        }else
            EditsList[4]->setText("Некорректные данные");
    });

}

void MainWindow::on_PolButton_clicked()
{
    if(state == Pol)
        return;

    state = Pol;

    delWidgets();


    ApolArea = new QScrollArea(this);

    BpolArea = new QScrollArea(this);

    ApolWidg = new QWidget(this);
    ApolWidg->setFixedHeight(200);

    BpolWidg = new QWidget(this);
    BpolWidg->setFixedHeight(200);

    QVBoxLayout* mainVertical = new QVBoxLayout();
    LayoutsList.append(mainVertical);
    ui->horizontalLayout->addLayout(mainVertical);

    QHBoxLayout* APolLayout = new QHBoxLayout();
    LayoutsList.append(APolLayout);
    ApolWidg->setLayout(APolLayout);
    ApolArea->setWidget(ApolWidg);

    QHBoxLayout* BPolLayout = new QHBoxLayout();
    LayoutsList.append(BPolLayout);
    BpolWidg->setLayout(BPolLayout);
    BpolArea->setWidget(BpolWidg);

    QPushButton* AminusPol = new QPushButton(this);
    AminusPol->setText("-");
    AminusPol->setEnabled(false);
    ButtonsList.append(AminusPol);
    APolLayout->addWidget(AminusPol);

    QComboBox* sign1 = new QComboBox(this);
    sign1->addItem("+");
    sign1->addItem("-");
    BoxesListA.append(sign1);
    APolLayout->addWidget(sign1);

    QVBoxLayout* AsubLayout = new QVBoxLayout();
    LayoutsList.append(AsubLayout);
    APolLayout->addLayout(AsubLayout);

    QTextEdit* ANum = new QTextEdit(ApolWidg);
    ANum->setText("0");
    EditsListA.append(ANum);
    AsubLayout->addWidget(ANum);

    QTextEdit* ADenum = new QTextEdit(ApolWidg);
    ADenum->setText("1");
    EditsListA.append(ADenum);
    AsubLayout->addWidget(ADenum);

    QLabel* x1 = new QLabel(ApolWidg);
    x1->setText("X^");
    LabelsListA.append(x1);
    APolLayout->addWidget(x1);

    QLineEdit* Degree1 = new QLineEdit(ApolWidg);
    Degree1->setText("1");
    LineEditsListA.append(Degree1);
    APolLayout->addWidget(Degree1);

    QPushButton* AplusPol = new QPushButton(ApolWidg);
    AplusPol->setText("+");
    ButtonsList.append(AplusPol);
    APolLayout->addWidget(AplusPol);

    QSpacerItem* ASpacer = new QSpacerItem(0,0,QSizePolicy::Expanding);
    SpacersList.append(ASpacer);
    APolLayout->addSpacerItem(ASpacer);

    QPushButton* BminusPol = new QPushButton(BpolWidg);
    BminusPol->setText("-");
    BminusPol->setEnabled(false);
    ButtonsList.append(BminusPol);
    BPolLayout->addWidget(BminusPol);

    QComboBox* sign2 = new QComboBox(BpolWidg);
    sign2->addItem("+");
    sign2->addItem("-");
    BoxesListB.append(sign2);
    BPolLayout->addWidget(sign2);

    QVBoxLayout* BsubLayout = new QVBoxLayout(BpolWidg);
    LayoutsList.append(BsubLayout);
    BPolLayout->addLayout(BsubLayout);

    QTextEdit* BNum = new QTextEdit(BpolWidg);
    BNum->setText("0");
    EditsListB.append(BNum);
    BsubLayout->addWidget(BNum);

    QTextEdit* BDenum = new QTextEdit(BpolWidg);
    BDenum->setText("1");
    EditsListB.append(BDenum);
    BsubLayout->addWidget(BDenum);

    QLabel* x2 = new QLabel(BpolWidg);
    x2->setText("X^");
    LabelsListB.append(x2);
    BPolLayout->addWidget(x2);

    QLineEdit* Degree2 = new QLineEdit(BpolWidg);
    Degree2->setText("1");
    LineEditsListB.append(Degree2);
    BPolLayout->addWidget(Degree2);

    QPushButton* BplusPol = new QPushButton(BpolWidg);
    BplusPol->setText("+");
    ButtonsList.append(BplusPol);
    BPolLayout->addWidget(BplusPol);

    QSpacerItem* BSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding);
    SpacersList.append(BSpacer);
    BPolLayout->addSpacerItem(BSpacer);


    QPushButton* plus = new QPushButton(this);
    plus->setText("A + B");
    ButtonsList.append(plus);
    ui->verticalLayout_3->addWidget(plus);

    QPushButton* minus = new QPushButton(this);
    minus->setText("A - B");
    ButtonsList.append(minus);
    ui->verticalLayout_3->addWidget(minus);

    QPushButton* multiply = new QPushButton(this);
    multiply->setText("A * B");
    ButtonsList.append(multiply);
    ui->verticalLayout_3->addWidget(multiply);

    QPushButton* div = new QPushButton(this);
    div->setText("A div B");
    ButtonsList.append(div);
    ui->verticalLayout_3->addWidget(div);

    QPushButton* mod = new QPushButton(this);
    mod->setText("A mod B");
    ButtonsList.append(mod);
    ui->verticalLayout_3->addWidget(mod);

    QPushButton* nod = new QPushButton(this);
    nod->setText("НОД");
    ButtonsList.append(nod);
    ui->verticalLayout_3->addWidget(nod);

    QPushButton* NMRa = new QPushButton(this);
    NMRa->setText("Кратные корни A\n в простые");
    ButtonsList.append(NMRa);
    ui->verticalLayout_3->addWidget(NMRa);

    QPushButton* NMRb = new QPushButton(this);
    NMRb->setText("Кратные корни B\n в простые");
    ButtonsList.append(NMRb);
    ui->verticalLayout_3->addWidget(NMRb);

    ApolArea->setWidgetResizable(true);
    BpolArea->setWidgetResizable(true);

    mainVertical->addWidget(ApolArea);
    mainVertical->addWidget(BpolArea);

    ApolArea->show();
    BpolArea->show();

    plus->show();

    minus->show();

    multiply->show();

    div->show();

    mod->show();

    nod->show();

    NMRa->show();

    NMRb->show();

    AminusPol->setFixedHeight(ui->NatButton->height());
    AminusPol->setFixedWidth(ui->NatButton->height());
    AminusPol->show();

    sign1->setFixedHeight(ui->NatButton->height());
    sign1->setFixedWidth(1.5*ui->NatButton->height());
    sign1->show();

    ANum->setFixedHeight(2*ui->NatButton->height());
    ANum->setFixedWidth(100);
    ANum->show();

    ADenum->setFixedHeight(2*ui->NatButton->height());
    ADenum->setFixedWidth(100);
    ADenum->show();

    x1->show();

    Degree1->setFixedWidth(50);
    Degree1->show();

    AplusPol->setFixedHeight(ui->NatButton->height());
    AplusPol->setFixedWidth(ui->NatButton->height());
    AplusPol->show();

    BminusPol->setFixedHeight(ui->NatButton->height());
    BminusPol->setFixedWidth(ui->NatButton->height());
    BminusPol->show();

    sign2->setFixedHeight(ui->NatButton->height());
    sign2->setFixedWidth(1.5*ui->NatButton->height());
    sign2->show();

    BNum->setFixedHeight(2*ui->NatButton->height());
    BNum->setFixedWidth(100);
    BNum->show();

    BDenum->setFixedHeight(2*ui->NatButton->height());
    BDenum->setFixedWidth(100);
    BDenum->show();

    x2->show();

    Degree2->setFixedWidth(50);
    Degree2->show();

    BplusPol->setFixedHeight(ui->NatButton->height());
    BplusPol->setFixedWidth(ui->NatButton->height());
    BplusPol->show();

    drawAnimation(plus);
    drawAnimation(minus);
    drawAnimation(multiply);
    drawAnimation(div);
    drawAnimation(mod);
    drawAnimation(nod);
    drawAnimation(NMRa);
    drawAnimation(NMRb);

    connect(AplusPol,&QPushButton::clicked,[=](){


        APolLayout->removeWidget(AplusPol);
        APolLayout->removeItem(ASpacer);

        QComboBox* new_sign = new QComboBox(ApolWidg);
        new_sign->addItem("+");
        new_sign->addItem("-");
        BoxesListA.append(new_sign);
        APolLayout->addWidget(new_sign);

        QVBoxLayout* new_subLayout = new QVBoxLayout();
        //LayoutsList.append(new_subLayout);
        APolLayout->addLayout(new_subLayout);

        QTextEdit* new_Num = new QTextEdit(ApolWidg);
        new_Num->setText("0");
        EditsListA.append(new_Num);
        new_subLayout->addWidget(new_Num);

        QTextEdit* new_Denum = new QTextEdit(ApolWidg);
        new_Denum->setText("1");
        EditsListA.append(new_Denum);
        new_subLayout->addWidget(new_Denum);

        QLabel* new_x = new QLabel(ApolWidg);
        new_x->setText("X^");
        LabelsListA.append(new_x);
        APolLayout->addWidget(new_x);

        QLineEdit* new_Degree = new QLineEdit(ApolWidg);
        new_Degree->setText("1");
        LineEditsListA.append(new_Degree);
        APolLayout->addWidget(new_Degree);

        APolLayout->addWidget(AplusPol);
        APolLayout->addSpacerItem(ASpacer);
        AplusPol->show();

        new_sign->setFixedHeight(ui->NatButton->height());
        new_sign->setFixedWidth(1.5*ui->NatButton->height());
        new_sign->show();

        new_Num->setFixedHeight(2*ui->NatButton->height());
        new_Num->setFixedWidth(100);
        new_Num->show();

        new_Denum->setFixedHeight(2*ui->NatButton->height());
        new_Denum->setFixedWidth(100);
        new_Denum->show();

        new_x->show();

        new_Degree->setFixedWidth(50);
        new_Degree->show();

        AminusPol->setEnabled(true);
        ApolCounter++;
    });

    connect(BplusPol,&QPushButton::clicked,[=](){
        BPolLayout->removeWidget(BplusPol);
        BPolLayout->removeItem(BSpacer);

        QComboBox* new_sign = new QComboBox(BpolWidg);
        new_sign->addItem("+");
        new_sign->addItem("-");
        BoxesListB.append(new_sign);
        BPolLayout->addWidget(new_sign);

        QVBoxLayout* new_subLayout = new QVBoxLayout();
        LayoutsList.append(new_subLayout);
        BPolLayout->addLayout(new_subLayout);

        QTextEdit* new_Num = new QTextEdit(BpolWidg);
        new_Num->setText("0");
        EditsListB.append(new_Num);
        new_subLayout->addWidget(new_Num);

        QTextEdit* new_Denum = new QTextEdit(BpolWidg);
        new_Denum->setText("1");
        EditsListB.append(new_Denum);
        new_subLayout->addWidget(new_Denum);

        QLabel* new_x = new QLabel(BpolWidg);
        new_x->setText("X^");
        LabelsListB.append(new_x);
        BPolLayout->addWidget(new_x);

        QLineEdit* new_Degree = new QLineEdit(BpolWidg);
        new_Degree->setText("1");
        LineEditsListB.append(new_Degree);
        BPolLayout->addWidget(new_Degree);

        BPolLayout->addWidget(BplusPol);
        BPolLayout->addSpacerItem(BSpacer);
        BplusPol->show();

        new_sign->setFixedHeight(ui->NatButton->height());
        new_sign->setFixedWidth(1.5*ui->NatButton->height());
        new_sign->show();

        new_Num->setFixedHeight(2*ui->NatButton->height());
        new_Num->setFixedWidth(100);
        new_Num->show();

        new_Denum->setFixedHeight(2*ui->NatButton->height());
        new_Denum->setFixedWidth(100);
        new_Denum->show();

        new_x->show();

        new_Degree->setFixedWidth(50);
        new_Degree->show();

        BminusPol->setEnabled(true);
        BpolCounter++;
    });

    connect(AminusPol,&QPushButton::clicked,[=](){
        QWidget* tmp = LineEditsListA.first();
        LineEditsListA.removeFirst();
        delete tmp;

        tmp = LabelsListA.first();
        LabelsListA.removeFirst();
        delete tmp;

        tmp = EditsListA.first();
        EditsListA.removeFirst();
        delete tmp;

        tmp = EditsListA.first();
        EditsListA.removeFirst();
        delete tmp;

        tmp = BoxesListA.first();
        BoxesListA.removeFirst();
        delete tmp;

        if(--ApolCounter==1)
            AminusPol->setEnabled(false);
    });

    connect(BminusPol,&QPushButton::clicked,[=](){

        QWidget* tmp = LineEditsListB.first();
        LineEditsListB.removeFirst();
        delete tmp;

        tmp = LabelsListB.first();
        LabelsListB.removeFirst();
        delete tmp;

        tmp = EditsListB.first();
        EditsListB.removeFirst();
        delete tmp;

        tmp = EditsListB.first();
        EditsListB.removeFirst();
        delete tmp;

        tmp = BoxesListB.first();
        BoxesListB.removeFirst();
        delete tmp;

        if(--BpolCounter==1)
            BminusPol->setEnabled(false);
    });



    connect(plus,&QPushButton::clicked,[=](){
        bool flagA = true;
        bool flagB = true;

        std::map<Natural,Rational,Comparator> PolinomA;
        std::map<Natural,Rational,Comparator> PolinomB;

        for(int i = 0;i<LineEditsListA.size();i++){
            QString ANum = this->EditsListA[2*i]->toPlainText();
            ANum.replace("\n","");

            QString ADenum = this->EditsListA[2*i+1]->toPlainText();
            ADenum.replace("\n","");

            QString ADegree = this->LineEditsListA[i]->text();
            ADegree.replace("\n","");

            bool f1 = validation(ANum);
            bool f2 = validation(ADenum);
            bool f3 = validation(ADegree);

            ANum = BoxesListA[i]->currentText()+ANum;

            flagA = f1&&f2&&f3;

            if(flagA){
                Natural* Deg = new Natural(std::string(ADegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(ANum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(ADenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomA[*Deg] = PolinomA[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagA = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        for(int i = 0;i<LineEditsListB.size();i++){
            QString BNum = this->EditsListB[2*i]->toPlainText();
            BNum.replace("\n","");

            QString BDenum = this->EditsListB[2*i+1]->toPlainText();
            BDenum.replace("\n","");

            QString BDegree = this->LineEditsListB[i]->text();
            BDegree.replace("\n","");

            bool f1 = validation(BNum);
            bool f2 = validation(BDenum);
            bool f3 = validation(BDegree);

            BNum = BoxesListB[i]->currentText()+BNum;

            flagB = f1&&f2&&f3;

            if(flagB){
                Natural* Deg = new Natural(std::string(BDegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(BNum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(BDenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomB[*Deg] = PolinomB[*Deg].ADD_QQ_Q(*Coeff);

                else
                    flagB = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        if(flagA&&flagB){
            Polinom* a = new Polinom(PolinomA);
            Polinom* b = new Polinom(PolinomB);

            Polinom *c = new Polinom(a->ADD_PP_P(*b));

            printPolinom(*c);

            delete a;
            delete b;
            delete c;
        }else
            printIncorrect();
    });

    connect(minus,&QPushButton::clicked,[=](){
        bool flagA = true;
        bool flagB = true;

        std::map<Natural,Rational,Comparator> PolinomA;
        std::map<Natural,Rational,Comparator> PolinomB;

        for(int i = 0;i<LineEditsListA.size();i++){
            QString ANum = this->EditsListA[2*i]->toPlainText();
            ANum.replace("\n","");

            QString ADenum = this->EditsListA[2*i+1]->toPlainText();
            ADenum.replace("\n","");

            QString ADegree = this->LineEditsListA[i]->text();
            ADegree.replace("\n","");

            bool f1 = validation(ANum);
            bool f2 = validation(ADenum);
            bool f3 = validation(ADegree);

            ANum = BoxesListA[i]->currentText()+ANum;

            flagA = f1&&f2&&f3;

            if(flagA){
                Natural* Deg = new Natural(std::string(ADegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(ANum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(ADenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomA[*Deg] = PolinomA[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagA = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        for(int i = 0;i<LineEditsListB.size();i++){
            QString BNum = this->EditsListB[2*i]->toPlainText();
            BNum.replace("\n","");

            QString BDenum = this->EditsListB[2*i+1]->toPlainText();
            BDenum.replace("\n","");

            QString BDegree = this->LineEditsListB[i]->text();
            BDegree.replace("\n","");

            bool f1 = validation(BNum);
            bool f2 = validation(BDenum);
            bool f3 = validation(BDegree);

            BNum = BoxesListB[i]->currentText()+BNum;

            flagB = f1&&f2&&f3;

            if(flagB){
                Natural* Deg = new Natural(std::string(BDegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(BNum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(BDenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomB[*Deg] = PolinomB[*Deg].ADD_QQ_Q(*Coeff);

                else
                    flagB = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        if(flagA&&flagB){
            Polinom* a = new Polinom(PolinomA);
            Polinom* b = new Polinom(PolinomB);

            Polinom *c = new Polinom(a->SUB_PP_P(*b));

            printPolinom(*c);

            delete a;
            delete b;
            delete c;
        }else
            printIncorrect();
    });

    connect(multiply,&QPushButton::clicked,[=](){
        bool flagA = true;
        bool flagB = true;

        std::map<Natural,Rational,Comparator> PolinomA;
        std::map<Natural,Rational,Comparator> PolinomB;

        for(int i = 0;i<LineEditsListA.size();i++){
            QString ANum = this->EditsListA[2*i]->toPlainText();
            ANum.replace("\n","");

            QString ADenum = this->EditsListA[2*i+1]->toPlainText();
            ADenum.replace("\n","");

            QString ADegree = this->LineEditsListA[i]->text();
            ADegree.replace("\n","");

            bool f1 = validation(ANum);
            bool f2 = validation(ADenum);
            bool f3 = validation(ADegree);

            ANum = BoxesListA[i]->currentText()+ANum;

            flagA = f1&&f2&&f3;

            if(flagA){
                Natural* Deg = new Natural(std::string(ADegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(ANum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(ADenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomA[*Deg] = PolinomA[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagA = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        for(int i = 0;i<LineEditsListB.size();i++){
            QString BNum = this->EditsListB[2*i]->toPlainText();
            BNum.replace("\n","");

            QString BDenum = this->EditsListB[2*i+1]->toPlainText();
            BDenum.replace("\n","");

            QString BDegree = this->LineEditsListB[i]->text();
            BDegree.replace("\n","");

            bool f1 = validation(BNum);
            bool f2 = validation(BDenum);
            bool f3 = validation(BDegree);

            BNum = BoxesListB[i]->currentText()+BNum;

            flagB = f1&&f2&&f3;

            if(flagB){
                Natural* Deg = new Natural(std::string(BDegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(BNum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(BDenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomB[*Deg] = PolinomB[*Deg].ADD_QQ_Q(*Coeff);

                else
                    flagB = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        if(flagA&&flagB){
            Polinom* a = new Polinom(PolinomA);
            Polinom* b = new Polinom(PolinomB);

            Polinom *c = new Polinom(a->MUL_PP_P(*b));

            printPolinom(*c);

            delete a;
            delete b;
            delete c;
        }else
            printIncorrect();
    });

    connect(div,&QPushButton::clicked,[=](){
        bool flagA = true;
        bool flagB = true;

        std::map<Natural,Rational,Comparator> PolinomA;
        std::map<Natural,Rational,Comparator> PolinomB;

        for(int i = 0;i<LineEditsListA.size();i++){
            QString ANum = this->EditsListA[2*i]->toPlainText();
            ANum.replace("\n","");

            QString ADenum = this->EditsListA[2*i+1]->toPlainText();
            ADenum.replace("\n","");

            QString ADegree = this->LineEditsListA[i]->text();
            ADegree.replace("\n","");

            bool f1 = validation(ANum);
            bool f2 = validation(ADenum);
            bool f3 = validation(ADegree);

            ANum = BoxesListA[i]->currentText()+ANum;

            flagA = f1&&f2&&f3;

            if(flagA){
                Natural* Deg = new Natural(std::string(ADegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(ANum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(ADenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomA[*Deg] = PolinomA[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagA = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        for(int i = 0;i<LineEditsListB.size();i++){
            QString BNum = this->EditsListB[2*i]->toPlainText();
            BNum.replace("\n","");

            QString BDenum = this->EditsListB[2*i+1]->toPlainText();
            BDenum.replace("\n","");

            QString BDegree = this->LineEditsListB[i]->text();
            BDegree.replace("\n","");

            bool f1 = validation(BNum);
            bool f2 = validation(BDenum);
            bool f3 = validation(BDegree);

            BNum = BoxesListB[i]->currentText()+BNum;

            flagB = f1&&f2&&f3;

            if(flagB){
                Natural* Deg = new Natural(std::string(BDegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(BNum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(BDenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomB[*Deg] = PolinomB[*Deg].ADD_QQ_Q(*Coeff);

                else
                    flagB = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        if(flagA&&flagB){
            Polinom* a = new Polinom(PolinomA);
            Polinom* b = new Polinom(PolinomB);
            if(!b->DEG_P_N().COM_NN_D(Natural("0"))==0||!b->get_C()[Natural("0")].get_NUM()->POZ_Z_D()==0){
                Polinom *c = new Polinom(a->DIV_PP_P(*b));

                printPolinom(*c);
                delete c;
            }else
                printIncorrect();
            delete a;
            delete b;
        }else
            printIncorrect();
    });

    connect(mod,&QPushButton::clicked,[=](){
        bool flagA = true;
        bool flagB = true;

        std::map<Natural,Rational,Comparator> PolinomA;
        std::map<Natural,Rational,Comparator> PolinomB;

        for(int i = 0;i<LineEditsListA.size();i++){
            QString ANum = this->EditsListA[2*i]->toPlainText();
            ANum.replace("\n","");

            QString ADenum = this->EditsListA[2*i+1]->toPlainText();
            ADenum.replace("\n","");

            QString ADegree = this->LineEditsListA[i]->text();
            ADegree.replace("\n","");

            bool f1 = validation(ANum);
            bool f2 = validation(ADenum);
            bool f3 = validation(ADegree);

            ANum = BoxesListA[i]->currentText()+ANum;

            flagA = f1&&f2&&f3;

            if(flagA){
                Natural* Deg = new Natural(std::string(ADegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(ANum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(ADenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomA[*Deg] = PolinomA[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagA = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        for(int i = 0;i<LineEditsListB.size();i++){
            QString BNum = this->EditsListB[2*i]->toPlainText();
            BNum.replace("\n","");

            QString BDenum = this->EditsListB[2*i+1]->toPlainText();
            BDenum.replace("\n","");

            QString BDegree = this->LineEditsListB[i]->text();
            BDegree.replace("\n","");

            bool f1 = validation(BNum);
            bool f2 = validation(BDenum);
            bool f3 = validation(BDegree);

            BNum = BoxesListB[i]->currentText()+BNum;

            flagB = f1&&f2&&f3;

            if(flagB){
                Natural* Deg = new Natural(std::string(BDegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(BNum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(BDenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomB[*Deg] = PolinomB[*Deg].ADD_QQ_Q(*Coeff);

                else
                    flagB = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        if(flagA&&flagB){
            Polinom* a = new Polinom(PolinomA);
            Polinom* b = new Polinom(PolinomB);
            if(!b->DEG_P_N().COM_NN_D(Natural("0"))==0||!b->get_C()[Natural("0")].get_NUM()->POZ_Z_D()==0){
                Polinom *c = new Polinom(a->MOD_PP_P(*b));

                printPolinom(*c);
                delete c;
            }else
                printIncorrect();
            delete a;
            delete b;
        }else
            printIncorrect();
    });


    connect(nod,&QPushButton::clicked,[=](){
        bool flagA = true;
        bool flagB = true;

        std::map<Natural,Rational,Comparator> PolinomA;
        std::map<Natural,Rational,Comparator> PolinomB;

        for(int i = 0;i<LineEditsListA.size();i++){
            QString ANum = this->EditsListA[2*i]->toPlainText();
            ANum.replace("\n","");

            QString ADenum = this->EditsListA[2*i+1]->toPlainText();
            ADenum.replace("\n","");

            QString ADegree = this->LineEditsListA[i]->text();
            ADegree.replace("\n","");

            bool f1 = validation(ANum);
            bool f2 = validation(ADenum);
            bool f3 = validation(ADegree);

            ANum = BoxesListA[i]->currentText()+ANum;

            flagA = f1&&f2&&f3;

            if(flagA){
                Natural* Deg = new Natural(std::string(ADegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(ANum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(ADenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomA[*Deg] = PolinomA[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagA = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        for(int i = 0;i<LineEditsListB.size();i++){
            QString BNum = this->EditsListB[2*i]->toPlainText();
            BNum.replace("\n","");

            QString BDenum = this->EditsListB[2*i+1]->toPlainText();
            BDenum.replace("\n","");

            QString BDegree = this->LineEditsListB[i]->text();
            BDegree.replace("\n","");

            bool f1 = validation(BNum);
            bool f2 = validation(BDenum);
            bool f3 = validation(BDegree);

            BNum = BoxesListB[i]->currentText()+BNum;

            flagB = f1&&f2&&f3;

            if(flagB){
                Natural* Deg = new Natural(std::string(BDegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(BNum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(BDenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomB[*Deg] = PolinomB[*Deg].ADD_QQ_Q(*Coeff);

                else
                    flagB = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }

        if(flagA&&flagB){
            Polinom* a = new Polinom(PolinomA);
            Polinom* b = new Polinom(PolinomB);
            if(!b->DEG_P_N().COM_NN_D(Natural("0"))==0||!b->get_C()[Natural("0")].get_NUM()->POZ_Z_D()==0){
                Polinom *c = new Polinom(a->GCF_PP_P(*b));

                printPolinom(*c);
                delete c;
            }else
                printIncorrect();
            delete a;
            delete b;
        }else
            printIncorrect();
    });

    connect(NMRa,&QPushButton::clicked,[=](){
        bool flagA = true;

        std::map<Natural,Rational,Comparator> PolinomA;

        for(int i = 0;i<LineEditsListA.size();i++){
            QString ANum = this->EditsListA[2*i]->toPlainText();
            ANum.replace("\n","");

            QString ADenum = this->EditsListA[2*i+1]->toPlainText();
            ADenum.replace("\n","");

            QString ADegree = this->LineEditsListA[i]->text();
            ADegree.replace("\n","");

            bool f1 = validation(ANum);
            bool f2 = validation(ADenum);
            bool f3 = validation(ADegree);

            ANum = BoxesListA[i]->currentText()+ANum;

            flagA = f1&&f2&&f3;

            if(flagA){
                Natural* Deg = new Natural(std::string(ADegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(ANum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(ADenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomA[*Deg] = PolinomA[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagA = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }


        if(flagA){
            Polinom* a = new Polinom(PolinomA);
            Polinom* c = new Polinom(a->NMR_P_P());

            printPolinom(*c);

            delete a;
            delete c;
        }else
            printIncorrect();
    });

    connect(NMRb,&QPushButton::clicked,[=](){
        bool flagB = true;

        std::map<Natural,Rational,Comparator> PolinomB;

        for(int i = 0;i<LineEditsListB.size();i++){
            QString BNum = this->EditsListB[2*i]->toPlainText();
            BNum.replace("\n","");

            QString BDenum = this->EditsListB[2*i+1]->toPlainText();
            BDenum.replace("\n","");

            QString BDegree = this->LineEditsListB[i]->text();
            BDegree.replace("\n","");

            bool f1 = validation(BNum);
            bool f2 = validation(BDenum);
            bool f3 = validation(BDegree);

            BNum = BoxesListA[i]->currentText()+BNum;

            flagB = f1&&f2&&f3;

            if(flagB){
                Natural* Deg = new Natural(std::string(BDegree.toLocal8Bit().constData()));
                Integer num = Integer(std::string(BNum.toLocal8Bit().constData()));
                Natural denum = Natural(std::string(BDenum.toLocal8Bit().constData()));
                Rational *Coeff = new Rational(num,denum);

                if(denum.NZER_N_B())
                    PolinomB[*Deg] = PolinomB[*Deg].ADD_QQ_Q(*Coeff);
                else
                    flagB = false;

                delete Deg;
                delete Coeff;
            }else
                break;
        }


        if(flagB){
            Polinom* b = new Polinom(PolinomB);
            Polinom* c = new Polinom(b->NMR_P_P());

            printPolinom(*c);

            delete b;
            delete c;
        }else
            printIncorrect();
    });

}

void MainWindow::drawAnimation(QWidget* widget)
{
    QRect finish = widget->geometry();
    switch(state){
    case Nat:
        widget->setGeometry(ui->NatButton->geometry());
        break;

    case Int:
        widget->setGeometry(ui->IntButton->geometry());
        break;

    case Rat:
        widget->setGeometry(ui->RatButton->geometry());
        break;

    case Pol:
        widget->setGeometry(ui->PolButton->geometry());
        break;
    }

    QPropertyAnimation* animation = new QPropertyAnimation(widget,"geometry");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(finish);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::delWidgets(){

    while(!EditsListA.empty()){
        EditsListA.removeFirst();
    }

    while(!EditsListB.empty()){
        EditsListB.removeFirst();
    }

    while(!LineEditsListA.empty()){
        LineEditsListA.removeFirst();
    }

    while(!LineEditsListB.empty()){
        LineEditsListB.removeFirst();
    }

    while(!LabelsListA.empty()){
        LabelsListA.removeFirst();
    }

    while(!LabelsListB.empty()){
        LabelsListB.removeFirst();
    }

    while(!EditsList.empty()){
        QTextEdit* tmp = EditsList.first();
        EditsList.removeFirst();
        delete tmp;
    }

    while(!BoxesListA.empty()){
        BoxesListA.removeFirst();
    }

    while(!BoxesListB.empty()){
        BoxesListB.removeFirst();
    }

    while(!ButtonsList.empty()){
        QPushButton* tmp = ButtonsList.first();
        ButtonsList.removeFirst();
        delete tmp;
    }

    while(!LabelsList.empty()){
        QLabel* tmp = LabelsList.first();
        LabelsList.removeFirst();
        delete tmp;
    }

    while(!BoxesList.empty()){
        QComboBox* tmp = BoxesList.first();
        BoxesList.removeFirst();
        delete tmp;
    }

    while(!SpacersList.empty()){
        SpacersList.removeFirst();
    }


    while(!LayoutsList.empty()){
        QLayout* tmp = LayoutsList.last();
        LayoutsList.removeLast();
        delete tmp;
    }

    if(ApolArea!=nullptr){
        delete ApolArea;
        ApolArea = nullptr;
    }

    if(BpolArea!=nullptr){
        delete BpolArea;
        BpolArea = nullptr;
    }


}

void MainWindow::printNatural(const Natural &number, QTextEdit &text)
{
    int *arr = number.get_Arr();
        QString ans = "";
    for(int i = 0;i<number.get_n();i++)
        ans+='0'+arr[number.get_n()-1-i];

    text.setText(ans);
}

void MainWindow::printInteger(Integer &number, QTextEdit &text)
{
    int *arr = number.get_Arr();
    QString ans = "";
    if(number.get_sign()==true)
        ans+="-";
    for(int i = 0;i<number.get_n();i++)
        ans+='0'+arr[number.get_n()-1-i];

    text.setText(ans);
}

void MainWindow::printRational(Rational &number, QTextEdit &text)
{
    if(number.INT_Q_B())
        printInteger(number.TRANS_Q_Z(),text);
    else{
        int *arr = number.get_NUM()->get_Arr();
        QString ans = "";
        if(number.get_NUM()->get_sign()==true)
            ans+="-";
        for(int i = 0;i<number.get_NUM()->get_n();i++)
            ans+='0'+arr[number.get_NUM()->get_n()-1-i];

        ans+=" / ";

        arr = number.get_DENUM()->get_Arr();
        for(int i = 0;i<number.get_DENUM()->get_n();i++)
            ans+='0'+arr[number.get_DENUM()->get_n()-1-i];

        text.setText(ans);
    }
}

void MainWindow::printPolinom(Polinom &pol)
{
    QDialog* dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout* l = new QVBoxLayout(dialog);
    QTextEdit* ans = new QTextEdit(dialog);
    QPushButton* FAC_button = new QPushButton(dialog);
    FAC_button->setText("Вынести НОК знаменаталей и НОД числителей");

    QString str = "";

    std::map<Natural,Rational,Comparator> temp = pol.get_C();
    for(auto it = temp.begin();it!=temp.end();it++){
        printRational(it->second,*ans);


        if(it!=temp.begin()&&it->second.get_NUM()->POZ_Z_D()==2)
            str+=" +"+ans->toPlainText();
        else if(it!=temp.begin())
            str+=" "+ans->toPlainText();
        else
            str+=ans->toPlainText();

        printNatural(it->first,*ans);

        if(ans->toPlainText()=="1")
            str+=" *x";
        else if(ans->toPlainText()!="0")
            str+=" *x^"+ans->toPlainText();

    }

    ans->setText(str);
    l->addWidget(ans);
    l->addWidget(FAC_button);
    ans->show();

    dialog->show();

    connect(FAC_button,&QPushButton::clicked,[=](){
        Rational FAC = pol.FAC_P_Q();
        Polinom p = pol;
        QString s = "";
        if((pol.get_C().size()>1)&&(!FAC.get_NUM()->TRANS_Z_N().COM_NN_D(Natural("1"))==0||!FAC.get_DENUM()->COM_NN_D(Natural("1"))==0)){
            std::map<Natural,Rational,Comparator> div_m;
            div_m[Natural("0")] = FAC;
            Polinom DIV(div_m);
            p = p.DIV_PP_P(DIV);
            printRational(FAC,*ans);
            s+=ans->toPlainText()+" (";
        }

        std::map<Natural,Rational,Comparator> temp = p.get_C();
        for(auto it = temp.begin();it!=temp.end();it++){
            printRational(it->second,*ans);


            if(it!=temp.begin()&&it->second.get_NUM()->POZ_Z_D()==2)
                s+=" +"+ans->toPlainText();
            else if(it!=temp.begin())
                s+=" "+ans->toPlainText();
            else
                s+=ans->toPlainText();

            printNatural(it->first,*ans);

            if(ans->toPlainText()=="1")
                s+=" *x";
            else if(ans->toPlainText()!="0")
                s+=" *x^"+ans->toPlainText();

        }

        if((p.get_C().size()>1)&&(!FAC.get_NUM()->TRANS_Z_N().COM_NN_D(Natural("1"))==0||!FAC.get_DENUM()->COM_NN_D(Natural("1"))==0))
            s+=" )";

        ans->setText(s);
    });
}

void MainWindow::printIncorrect()
{
    QDialog* dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QGridLayout* l = new QGridLayout(dialog);
    QTextEdit* ans = new QTextEdit(dialog);

    ans->setText("Некорректные данные");
    l->addWidget(ans);
    dialog->setLayout(l);

    dialog->show();
}

bool MainWindow::validation(QString &number)
{
    if(number.size()==0)
        return false;
    QString validStr = "";
    int i = 0;
    while(number[i]=='0'&&i<number.size()-1)
        i++;

    for(i;i<number.size();i++)
        if(number[i]<'0'||number[i]>'9')
            return false;
        else
            validStr+=number[i];

    number = validStr;
    return true;
}

void MainWindow::on_reference_clicked()
{
    Reference* refWin = new Reference(ui->reference,this);
    refWin->setAttribute(Qt::WA_DeleteOnClose);
    refWin->show();

    ui->reference->setEnabled(false);
}
