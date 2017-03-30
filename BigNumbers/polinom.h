#ifndef POLINOM_H
#define POLINOM_H

#include <map>
#include <string>
#include <vector>

#include "rational.h"

struct Comparator{
    bool operator()(const Natural &f,const Natural &s)const{
        return ((f.COM_NN_D(s))==2);
    }
};//Учим std::map сравнивать наши натуральные числа

class Polinom
{
private:

    std::map<Natural,Rational,Comparator> C;//Дерево коэффициентов
    Natural* hDegree;//Старшая степень многочлена

public:

    Polinom(std::map<Natural,Rational,Comparator>&);//Конструктор, получающий дерево коэффициентов

    Polinom(const Polinom&);//Конструктор копирования


    Polinom& operator = (const Polinom&);//Перегрузка оператора присваивания

    Polinom& ADD_PP_P(const Polinom&) const;//Сложение двух многочленов

    Polinom& SUB_PP_P(const Polinom&) const;//Разность двух многочленов

    Polinom& MUL_PQ_P(const Rational&) const;//Умножение многочлена на вещественное число

    Polinom& MUL_Pxk_P(const Natural&) const;//Умножение многочлена на x^k

    Rational& LED_P_Q() const;//Получение старшего коэффициента многочлена

    Natural& DEG_P_N() const;//Степень многочлена

    Rational& FAC_P_Q() const;//Вынесение НОК числителей и НОД знаменателей

    Polinom& MUL_PP_P(const Polinom&) const;//Умножение многочленов

    Polinom& DIV_PP_P(const Polinom&) const;//Частное от деления многочленов

    Polinom& MOD_PP_P(const Polinom&) const;//Остаток от деления многочленов

    Polinom& GCF_PP_P(const Polinom&) const;//НОД многочленов

    Polinom& DER_P_P() const;//Производная многочлена

    Polinom& NMR_P_P() const;//Преобразование многочлена - кратные корни в простые


    Natural& get_Degree()const{return *this->hDegree;}//Получение старшей степени многочлена

    std::map<Natural,Rational,Comparator> get_C()const{return this->C;}//Получение дерева коэффициентов многочлена

    ~Polinom();//Деструктор

};

#endif // POLINOM_H
