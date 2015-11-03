#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <cmath>
#include <omp.h>
#include <vector>
#include <tbb/blocked_range2d.h>

class ApplySolver {
public:
	void operator()(tbb::blocked_range2d<size_t>& r)const {
		for(int i=r.rows().begin(), i_end=r.rows().end(); i<i_end; i++){
            for(int j=r.cols().begin(), j_end=r.cols().end(); j<j_end; j++){
    	        printf("%d/%d\n",i,j);
            }
        }
	}
};
void Parallel_for(){
	ApplySolver solver;
	tbb::parallel_for(tbb::blocked_range2d<size_t>(1,5,1,5),solver);
}
int main(int argc, char const *argv[])
{

	Parallel_for();
	return 0;
}