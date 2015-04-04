#include "runge_stoch4.hpp"

void runge_stoch4c(void (*det)(double*,double*,double),void (*stoch)(double*,double*,double),double *in,int dimension,double *t,double dt,double ds,double *out){
    double k[4][dimension];
    double temp[dimension];
    double temp2[dimension];
    det(in,k[0],*t);
    stoch(in,temp2,*t);
    for(int i=0;i<dimension;i++){
        k[0][i]=dt*k[0][i]+ds*temp2[i];
        temp[i]=in[i]+k[0][i]/2;
    }
    det(temp,k[1],*t);
    stoch(temp,temp2,*t);
    for(int i=0;i<dimension;i++){
        k[1][i]=dt*k[1][i]+ds*temp2[i];
        temp[i]=in[i]+k[1][i]/2;
    }
    det(temp,k[2],*t);
    stoch(temp,temp2,*t);
    for(int i=0;i<dimension;i++){
        k[2][i]=dt*k[2][i]+ds*temp2[i];
        temp[i]=in[i]+k[2][i];
    }
    det(temp,k[3],*t);
    stoch(temp,temp2,*t);
    for(int i=0;i<dimension;i++){
        k[3][i]=dt*k[3][i]+ds*temp2[i];
        temp[i]=(k[0][i]+k[1][i]*2+k[2][i]*2+k[3][i])/6;
        out[i]+=temp[i];
    }
    *t+=dt;
}
