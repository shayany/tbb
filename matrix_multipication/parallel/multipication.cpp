#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>
#include <tbb/blocked_range2d.h>
int const n=1000;
int const m=1000;
int const size=1000;

class Multiply
{
    float (*my_a)[size], (*my_b)[m], (*my_c)[m];    
public:   
    void operator()(const tbb::blocked_range2d<size_t>& r) const {
        float (*a)[size]=my_a;
        float (*b)[m]=my_b;
        float (*c)[m]=my_c; 
        for(int i=r.rows().begin(); i!=r.rows().end(); ++i )
        {
            for(int j=r.cols().begin(); j!=r.cols().end(); ++j )
            {
                for(int k=0;k<size;++k)
                {
                    c[i][j]+=a[i][k]*b[k][j];
                }                
            }
        }            
    }
    Multiply(float a[n][size],float b[size][m], float c[n][m]) :
        my_a(a), my_b(b), my_c(c) {

        }
};

void calculate(float a[n][size],float b[size][m],float c[n][m]){    

    tbb::parallel_for (tbb::blocked_range2d<size_t>(0, n, 32, 0, m, 32),Multiply(a,b,c) );
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

