#include <iostream>

#include <math.h>
#include <string.h>
#include <ctime>
//Тестовая задача. В данном случае Метод Ругнге-Кутты для стохастических уравнений.
#include <runge_stoch4.hpp>

//Используемые для тестирования контейнеры.
#include <valarray>
#include <armadillo>
#include <vect.hpp>

//Зададим какие нибудь функции - пока отбалды. Потом может допишем примеры поинтереснее.
template<typename T> T det(T a,double t){
    return a/t;
}

template<typename T> T stoch(T a,double t){
    return -(a/(t*0.1));
}

inline void detc(double *in,double *out,double t){
    for(int i=0;i<3;i++){
        out[i]=in[i]/t;
    }
}

inline void stochc(double *in,double *out,double t){
    for(int i=0;i<3;i++){
        out[i]=-(in[i]/(t*0.1));
    }
}
int main(int argc, char *argv[])
{
    double dt=1E-5;     //Постоянная интегрирования для детерминированной части дифференциального уравнения.
    double ds=sqrt(dt); //Постоянная интегрирования для стохастической части дифференциального уравнения.
    int ii=30000;       //Колличество шагов интегрирования.
    double x0[]={1E+42,1E+42,1E+42};    //Начальные условия.
    double t0=1;                        //Начальное время
   {
        std::valarray<double> x(x0,3);
        double t=t0;

        std::cout<<"Контейнер valarray<double> "<<ii<<" прогонов время в пс: ";
        long a=clock();

        for(int i=0;i<ii;i++){
            runge_stoch4(det<std::valarray<double> >,stoch<std::valarray<double> >,x,t,dt,ds,x);
        }
        a=clock()-a;
        std::cout<<a<<std::endl;

        std::cout<<"x[0]="<<x[1]<<std::endl;
        std::cout<<"x[1]="<<x[0]<<std::endl;
        std::cout<<"x[2]="<<x[2]<<std::endl;
        std::cout<<"t="<<t<<std::endl;
    }
    {

        arma::Col<double> x(x0,3);
        double t=t0;

        std::cout<<"Armadillo Col<double> "<<ii<<" прогонов время в пс: ";
        long a=clock();

        for(int i=0;i<ii;i++){
            runge_stoch4(det<arma::Col<double> >,stoch<arma::Col<double> >,x,t,dt,ds,x);
        }
        a=clock()-a;
        std::cout<<a<<std::endl;
        std::cout<<"x[0]="<<x[1]<<std::endl;
        std::cout<<"x[1]="<<x[0]<<std::endl;
        std::cout<<"x[2]="<<x[2]<<std::endl;
        std::cout<<"t="<<t<<std::endl;

    }
    {
        vect<double,3> x(x0,3);
        double t=t0;

        std::cout<<"Контейнер-велосипед "<<ii<<" прогонов время в пс: ";
        long a=clock();

        for(int i=0;i<ii;i++){
            runge_stoch4(det<vect<double,3> >,stoch<vect<double,3> >,x,t,dt,ds,x);
        }
        a=clock()-a;
        std::cout<<a<<std::endl;
        std::cout<<"x[0]="<<x[1]<<std::endl;
        std::cout<<"x[1]="<<x[0]<<std::endl;
        std::cout<<"x[2]="<<x[2]<<std::endl;
        std::cout<<"t="<<t<<std::endl;


    }
    {
        double x[3];
        double t=t0;
        memcpy(x,x0,sizeof(x));

        std::cout<<"Чистый С "<<ii<<" прогонов время в пс: ";
        long a=clock();

        for(int i=0;i<ii;i++){
            runge_stoch4c(detc,stochc,x,3,&t,dt,ds,x);
        }
        a=clock()-a;
        std::cout<<a<<std::endl;
        std::cout<<"x[0]="<<x[1]<<std::endl;
        std::cout<<"x[1]="<<x[0]<<std::endl;
        std::cout<<"x[2]="<<x[2]<<std::endl;
        std::cout<<"t="<<t<<std::endl;

    }
    std::cout<<"Выводы делайте сами."<< std::endl;
}
