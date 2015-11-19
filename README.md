For connecting to abel:

```shell
ssh -Y abel.uio.no
```
###Loading the modules:
	For working with thread building block we have to load intel/2016.0 module .
###Compile the file :
```shell
  icpc min.cpp -o min.out -std=c++11 -ltbb -openmp -O3 -g -Wall
```  
  Or
```shell
	icpc parallel_for.cpp -I/cluster/software/VERSIONS/intel-2016.0/compilers_and_libraries_2016.0.109/linux/tbb/include 
	-L/cluster/software/VERSIONS/intel-2016.0/compilers_and_libraries_2016.0.109/linux/tbb/lib/intel64_lin/gcc4.4
	-o parallel -openmp -std=c++11 -ltbb
```
Also we have to add dynamic dependency libraries which in our case I have

```shell
source /cluster/software/VERSIONS/intel-2016.0/compilers_and_libraries_2016.0.109/linux/tbb/bin/tbbvars.sh intel64
```

