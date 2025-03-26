close all

vN = 1000:1000:8000;
[A,b,x,vec_loop_times,vec_iteration_count] = benchmark_solve_Jacobi(vN);