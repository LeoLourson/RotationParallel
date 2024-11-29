#pragma once
#include "MyException.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <pthread.h>

using namespace std;

template <typename TYPE>
void delete_matrix(TYPE **a, int m) {//m - столбцов
    for(int i=0; i<m; i++) delete[] a[i];
   	delete [] a;
}

template <typename TYPE>
TYPE** create_matrix(int n, int m) {//n - количество строк... m - столбцов
	TYPE** a;
	try {
		a = new TYPE*[m];
	} catch (...) { 
		throw MyException("head.h::create_array: memory allocation error\n", EC_MEM); 
	}
	
    for(int i=0; i<m; i++) {
    	try {
        	a[i] = new TYPE[n];
        } catch (...) { 
			throw MyException("head.h::create_array: memory allocation error\n", EC_MEM); 
		}
    }
    return a;
}

void output(int , int , int , double** );
void output(int , int , double* );
void input(int , char* filename, double** );
double function(int , int , int , int );

void rotate(int , int , double , double , double* );
void* transform(void *args);

double residual(const int , double** , double* , double* );

int solution(int , double** , double* , double* );
