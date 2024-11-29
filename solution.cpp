#include "head.h"
#define EPS 1e-32
#define NUM_THREADS 3



typedef struct {

	int threadID; //айди потока
	int n, colomn, start, end;
	double** a;
	double* b;
	
} thread_args;


int solution(int n, double** a, double* b, double* x) {

	//std::pair<double, double> fi;
	int i, j, k, rc; //, j, i;
	
	

	for (k = 0; k < n-1; k++) { //приводим k-й столбик
		
		
		pthread_t threads[NUM_THREADS]; //массив потоков
		
		//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	
		thread_args args[NUM_THREADS]; //выделение памяти под аргументы
		
		//согласно лемме есть n-k матриц...
		int PerThread = (n-k) / NUM_THREADS;
		
		for (int t = 0; t < NUM_THREADS; t++) {
		    args[t].threadID = t;
		    args[t].n = n;
		    args[t].colomn = k;
		    args[t].start = (k+1) + t * PerThread;
		    args[t].end = (k+1) + (t+1) * PerThread;
		    args[t].a = a;
		    args[t].b = b;
			//cout << args[t].end << endl;
		    if (t == NUM_THREADS - 1) {
		        args[t].end = n; // чтобы последний был обработан
		        
		    }
		    
			//запускаем
		    rc = pthread_create(&threads[t], NULL, transform, &args[t]);
		    if (rc) {exit(1); return 1; }
		}
		
		//ожидаем завершения......
		for (int t = 0; t < NUM_THREADS; t++) {
		    pthread_join(threads[t], NULL);
		}
		
		//pthread_exit(NULL);

		
		//output(n, n, n, a);
	}

	for (i = n-2; i >= 0; i--) {
		x[i] = b[i];
		for ( j = i+1; j < n; j++) {
			x[i] -= a[j][i]*x[j];
		}
		if (abs(a[i][i])< EPS) throw MyException("solution.cpp::solution: division by zero error\n", EC_ZERO);
		x[i] = x[i]/a[i][i];
	}

	if (abs(a[n-1][n-1])< EPS) throw MyException("solution.cpp::solution: division by zero error\n", EC_ZERO);
	x[n-1] = b[n-1]/a[n-1][n-1];
	
	return 0;
}

void* transform(void *args) {

	thread_args* data = (thread_args*)args;
	//int threadID = data->threadID; //айди потока
	int n = data->n;
	int k = data->colomn; 
	int start = data->start; int end = data->end;
    double **a = data->a; double *b = data->b;
    
    //output(10, 10, 10, a);
    double norm, x, y, fi1, fi2;
 
	int j; double r = abs(a[k][k]);
	
	for (j = start; j < end; j++) { 
		r += abs(a[k][j]);
		if (r < EPS) continue; //тогда и поворачивать не нужно...
		x = a[k][k];
		y = a[k][j];
		norm = sqrt(x*x+y*y);
		//а как обработать исключение???
		if (abs(norm)< EPS) return NULL; //ф вот так!
		fi1 = x/norm;
		fi2 = y/norm;
		
		
		rotate(j, k, fi1, fi2, b); // вращаем правую часть отдельно
		
		
		for (int l=0; l<n; l++) {
			rotate(j, k, fi1, fi2, a[l]); // и провернули стольцы, первый индекс - столбец!!
		}
		
			
	}
	pthread_exit(NULL);
}
