#include <iostream>
#include <pthread.h>
#include <bits/stdc++.h>

using namespace std;

class Matrix {
public:

	int matrix[100][100];
	int m;
	int n;

	Matrix(int m,int n) {
		this->m = m;
		this->n = n;
	}

	void define() {
		int i,j;

		cout<<"Enter matrix elements ( row wise )."<<endl;

		for(i = 0; i < m; i++) {
			for(j = 0; j < n; j++) {
				cin>>matrix[i][j];
			}
		}
	}

	void display_matrix() {
		int i,j;

		for(i = 0; i < m; i++) {
			for(j = 0; j < n; j++) {
				cout<<matrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};

Matrix global1(0,0);
Matrix global2(0,0);
Matrix global3(0,0);

void *operate(void* thread_id) {
	long id;
	id = (long)thread_id;

	int row_number = (int)id;
	int i,j,k;
	
	for(i = 0; i < global2.n; i++) { // iteration through all columns
		int sum = 0;

		thread::id this_id = this_thread::get_id();
		cout<<"working thread id is = "<<this_id<<endl;
				
		//cout<<"Thread "<<row_number<<" is updating."<<endl;
		for(j = 0; j < global2.m; j++) { // iterations through column
			sum += global1.matrix[row_number][j] * global2.matrix[j][i];
			global3.display_matrix();
			cout<<endl;
			//cout<<endl;
		}
		global3.matrix[row_number][i] = sum;
	}
}

Matrix init() {
	
	int m,n;

	cout<<"Enter size of matrix = ";
	cin>>m;
	cin>>n;

	Matrix matrix(m,n);
	matrix.define();

	return matrix;
}

int main(void) {

	Matrix mat1 = init();
	Matrix mat2 = init();

	if(mat1.n!=mat2.m) {
		cout<<"Cannot operate matrix multiplication on the given input. Terminating..."<<endl;
		//exit(-1);
	}

	else {
		int Number_of_threads = mat1.m;
		Matrix mat3(mat1.m,mat2.n);

		global1 = mat1;
		global2 = mat2;
		global3 = mat3;

    	pthread_t t1[Number_of_threads];

    	for(int i = 0; i < Number_of_threads; i++)
    		pthread_create(&t1[i], NULL, &operate, (void *)i);

    	void* result;
    	for(int i = 0; i < Number_of_threads; i++)
    		pthread_join(t1[i],&result);

    	cout<<"Input matrices are."<<endl;
   		global1.display_matrix();
   		cout<<endl;
	    global2.display_matrix();

    	cout<<"Final matrix is = "<<endl;
    	global3.display_matrix();
	}
    return 0;
}