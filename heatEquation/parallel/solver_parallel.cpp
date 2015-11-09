
/*
 *
 *2D converted to 1D
 *Global variable
 *
 */
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>
#include <tbb/blocked_range2d.h>
int const m=1000;
int const n=1000;
float u[n*m];
float f[n*m];
float u_new[n*m];
void calculate(int x1, int y1, float* u,int x2,int y2, float* f,float t0,float t1,float dt,float nu){
    
    for (int i=0; i<x1; i++)
        for (int j=0; j<y1; j++)
            u_new[i*y1 + j]=u[i*y1 + j];

    for(float counterLoop=t0;counterLoop<=t1;counterLoop+=dt)
    {
        tbb::parallel_for( tbb::blocked_range2d<size_t>(1, x1, 1, y1),
        [&]( const tbb::blocked_range2d<size_t> &r ) {
            for(int i=r.rows().begin(), i_end=r.rows().end(); i<i_end; i++){
                for(int j=r.cols().begin(), j_end=r.cols().end(); j<j_end; j++){
                    u_new[i*y1+j]=u[i*y1+j] + dt * (nu*u[(i-1)*y1+j] + nu*u[i*y1+j-1] - 4*nu*u[i*y1+j] + nu*u[i*y1+j+1] + nu*u[(i+1)*y1+j] + f[i*y1+j]);
                }
            }
        },tbb::auto_partitioner());

        //for(int i=1;i<x1;i++)
        //{
        //    for(int j=1;j<y1;j++)
        //        u_new[i*y1+j]=u[i*y1+j] + dt * (nu*u[(i-1)*y1+j] + nu*u[i*y1+j-1] - 4*nu*u[i*y1+j] + nu*u[i*y1+j+1] + nu*u[(i+1)*y1+j] + f[i*y1+j]);
        //}
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
    
    calculate(n, m,u,n,m,f,0,1000,.1,1);

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

