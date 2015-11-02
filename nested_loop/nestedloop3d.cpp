#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <tbb/blocked_range3d.h>
#include <cmath>
#include <omp.h>

float *output;
float *input;
using namespace std;
using namespace tbb;

int main() {
	
tbb::parallel_for( tbb::blocked_range3d<int>(0, 10, 0, 10, 0, 10),
    []( const tbb::blocked_range3d<int> &r ) {
        for(int i=r.pages().begin(), i_end=r.pages().end(); i<i_end; i++){
            for(int j=r.rows().begin(), j_end=r.rows().end(); j<j_end; j++){
                for(int k=r.cols().begin(), k_end=r.cols().end(); k<k_end; k++){
                    printf("Hello World %d/%d/%d\n", i,j,k);
                }
            }
        }
});
	return 0;
}
