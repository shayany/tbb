/*
 *In this implementation, I have tried to serially solve a heat equation.
 *I have done the copy using a using a pointer!(For the sake of experiment)
 *The two dimensional array has been declared in a one dimensional structure.
 *I did not use the STD:VECTOR
 */
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>
int const n=10;
int const m=5;
float u[n*m];
float f[n*m];
float u_new[n*m];

void calculate(int x1, int y1, float* u,int x2,int y2, float* f,float t0,float t1,float dt,float nu){    

   
    for(float counterLoop=t0;counterLoop<=t1;counterLoop+=dt)
    {
        for(int i=1;i<x1;i++)
        {
            for(int j=1;j<y1;j++)
                u_new[i*y1+j]=u[i*y1+j] + dt * (nu*u[(i-1)*y1+j] + nu*u[i*y1+j-1] - 4*nu*u[i*y1+j] + nu*u[i*y1+j+1] + nu*u[(i+1)*y1+j] + f[i*y1+j]);
        }
        for (int i=1; i<x1-1; i++)
            for (int j=1; j<y1-1; j++)
                    u[i*y1 + j]=u_new[i*y1 + j];      	
    }

}
void main()
{

    double timer=0.;    

    for (int i=0;i<n*m;i++)
    {
        u[i]=0;
        f[i]=1;
    }
    
    timer-=omp_get_wtime();//Start timer
    
    calculate(n, m, u,n,m, f,0,1000,.1,1);

    timer+=omp_get_wtime();//End timer
    
    std::cout.setf(std::ios::fixed);
    std::cout<<"\nTime:"<<std::setprecision(15)<<timer<<"\n";
    
    std::cout.setf(std::ios::fixed);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            std::cout<<std::setprecision(10)<<u[i*m + j]<<"\t";
        }    
        std::cout<<"\n";
    }
}
