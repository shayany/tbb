#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>
#include <tbb/blocked_range3d.h>

int const n=1000;
int const m=1000;
int const p=1000;
class ApplySolver {
	//std::vector<std::vector<double>> my_u;
	//std::vector<std::vector<double>> my_f;
	//std::vector<std::vector<double>> &my_u_new;
	std::vector<std::vector<std::vector<double>>> &u;
	std::vector<std::vector<std::vector<double>>> &f;
	std::vector<std::vector<std::vector<double>>> &u_new;
	double my_nu;
	double my_dt;
public:	
	void operator()(const tbb::blocked_range3d<size_t>& r)const {
	//std::vector<std::vector<double>> u=my_u;
	//std::vector<std::vector<double>> f=my_f;
	//std::vector<std::vector<double>> &u_new=my_u_new;
		double dt=my_dt;
		double nu=my_nu;
		for(int i=r.pages().begin(), i_end=r.pages().end(); i<i_end; i++){
			for(int j=r.rows().begin(), j_end=r.rows().end(); j<j_end; j++){
        			for(int k=r.cols().begin(), k_end=r.cols().end(); k<k_end; k++){
//u_new[i][j][k]+=i+j+k;    	        
			u_new[i][j][k]=u[i][j][k] + dt * (nu*u[i-1][j][k] + nu*u[i][j-1][k] + nu*u[i][j][k-1] - 6*nu*u[i][j][k] + nu*u[i+1][j][k] + nu*u[i][j+1][k] +nu*u[i][j][k+1] + f[i][j][k]);
        			}
        		}
		}
	}

	//Constructior
	ApplySolver(std::vector<std::vector<std::vector<double>>> &u_args,std::vector<std::vector<std::vector<double>>> &f_args,std::vector<std::vector<std::vector<double>>> &u_new_args,double nu,double dt):u(u_args),f(f_args),u_new(u_new_args),my_nu(nu),my_dt(dt){}
};


void MyPrint(std::vector<std::vector<std::vector<double>>> input){
	std::cout.setf(std::ios::fixed);
	for (int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			for(int k=0;k<p;k++){
				std::cout<<std::setprecision(15)<<input[i][j][k]<<"\t";
			}
			std::cout<<"\n";	
		}
		std::cout<<"\n";
	}
}

int Parallel_for(){
	//Start Initialization
	double timer=0.0;	
		
	double dt=.1;
	double t0=0;
	double t1=1000;
	double nu=1;
	tbb::task_scheduler_init init(tbb::task_scheduler_init::deferred);
	init.initialize(16);
    std::vector<std::vector<std::vector<double>>> u;
    std::vector<std::vector<std::vector<double>>> f;
    std::vector<std::vector<std::vector<double>>> u_new;
    
    u.resize(n);
    f.resize(n);
    u_new.resize(n);
    for (int i = 0; i < n; ++i)
    {
        u[i].resize(m);
        f[i].resize(m);
        u_new[i].resize(m);
    }
    for (int i=0;i<n;i++)
    {
        for (int j = 0; j < m; ++j)
        {
            u[i][j].resize(p);
            f[i][j].resize(p);
            u_new[i][j].resize(p);		
        }
    }	
    for (int i=0;i<n;i++)
    {
        for (int j = 0; j < m; ++j)
        {
	    for(int k=0;k<p;k++)
	    {	
            	u[i][j][k]=0;
            	f[i][j][k]=1;
	    }
        }
    }
	//End Initialization
	
	timer-=omp_get_wtime();//Start timer
	double timer_copy=.0;	
	double avg=0;
	for(double t=t0;t<=t1;t+=dt)
	{
		tbb::parallel_for(tbb::blocked_range3d<size_t>(1,n-1,32,1,m-1,32,1,p-1,32),ApplySolver(u,f,u_new,nu,dt));		
		
		//Copy u_new to u
		timer_copy-=omp_get_wtime();	
		std::swap(u,u_new);	
		//u=u_new;
		timer_copy+=omp_get_wtime();
		avg+=timer_copy;
		timer_copy=0;
		/*for (int i = 0; i < n; ++i)
		{
			for (int j = 0 ; j < m; ++j)
			{	
				u[i][j]=u_new[i][j];
			}	
		}*/
	}   
    timer+=omp_get_wtime();//End timer
   
    std::cout.setf(std::ios::fixed);
    std::cout<<"\nCopy Time:"<<std::setprecision(15)<<avg<<"\n";

    std::cout.setf(std::ios::fixed);
    std::cout<<"\nTotal Time:"<<std::setprecision(15)<<timer<<"\n";
   // MyPrint(u);
/*
        printf("\n%f\n",u[100][100]);
        printf("\n%f\n",u[100][101]);
        printf("\n%f\n",u[100][102]);
        printf("\n%f\n",u[100][103]);
        printf("\n%f\n",u[100][104]);
*/
}


int main(int argc, char const *argv[])
{
	Parallel_for();
	return 0;
}
