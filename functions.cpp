#include "head.h"
#define EPS 1e-32

using namespace std;

void input(int n, char* filename, double** a) {
	ifstream f;
	f.open(filename);
	if( f.is_open() ){
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				f >> a[j][i]; // j - столбец !!!
				
				if ( f.fail() ) throw MyException("functions.cpp::input: bad data error\n", EC_BADDATA); //The feof routine determines whether the end of stream has been passed...
			}
		}
		f.close();
	} else throw MyException("functions.cpp::input: bad open error\n", EC_BADOPEN);
}

void output(int n, int l, int m, double** a) {
	cout.setf(ios::scientific);
	for (int i=0; i<m && i<l; i++) {
		for (int j=0; j<m && j<n; j++) {
			cout << a[j][i] << " ";
		}
		cout << endl;	
	}
	cout << endl;
}

void output(int n, int m, double* b) {
	cout.setf(ios::scientific);
	for (int i=0; i<m && i<n; i++) {
		cout << b[i];
		cout << endl;
	}
	cout << endl;
}

double function(int k, int n, int i, int j) {
	switch (k) {
		case 1:
			return n-max(i,j)+1;
		case 2:
			return max(i,j);
		case 3:
			return abs(i-j);
		case 4:
			return 1.0/(i+j-1);
		default:
			throw MyException("functions.cpp::function: bad input data error\n", EC_BADINPUT);
	}
}

//////////////////////////////////////////////////////////////

void rotate(int i, int j, double fi1, double fi2, double* x) {
	double xi = x[i];
	x[i] = xi*fi1 - x[j]*fi2;
	x[j] = xi*fi2 + x[j]*fi1;
}




double residual(const int n, double** a, double* b, double* x) {
	double norm = 0;
	double numerator = 0;
	double denominator = 0;
	double* r;

	try { r = new double[n]; } catch (...) {
		throw MyException("functions.cpp::residual: memory error\n", EC_MEM);
	}
	for (int i = 0; i < n; i++) r[i] = 0;


	for (int i = 0; i < n; i++) {
		for (int j = 0; j< n; j++) {
			r[i] += a[j][i]*x[j];
		}
		r[i] -= b[i];
	}
	for (int i = 0; i < n; i++) {
		numerator += r[i]*r[i];
		denominator += b[i]*b[i];
	}
	if (abs(denominator)< EPS) throw MyException("functions.cpp::residual: division by zero error\n", EC_ZERO);

	numerator = sqrt(numerator);
	denominator = sqrt(denominator);

	delete [] r;

	norm = numerator/denominator;

	return norm;
}


