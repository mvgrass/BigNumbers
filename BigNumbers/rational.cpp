#include "rational.h"

/********************************************************/
/*******Конструктор, принимающий целое и натуральное*****/
Rational::Rational()
{
    this->numerator = new Integer("+0");
    this->denumerator  = new Natural("1");
}

Rational::Rational(Integer &num, Natural &denum)
{
    this->numerator = new Integer(num);
    this->denumerator = new Natural(denum);
}


/********************************************************/
/******************Конуструктор копировани***************/
Rational::Rational(const Rational &other)
{
    if(this!=&other){
        this->numerator = new Integer(*other.get_NUM());
        this->denumerator = new Natural(*other.get_DENUM());

    }
}


/********************************************************/
/*****Конструктор приведения целого к рациональному******/
Rational::Rational(const Integer &other)
{
    //Задаем знаменатель равным 1
    this->numerator = new Integer(other);
    this->denumerator = new Natural("1");
}


/********************************************************/
/************Перегрузка оператора присваивания***********/
Rational &Rational::operator=(const Rational &other)
{
    if(this!=&other){
        this->numerator = new Integer(*other.get_NUM());
        this->denumerator = new Natural(*other.get_DENUM());
    }

    return *this;
}


/********************************************************/
/********************Сокращение числа********************/
Rational &Rational::RED_Q_Q() const
{
    //Найдем НОД числителя и модуля знаменателя и поделим их на НОД
    Natural GCF = this->denumerator->GCF_NN_N(this->numerator->ABS_Z_N());

    Rational* RED = new Rational(this->numerator->DIV_ZZ_Z(GCF),this->denumerator->DIV_NN_N(GCF));
    return *RED;
}


/********************************************************/
/************Является ли число целым*********************/
bool Rational::INT_Q_B() const
{
    //Сокращаем дробь и проверяем является ли ее знаменатель единицей
    if(this->RED_Q_Q().denumerator->COM_NN_D(Natural("1"))==0)
        return true;
    else
        return false;
}


/********************************************************/
/***Приведение рационального к натуральному**************/
Integer &Rational::TRANS_Q_Z() const
{
    //Проверку должна выполнять вызывающая функция
    Integer* TRANS = new Integer(*(this->RED_Q_Q().numerator));

    return *TRANS;
}


/********************************************************/
/*****************Сложение рациональных******************/
Rational &Rational::ADD_QQ_Q(const Rational &other) const
{
    //Присвоим знаменателю НОК знаменталей слагаемых
    Natural Denum = this->denumerator->LCM_NN_N(*(other.get_DENUM()));

    //Числитель высчитаем как сумму числителя первого умноженного на дополнительный множитель
    //и втогоро числителя на дополнительный множитель
    Integer Num = this->numerator->MUL_ZZ_Z(Integer(Denum.DIV_NN_N(*(this->denumerator))));
    Num = Num.ADD_ZZ_Z(other.get_NUM()->MUL_ZZ_Z(Integer(Denum.DIV_NN_N(*(other.get_DENUM())))));

    //Сократим результат
    Rational *SUM = new Rational(Rational(Num,Denum).RED_Q_Q());

    return *SUM;
}


/********************************************************/
/*******************Разность рациональных****************/
Rational &Rational::SUB_QQ_Q(const Rational &other) const
{
    //Домножим числитель вычитаемого на (-1) и выполним сложение
    Rational Opposite = Rational(other.get_NUM()->MUL_ZM_Z(),*(other.get_DENUM()));
    Rational* SUB = new Rational(this->ADD_QQ_Q(Opposite));

    return *SUB;
}


/********************************************************/
/*****************Умножение рациональных*****************/
Rational &Rational::MUL_QQ_Q(const Rational &other) const
{
    //Выполняем перемножение числителей и знаменателй
    Integer NUM = this->numerator->MUL_ZZ_Z(*(other.get_NUM()));

    Natural DENUM = this->denumerator->MUL_NN_N(*(other.get_DENUM()));

    //Сокращаем результат
    Rational* MUL = new Rational(Rational(NUM,DENUM).RED_Q_Q());

    return *MUL;
}


/********************************************************/
/*****************Деление рациональных*******************/
Rational &Rational::DIV_QQ_Q(const Rational &other) const
{
    //Меняем местами числитель и знаменатель второй дроби
    //Выполяем умножение
    //Проверку деления на ноль выполняет вызывающая фкнкция
    Integer NUM = Integer(*other.get_DENUM());
    Natural DENUM = other.get_NUM()->TRANS_Z_N();

    if(other.get_NUM()->POZ_Z_D()==1)
        NUM = NUM.MUL_ZM_Z();


    Rational* DIV = new Rational(this->MUL_QQ_Q(Rational(NUM,DENUM)));

    return *DIV;
}


/********************************************************/
/***********************Деструктор***********************/
Rational::~Rational()
{
    delete numerator;
    delete denumerator;
}
