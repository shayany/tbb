#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>

void calculate(int x1, int y1,std::vector<double>&  u,int x2,int y2,std::vector<double>&  f,double t0,double t1,double dt,double nu){
    std::vector<double> u_new(x1*y1);
    double counterLoop=t0;


    for (int i=0; i<x1; i++)
        for (int j=0; j<y1; j++)
            u_new[i*y1 + j]=u[i*y1 + j];

    while(counterLoop<=t1)
    {
        for(int i=1;i<x1;i++)
        {
            for(int j=1;j<y1;j++)
                u_new[i*y1+j]=u[i*y1+j] + dt * (nu*u[(i-1)*y1+j] + nu*u[i*y1+j-1] - 4*nu*u[i*y1+j] + nu*u[i*y1+j+1] + nu*u[(i+1)*y1+j] + f[i*y1+j]);
        }
        for (int i=1; i<x1-1; i++)
            for (int j=1; j<y1-1; j++)
                    u[i*y1 + j]=u_new[i*y1 + j];
        counterLoop+=dt;
    }

}
void main()
{
    int const m=500;
    int const n=500;
    double timer=0.;    
    std::vector<double> u(n*m);
    std::vector<double> f(n*m);
    for (int i=0;i<n*m;i++)
    {
        u[i]=0;
        f[i]=1;
    }
    
    timer-=omp_get_wtime();//Start timer
    
    calculate(n, m, u,n,m, f,0,1000,.1,1);

    timer+=omp_get_wtime();//End timer
    
    std::cout.setf(std::ios::fixed);
    std::cout<<"\n"<<std::setprecision(15)<<timer<<"\n";
    
    /*std::cout.setf(std::ios::fixed);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            std::cout<<std::setprecision(10)<<u[i*m + j]<<"\t";
        }    
        std::cout<<"\n";
    }*/          
}
