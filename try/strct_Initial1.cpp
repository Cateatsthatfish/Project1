//2020.10.28
#include<iostream>
using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas = new float[total];
};

Matrix & multiplication(const Matrix & A, const Matrix & B);
void display_Matrix(const Matrix & A);

int main(){
    ////////////initialization type 1
    Matrix A;
    A.row = 2;
    A.column = 2;
    A.total = A.row * A.column;
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i+1;
    }

    display_Matrix(A);
    delete [] A.datas;

    //Matrix C = multiplication()
    return 0;
}

Matrix & multiplication(const Matrix & A, const Matrix & B){
    //Matrix 
}
void display_Matrix(const Matrix & A){
    cout << "row = " << A.row << endl;
    cout << "column =" << A.column << endl;
    cout << "total = " << A.total << endl;
    for(int i = 0; i< A.total; i++){
        cout << A.datas[i] << " ";
    }
}