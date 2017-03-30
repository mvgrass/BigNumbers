/*************************************
 * Класс разрабатывал:               *
 * Грасс Максим                      *
 * 6307                              *
 *************************************/
#include "integer.h"

/********************************************************/
/**************Констурктор без аргументов****************/
Integer::Integer()
{
    Integer("+0");
}

/********************************************************/
/**************Констурктор, принимющий строку************/
Integer::Integer(std::string number)
{
    //Гарантия корректности строки на вызывающей стороне
    this->sign = (number[0]=='+')?false:true;//Пулачаем знак из первого символа
    this->n = number.size()-1;//Вычисляем номер старшего разряда из длины строки
    this->Arr = (int*)malloc(sizeof(int)*n);
    //Записываем массив от младшего разряда к старшему для удобства
    for(int i = 0;i<this->n;i++)
        this->Arr[i] = number[(this->n)-i]-'0';
}


/************************************************************************/
/*Конструктор, принимающий массив разядов, номер старшего разряда и знак*/
Integer::Integer(const int *arr, const int n, const bool s)
{
    //Поэлементно копируем параметры функции в члены класса
    this->sign = s;
    this->n = n;
    this->Arr = (int *)malloc(sizeof(int)*n);
    for(int i = 0;i<this->n;i++)
        this->Arr[i] = arr[i];
}


/********************************************************/
/*****************Конструктор копирования****************/
Integer::Integer(const Integer &other)
{
    //Почленно копируем элементы передаваемого объекта в наш
    if(this!=&other){
        this->sign = other.get_sign();
        this->n = other.get_n();
        this->Arr = (int*)malloc(sizeof(int)*this->n);
        const int *arr = other.get_Arr();
        for(int i = 0;i<n;i++)
            this->Arr[i] = arr[i];
    }
}


/********************************************************/
/*****Конструктор приведения натурального к целому*******/
Integer::Integer(const Natural &other)
{
    //Устанавливаем знак в состояние false, массив разрядов и номер старшего разряда просто копируем
    this->sign = false;
    this->n = other.get_n();
    this->Arr = (int*)malloc(sizeof(int)*this->n);
    const int *arr = other.get_Arr();
    for(int i = 0;i<n;i++)
        this->Arr[i] = arr[i];

}


/********************************************************/
/************Перегрузка оператора присваивания***********/
Integer &Integer::operator=(const Integer &other)
{
    //Почленное копирование элементов правого числа в левое
    if(this!=&other){
        if(this->Arr!=nullptr){
            free(this->Arr);
            this->Arr = nullptr;
        }

        this->sign = other.get_sign();
        this->n = other.get_n();
        this->Arr = (int*)malloc(sizeof(int)*this->n);
        const int *arr = other.get_Arr();
        for(int i = 0;i<n;i++)
            this->Arr[i] = arr[i];
    }
    return *this;
}


/********************************************************/
/******************Модуль целого числа*******************/
Natural &Integer::ABS_Z_N() const
{
    //Вызываем конструктор натурального числа от массива разрядов и номера старшего
    //опустив знак
    Natural* ABS = new Natural(this->Arr,this->n);

    return *ABS;
}


/*******************************************************************/
/****************Функция определяющая знак числа********************/
int Integer::POZ_Z_D() const
{

    if(this->n==1&&this->Arr[0]==0)//Признак нуля номер старшего разря 1 и в нем записан 0
        return 0;
    else if(this->sign==false)//Иначе по члену знаку объекта делаем вывод о знаке числа
        return 2;
    else
        return 1;
}


/********************************************************/
/*****************Умножение целого на (-1)***************/
Integer &Integer::MUL_ZM_Z() const
{
    //Вызываем конструктор с нашим массивом разрядов, номером старшего разряда и противоположным знаком
    Integer* opposite = new Integer(this->Arr,this->n,!this->sign);

    return *opposite;
}


/********************************************************/
/************Преобразование целого в натуральное*********/
Natural &Integer::TRANS_Z_N() const
{
    //Требует от вызывающей стороны проверки на неотрицательность
    Natural* NAT = new Natural(this->Arr,this->n);

    return *NAT;
}


/********************************************************/
/******************Сложение двух целых*******************/
Integer &Integer::ADD_ZZ_Z(const Integer &other) const
{
    //Если знаки сопадают выполняем сложение натуральных результаты присваиваем соответствующий знак
    if(this->sign==true&&other.get_sign()==true||this->sign==false&&other.get_sign()==false){
        Natural* add1 = new Natural(this->ABS_Z_N());
        Natural* add2 = new Natural(other.ABS_Z_N());

        Natural* SUM_N = new Natural(add1->ADD_NN_N(*add2));

        Integer* SUM_Z = new Integer(SUM_N->get_Arr(),SUM_N->get_n(),(SUM_N->NZER_N_B()==0)?false:this->sign);

        delete add1;
        delete add2;
        delete SUM_N;

        return *SUM_Z;

    }else{
        //Знаки разные - производим вычитание из модуля большего модуля меньшего резултату присваиваем знак большего
        Natural* add1 = new Natural(this->ABS_Z_N());
        Natural* add2 = new Natural(other.ABS_Z_N());

        Natural* SUB_N = new Natural(add1->SUB_NN_N(*add2));

        bool s;
        int compare = add1->COM_NN_D(*add2);
        if(compare==2)
            s = this->sign;
        else if(compare == 1)
            s = other.get_sign();
        else
            s = false;

        Integer* SUM_Z = new Integer(SUB_N->get_Arr(),SUB_N->get_n(),s);

        delete add1;
        delete add2;
        delete SUB_N;

        return *SUM_Z;

    }
}


/********************************************************/
/*****************Разность целых чисел*******************/
Integer &Integer::SUB_ZZ_Z(const Integer &other) const
{
    //Вызовем сложение, предварительно умножив вычитаемое на (-1)
    Integer* SUB_Z = new Integer(this->ADD_ZZ_Z(other.MUL_ZM_Z()));

    return *SUB_Z;
}


/********************************************************/
/**************Умножение целых чисел*********************/
Integer &Integer::MUL_ZZ_Z(const Integer &other) const
{
    int sign1 = this->POZ_Z_D();
    int sign2 = other.POZ_Z_D();

    //Если одно из чисел 0, то вернем 0
    if(sign1==0||sign2==0){
        Integer* MUL = new Integer("+0");

        return *MUL;
    }else {
        //Иначе перемножим модули чисел
        Integer* MUL= new Integer(this->ABS_Z_N().MUL_NN_N(other.ABS_Z_N()));

        //Если у множителей были разные знаки, то умножим результат на (-1)
        if(sign1!=sign2)
            *MUL = MUL->MUL_ZM_Z();

        return *MUL;
    }
}


/*****************************************************************/
/*****************Деление цлеого на натуральное*******************/
Integer &Integer::DIV_ZZ_Z(const Natural &other) const
{
    Natural cur = Natural(this->ABS_Z_N());

    Integer* ans = new Integer("+0");

    if(this->POZ_Z_D()==1){
        //Если число отрицательное, то проверим кратен ли модуль числа делителю
        if(cur.MOD_NN_N(other).NZER_N_B())
            //Если нет, то выполним деление к результату прибавим единицу и умножим все на (-1)
            ans = new Integer(Integer(cur.DIV_NN_N(other).ADD_1N_N()).MUL_ZM_Z());
        else
            //Если равно нулю, то выполним деление и умножим резульатат на (-1)
            ans = new Integer(Integer(cur.DIV_NN_N(other)).MUL_ZM_Z());
    }
    else
        //Если число положительное просто выболним приведение к натуральному и поделим
        ans = new Integer(this->TRANS_Z_N().DIV_NN_N(other));

    return *ans;

}


/***********************************************************/
/***********Остаток от деления целого на натуральное********/
Integer &Integer::MOD_ZZ_Z(const Natural &other) const
{
    //Вычислим частное
    Integer DIV(this->DIV_ZZ_Z(other));

    //Результату присвоим рызность делители и частного умноженного на делитель
    Integer* MOD = new Integer(this->SUB_ZZ_Z(DIV.MUL_ZZ_Z(Integer(other))));

    return *MOD;
}


/********************************************************/
/*********************Деструктор*************************/
Integer::~Integer()
{
    if(this->Arr!=nullptr)
        free(this->Arr);

    this->Arr = nullptr;
}
