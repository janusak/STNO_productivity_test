#ifndef RUNGE_STIOCH4
#define RUNGE_STIOCH4
#include <iostream>
/**
*@brief Реалимзация метода Рунге-Кутты 4-го порядка стохастического для языка С++
*Метод написан для интеграла Стратоновича и может отличаться от представлнных в литературе т.к. там обычно даются примеры для интеграла Ито
*В качестве  val_type может быть использован к примеру std::valarray или другая реализация контейнера реализующего простейшие математически операции над векторами.
*@param void (*det)(double*,double*,double)     Детерминированная часть стохастического интеграла.
*@param void (*stoch)(double*,double*,double)   Стохастическая часть стохастического интеграла
*@param double *in Входные значения параметров интеграла.
*@param int dimension размерность уравнения.
*@param double dt Шаг интегрирования для детерминированной части уравнения.
*@param double ds Шаг интегрирования для стохастической части уравнения. Для нормального шума берётся равным sqrt(dt)
*@param double *out значение параметров интеграла после пройденного шага интегрирования.
*/
template <typename fun_type1,typename fun_type2,typename val_type>
inline void runge_stoch4(fun_type1 df,fun_type2 sf, val_type &in, double &t,double dt,double ds,val_type &out){
    val_type k1;
    val_type k2;
    val_type k3;
    val_type k4;

    k1 = df(in,t)*dt          + sf(in,t)*ds;
    k2 = df(in+k1/2.,t)*dt    + sf(in+k1/2.,t)*ds;
    k3 = df(in+k2/2.,t)*dt    + sf(in+k2/2.,t)*ds;
    k4 = df(in+k3,t)*dt       + sf(in+k3,t)*ds;
    out=in+(k1+k2*2.+k3*2.+k4)/6. ;
    t=t+dt;
}
/**
*@brief Реалимзация метода Рунге-Кутты 4-го порядка стохастического для языка С
* Метод написан для интеграла Стратоновича и может отличаться от представлнных в литературе т.к. там обычно даются примеры для интеграла Ито
*@param void (*det)(double*,double*,double)     Детерминированная часть стохастического интеграла.
*@param void (*stoch)(double*,double*,double)   Стохастическая часть стохастического интеграла
*@param double *in Входные значения параметров интеграла.
*@param int dimension размерность уравнения.
*@param double dt Шаг интегрирования для детерминированной части уравнения.
*@param double ds Шаг интегрирования для стохастической части уравнения. Для нормального шума берётся равным sqrt(dt)
*@param double *out значение параметров интеграла после пройденного шага интегрирования.
*/
void runge_stoch4c(void (*det)(double*,double*,double),void (*stoch)(double*,double*,double),double *in,int dimension,double *t,double dt,double ds,double *out);
#endif //RUNGE_STIOCH4
