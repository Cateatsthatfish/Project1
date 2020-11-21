#include<iostream>
#include<chrono> //计算时间
#include <string> //getline()
#include <cstdlib> //随机数
#include <ctime> //随机数
#include <windows.h> //多线程

//#pragma GCC optimize(3, "Ofast", "inline") //加速

//随机数
const int a = 0;
const int b = 1;

// A(m,n) B(n,l)-> C(m.l)
int m(0),n(0),l(0);

using namespace std;

struct Matrix{
    int row;
    int column;
    int total ;
    float * datas ;
};

///4 lines
struct MYDATA {
    int begin, end;
    float *A, *B, *C;
    int P, N;
};


void display_Matrix(const Matrix & A);
void initial_Matrix(Matrix &A);
void reset_Matrix(Matrix &A);
bool isValid_int(string in);


void multi_ijk(const Matrix & A, const Matrix & B, Matrix &C);
void multi_ikj(const Matrix & A, const Matrix & B, Matrix &C);
//https://blog.csdn.net/artorias123/article/details/86527456
void kernel(Matrix &c, float *a , float*b, int row, int col);
void multi_block(const Matrix & A, const Matrix & B, Matrix &C);
//https://blog.csdn.net/qq_40515692/article/details/106749232
DWORD ThreadProc(LPVOID IpParam);
void multi_4line(const Matrix & A, const Matrix & B, Matrix &C);
void multi_4Revs(const Matrix & A, const Matrix & B, Matrix &C);
Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C);

int main(){

//-------------------------------------part 1: initial matrix A and B ---------------------
    struct Matrix A;
    cout << "set the first matrix A(m1,n1):" << endl;
    initial_Matrix(A);
    //display_Matrix(A);

    struct Matrix B;
    cout << "set the second matrix B(m2,n2):" << endl;
    initial_Matrix(B);
    //display_Matrix(B);

   

//-------------------------------------part 2: B.row==A.column ----------------------------
    cout << endl;
    cout << "……start to compute the multiplication of A and B to get matric C(m1,n2)……" << endl;
    while(B.row!=A.column){
    cout << "OOPs! the sizes of matrix A and B don't match!" << endl;
    cout << "->press \'1\' to reset matrix B with the right row number;" << endl;
    cout << "->press any other key to quit;" << endl;
    string choice;
    getline(cin,choice);    
    if(choice.length()==1 && choice[0]=='1'){
        initial_Matrix(B);
    }else{
        cout << "bye! "<< endl;
        return 0;
    }
    }

 //-------------------------------------part 3: compute A*B ---------------------------------
    struct Matrix C ;

    m = A.row;
    n = A.column;
    l = B.column; 

    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();
    
//////////////// ijk
    cout << "multi_ijk:   " ;
    multi_ijk(A,B,C);
    //display_Matrix(C);
    reset_Matrix(C);

//////////////// ikj
    cout << "multi_ikj:   " ;
    multi_ikj(A,B,C);
    //display_Matrix(C);

////////////////  block: 4*4 only
    cout << "multi_block: " ;
    if(!(m%4==0 && n%4==0 && l%4 == 0)){
        cout << endl;
        cout << "only operate when m,n and l are the multi of 4" << endl;
        cout << endl;
    }else{
    multi_block(A,B,C);
    //display_Matrix(C);
    }
    reset_Matrix(C);

////////////////  4line
    cout << "multi_4line: " ;
    multi_4line(A,B,C);
    //display_Matrix(C);

////////////////  4Revs
    cout << "multi_4Revs: " ;
    multi_4Revs(A,B,C);
    //display_Matrix(C);


    cout << endl;

 //-------------------------------------part 4: display A,B,C---------------------------------
    if( A.row<=10 && A.column <= 10 && B.row <= 10 && B.row <= 10){
        cout << "----- matrix A -----" << endl;
        display_Matrix(A);
        cout << "----- matrix B -----" << endl;
        display_Matrix(B);
        cout << "---- matrix A*B ----" << endl;
        display_Matrix(C);

    }


    delete [] A.datas;
    delete [] B.datas;
    delete [] C.datas;

    //Matrix C = multiplication()
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
                temp += A.datas[n*i+k] * B.datas[l*k+j];
                }
                C.datas[l*i+j] = temp;  
        }
    }
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;

    return C;

}

void multi_ijk(const Matrix & A, const Matrix & B, Matrix &C){
    auto t1=std::chrono::steady_clock::now(); //开始时间
    for(int i = 0; i < m ; i++ ){
        for(int j = 0; j < l; j++ ){
            float temp = 0; 
            for (int k = 0; k< n; k++){
                temp += A.datas[n*i+k] * B.datas[l*k+j];
                }
                C.datas[l*i+j] = temp;  
        }
    }
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
}

void multi_ikj(const Matrix & A, const Matrix & B, Matrix &C){

    auto t1=std::chrono::steady_clock::now(); //开始时间
    for(int i = 0; i < m ; i++ ){
        for (int k = 0; k< n; k++){
            float multi = A.datas[n*i+k];
            for(int j = 0; j < l; j++ ){
                C.datas[l*i+j] += multi * B.datas[l*k+j];
                }                 
        }
    }
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
}

void kernel(Matrix& c, float *a , float*b, int row, int col){
    
    int n0(n*row),n1(n*(row+1)),n2(n*(row+2)),n3(n*(row+3));
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
            *b0(b),*b1(b+n),*b2(b+2*n),*b3(b+3*n),
            *end=b0+n;
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

    c.datas[col*l+row] = t0;
    c.datas[col*l+row+1] = t1;
    c.datas[col*l+row+2] = t2;
    c.datas[col*l+row+3] = t3;

    c.datas[(col+1)*l+row] = t4;
    c.datas[(col+1)*l+row+1] = t5;
    c.datas[(col+1)*l+row+2] = t6;
    c.datas[(col+1)*l+row+3] = t7;

    c.datas[(col+2)*l+row] = t8;
    c.datas[(col+2)*l+row+1] = t9;
    c.datas[(col+2)*l+row+2] = t10;
    c.datas[(col+2)*l+row+3] = t11;

    c.datas[(col+3)*l+row] = t12;
    c.datas[(col+3)*l+row+1] = t13;
    c.datas[(col+3)*l+row+2] = t14;
    c.datas[(col+3)*l+row+3] = t15;


}

void multi_block(const Matrix & A, const Matrix & B, Matrix &C){
    float * tmpB = new float[4*n];
    int n1(n),n2(2*n),n3(3*n);

    auto t1=std::chrono::steady_clock::now(); //开始时间

        for(int j = 0; j < l; j+=4){
        for(int k = 0; k < n ; k++){
            tmpB[k] =  B.datas[l*k+j];
            tmpB[k+n1] = B.datas[l*k+j+1];
            tmpB[k+n2] = B.datas[l*k+j+2];
            tmpB[k+n3] = B.datas[l*k+j+3];
        }
        for(int i = 0; i < m; i+=4){
            kernel(C,A.datas,tmpB,i,j);            
        }
    }

    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
    delete [] tmpB;
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

void multi_4line(const Matrix & A, const Matrix & B, Matrix &C){

    const int lines = 4;
    HANDLE hThread[lines];
    static MYDATA mydt[lines];
    int temp = (m * l) / lines;

    auto t1=std::chrono::steady_clock::now(); //开始时间

    for (int i = 0; i < lines; ++i) {
        mydt[i].A = A.datas;
        mydt[i].B = B.datas;
        mydt[i].C = C.datas;
        mydt[i].begin = i * temp;
        mydt[i].end = i * temp + temp;
        mydt[i].P = l;
        mydt[i].N = n;
        if (i == lines - 1) // 最后一个线程计算剩余的
            mydt[i].end = m * l;
        hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc, &mydt[i], 0, NULL);
    }
    WaitForMultipleObjects(lines, hThread, TRUE, INFINITE);

    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;

}

void multi_4Revs(const Matrix & A, const Matrix & B, Matrix &C){

    float *revB = new float[B.total];
    for (int index = 0; index < B.total; index++) {
        int i = index / l, j = index % l;
        revB[i * l + j] = B.datas[j * l + i];
    }

    const int lines = 4;
    HANDLE hThread[lines];
    static MYDATA mydt[lines];
    int temp = (m * l) / lines;
    auto t1=std::chrono::steady_clock::now(); //开始时间

    for (int i = 0; i < lines; ++i) {
        mydt[i].A = A.datas;
        mydt[i].B = B.datas;
        mydt[i].C = C.datas;
        mydt[i].begin = i * temp;
        mydt[i].end = i * temp + temp;
        mydt[i].P = l;
        mydt[i].N = n;
        if (i == lines - 1) // 最后一个线程计算剩余的
            mydt[i].end = m * l;
        hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc, &mydt[i], 0, NULL);
    }
    WaitForMultipleObjects(lines, hThread, TRUE, INFINITE);

    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;

}

void initial_Matrix(Matrix &A){
    string n1_in, m1_in; 
    int n1,m1;
    //cout << "initialize a m*n matrix:(m,n are positive integers)" << endl;
    cout << "#row = ";
    getline(cin,m1_in);
    while(!isValid_int(m1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "#row = ";
    getline(cin,m1_in);    
        }

    cout << "#column = ";
    getline(cin,n1_in);
    while(!isValid_int(n1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "#column = ";
    getline(cin,n1_in);      
        }

    m1 = atoi(m1_in.c_str());
    n1 = atoi(n1_in.c_str());

    A.row = m1;
    A.column = n1;
    A.total = A.row * A.column;
    A.datas = new float [A.total]();

    srand((int)time(0));
    for(int i = 0; i< A.total;i++){
        //A.datas[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
        A.datas[i] = i;
    }

}

void display_Matrix(const Matrix & A){
    /*
    cout << "row = " << A.row << endl;
    cout << "column =" << A.column << endl;
    cout << "total = " << A.total << endl;
    */
    //cout << "location = " << &A << endl;
    //cout << "location of data = " << &A.datas <<endl;
    int n = A.column;
    for(int i = 0; i< A.row;i++){
        for(int j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void reset_Matrix(Matrix &A){
    for(int i = 0; i< A.total ; i++){
        A.datas[i] = 0;
    }
}

bool isValid_int(string in){
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