/*************************************
 * Класс разрабатывал:               *
 * Грасс Максим                      *
 * 6307                              *
 *************************************/
#include "polinom.h"

/*******************************************************************/
/*********Конструктор, принимающий дерево коэффициентов*************/
Polinom::Polinom(std::map<Natural,Rational,Comparator> &C_other)
{
    //Проходимся по коэффициентам и записываем все ненулевые коэффициенты
    for(auto it = C_other.begin();it!=C_other.end();it++)
        if(it->second.get_NUM()->POZ_Z_D()!=0)
            this->C[it->first] = it->second;

    //Если мы не записали в итоге ни одного коэффициента
    //то запишем туда 0
    if(this->C.empty())
        this->C[Natural("0")] = Rational();

    this->hDegree = new Natural((this->C.begin())->first);

}


/******************************************************************/
/*****************Конструктор копирования**************************/
Polinom::Polinom(const Polinom &other)
{
    if(this!=&other){
        //Очищаем коэффициенты
        this->C.clear();
        std::map<Natural,Rational,Comparator> temp = other.get_C();
        //Записываем все ненулевые коэффициенты
        for(auto it = temp.begin();it!=temp.end();it++)
            if(it->second.get_NUM()->POZ_Z_D()!=0)
                this->C[it->first] = it->second;

        //Если ничего не записали - запишем 0
        if(this->C.empty())
             this->C[Natural("0")] = Rational();

        this->hDegree = new Natural((this->C.begin())->first);
    }
}


/************************************************************************/
/*************Перегрузка оператора присваивани***************************/
Polinom &Polinom::operator =(const Polinom &other)
{
    //Аналогично конструктору копирования
    if(this!=&other){
        this->C.clear();
        std::map<Natural,Rational,Comparator> temp = other.get_C();
        for(auto it = temp.begin();it!=temp.end();it++)
           if(it->second.get_NUM()->POZ_Z_D()!=0)
                this->C[it->first] = it->second;

        if(this->C.empty())
             this->C[Natural("0")] = Rational();

        this->hDegree = new Natural((this->C.begin())->first);


    }

    return *this;
}


/**********************************************************/
/***************Сумма многочленов**************************/
Polinom &Polinom::ADD_PP_P(const Polinom &other) const
{
    //Запомним коэффциенты одного многочлена
    std::map<Natural,Rational,Comparator>temp = other.get_C();

    //Пройдемся по коэффициентам второго попутно складывая их с коэффициентами первого
    //при сопадении степеней
    for(auto it = this->C.begin();it!=this->C.end();it++)
        temp[it->first] = temp[it->first].ADD_QQ_Q(it->second);

    Polinom* ADD = new Polinom(temp);

    return *ADD;
}


/****************************************************************/
/******************Разность многочленов**************************/
Polinom &Polinom::SUB_PP_P(const Polinom &other) const
{
    std::map<Natural,Rational,Comparator>temp = this->get_C();
    std::map<Natural,Rational,Comparator>temp_other = other.get_C();

    //Пройдемся по коэффициентам второго многочлена вычитая их из коэффициентов первого
    //при сопадении степеней
    for(auto it = temp_other.begin();it!=temp_other.end();it++)
        temp[it->first] = temp[it->first].SUB_QQ_Q(it->second);

    Polinom* SUB = new Polinom(temp);

    return *SUB;
}


/***********************************************************************************/
/********************Умножение многочлена на рациональное число*********************/
Polinom& Polinom::MUL_PQ_P(const Rational &num) const
{
    std::map<Natural,Rational,Comparator>temp = this->C;

    //Пройдемся по коэффициентам многочлена домножая каждый на рациональное число
    for(auto it = temp.begin();it!=temp.end();it++)
        temp[it->first] = temp[it->first].MUL_QQ_Q(num);

    Polinom* MUL = new Polinom(temp);

    return *MUL;
}


/******************************************************************/
/***************Умножение многочлена на x^k************************/
Polinom& Polinom::MUL_Pxk_P(const Natural& k) const
{
    //Cоздаем новое дерево коэффициентов
    std::map<Natural,Rational,Comparator>temp;

    //Проходимся по коэффициентам многочлена
    //Записываем коэффициент в новое дерево
    //по ключу: текующий ключ плюс k
    for(auto it = this->C.begin();it!=this->C.end();it++)
        temp[it->first.ADD_NN_N(k)] = it->second;

    Polinom* MUL = new Polinom(temp);

    return *MUL;
}


/**************************************************************************/
/****************Получение старшего коэффициента***************************/
Rational& Polinom::LED_P_Q() const{

    //Возвращаем коэффициент соответствующий старшей степени
    Rational* LED = new Rational(this->C.find(*this->hDegree)->second);

    return *LED;
}


/*********************************************************************/
/*******************Получение старшей степени*************************/
Natural& Polinom::DEG_P_N() const{

    //Возвращаем значение старшей степени
    Natural* DEG = new Natural(*this->hDegree);

    return *DEG;
}


/********************************************************************************************************/
/**********************Получение рационального числа для вынесения за скобку*****************************/
Rational &Polinom::FAC_P_Q() const
{
    Natural LCM("1");

    //Найдем НОК всех знаменталей
    for(auto rat:this->get_C())
        LCM = rat.second.get_DENUM()->LCM_NN_N(LCM);

    //Домножаем числители на дополнительные множители
    Polinom p(*this);
    for(auto rat:this->get_C())
        p.get_C()[rat.first] = Rational(rat.second.get_NUM()->MUL_ZZ_Z(Integer(LCM).DIV_ZZ_Z(*rat.second.get_DENUM())));

    Integer GCF("+0");

    //Ищем НОД числителей
    for(auto rat:p.get_C())
        GCF = Integer(rat.second.get_NUM()->TRANS_Z_N().GCF_NN_N(GCF.TRANS_Z_N()));

    Rational* FAC = new Rational(Rational(GCF,LCM).RED_Q_Q());

    return *FAC;
}


/*************************************************************/
/******************Умножение многочленов**********************/
Polinom &Polinom::MUL_PP_P(const Polinom &other) const
{
    std::map<Natural,Rational,Comparator>t;
    Polinom temp(t);

    std::map<Natural,Rational,Comparator>second_m = other.get_C();

    //Пройдем по одной дроби умножая каждый член на вторую дробь
    for(auto it = second_m.begin();it!=second_m.end();it++)
        temp = temp.ADD_PP_P(this->MUL_PQ_P(it->second).MUL_Pxk_P(it->first));



    Polinom* MUL = new Polinom(temp);

    return *MUL;
}


/*******************************************************************************/
/*****************Выделение целой части от деления многочленов******************/
Polinom &Polinom::DIV_PP_P(const Polinom &other) const
{
    //Проверка деления на 0 лежит на вызывающей функции
    Polinom temp(*this);

    //Если степень делителя равна нулю, то просто умножим полином
    //на перевернутую дробь
    if(other.DEG_P_N().COM_NN_D(Natural("0"))==0){
        Integer Num("+1");
        Natural Denum("1");
        Polinom *DIV = new Polinom(this->MUL_PQ_P(Rational(Num,Denum).DIV_QQ_Q(other.get_C()[Natural("0")])));

        return *DIV;
    }

    //Пока степень делителя больше или равна степени знаменталя
    //выполняем деление в столбик
    std::map<Natural,Rational,Comparator>t;
    Polinom d(t);
    while(temp.DEG_P_N().COM_NN_D(other.DEG_P_N())!=1){
        Rational Coeff(temp.get_C()[temp.DEG_P_N()].DIV_QQ_Q(other.get_C()[other.DEG_P_N()]));//Находим текущий коэффициент

        std::map<Natural,Rational,Comparator>temp_c;
        temp_c[temp.DEG_P_N().SUB_NN_N(other.DEG_P_N())] = Coeff;

        d = d.ADD_PP_P(Polinom(temp_c));//Добавим к текущему полиному член Coeff*x^(Степень делителя - степень делимого)

        temp = temp.SUB_PP_P(Polinom(temp_c).MUL_PP_P(other));//Выполним вычитание из текущего делимого делитель
                                                              //домноженный на текущий член частного
    }

    Polinom* DIV = new Polinom(d);

    return *DIV;
}


/*********************************************************************************/
/*****************Получчение остатка от деления многочленов***********************/
Polinom &Polinom::MOD_PP_P(const Polinom &other) const
{
    //Проверка деления на 0 лежит на вызывающей функции

    //Найдем целую часть
    Polinom DIV = this->DIV_PP_P(other);

    //Вычтем из многочлена целую часть, умноженную на делитель
    Polinom* MOD = new Polinom(this->SUB_PP_P(DIV.MUL_PP_P(other)));

    return *MOD;
}


/******************************************************************/
/********************Нахождение НОД многочленов********************/
Polinom &Polinom::GCF_PP_P(const Polinom &other) const
{
    Polinom higher = (this->DEG_P_N().COM_NN_D(other.DEG_P_N())==2)?*this:other;
    Polinom lower = (this->DEG_P_N().COM_NN_D(other.DEG_P_N())!=2)?*this:other;

    //Реализуем алгоритм Евклида. Взятие модуля, пока меньшее не станет равно нулевому многочлену
    while(!lower.DEG_P_N().COM_NN_D(Natural("0"))==0||!lower.get_C()[Natural("0")].get_NUM()->POZ_Z_D()==0){
        Polinom temp(lower);

        lower = higher.MOD_PP_P(lower);

        higher = temp;
    }

    Polinom* GCF = new Polinom(higher);

    return *GCF;
}


/*************************************************************************/
/*****************Нахождение производной многочлена***********************/
Polinom &Polinom::DER_P_P() const
{
    std::map<Natural,Rational,Comparator>temp;

    //В новое дерево запишем коэффициент умноженный на старую степень, новая степень на единицу меньше
    //Степени равные нулю игнорируем
    for(auto it = this->C.begin();it!=this->C.end();it++){
        if(it->first.NZER_N_B())
            temp[it->first.SUB_NN_N(Natural("1"))] = it->second.MUL_QQ_Q(Rational(Integer(it->first)));
    }

    Polinom* DER = new Polinom(temp);

    return *DER;
}


/************************************************************************/
/**************Преобразование кратных корней в простые*******************/
Polinom &Polinom::NMR_P_P() const
{
    //Делим многочлен на его НОД с его производной
    //Кратные корни в производной понижают степень на единицу
    //следовательно при делении станут простыми
    //А простые не участвуют в разложении производой
    Polinom DER = this->DER_P_P();

    Polinom GCF = this->GCF_PP_P(DER);

    Polinom *NMR;

    if(!GCF.DEG_P_N().COM_NN_D(Natural("0"))==0||!GCF.get_C()[Natural("0")].get_NUM()->POZ_Z_D()==0)
        NMR = new Polinom(this->DIV_PP_P(GCF));
    else
        NMR = new Polinom(GCF);//Присваивание 0 при общем делителе равном 0

    return *NMR;
}


/*************************************************************/
/**********************Деструктор*****************************/
Polinom::~Polinom()
{
    delete hDegree;
}

