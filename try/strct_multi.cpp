//2020.10.28
#include<iostream>
using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas = new float[total];
};

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C);
void display_Matrix(const Matrix & A);
void initial_MatrixA(Matrix &A);
void initial_MatrixB(Matrix &A);

int main(){
    ////////////initialization type 2 ->use set function
    Matrix A;
    initial_MatrixA(A);
    display_Matrix(A);

    Matrix B;
    initial_MatrixB(B);
    display_Matrix(B);

    Matrix C;
    C = multiplication(A,B,C);
    display_Matrix(C);

    //判定可以相乘的条件
    //if(A.column == B.row){    }
    delete [] A.datas;
    delete [] B.datas;
    //delete [] C.datas;

    //Matrix C = multiplication()
    return 0;
}

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C){
    C.row = A.row;
    C.column = B.column;
    C.total = C.row * C.column;
    long long an = A.column;
    long long bn = B.column;

    long long m = A.row;
    long long n = A.column;
    long long l = B.column;
    C.row = m;
    C.column = l;

    for(long long i = 0; i < m ; i++ ){
        for(long long j = 0; j < l; j++ ){
            float temp = 0; 
            for (long long k = 0; k< n; k++){
                //cout << "i="<< i << " j="<< j << " k= "<< k ;
                // cout << " k+an*i: " << k+an*i << " j+bn*k: " << j+bn*k ;
                //cout << "A["<< n*i+k << "] " << "B["<< l*k+j << "] ";

                temp += A.datas[n*i+k] * B.datas[l*k+j];
                //cout << A.datas[n*i+k] << "*" << B.datas[l*k+j] << " + " ;
                }
                //cout << " ->C["<< l*i+j << "]= "<<temp << endl;   

                //cout << " j+ bn*i: " << j+ bn*i << endl;
                C.datas[l*i+j] = temp;

            
        }
    }

    return C;

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
    A.row = 3;
    A.column = 3;
    A.total = A.row * A.column;
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}
void initial_MatrixB(Matrix &A){
    A.row = 3;
    A.column = 3;
    A.total = A.row * A.column;
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}