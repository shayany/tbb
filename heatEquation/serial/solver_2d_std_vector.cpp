/*
 * I have done this implementation via vector:std
 * The initialization has done automatically (use all the available thread and tasks)
 * physical copy
 * HEAP memory
*/
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>
int const n=1000;
int const m=1000;

void calculate(std::vector<std::vector<double>> &u,std::vector<std::vector<double>> f,double t0,double t1,double dt,double nu){    

    std::vector<std::vector<double>> u_new;
    u_new.resize(n);
//				    double timer=0;
//				    double avg=0;
    for (int i = 0; i < n; ++i)
    {
        u_new[i].resize(m);
    }


//				    double timer_copy=.0;				
    for(double counterLoop=t0;counterLoop<=t1;counterLoop+=dt)
    {
        for(int i=1;i<n-1;i++)
        {
            for(int j=1;j<m-1;j++)
                u_new[i][j]=u[i][j] + dt * (nu*u[i-1][j] + nu*u[i][j-1] - 4*nu*u[i][j] + nu*u[i][j+1] + nu*u[i+1][j] + f[i][j]);
        }
//		        	timer_copy-=omp_get_wtime();
        u=u_new;

//				timer_copy+=omp_get_wtime();
//				avg+=timer_copy;
//				timer_copy=0;
        //timer+=omp_get_wtime();//End timer
        //avg+=timer;
        //timer=0;
    }
// 				std::cout.setf(std::ios::fixed);
//			        std::cout<<"\nCopy Time:"<<std::setprecision(15)<<avg<<"\n";
       
}
void main()
{

    double timer=0.;    

    std::vector<std::vector<double>> u;
    std::vector<std::vector<double>> f;
    u.resize(n);
    f.resize(n);
    for (int i = 0; i < n; ++i)
    {
        u[i].resize(m);
        f[i].resize(m);
    }

    for (int i=0;i<n;i++)
    {
        for (int j = 0; j < m; ++j)
        {
            u[i][j]=0;
            f[i][j]=1;
        }
    }
    
    timer-=omp_get_wtime();//Start timer
    
    calculate(u,f,0,1000,.1,1);

    timer+=omp_get_wtime();//End timer
    
    std::cout.setf(std::ios::fixed);
    std::cout<<"\nTime:"<<std::setprecision(15)<<timer<<"\n";
   /*Print 
    std::cout.setf(std::ios::fixed);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            std::cout<<std::setprecision(15)<<u[i][j]<<"\t";
        }    
        std::cout<<"\n";
    }*/
}
