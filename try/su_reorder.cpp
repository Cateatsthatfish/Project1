//from strct_multi.cpp
//改变循环顺序：ijk->ikj
//https://zhuanlan.zhihu.com/p/146250334

/*
矩阵定位和数组定位
A：m*n -> A(i,k)=datas[i*n+k]
B：n*l -> B(k,j)=datas[k*l+j]
C: m*l -> C(i,j)=datas[i*l+j]
*/
#include<chrono> //计算时间
#include<iostream>
using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas;
};

Matrix & multiplication_reorder(const Matrix & A, const Matrix & B, Matrix &C);
void display_Matrix(const Matrix & A);
void initial_MatrixA(Matrix &A);
void initial_MatrixB(Matrix &A);

int main(){
    ////////////initialization type 2 ->use set function
    Matrix A;
    initial_MatrixA(A);
    //display_Matrix(A);

    Matrix B;
    initial_MatrixB(B);
    //display_Matrix(B);

    Matrix C;
    C = multiplication_reorder(A,B,C);
    //display_Matrix(C);
    
    for(int i = 0; i< 5; i++){
        cout << 1+i <<":";
        C = multiplication_reorder(A,B,C);
    }
    
   /*
   display_Matrix(A);
   display_Matrix(B);
   display_Matrix(C);
    */
    cout << "finished!" <<endl;
    //display_Matrix(C);

    delete [] A.datas;
    delete [] B.datas;
    delete [] C.datas;

    //Matrix C = multiplication()
    return 0;
}

Matrix & multiplication_reorder(const Matrix & A, const Matrix & B, Matrix &C){

    long long m = A.row;
    long long n = A.column;
    long long l = B.column;
    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();

    auto t1=std::chrono::steady_clock::now(); //开始时间
    for(long long i = 0; i < m ; i++ ){
        for (long long k = 0; k< n; k++){
        if(A.datas[n*i+k]){
        for(long long j = 0; j < l; j++ ){

            
                //cout << "i="<< i << " j="<< j << " k= "<< k ;
                // cout << " k+an*i: " << k+an*i << " j+bn*k: " << j+bn*k ;
                //cout << "A["<< n*i+k << "] " << "B["<< l*k+j << "] ";

                C.datas[l*i+j] += A.datas[n*i+k] * B.datas[l*k+j];
                //cout << A.datas[n*i+k] << "*" << B.datas[l*k+j] << " + " ;
                }
                //cout << " ->C["<< l*i+j << "]= "<<temp << endl;   

                //cout << " j+ bn*i: " << j+ bn*i << endl;
                 
        }
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
    long long n = A.column;
    
    
    for(long long i = 0; i< A.row;i++){
        for(long long j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << "  ";
        }
        cout << endl;
    }
    /*
    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;
    */
}

void initial_MatrixA(Matrix &A){
    A.row = 1400;
    A.column = 1400;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}
void initial_MatrixB(Matrix &A){
    A.row = 1400;
    A.column = 1400;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}