// from strct_multi.cpp & my_Matrix.h

/*
矩阵定位和数组定位
A：m*n -> A(i,k)=datas[i*n+k]
B：n*l -> B(k,j)=datas[k*l+j]
C: m*l -> C(i,j)=datas[i*l+j]
*/
#include<chrono> //计算时间

#include <cstdlib>
#include <immintrin.h>
// my_Matrix.h
#include<iostream>
using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas;
};

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C);
Matrix & multiplication_openblas(const Matrix & A, const Matrix & B, Matrix &C);
void kernel(float* c, float **a , float*b, int row, int col);
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

    /*
    for(int i = 0; i< 5; i++){
        cout << 1+i <<":";
        C = multiplication(A,B,C);
    }
    */
    
    cout << "finished!" <<endl;
    //display_Matrix(C);

    delete [] A.datas;
    delete [] B.datas;
    delete [] C.datas;

    //Matrix C = multiplication()
    return 0;
}

void kernel(float* c, float **a , float*b, int row, int col){
    register float t0(0),t1(0),t2(0),t3(0),t4(0),t5(0),t6(0),t7(0),
                    t8(0),t9(0),t10(0),t11(0),t12(0),t13(0),t14(0),t15(0); 



}
Matrix & multiplication_openblas(const Matrix & A, const Matrix & B, Matrix &C){
    long long m = A.row;
    long long n = A.column;
    long long l = B.column;
    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();

    float *tr[4];

    for(int i = 0; i< 4; i++){
        tr[i] = new float[n]();
    }
    //for(int j = )
}

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C){

    long long m = A.row;
    long long n = A.column;
    long long l = B.column;
    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();

    auto t1=std::chrono::steady_clock::now(); //开始时间
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
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;

    return C;

}


void display_Matrix(const Matrix & A){
    /*
    cout << "row = " << A.row << endl;
    cout << "column =" << A.column << endl;
    cout << "total = " << A.total << endl;
    */

    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;

   
    long long n = A.column;
    
    
    for(long long i = 0; i< A.row;i++){
        for(long long j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << "  ";
        }
        cout << endl;
    }
    

}

void initial_MatrixA(Matrix &A){
    A.row = 2;
    A.column = 5;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}
void initial_MatrixB(Matrix &A){
    A.row = 5;
    A.column = 2;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}