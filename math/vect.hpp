#ifndef VECT_H_INCLUDED
#define VECT_H_INCLUDED
#include <cassert>
#include <cstdio>
/**
*@brief Базовый класс контейнера вектора. Некий самописеный велосипед.
*перегружены основные операции характерные для всех многомерных типов.
*не смотря на то, что указатель на данные вектора является открытым типов в структурах не относящихся к классу рекомендуется пользоваться оператором [] для доступа к членам. Это позволит избежать ошибок, которые в противном случае будет очень тяжело обнаружить. В структурах относящихся к классу это не делается из сообрадений быстродействия и простоты кода.
*/
#ifndef nullptr
    #define nullptr NULL
#endif
template <class Type, int N> class vect{
public:
    Type data[N];                                                   ///Итератор(не инвалидизируется)
    int size();                                                     ///Взятие размерности вектора
    vect();                                                    ///КОнструктор без параметров
    vect(Type* a);                                             ///Конструктор с взятием данных из массива
    vect(Type* a,int b);                                       ///Конструктор с взятием части данных из массива
    Type &operator[](int i);                                        ///Оператор индексирования
    ///Операторы приведения типов
    template <int V>
    operator vect<Type,V>();                                   ///Оператор приведения одного вектора другому
    operator Type();                                           ///Оператор приведения вектора к числу
    ///Математические операторы
    const vect<Type,N> &operator=(const vect<Type,N> &a);      ///Присваивание
    vect<Type,N> operator+(const vect &a);                     ///Сложение
    const vect<Type,N> &operator+=(const vect<Type,N> &a);     ///Сложение с присваиванием
    vect operator-(const vect<Type,N> &a);                     ///Вычитание
    const vect<Type,N> &operator-=(const vect<Type,N> &a);     ///Вычитание с приравниванием
    vect<Type,N> operator*(const Type &a);                     ///Умножение на число
    const vect<Type,N> &operator*=(const Type &a);             ///Умножение на число с приравниванием
    vect<Type,N> operator/(const Type &a);                     ///Деление на число
    const vect<Type,N> &operator/=(const Type &a);             ///Деление на число с при равниванием
    const vect<Type,N> &operator-();                           ///Поворот на 180 градусов по всем осям
};

/**
*@brief Конструктор
* без параметров - инициализирует внутренний массив в 0
*/
template <class Type, int N>
vect<Type,N>::vect(){
    for(int i=0;i<N;i++){
        data[i]=0;
    }
}

/**
*@brief Конструктор0
*@param Type* a массив, первые N членов которого попадут во внутренний массив экземпляра класса
*/
template <class Type, int N>
vect<Type,N>::vect(Type* a){
    assert(a!=nullptr);
    for(int i=0;i<N;i++){
        data[i]=a[i];
    }
}

/**
*@brief Конструктор2
*@param Type* a массив члены которого попадут во внутренний массив экземпляра класса
*@param int b колличество членов которые надо передать из массива a во внутренний массив класса
*если b больше N, то иза передаваемого массива будут взяты только первые N членов
*если b меньше N, то члены с индексом больше b будут инициализированы в 0
*/
template <class Type, int N>
vect<Type,N>::vect(Type* a,int b){
    assert(a!=nullptr);
    for(int i=0;i<N;i++){
        if(i<b){data[i]=a[i];}else{data[i]=0;};
    }
}
template <class Type, int N>
int vect<Type,N>::size(){
    return N;
}

/**
*@brief оператор индексирования.
*позволяет относительно безопасно получать доступ к данным класса.
*/
template <class Type, int N>
Type &vect<Type,N>::operator[](int i){
    assert(this!=nullptr&&i<N&&i>=0);
    return data[i];
}

/**
*@brief Приведение вектора одной размерности к вектору другой размерности.
*в случае если приводимый вектор меньше вектора назначения заполняются поля только до величины вектора назначения.
*если наоборот вектор назначения больше преобразуемого, то недостающие поля проинициализируются в 0
*оператор позволяет не задумываесь приводить один вектор к другому.
*/
template <class Type, int N>
template <int V>
vect<Type,N>::operator vect<Type,V>(){
    assert(this!=nullptr);
    vect<Type,V> temp;
    for(int i=0;i<V;i++){
        if(i<N){
            temp.data[i]=data[i];
        }else{
            temp.data[i]=0;
        }
    }
    return temp;
}

/**
*@brief Оператор приведения vect к type
*позволяет свободно конвертировать данные из бьазового типа в тип вектора и обратно.
*/
template <class Type, int N>
vect<Type,N>::operator Type(){
    assert(this!=nullptr);
    Type a;
    a=data[0];
    return a;
}
/**
*@brief Оператор присваивания vect одинаковых типов.
*@param vect a присваиваемый экземпляр класса
*/
template <class Type, int N>
const vect<Type,N> &vect<Type,N>::operator=(const vect<Type,N> &a){
    assert(this!=nullptr&&(&a!=nullptr));
    for(int i=0;i<N;i++){
       data[i]=a.data[i];
    }
    return *this;
}

/**
*@brief Оператор сложения vect и vect
*@param const vect &a второе слагаемое. Первым слагаемым является текущий экземпляр класса.
*@return возвращает новый экземпляр класса vect
*/
template <class Type, int N>
vect<Type,N> vect<Type,N>::operator+(const vect<Type,N> &a){
    assert(this!=nullptr&&(&a!=nullptr));
    vect<Type,N> temp;
    for(int i=0;i<N;i++){
        temp.data[i]=data[i]+a.data[i];
    }
    return temp;
}

/**
*@brief Оператор присваивания со сложением
*@param const vect &a вектор прибавляемый к текущему значению.
*@return возвращает изменённый в соотвествии с переданным значением экземпляр класса вектора.
*/
template <class Type, int N>
const vect<Type,N> &vect<Type,N>::operator+=(const vect<Type,N> &a){
    assert(this!=nullptr&&(&a!=nullptr));
    for(int i=0;i<N;i++){
        data[i]+=a.data[i];
    }
    return *this;
}

/**
*@brief Оператор вычитания vect из vect
*@param const vect &a вычитатель. Вычитаемым является текущий экземпляр класса.
*@return возвращает новый экземпляр класса vect
*/
template <class Type, int N>
vect<Type,N> vect<Type,N>::operator-(const vect<Type,N> &a){
    assert(this!=nullptr&&(&a!=nullptr));
    vect<Type,N> temp;
    for(int i=0;i<N;i++){
        temp.data[i]=data[i]-a.data[i];
    }
   return temp;
}

/**
*@brief Оператор присваивания с вычитанием
*@param const vect &a вектор вычитаемый из текущего значения
*@return возвращает текущий экземпляр класса из которого вычтено a
*/
template <class Type, int N>
const vect<Type,N> &vect<Type,N>::operator-=(const vect<Type,N> &a){
    assert(this!=nullptr&&(&a!=nullptr));
    assert(this!=nullptr&&(&a!=nullptr));
    for(int i=0;i<N;i++){
        data[i]-=a.data[i];
    }
    return *this;
}

/**
*@brief Оператор умножения вектора на число
*@param const Type &a число на которое необходимо умножить текущий экземпляр вектора
**@return возвращает новый экземпляр класса vect
*/
template <class Type, int N>
vect<Type,N> vect<Type,N>::operator*(const Type &a){
    assert(this!=nullptr&&(&a!=nullptr));
    vect<Type,N> temp;
    for(int i=0;i<N;i++){
        temp.data[i]=data[i]*a;
    }
    return temp;
}

/**
*@brief Оператор присваивания с умножением вектора на число
*@param const Type &a число на которое умножается вектор
*@return возвращает текущий экземпляр класса умноженный на a
*/
template <class Type, int N>
const vect<Type,N> &vect<Type,N>::operator*=(const Type &a){
    assert(this!=nullptr&&&a!=nullptr);
    for(int i=0;i<N;i++){
        data[i]*=a;
    }
    return *this;
}

/**
*@brief Оператор деления вектора на число
*@param const Type &a число на которое делится
**@return возвращает новый экземпляр класса vect
*/
template <class Type, int N>
vect<Type,N> vect<Type,N>::operator/(const Type &a){
    assert(this!=nullptr&&(&a!=nullptr));
    vect<Type,N> temp;
    for(int i=0;i<N;i++){
        temp.data[i]=data[i]/a;
    }
    return temp;
}

/**
*@brief Оператор присваивания с делением вектора на число
*@param const Type &a число на которое делится вектор
*@return возвращает текущий экземпляр класса умноженный на a
*/
template <class Type, int N>
const vect<Type,N> &vect<Type,N>::operator/=(const Type &a){
    assert(this!=nullptr&&&a!=nullptr);
    for(int i=0;i<N;i++){
        data[i]/=a;
    }
    return *this;
}

/**
*@brief Оператор смены знака значения.
*менят знак всех элементов вектора.
*/
template <class Type, int N>
const vect<Type,N> &vect<Type,N>::operator-(){
    assert(this!=nullptr);
    for(int i=0;i<N;i++){
       data[i]=-data[i];
    }
    return *this;
}

#endif // ORT_H_INCLUDED
