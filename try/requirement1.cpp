//2020.11.3

//2020.10.28
#include<iostream>
#include<chrono> //计算时间方法一【failed】
#include<Windows.h> //计算时间方法二


using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas = new float[total];
};

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C);
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
    //display_Matrix(A);

    Matrix B;
    initial_Matrix(B);
    //display_Matrix(B);

    Matrix C;
    //cout << "interrupt" << endl;


    C = multiplication(A,B,C);

    
    display_Matrix(C);

    //判定可以相乘的条件
    //if(A.column == B.row){    }
    delete [] A.datas;
    delete [] B.datas;
    delete [] C.datas;

    //Matrix C = multiplication()
    return 0;
}

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C){
    C.row = A.row;
    C.column = B.column;
    C.total = C.row * C.column;
    long long n = A.column;
    C.datas = new float[C.total]; 

    for(long long i = 0; i < C.row ; i++ ){
        for(long long j = 0; j < C.column; j++ ){
            float temp = 0; //// long double (最后计算出来的C可以是long double 吗？)
            for (long long k = 0; k< n; k++){
                //cout << "A " << k+n*i << " B " << j+n*k << endl;
                temp += A.datas[k+n*i] * B.datas[j+n*k];
                }
                //cout << "C " << j+n*i << endl;
                C.datas[j+n*i] = temp;

            
        }
    }
    return C;

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
    A.datas = new float[A.total];
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}