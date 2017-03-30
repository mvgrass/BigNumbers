#include "natural.h"

/*********************************************************/
/************Конструктор без агументов********************/
Natural::Natural()
{
    Natural("0");
}

/*********************************************************/
/************Конструктор, принимающий строку**************/
Natural::Natural(std::string number)
{
    //Считается, что строка подана уже пройдя валидацию и в ней нет всякого рода "мусора"
    this->n = number.size();
    this->Arr = (int*)malloc(sizeof(int)*n);

    //Для удобства будем хранить разряды в обратном порядке
    for(int i = 0;i<this->n;i++)
        this->Arr[i] = number[(this->n-1)-i]-'0';

}


/********************************************************************/
/*****Конструктор, принимающий массив и номер старшего разряда********/
Natural::Natural(const int *arr,const int n)
{

    //Присваиваем старшему разряду число n, переданное в функцию
    this->n = n;
    this->Arr = (int *)malloc(sizeof(int)*n);

    //Поэлементно записываем в массив числа элементы массива, переданного в функцию
    for(int i = 0;i<this->n;i++)
        this->Arr[i] = arr[i];
}


/********************************************************/
/**************Конструктор копирования*******************/
Natural::Natural(const Natural & other)
{
    //Копирует переданное натуральное число в новое
    if(this!=&other){
        this->n = other.get_n();
        this->Arr = (int*)malloc(sizeof(int)*this->n);
        const int *arr = other.get_Arr();
        for(int i = 0;i<n;i++)
            this->Arr[i] = arr[i];
    }

}


/******************************************************************/
/*************Перегрузка оператора присваивания********************/
Natural& Natural::operator=(const Natural & other)
{
    //Копирует переданное натуральное число в текущее
    if(this!=&other){
        if(this->Arr!=nullptr){
            free(this->Arr);
            this->Arr = nullptr;
        }

        this->n = other.get_n();
        this->Arr = (int*)malloc(sizeof(int)*this->n);
        const int *arr = other.get_Arr();
        for(int i = 0;i<n;i++)
            this->Arr[i] = arr[i];
    }
    return *this;
}


/********************************************************/
/*************Сравнение натуральных чисел****************/
int Natural::COM_NN_D(const Natural &other) const
{
    //Если первое больше второго возвращаем 2, если меньше - 1, иначе 0

    if(this->n>other.get_n()) //Если номер старшего разрда первого больше номера
        return 2;             //старшего разряда вторго, то первое больше
    else if(this->n<other.get_n())//Если у второго больше, то второе число больше
        return 1;
    else{
        //Номера старших разрядов оказались равны
        int *other_arr = other.get_Arr();

        //Идем от старшего разряда к младшему первое различие даст нам понять, кто больше
        //Если различий не оказалось - числа равны
        for(int i = 0;i<this->n;i++)
            if(this->Arr[(this->n-1)-i]>other_arr[(this->n-1)-i])
                return 2;
            else if(this->Arr[(this->n-1)-i]<other_arr[(this->n-1)-i])
                return 1;

        return 0;

    }
}


/********************************************************/
/*************Является ли число нулем********************/
bool Natural::NZER_N_B() const
{
    //Если не яляется вернуть 1, иначе 0
    return !(this->n==1&&Arr[0]==0);//Признак нуля: номер старшего разряда - 1 и в нем записан 0
}


/********************************************************/
/*****************Прибавление 1 к числу******************/
Natural &Natural::ADD_1N_N()
{
    int n = 0;
    int *arr = nullptr;

    //Прибавляем начиная от младшего разрда 1 к каждому разряду до тех
    //пор, пока перенос не станет равен 0
    int extra = 1;
    for(int i = 0;i<this->n;i++){
        if(extra == 0)
            break;
        arr = (int*)realloc(arr,sizeof(int)*(++n));
        arr[n-1] = (this->Arr[i]+extra)%10;
        extra = (this->Arr[i]+extra)/10;
    }

    //Если досрочно завершили перенос, то этот цикл допишет оставшиеся разряды
    for(int i = n;i<this->n;i++){
        arr = (int*)realloc(arr,sizeof(int)*(++n));
        arr[n-1] = this->Arr[i];
    }

    //Если остался перенос, а число кончилось, увелим номер старшего разряда на единицу
    //и запишем туда 1
    if(extra == 1){
        arr = (int*)realloc(arr,sizeof(int)*(++n));
        arr[n-1] = 1;
    }

    Natural* plus = new Natural(arr,n);

    if(arr!=nullptr)
        free(arr);

    return *plus;
}


/***************************************************************/
/****************Сложение натуральных чисел*********************/
Natural &Natural::ADD_NN_N(const Natural &other) const
{
    int minn = 0;
    int maxn = 0;

    //Выясним, кто из двух чисел больше
    int compare = this->COM_NN_D(other);
    switch(compare){
    case 0:
        minn = this->n;
        maxn = this->n;
        break;

    case 1:
        minn = this->n;
        maxn = other.n;
        break;

    case 2:
        minn = other.n;
        maxn = this->n;
        break;
    }

    int* other_arr = other.get_Arr();

    int sum_n = 0;
    int* sum_arr = nullptr;

    //Пока не закончатся разряды меньшего числа поразрдно складываем
    //числа, не забывая о переносе
    int extra = 0;
    for(sum_n = 0;sum_n<minn;sum_n++){
        sum_arr = (int*)realloc(sum_arr,sizeof(int)*(sum_n+1));
        sum_arr[sum_n] = (this->Arr[sum_n]+other_arr[sum_n]+extra)%10;
        extra = (this->Arr[sum_n]+other_arr[sum_n]+extra)/10;
    }

    //Дальше заполняем оставшиеся разряды разрядами большего числа,
    //не забывая о переносе
    for(sum_n= sum_n;sum_n<maxn;sum_n++){
        sum_arr = (int*)realloc(sum_arr,sizeof(int)*(sum_n+1));
        sum_arr[sum_n] = (compare==2)?(this->Arr[sum_n]+extra)%10:(other_arr[sum_n]+extra)%10;
        extra = (compare==2)?(this->Arr[sum_n]+extra)/10:(other_arr[sum_n]+extra)/10;
    }

    //Если разряды обоих чисел закончились, а перенос остался,
    //то увеличим номер старшего разряда суммы на единицу и запишем туда 1
    if(extra!=0){
        sum_arr = (int*)realloc(sum_arr,sizeof(int)*(++sum_n));
        sum_arr[sum_n-1] = extra;
    }

    Natural* sum = new Natural(sum_arr,sum_n);

    if(sum_arr!=nullptr)
        free(sum_arr);

    return *sum;
}


/********************************************************/
/*******************Разность чисел***********************/
Natural &Natural::SUB_NN_N(const Natural &other) const
{

    int n = 0;
    int *sub_arr = nullptr;

    Natural A(NULL,0);
    Natural B(NULL,0);

    //Выясним, какое из чисел больше, чтобы понять кого из кого
    //будем вычитать, если равны - выдаем ответ 0
    if(this->COM_NN_D(other)==2){
        A = *this;
        B = other;
    }else if(this->COM_NN_D(other)==1){
        A = other;
        B = *this;
    }else{
        Natural* SUB = new Natural("0");
        return *SUB;
    }

    n = A.get_n();
    sub_arr = (int*)malloc(sizeof(int)*n);

    int* A_arr = A.get_Arr();
    int* B_arr = B.get_Arr();


    int i = 0;
    int p = 0;
    //Начиная с младшего разряда поразрядно вычитаем
    //из большего числа меньшего с учетом занятых десяток из старших разрядов
    for(i = 0;i<B.get_n();i++)
        if(A_arr[i]-p-B_arr[i]>=0){
            sub_arr[i] = A_arr[i]-p-B_arr[i];
            p = 0;
        }else{
            sub_arr[i] = 10+A_arr[i]-p-B_arr[i];
            p = 1;
        }

    //Пока заем из старших разрядов не станет равен нулю
    //продолжаем процесс
    while(p!=0){
            if(A_arr[i]-p>=0){
                sub_arr[i] = A_arr[i]-p;
                p = 0;
            }else{
                sub_arr[i] = 10+A_arr[i]-p;
                p = 1;
            }

            i++;
    }

    //Дописываем в разность оставшиеся нетронутыми разряды большего числа
    for(i;i<A.get_n();i++){
        sub_arr[i] = A_arr[i];
    }

    //Избавляемся от ведущих нулей
    while(sub_arr[n-1]==0){
        sub_arr = (int*)realloc(sub_arr,sizeof(int)*(--n));
    }

    Natural* ans = new Natural(sub_arr,n);

    if(sub_arr!=nullptr)
        free(sub_arr);

    return *ans;
}


/********************************************************/
/**************Умножение на цифру k************************/
Natural &Natural::MUL_ND_N(const int k) const
{
    //Если k == 0, то вернем 0
    if(k==0){
        Natural* MUL_ND = new Natural("0");

        return *MUL_ND;
    }


    int* arr = nullptr;
    int n = 0;

    //Начиная от младшего бита выполним умножение на цифру,
    //не забывая о переносе разрядов
    int extra = 0;
    for(int i = 0;i<this->n;i++){
        arr = (int*)realloc(arr,sizeof(int)*(++n));
        arr[i] = (this->Arr[i]*k+extra)%10;
        extra = (this->Arr[i]*k+extra)/10;
    }

    //Если после прохода по всем разряда перенос остался ненулевым
    //увеличим на единицу номер старшего разряда умножения и запишем в него наш перенос
    if(extra!=0){
        arr = (int*)realloc(arr,sizeof(int)*(++n));
        arr[n-1] = extra;
    }

    Natural* MUL_ND = new Natural(arr,n);

    if(arr!=nullptr)
        free(arr);
    return *MUL_ND;
}


/**********************************************************************/
/*************Умножение натурального на 10^k***************************/
Natural &Natural::MUL_Nk_N(const int k) const
{
    int *arr = nullptr;
    int n = 0;

    //Проверим является ли наше число нулем
    if(this->NZER_N_B()){

        //Запишем в k младшие разрядов k нулей
        for(int i = 0;i<k;i++){
            arr = (int*)realloc(arr,sizeof(int)*(++n));
            arr[i] = 0;
        }

        //А затем просто перенесе в старшие разряды наше число
        for(int i = k;i<(this->n+k);i++){
            arr = (int*)realloc(arr,sizeof(int)*(++n));
            arr[i] = this->Arr[i-k];
        }

        Natural *MUL_Nk = new Natural(arr,n);
        if(arr!=nullptr)
            free(arr);

        return *MUL_Nk;

    }else{
        //Число равно 0, просто возвращаем его же копию
        Natural *MUL_Nk = new Natural(*this);
        return *MUL_Nk;
    }

}


/**************************************************************************/
/********************Умножение двух натуральных чисел**********************/
Natural &Natural::MUL_NN_N(const Natural & other) const
{
    //Функция моделирует умножение столбиком

    Natural A(NULL,0);
    Natural B(NULL,0);

    //Выясним какое большше
    if(this->COM_NN_D(other)!=1){
        A = *this;
        B = other;
    }else{
        A = other;
        B = *this;
    }

    Natural temp("0");//Промежуточная сумма для i слагаемых из умножения столбиком

    //Для каждого разряда второго из множителей прибавим к сумме значение этого разрда умноженное на первый множитель
    //и возведенное в степень 10^i, где i позиция разряда начиная с нуля
    for(int i = 0;i<B.get_n();i++)
       temp = temp.ADD_NN_N(Natural(A.MUL_ND_N(B.get_Arr()[i]).MUL_Nk_N(i)));

    Natural* MUL_NN = new Natural(temp);

    return *MUL_NN;
}


/****************************************************************************/
/**************Вычитание из натурального другого натурального, умноженного на
цифру для случая с неотрицательным результатом*******************************/
Natural &Natural::SUB_NDN_N(const Natural& other, int k) const
{
    //Просто воспользуемся уже написанными до этого функциями умножения на цифру и вычитания
    Natural* SUB_NDN = new Natural(this->SUB_NN_N(other.MUL_ND_N(k)));

    return *SUB_NDN;
}


/******************************************************************************/
/*************Поиск первой цифры от деления числа на меньшее*******************/
/**************************умноженное на 10^k**********************************/
int Natural::DIV_NN_Dk(const Natural &other,int k) const
{
    //Цифра ищется перебором от 1 до 9, корректность k гарантируется вызывающей стороной
    int i = 1;
    Natural cur(other.MUL_Nk_N(k));

    while(i<10&&this->COM_NN_D(cur.MUL_ND_N(i))!=1)
          i++;

    return i-1;
}


/********************************************************/
/*******Частное от деления двух натуралныхчисел**********/
Natural &Natural::DIV_NN_N(const Natural &other) const
{
    Natural cur(*this);

    //Функция моделирует деление столбиком
    Natural SUM("0");
    while(cur.COM_NN_D(other)!=1){

        //Сначала определяем на какую степень 10 нужно домножить делитель
        int k = 0;
        if(cur.COM_NN_D(other.MUL_Nk_N(cur.get_n()-other.get_n()))!=1)
            k = cur.get_n() - other.get_n();
        else if(cur.get_n()>1){
            k = cur.get_n() - other.get_n()-1;

        }

        //Вычисляем первую цифру от деления
        int num = cur.DIV_NN_Dk(other,k);
        //Прибавляем к результату полученную цифру умноженну на ее порядковое место в числе
        SUM = SUM.ADD_NN_N(Natural("1").MUL_ND_N(num).MUL_Nk_N(k));
        //Обновляем делимое как разность старого делимого и делителья умноженно на 10^k и текущую цифру
        cur = cur.SUB_NDN_N(other.MUL_Nk_N(k),num);
    }

    Natural* DIV = new Natural(SUM);
    return *DIV;
}


/********************************************************/
/*****Остаток от деления двух натуральных чисел**********/
Natural &Natural::MOD_NN_N(const Natural &other) const
{
    //Высчитаем частное
    Natural DIV = this->DIV_NN_N(other);

    //В остаток запишем разность делимого и частного, умноженного на делитель
    Natural* MOD = new Natural(this->SUB_NN_N(other.MUL_NN_N(DIV)));
    return *MOD;
}

/********************************************************/
/********************НОД*********************************/
Natural &Natural::GCF_NN_N(const Natural &other) const
{
    //Если одно из двух чисел 0, то ответ - второе число
    if(!this->NZER_N_B()){
        Natural* GCF = new Natural(other);
        return *GCF;
    }else if(!other.NZER_N_B()){
        Natural *GCF = new Natural(*this);
        return *GCF;
    }


    Natural higher("0");
    Natural lower("0");

    //Выясним, какое из чисел больше
    if(this->COM_NN_D(other)!=1){
        higher = *this;
        lower = other;
    }else{
        higher = other;
        lower = *this;
    }

    //Реализуем алгоритм Евклида при помощи уже написанных операций взятия частно и модуля
    while(higher.MOD_NN_N(lower).NZER_N_B()){
        Natural temp(lower);
        lower = higher.MOD_NN_N(lower);
        higher = temp;
    }

    Natural* GCF = new Natural(lower);

    return *GCF;
}


/********************************************************/
/**********************НОК*******************************/
Natural &Natural::LCM_NN_N(const Natural &other) const
{

    //Если одно из чисел 0, то ответ 0
    if(!this->NZER_N_B()||!other.NZER_N_B()){
        Natural *LCM = new Natural("0");

        return *LCM;
    }

    Natural GCF = this->GCF_NN_N(other);

    //Воспользуемся формудой НОК = (A*B)/НОД(A*B)
    Natural *LCM = new Natural(this->MUL_NN_N(other).DIV_NN_N(GCF));

    return *LCM;
}


/********************************************************/
/*****************Деструктор*****************************/
Natural::~Natural()
{
    if(this->Arr!=nullptr)
        free(this->Arr);

    this->Arr = nullptr;
}
