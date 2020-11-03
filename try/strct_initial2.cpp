#include<chrono> //time counting
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
void initial_Matrix(Matrix &A);

int main(){
    ////////////initialization type 2 ->use set function
    Matrix A;
    auto t1=std::chrono::steady_clock::now();
    initial_Matrix(A);
    auto t2=std::chrono::steady_clock::now();
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
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

////这里初始化的内容待改进
void initial_Matrix(Matrix &A){
    A.row = 2;
    A.column = 2;
    A.total = A.row * A.column;
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i+1;
    }

}