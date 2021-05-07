Instructions :
1. Download testcase folder from "https://github.com/ajaykvala/Single-threads".
2. Put testcase folder in the directory where you would run the code.
2. Follow other instructions given below.


Format of input file is as follows :
1. First line has only the size of matrix.
2. From second line we have cost of edges separated by spaces. 


RUN serial.cpp:
1. Open code file
2. Set start_size = Smallest matrix size to start with.
3. Set end_size = Largest matrix size to go for.
4. Set num = Number of runs for each matrix size.
5. In the terminal run the following commands:
	a. g++ -O2 serial.cpp -o tt
	b. ./tt
6. A csv file with results will get created. 


RUN middle_loop_parallel_fw.cpp :
1. Open code file
2. Set start_size = Smallest matrix size to start with.
3. Set end_size = Largest matrix size to go for.
4. Set max_thds = No. of maximum threads.
5. Set num = Number of runs for each matrix size.
6. In the terminal run the following commands:
	a. g++ -O2 -fopenmp -mavx2 middle_loop_parallel_fw.cpp -o tt (remove -mavx2 from command and #pragma omp simd from code if you want to disable vectorisation)
	b. ./tt
7. A csv file with results will get created. 


RUN block_fw.cpp :
1. Open code file.
2. Set start_size = Smallest matrix size to start with.
3. Set end_size = Largest matrix size to go for.
4. Set max_thds = No. of maximum threads.
5. Set num = Number of runs for each matrix size.
6. Set BLOCK_SIZE = Desired block size
7. In the terminal run the following commands
	a. g++ -O2 -fopenmp -mavx2 block_fw.cpp -o tt (remove -mavx2 from command and #pragma omp simd from code if you want to disable vectorisation)
	b. ./tt
8. A csv file with results will get created. 


RUN mpi.cpp :
1. Open code file.
2. Set size = Size of matrix
3. Set testcase_no = Testcase file number to run(if you want to run /testcase/1024/input07.txt then set this to 7)
4. In the terminal run the following commands
	a. mpicxx -O3 -mavx2 mpi.cpp -o tt (remove -mavx2 and change -O3 to -O2 from command if you want to disable vectorisation)
	b. mpirun -machine=machines -np={number of processor} ./tt
5. Results are dispayed in the terminal window.


NOTE :
If you want to test code on a custom input then you'll have to provide input file(in above mentioned format) and corresponding correct output file.
