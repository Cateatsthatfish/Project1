#include<chrono> //time counting
#include<iostream>
#include <string> //getline()
#include <cstdlib> //随机数
#include <ctime> //随机数

using namespace std;
const int a = 0;
const int b = 1;

struct Matrix{
    long long row;
    long long column;
    long long total ;
    float * datas ;
};

Matrix & multiplication(const Matrix & A, const Matrix & B);
void display_Matrix(const Matrix & A);
void initial_Matrix(Matrix &A);
bool isValid_int(string in);

int main(){
    ////////////initialization type 2 ->use set function
    Matrix A;
    auto t1=std::chrono::steady_clock::now();
    initial_Matrix(A);
    auto t2=std::chrono::steady_clock::now();
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
    //display_Matrix(A);
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