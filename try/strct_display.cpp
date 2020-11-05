//2020.10.28
#include<iostream>
using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas = new float[total];
};


void display_Matrix(const Matrix & A);
void initial_MatrixA(Matrix &A);
void initial_MatrixB(Matrix &A);

int main(){
    ////////////initialization type 2 ->use set function
    Matrix A;
    initial_MatrixA(A);
    display_Matrix(A);

    delete [] A.datas;

    return 0;
}

void display_Matrix(const Matrix & A){
    cout << "row = " << A.row << endl;
    cout << "column =" << A.column << endl;
    cout << "total = " << A.total << endl;
    long long n = A.column;
    for(long long i = 0; i< A.row;i++){
        for(long long j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

////这里初始化的内容待改进
void initial_MatrixA(Matrix &A){
    A.row = 5;
    A.column = 3;
    A.total = A.row * A.column;
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = 1;
    }

}
