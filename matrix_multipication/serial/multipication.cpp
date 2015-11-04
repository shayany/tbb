#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>

int const n=1000;
int const m=1000;
int const size=1000;

void calculate(float a[n][size],float b[size][m],float c[n][m]){    

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<size;k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }                
        }
    }

}
void main()
{
    float a[n][size];
    float b[size][m];
    float c[n][m];
    double timer=0.;    

    float counter=1;
    
    for (int i=0; i<n; i++)
        for (int j=0; j<size; j++)
            a[i][j]=counter++;
    
    for (int i=0; i<size; i++)
        for (int j=0; j<m; j++)
            b[i][j]=counter++;

    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            c[i][j]=0;    
    
    timer-=omp_get_wtime();//Start timer
    
    calculate(a,b,c);

    timer+=omp_get_wtime();//End timer
    
    
    std::cout.setf(std::ios::fixed);
    std::cout<<"\nTime:"<<std::setprecision(15)<<timer<<"\n";
    /*
    std::cout.setf(std::ios::fixed);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<size; j++)
        {
            std::cout<<std::setprecision(2)<<a[i][j]<<"\t";
        }    
        std::cout<<"\n";
    }
    std::cout.setf(std::ios::fixed);
    std::cout<<"\n";
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<m; j++)
        {
            std::cout<<std::setprecision(2)<<b[i][j]<<"\t";
        }    
        std::cout<<"\n";
    }
    std::cout<<"\n";
    std::cout.setf(std::ios::fixed);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            std::cout<<std::setprecision(2)<<c[i][j]<<"\t";
        }    
        std::cout<<"\n";
    }*/
}

