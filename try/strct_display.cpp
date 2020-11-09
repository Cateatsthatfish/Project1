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
void display_MatrixB(const Matrix & A);
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

//按照行来输出（先从左到右，再从上到下）
void display_Matrix(const Matrix & A){
    //基本信息：
    cout << "row = " << A.row << endl;
    cout << "column =" << A.column << endl;
    cout << "total = " << A.total << endl;
    //数组：
    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;
    //以矩阵形式展出：
    long long n = A.column;
    for(long long i = 0; i< A.row;i++){
        for(long long j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//按照列来输出（先从上到下，再从左到右）
void display_MatrixB(const Matrix & A){
    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;
    long long n = A.column;
    for(long long j =0 ; j < A.column ; j++){
        for(long long i = 0; i< A.row;i++){
        
        cout << A.datas[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

////这里初始化的内容待改进
void initial_MatrixA(Matrix &A){
    A.row = 4;
    A.column = 3;
    A.total = A.row * A.column;
    for(long long i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}
