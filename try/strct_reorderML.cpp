//from strct_multi.cpp->strct_reorder尝试减少循环次数的版本

/*

假设矩阵B中的元素储存在datas[]中的时候是按照一列接着一列而不是一行一行的顺序以此为前提进行计算

矩阵定位和数组定位:
A：m*n -> A(i,k)=datas[i*n+k]
B：n*l -> B(k,j)=datas[j*n+k]
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


Matrix & multiplication_1(const Matrix & A, const Matrix & B, Matrix &C);
void display_Matrix(const Matrix & A);
void display_MatrixB(const Matrix & A);
void initial_MatrixA(Matrix &A);
void initial_MatrixB(Matrix &A);

int main(){
    ////////////initialization type 2 ->use set function
    
    Matrix A;
    initial_MatrixA(A);
    //display_Matrix(A);
    
    Matrix B;
    initial_MatrixB(B);
    //display_MatrixB(B);
    
    Matrix C;
    C = multiplication_1(A,B,C);
    //display_Matrix(C);
    
    
    for(int i = 0; i< 5; i++){
        cout << 1+i <<":";
        C = multiplication_1(A,B,C);
    }
    

    cout << "finished!" <<endl;
   

    delete [] A.datas;

    delete [] B.datas;
    delete [] C.datas;


    return 0;
}

Matrix & multiplication_1(const Matrix & A, const Matrix & B, Matrix &C){

    long long m = A.row;
    long long n = A.column;
    long long l = B.column;
    //long long loop = n/4;
    long long loop = n/2;
    //long long left = n%4;
    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();

    auto t1=std::chrono::steady_clock::now(); //开始时间
    for(long long i = 0; i < m ; i++ ){
        for(long long j = 0; j < l; j++ ){
            float temp = 0; 
            //for (long long k = 0; k< n; k++){
            //for (long long k = 0; k< (4*loop); k+=4){
            for (long long k = 0; k< (2*loop); k+=2){ 
                temp += A.datas[n*i+k] * B.datas[n*j+k];
                temp += A.datas[n*i+k+1] * B.datas[n*j+k+1];
                /*
                temp += A.datas[n*i+k+2] * B.datas[n*j+k+2];
                temp += A.datas[n*i+k+3] * B.datas[n*j+k+3];  
                */              

                //cout << A.datas[n*i+k] << "*" << B.datas[n*j+k] << " + " ;
                }
            for(long long k = (2*loop); k<n;k++){
                temp += A.datas[n*i+k] * B.datas[n*j+k];
            }
                //cout << " ->C["<< l*i+j << "]= "<<temp << endl; 
                 C.datas[l*i+j]=temp;
        }
    }
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;

    return C;

}
void display_Matrix(const Matrix & A){
    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;
    long long n = A.column;
    for(long long i = 0; i< A.row;i++){
        for(long long j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void display_MatrixB(const Matrix & A){
    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;
    long long n = A.row;
    
    for(long long i = 0; i< A.row;i++){
        for(long long j =0 ; j < A.column ; j++){
        cout << A.datas[j*n+i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void initial_MatrixA(Matrix &A){
    A.row =1400;
    A.column = 1400;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}

void initial_MatrixB(Matrix &B){
    B.row = 1400;
    B.column = 1400;
    B.total = B.row * B.column;
    B.datas = new float[B.total]();
    /*
    for(long long i = 0; i< B.total;i++){
        B.datas[i] = i;
    }
    */
   int k = 0;

    for(long long i = 0; i < B.row;i++){
        for(long long j = 0; j < B.column; j++){
            B.datas[j*B.row+i] = k;
            k++;
        }
    }
   

}