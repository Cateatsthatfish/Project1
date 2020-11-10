/*
https://blog.csdn.net/qq_40515692/article/details/106749232
others_multiline1.cpp的优化版本
B[k*P+j]->B[j*P+k]


*/


#include <windows.h> //多线程头文件
#include <iostream>
#include <ctime>
#include <chrono>  // 计算时间

using namespace std;

struct Matrix{
    int row;
    int column;
    int total ;
    float * datas;
};

struct MYDATA {
    int begin, end;
    float *A, *B, *C;
    int P, N;
};


//?
DWORD ThreadProc(LPVOID IpParam) {
    MYDATA *pmd = (MYDATA *) IpParam;
    float *A = pmd->A, *B = pmd->B, *C = pmd->C;
    int begin = pmd->begin, end = pmd->end, P = pmd->P, N = pmd->N;

    // 线程多的话，这个最好应该提出来
    int sizeB = N * P;
    int *revB = new int[sizeB];
    for (int index = 0; index < sizeB; index++) {
        int i = index / P, j = index % P;
        revB[i * P + j] = B[j * P + i];
    }

    for (int index = begin; index < end; index++) {
        int i = index / P, j = index % P;
        C[i * P + j] = 0;
        for (int k = 0; k < N; ++k) {
            C[i * P + j] += A[i * N + k] * revB[j * P + k];
        }
    }
    delete[]revB;
    return 0;
}

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C);
void display_Matrix(const Matrix & A);
void initial_MatrixA(Matrix &A);
void initial_MatrixB(Matrix &A);



int main()
{

    Matrix A;
    initial_MatrixA(A);
    //display_Matrix(A);

    Matrix B;
    initial_MatrixB(B);
    //display_Matrix(B);

    Matrix C;

    // const？
    int M = A.row;
    int N = A.column;
    int P = B.column;
    C.row = M;
    C.column = P;
    C.total = M*P;
    C.datas = new float[C.total]();



    const int m = 4;
    for(int i = 0; i< 5; i++){
    auto t1=std::chrono::steady_clock::now(); 

    // ----------------------------------- 多线程

    //句柄：
    //https://www.cnblogs.com/marchtea/archive/2011/12/04/2275534.html
    HANDLE hThread[m];
    static MYDATA mydt[m];
    int temp = (M * P) / m;
   for (int i = 0; i < m; ++i) {
        mydt[i].A = A.datas, mydt[i].B = B.datas, mydt[i].C = C.datas;
        mydt[i].begin = i * temp, mydt[i].end = i * temp + temp, mydt[i].P = P, mydt[i].N = N;
        if (i == m - 1) // 最后一个线程计算剩余的
            mydt[i].end = M * P;
        hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc, &mydt[i], 0, NULL);
    }
    WaitForMultipleObjects(m, hThread, TRUE, INFINITE);

    auto t2=std::chrono::steady_clock::now();
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
    }
    
/*
    display_Matrix(A);
    display_Matrix(B);
    display_Matrix(C);
*/
    delete [] A.datas;
    delete [] B.datas;
    delete [] C.datas;


    return 0;
}


Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C){

    int m = A.row;
    int n = A.column;
    int l = B.column;
    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();

    auto t1=std::chrono::steady_clock::now(); //开始时间
    for(int i = 0; i < m ; i++ ){
        for(int j = 0; j < l; j++ ){
            float temp = 0; 
            for (int k = 0; k< n; k++){
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
   /*
    int n = A.column;
    for(int i = 0; i< A.row;i++){
        for(int j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
    
    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;
    
}

void initial_MatrixA(Matrix &A){
    A.row = 1400;
    A.column = 1400;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}
void initial_MatrixB(Matrix &A){
    A.row = 1400;
    A.column = 1400;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}