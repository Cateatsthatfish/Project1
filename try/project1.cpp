
#include<iostream>
#include<chrono> //计算时间方法一
#include <string> //getline()
#include <cstdlib> //随机数
#include <ctime> //随机数

#pragma GCC optimize(3, "Ofast", "inline") //加速

const int a = 0;
const int b = 1;

using namespace std;
struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas ;
};

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C);
void display_Matrix(const Matrix & A);
void initial_Matrix(Matrix &A);
bool isValid_int(string in);

int main(){
    ////////////initialization type 2 ->use set function
    struct Matrix A;
    initial_Matrix(A);
    //display_Matrix(A);

    struct Matrix B;
    initial_Matrix(B);
    //display_Matrix(B);

    
    struct Matrix C ;

    auto t1=std::chrono::steady_clock::now(); //开始时间
    
    C = multiplication(A,B,C);
   
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
   
    
    //display_Matrix(C);

    //判定可以相乘的条件
    //if(A.column == B.row){    }
    delete [] A.datas;
    delete [] B.datas;
    delete [] C.datas;

    //Matrix C = multiplication()
    return 0;
}

Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C){
    //cout << "in function" << endl;
    C.row = A.row;
    C.column = B.column;
    C.total = C.row * C.column;
    C.datas = new float[C.total];
    long long n = A.column;
    
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
    //cout << "row = " << A.row << endl;
    //cout << "column =" << A.column << endl;
    //cout << "total = " << A.total << endl;
    //cout << "location = " << &A << endl;
    //cout << "location of data = " << &A.datas <<endl;
    for(int i = 0; i< A.total; i++){
        cout << A.datas[i] << " ";
    }
    cout << endl;
}

////这里初始化的内容待改进
void initial_Matrix(Matrix &A){
    string n1_in, m1_in; 
    long long n1,m1;
    cout << "initialize a m*n matrix:(m,n are positive integers)" << endl;
    cout << "m= ";
    getline(cin,m1_in);
    while(!isValid_int(m1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "m= ";
    getline(cin,m1_in);    
        }

    cout << "n= ";
    getline(cin,n1_in);
    while(!isValid_int(n1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "n= ";
    getline(cin,n1_in);      
        }

    m1 = atoi(m1_in.c_str());
    n1 = atoi(n1_in.c_str());

    A.row = m1;
    A.column = n1;
    A.total = A.row * A.column;
    A.datas = new float [A.total];

    srand((int)time(0));
    for(int i = 0; i< A.total;i++){
        A.datas[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
    }

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