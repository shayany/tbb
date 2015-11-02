#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>


using namespace std;
using namespace tbb;
//Function Foo do something!
void Foo(float &item)
{
	item*=item;
}
//Apply function Foo on Array
void SerialApplyFoo(float a[], size_t n ) {
    for( size_t i=0; i!=n; ++i )
        Foo(a[i]);
}


int main() {
	
	cout<<"\n";
	tbb::task_scheduler_init init(tbb::task_scheduler_init::deferred);
        init.initialize(1);

	double timer=0.;
	const long n=1000000; 
	float b[n];
	
	//Initilize the array
	for(int i=0;i<n;i++)
		b[i]=i;
	

		
	timer-=omp_get_wtime();
	
	SerialApplyFoo(b,n);

	timer+=omp_get_wtime();

	cout.setf(ios::fixed);
	cout<<"\n"<<setprecision(15)<<timer<<"\n";
	cout.setf(ios::fixed);
	
	for(int i=0;i<10;i++)
		cout<<setprecision(0)<<b[i]<<endl;
	cout<<"\n";
	return 0;
}
