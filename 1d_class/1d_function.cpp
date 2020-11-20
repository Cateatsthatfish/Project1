#include <iostream>
//sse?
#include <immintrin.h>
// 随机数
#include <cstdlib>
#include <ctime>
// 头文件
#include "1d_matrix.h"
//多线程
#include <windows.h> 

const int a = -1;
const int b = 1;

using namespace std;

struct MYDATA {
    int begin, end;
    float *A, *B, *C;
    int P, N;
};

Matrix::Matrix(int r,int c){
    _Row = r;
    _Column = c;
    _Total = r*c;
    _Matrix = new float [_Total];

    srand((int)time(0));
    for(int i = 0 ; i<_Total;i++){
        _Matrix[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
        //_Matrix[i] = i;
    }
}

Matrix::Matrix(int r,int c, const float init){
    _Row = r;
    _Column = c;
    _Total = r*c;
    _Matrix = new float [_Total];

    for(int i = 0 ; i<_Total;i++){
        _Matrix[i] = i;
    }
    //_Matrix[4] = 3;

}

//拷贝构造
Matrix::Matrix(const Matrix& B){
    _Row = B._Row;
    _Column = B._Column;
    _Total = B._Total;
    _Matrix = new float [_Total];
    for(int i = 0; i< _Total;i++){
        _Matrix[i] = B._Matrix[i];
    }

}

void Matrix::display(){
    /*
    //基本信息：
    cout << "row = " << _Row << endl;
    cout << "column =" << _Column << endl;
    cout << "total = " << _Total << endl;
    //数组：
    for(int i = 0 ; i< _Total;i++){
        cout << _Matrix[i] << ",";
    }
    cout << endl;
    */
    //以矩阵形式：
    for(int i = 0; i< _Row;i++){
        for(int j =0 ; j < _Column ; j++){
        cout << (*this)(i,j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    
}

// C(i,j) = ∑ A(i,k)*B(k,j)
Matrix Matrix::multi_ijk(const Matrix&B){
    int M(_Row), N(_Column),P(B._Column);
    Matrix temp(M,P,0);
    for(int i = 0; i < M ; i++ ){
        for(int j = 0; j < P; j++ ){
            float c = 0; 
            for (int k = 0; k< N; k++){
                c += (*this)(i,k) * B(k,j);                
                }
            temp(i,j) = c;
        }
    }
    return temp;  
}


//https://zhuanlan.zhihu.com/p/146250334
// C(i,j) = ∑ A(i,k)*B(k,j)
Matrix Matrix::multi_ikj(const Matrix&B){
    int M(_Row), N(_Column),P(B._Column);
    Matrix temp(M,P,0);
    for(int i = 0; i < M ; i++ ){
        for (int k = 0; k< N; k++){
            float multi = (*this)(i,k); 
            for(int j = 0; j < P; j++ ){               
                temp(i,j) += multi * B(k,j);                
                }
        }
    }
    return temp; 
}

void Matrix::kernel(Matrix& c, float *a , float*b, int row, int col){
    int N(_Column);
    int n0(N*row),n1(N*(row+1)),n2(N*(row+2)),n3(N*(row+3));
    /*
    Matrix c : temp 
    float *a : this._Matrix
    float *b : tmpB 
    int row = i
    int col = j

    c(j,i) -> c(j+3,i+3)
    t0,  t1,  t2,  t3
    t4,  t5,  t6,  t7
    t8,  t9,  t10, t11
    t12, t13, t14, t15
    */
    register double t0(0),t1(0),t2(0),t3(0),t4(0),t5(0),t6(0),t7(0),
                    t8(0),t9(0),t10(0),t11(0),t12(0),t13(0),t14(0),t15(0);
    

    float *a0(a+n0),*a1(a+n1),*a2(a+n2),*a3(a+n3),
            *b0(b),*b1(b+N),*b2(b+2*N),*b3(b+3*N),
            *end=b0+N;
            //cout << *a0 << " " << *a1 << " " << *a2 << " " << *a3 << endl;
            

    do{
        t0+=*(a0)**(b0);
        t1+=*(a0)**(b1);
        t2+=*(a0)**(b2);
        t3+=*(a0++)**(b3);            

        t4+=*(a1)**(b0);
        t5+=*(a1)**(b1);
        t6+=*(a1)**(b2);
        t7+=*(a1++)**(b3);

        t8+=*(a2)**(b0);
        t9+=*(a2)**(b1);
        t10+=*(a2)**(b2);
        t11+=*(a2++)**(b3);

        t12+=*(a3)**(b0++);
        t13+=*(a3)**(b1++);
        t14+=*(a3)**(b2++);
        t15+=*(a3++)**(b3++);
            
    }while(b0!=end);

    c(col,row) = t0;
    c(col,row+1) = t1;
    c(col,row+2) = t2;
    c(col,row+3) = t3;

    c(col+1,row) = t4;
    c(col+1,row+1) = t5;
    c(col+1,row+2) = t6;
    c(col+1,row+3) = t7;

    c(col+2,row) = t8;
    c(col+2,row+1) = t9;
    c(col+2,row+2) = t10;
    c(col+2,row+3) = t11;

    c(col+3,row) = t12;
    c(col+3,row+1) = t13;
    c(col+3,row+2) = t14;
    c(col+3,row+3) = t15;


}

Matrix Matrix::multi_block(const Matrix &B){
    int M(_Row), N(_Column),P(B._Column);
    Matrix temp(M,P,0);
    float * tmpB = new float[4*N];
    int n1(N),n2(2*N),n3(3*N);
    
    for(int j = 0; j < P; j+=4){
        for(int k = 0; k < N ; k++){
            tmpB[k] =  B(k,j);
            tmpB[k+n1] = B(k,j+1);
            tmpB[k+n2] = B(k,j+2);
            tmpB[k+n3] = B(k,j+3);
        }
        /*
        for(int l = 0; l<4*N;l++){
            cout << tmpB[l] << " ";
        }
        */
        for(int i = 0; i < M; i+=4){
            kernel(temp,_Matrix,tmpB,i,j);            
        }
    }

    delete [] tmpB;
    return temp;   
}

DWORD ThreadProc(LPVOID IpParam) { 
    MYDATA *pmd = (MYDATA *) IpParam;
    float *A = pmd->A, *B = pmd->B, *C = pmd->C;
    int begin = pmd->begin, end = pmd->end, P = pmd->P, N = pmd->N;

    for (int index = begin; index < end; index++) {
        int  i = index / P, j = index % P;
        C[i * P + j] = 0;
        for (int k = 0; k < N; ++k) {
            C[i * P + j] += A[i * N + k] * B[k * P + j];
        }
    }
    return 0;
}

Matrix Matrix::multi_4line(const Matrix &B){
    int M(_Row), N(_Column),P(B._Column);
    Matrix C(M,P,0);

    const int m = 4;
    HANDLE hThread[m];
    static MYDATA mydt[m];
    int temp = (M * P) / m;
    for (int i = 0; i < m; ++i) {
        mydt[i].A = (*this)._Matrix, mydt[i].B = B._Matrix, mydt[i].C = C._Matrix;
        mydt[i].begin = i * temp, mydt[i].end = i * temp + temp, mydt[i].P = P, mydt[i].N = N;
        if (i == m - 1) // 最后一个线程计算剩余的
            mydt[i].end = M * P;
        hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc, &mydt[i], 0, NULL);
    }
    WaitForMultipleObjects(m, hThread, TRUE, INFINITE);

    return C;

}

/////?
Matrix Matrix::multi_4Revs(const Matrix &B){
    int M(_Row), N(_Column),P(B._Column);
    Matrix C(M,P,0);

    float *revB = new float[B._Total];
    for (int index = 0; index < B._Total; index++) {
        int i = index / P, j = index % P;
        revB[i * P + j] = B._Matrix[j * P + i];
    }

    const int m = 4;
    HANDLE hThread[m];
    static MYDATA mydt[m];
    int temp = (M * P) / m;
    for (int i = 0; i < m; ++i) {
        mydt[i].A = (*this)._Matrix;
        mydt[i].B = B._Matrix;
        mydt[i].C = C._Matrix;
        mydt[i].begin = i * temp;
        mydt[i].end = i * temp + temp;
        mydt[i].P = P;
        mydt[i].N = N;
        if (i == m - 1) // 最后一个线程计算剩余的
            mydt[i].end = M * P;
        hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc, &mydt[i], 0, NULL);
    }
    WaitForMultipleObjects(m, hThread, TRUE, INFINITE);

    return C;
}

bool isValid_int(string in)
{
    bool len = true;
    if(in.length()==0){
        len = false;
    
    }
    // 不允许第一位是0的情况,与不允许输入0
    if(in[0]=='0'){
        len = false;
    }
    for(int i = 0 ; i< in.length();i++){
        if(in[i]>'9'||in[i]<'0')
        {
            len = false;
            break;
        }
    }    
    return len;
}