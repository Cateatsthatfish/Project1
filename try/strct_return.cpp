//2020.10.28
#include<iostream>
using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas = new float[total];
};

Matrix & copy(const Matrix & A, Matrix & B);
void display_Matrix(const Matrix & A);
void initial_Matrix(Matrix &A);

int main(){
    ////////////initialization type 2 ->use set function
    Matrix A;
    initial_Matrix(A);
    display_Matrix(A);

    Matrix B = copy(A,B);
    display_Matrix(B);
    delete [] A.datas;
    delete [] B.datas;

    //Matrix C = multiplication()
    return 0;
}

Matrix & copy(const Matrix & A, Matrix & B){
    B = A;
    return B;
     
}
void display_Matrix(const Matrix & A){
    cout << "row = " << A.row << endl;
    cout << "column =" << A.column << endl;
    cout << "total = " << A.total << endl;
    for(int i = 0; i< A.total; i++){
        cout << A.datas[i] << " ";
    }
    cout << endl;
}

////这里初始化的内容待改进
void initial_Matrix(Matrix &A){
    A.row = 2;
    A.column = 2;
    A.total = A.row * A.column;
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i+1;
    }

}