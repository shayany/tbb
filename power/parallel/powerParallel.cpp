#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>

float *output;
float *input;
using namespace std;
using namespace tbb;
//Function Foo do something!
void Foo(float &item)
{
	item*=item;
}


class ApplyFoo {
    float *const my_a;
public:
    void operator()( const blocked_range<size_t>& r ) const {
        float *a = my_a;
        for( size_t i=r.begin(); i!=r.end(); ++i ) 
           Foo(a[i]);
    }
    ApplyFoo( float a[] ) :
        my_a(a)
    {}
};

void ParallelApplyFoo( float a[], size_t n ) {
    parallel_for(blocked_range<size_t>(0,n,100000), ApplyFoo(a));
}
int main() {
	
	cout<<"\n";
	tbb::task_scheduler_init init(tbb::task_scheduler_init::deferred);
        init.initialize(2);

	double timer=0.;
	const long n=1000000; 
	float b[n];
	
	//Initilize the array
	for(int i=0;i<n;i++)
		b[i]=i;

		
	timer-=omp_get_wtime();
	
	ParallelApplyFoo(b,n);	

	timer+=omp_get_wtime();

	cout.setf(ios::fixed);
	cout<<"\n"<<setprecision(15)<<timer<<"\n";
	cout.setf(ios::fixed);
	
	for(int i=0;i<10;i++)
		cout<<setprecision(0)<<b[i]<<endl;
	cout<<"\n";
	return 0;
}
