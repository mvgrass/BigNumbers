/*************************************
 * Класс разрабатывал:               *
 * Грасс Максим                      *
 * 6307                              *
 *************************************/
#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include "natural.h"

class Integer
{
private:
    int* Arr;//Массив разрядов числа
    int n;//Номер старшего разряда
    bool sign;//Знак числа

public:

    Integer();

    Integer(std::string);//Конструктор принимающий строку

    Integer(const int*,const int,const bool);//Конструктор принимающий массив разрядов, номер старшего разряд и знак

    Integer(const Integer&);//Конструктор копирования

    Integer(const Natural&);//Конструктор преобразования натурального в целое

    Integer & operator=(const Integer&);//Перегрузка оператора присваивания

    Natural & ABS_Z_N() const;//Модуль целого числа

    int POZ_Z_D() const;//Возвращение знака числа 2 - положительное, 0 - ноль, 1 - отрицательное

    Integer & MUL_ZM_Z() const;//Умножение целого числа на (-1)

    Natural & TRANS_Z_N() const;//Привод неотрицательного целого к натуральному

    Integer & ADD_ZZ_Z(const Integer &) const;//Сложение целых чисел

    Integer & SUB_ZZ_Z(const Integer &) const;//Вычитание целых чисел

    Integer & MUL_ZZ_Z(const Integer &) const;//Умножение целых чисел

    Integer & DIV_ZZ_Z(const Natural &) const;//Частное от деления с остатком целого на натуральное отличное от нуля

    Integer & MOD_ZZ_Z(const Natural &) const;//Остаток от деления с остатком целого на натуральное отличное от нуля

    int* get_Arr() const {return this->Arr;}
    int get_n() const {return this->n;}
    bool get_sign() const {return this->sign;}

    ~Integer();//Деструктор
};

#endif // NATURAL_H
