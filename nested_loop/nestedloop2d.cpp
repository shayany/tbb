#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <tbb/blocked_range2d.h>
#include <cmath>
#include <omp.h>

float *output;
float *input;
using namespace std;
using namespace tbb;

int main() {
tbb::parallel_for( tbb::blocked_range2d<int>(0, 10, 0, 10),
    []( const tbb::blocked_range2d<int> &r ) {
        for(int i=r.rows().begin(), i_end=r.rows().end(); i<i_end; i++){
            for(int j=r.cols().begin(), j_end=r.cols().end(); j<j_end; j++){
                printf("Hello World %d/%d\n", i,j);
            }
        }
});
	return 0;
}
