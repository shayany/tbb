#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>

//Function Foo do something!
void Foo(float *item)
{
	(*item)*=(*item);
}
//Apply function Foo on Array
void SerialApplyFoo(std::vector<float>& a, size_t n ) {
    for( size_t i=0; i!=n; ++i )
        //std::cout<<&a[i];
	Foo(&a[i]);

}

int main() {
	
	std::cout<<"\n";
	
	double timer=0.;
	const long n=100000000; 
	std::vector<float> b(n);
	
	//Initilize the array
	for(int i=0;i<n;i++)
		b[i]=0;
	
	//print array on standard output
	for(int i=n-10;i<n;i++)
               std::cout<<b[i]<<"\n";
		
	timer-=omp_get_wtime();//Start timer
	
	SerialApplyFoo(b,n);

	timer+=omp_get_wtime();//End timer
	
	std::cout.setf(std::ios::fixed);
	std::cout<<"\n"<<std::setprecision(15)<<timer<<"\n";
	std::cout.setf(std::ios::fixed);
	
	for(int i=n-10;i<n;i++)
		std::cout<<std::setprecision(0)<<b[i]<<"\n";
	std::cout<<"\n";
	return 0;
}
