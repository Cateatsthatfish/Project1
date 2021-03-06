/*
矩阵定位和数组定位
A：m*n -> A(i,k)=datas[i*n+k]
B：n*l -> B(k,j)=datas[k*l+j]
C: m*l -> C(i,j)=datas[i*l+j]
*/
#include<chrono> //计算时间
#include<iostream>
//#pragma GCC optimize(3, "Ofast", "inline") 
using namespace std;

struct Matrix{
    int row;
    int column;
    int total ;
    float * datas;
};

Matrix & multiplication_ijk(const Matrix & A, const Matrix & B, Matrix &C);
Matrix & multiplication_ikj(const Matrix & A, const Matrix & B, Matrix &C);
void display_Matrix(const Matrix & A);
void initial_MatrixA(Matrix &A);
void initial_MatrixB(Matrix &A);

int main(){

    Matrix A;
    initial_MatrixA(A);
    //display_Matrix(A);

    Matrix B;
    initial_MatrixB(B);
    //display_Matrix(B);

    Matrix C;

//    C = multiplication_ZRH(A,B,C);
//    C = multiplication_ijk(A,B,C);
//    C = multiplication_ikj(A,B,C);

    cout <<"------ijk------"<<endl;
//    for(int i = 0; i< 5; i++){
//        cout << 1+i <<":";
        C = multiplication_ijk(A,B,C);
//    }
    display_Matrix(C);
    
    //display_Matrix(C);


    cout <<"------ikj------"<<endl;
//    for(int i = 0; i< 5; i++){
//        cout << 1+i <<":";
        C = multiplication_ikj(A,B,C);
//    }
    display_Matrix(C);



    
    
    cout << "finished!" <<endl;
    //display_Matrix(C);

    delete [] A.datas;
    delete [] B.datas;
    delete [] C.datas;

    //Matrix C = multiplication()
    return 0;
}

// C(i,j) = ΣA(i,k)B(k,j)
Matrix & multiplication_ijk(const Matrix & A, const Matrix & B, Matrix &C){

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

//A(i,j)
// C(i,k) = ΣA(i,j)B(j,k)
Matrix & multiplication_ZRH(const Matrix & A, const Matrix & B, Matrix &C){

    int m = A.row;
    int n = A.column;
    int l = B.column;
    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();

    auto t1=std::chrono::steady_clock::now(); //开始时间
    for(int i = 0; i < m ; i++ ){
        for (int k = 0; k< n; k++){
        float multi = A.datas[n*i+k]; 
        for(int j = 0; j < l; j++ ){           
            
                //cout << "i="<< i << " j="<< j << " k= "<< k ;
                // cout << " k+an*i: " << k+an*i << " j+bn*k: " << j+bn*k ;
                //cout << "A["<< n*i+k << "] " << "B["<< l*k+j << "] ";
                C.datas[l*i+j] += multi * B.datas[l*k+j];
                //cout << A.datas[n*i+k] << "*" << B.datas[l*k+j] << " + " ;
                }
                //cout << " ->C["<< l*i+j << "]= "<<temp << endl;   

                //cout << " j+ bn*i: " << j+ bn*i << endl;
        }
    }
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;

    return C;

}

Matrix & multiplication_ikj(const Matrix & A, const Matrix & B, Matrix &C){

    int m = A.row;
    int n = A.column;
    int l = B.column;
    C.row = m;
    C.column = l;
    C.total = m*l;
    C.datas = new float[C.total]();

    auto t1=std::chrono::steady_clock::now(); //开始时间
    for(int i = 0; i < m ; i++ ){
        for (int k = 0; k< n; k++){
            float mult = A.datas[n*i+k];
            for(int j = 0; j < l; j++ ){
               C.datas[l*i+j] += mult * B.datas[l*k+j];
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

    for(int i = 0 ; i< A.total;i++){
        cout << A.datas[i] << ",";
    }
    cout << endl;

   
    int n = A.column;
    
    
    for(int i = 0; i< A.row;i++){
        for(int j =0 ; j < A.column ; j++){
        cout << A.datas[i*n+j] << "  ";
        }
        cout << endl;
    }
    

}

void initial_MatrixA(Matrix &A){
    A.row = 4;
    A.column = 8;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}
void initial_MatrixB(Matrix &A){
    A.row = 8;
    A.column = 4;
    A.total = A.row * A.column;
    A.datas = new float[A.total]();
    for(int i = 0; i< A.total;i++){
        A.datas[i] = i;
    }

}