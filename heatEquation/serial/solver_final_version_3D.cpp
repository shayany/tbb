/*
 *  1)Implemented by vector:std
 *  2)The initialization has done automatically (use all the available thread and tasks)
 *  3)Logical copy
 *  4)HEAP memory
 */
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>
int const n=250;
int const m=250;
int const p=250;

void calculate(std::vector<std::vector<std::vector<double>>> &u,std::vector<std::vector<std::vector<double>>> f,double t0,double t1,double dt,double nu){    

    std::vector<std::vector<std::vector<double>>> u_new;
    u_new.resize(n);
									    double timer=0;
									    double avg=0;
    for (int i = 0; i < n; ++i)
    {
	u_new[i].resize(m);
    }

    for (int i=0;i<n;i++)
    {
        for (int j = 0; j < m; ++j)
        {
        	u_new[i][j].resize(p);
        }
    }

    double timer_copy=.0;				

    for(double counterLoop=t0;counterLoop<=t1;counterLoop+=dt)
    {
        for(int i=1;i<n-1;i++)
        {
            for(int j=1;j<m-1;j++)
		{
		for(int k=1;k<p-1;k++)
		{
			//u_new[i][j][k]+=i+j+k;
                	u_new[i][j][k]=u[i][j][k] + dt * (nu*u[i-1][j][k] + nu*u[i][j-1][k] +nu*u[i][j][k-1] - 6*nu*u[i][j][k] + nu*u[i][j+1][k] + nu*u[i+1][j][k] +nu*u[i][j][k+1] + f[i][j][k]);
		}
		}
        }

        //timer-=omp_get_wtime();//Start timer
        //    for (int i=1; i<n-1; i++)
        //       for (int j=1; j<m-1; j++)
        //                u[i][j]=u_new[i][j];
       	timer_copy-=omp_get_wtime();
        std::swap(u,u_new);

	timer_copy+=omp_get_wtime();
	avg+=timer_copy;
	timer_copy=0;
        //timer+=omp_get_wtime();//End timer
        //avg+=timer;
        //timer=0;
    }
	//u=U;
 	std::cout.setf(std::ios::fixed);
	std::cout<<"\nCopy Time:"<<std::setprecision(15)<<avg<<"\n";
        //std::cout.setf(std::ios::fixed);
        //std::cout<<"\nAverge copy Time:"<<std::setprecision(15)<<avg/10001<<"\n";
}
void main()
{

    double timer=0.;    
    std::vector<std::vector<std::vector<double>>> u;
    std::vector<std::vector<std::vector<double>>> f;
    u.resize(n);
    f.resize(n);
    for (int i = 0; i < n; ++i)
    {
        u[i].resize(m);
        f[i].resize(m);
    }

    for (int i=0;i<n;++i)
    {
        for (int j = 0; j < m; ++j)
    	{
		 u[i][j].resize(p);
 		 f[i][j].resize(p);
	}
    }

    for (int i=0;i<n;i++)
    {
        for (int j = 0; j < m; j++)
        {
		for(int k=0; k<p ; k++)
		{
            		u[i][j][k]=0;
            		f[i][j][k]=1;
		}
        }
    }
    
    timer-=omp_get_wtime();//Start timer
    
    calculate(u,f,0,1000,.1,1);

    timer+=omp_get_wtime();//End timer
    
    std::cout.setf(std::ios::fixed);
    std::cout<<"\nTime:"<<std::setprecision(15)<<timer<<"\n";
    

//        printf("\n%f\n",u[100][100]);
//        printf("\n%f\n",u[100][101]);
//        printf("\n%f\n",u[100][102]);
//        printf("\n%f\n",u[100][103]);
//        printf("\n%f\n",u[100][104]);

    //printf("\n%f\n",u[100][100]);
    std::cout.setf(std::ios::fixed);
    /*for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
		for(int k=0;k<p;k++)
		{
            		std::cout<<std::setprecision(15)<<u[i][j][k]<<"\t";
		}
		std::cout<<"\n";
        }    
        std::cout<<"\n";
    }*/
}
