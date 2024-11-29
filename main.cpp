#include "head.h"

using namespace std;


int main(int argc, char *argv[]) {
	int n, m, k, rc;
	double** a;
	double* b; double* x;
	double norm;
	unsigned int end_time, start_time;
	
	if (!argc) { cout << "main.cpp::main: bad data error\n"; return -1; }
	
	try {
		n = stoi(argv[1]);  //размерность
		m = stoi(argv[2]);  //количество выводимых значений в матрице
		k = stoi(argv[3]);  //номер формулы или 0, когда из файла
	} catch (std::logic_error& ex) {
		cout << ex.what(); return -1;
	} catch (...) {
		cout << "main.cpp::main: bad data error\n"; return -1;
	}
	
	if (n <= 0 || m <= 0 || k < 0 || k > 4) { 
		cout << "main.cpp::main: bad data error\n"; 
		return -1;
	}
	
	try { a = create_matrix<double>(n, n); } catch (MyException& ex) {
		cout << ex.what() << endl << "CODE: "<< ex.Code() << endl; return -1;
	}

	if (k != 0) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				try { a[i][j] = function(k,n,i+1,j+1); } catch(MyException& ex) {
					cout << ex.what() << endl << "CODE: "<< ex.Code() << endl;
					delete_matrix<double>(a, n); return -1;
				}
			}
		}
    } else {
    	try { input(n, argv[4], a); } catch (MyException& ex) {
    		cout << ex.what() << endl << "CODE: "<< ex.Code() << endl;
			delete_matrix<double>(a, n); return -1;
    	}
    }

    try { b = new double[n]; } catch (...) {
		cout << "main.cpp::main: memory error\n"; delete_matrix<double>(a, n); return -1;
	}


	for (int i = 0; i < n; i++) {
		b[i] = 0;
		for (int k = 1; k <= (n+1)/2; k++) {
			b[i] += a[2*k-2][i]; // да, тут все ВЕРНО ПОТОМУ ЧТО ИНДЕКСЫ С 0 и СТОЛБЕЦ ПЕРВЫЙ
		}
	}

	try { x = new double[n]; } catch (...) {
		cout << "main.cpp::main: memory error\n";
		delete_matrix<double>(a, n);
		delete [] b;
		return -1;
	}

	for (int i = 0; i < n; i++) x[i] = 0;


    output(n, n, m, a);
	output(n, m, b);

	cout << "SOLVING..." << endl;

	try {
		start_time =  clock();
		rc = solution(n, a, b, x);
		end_time = clock();
		if (rc==1) return -1;
	} catch (MyException& ex) { //разобраться с ИСКЛЮЧЕНИЕМ В ЭТОМ МЕСТЕ
		cout << ex.what() << endl << "CODE: "<< ex.Code() << endl;
		delete_matrix<double>(a, n);
		delete [] b;
		delete [] x;
		return -1;
	}

	unsigned int time = end_time - start_time;

	output(n, n, m, a);
	//output(n, m, b);
	//output(n, m, x);

	try { norm = residual(n, a, b, x); } catch (MyException& ex) {
		cout << ex.what() << endl << "CODE: "<< ex.Code() << endl;
		delete_matrix<double>(a, n);
		delete [] b;
		delete [] x;
		return -1;
	}

	cout << "The solution is:\n";
	output(n, m, x);
	cout << endl<< "The residual is: "<< norm;
	cout << endl<< "The working time is: "<< time <<" ms..." << endl << endl;

    delete_matrix<double>(a, n);
	delete [] b;
	delete [] x;
   	return 0;
}
