#include<iostream>
#include<chrono> 
#include <cstdlib>
#include <immintrin.h>
#include "1d_matrix.h"
#include <string>

//#pragma GCC optimize(3, "Ofast", "inline")

const int n = 1000;
const size_t N1 = 4;
const size_t N2 = 8;

using namespace std;
int main(){

/*
    cout << "set the first matrix A(m1,n1):" << endl;
    string n1_in, m1_in; 
    long long n1,m1;
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
*/



    Matrix A(n,n,1),B(n,n,2);
    Matrix A(N1,N2,1),B(N2,N1,2);
//  A.display();
//  B.display();



    /*
    Matrix C = A.multi(B);
    C.display();
    */

 
//---------------------------------multi1--------------------------------
    auto t1=std::chrono::steady_clock::now(); 
//    cout << "multi1" <<endl;
//    A.multi1(B);
    Matrix C1 = A.multi_ijk(B);
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time1=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time1 << "ms)" << endl;

    C1.display();

//---------------------------------multi2--------------------------------
    auto t3=std::chrono::steady_clock::now(); 
//    A.multi2(B); 
    Matrix C2 =  A.multi_ikj(B);
    auto t4=std::chrono::steady_clock::now(); //结束时间
    double time2=std::chrono::duration<double,std::milli>(t4-t3).count();
    cout << "(time: " << time2 << "ms)" << endl;

    C2.display();
    

//---------------------------------multi3--------------------------------
//   for(int i =0; i< 5 ; i++){
    auto t5=std::chrono::steady_clock::now(); 
//    A.multi3(B);
    Matrix C3 = A.multi_block(B);
    auto t6=std::chrono::steady_clock::now(); //结束时间
    double time3=std::chrono::duration<double,std::milli>(t6-t5).count();
    cout << "(time: " << time3 << "ms)" << endl;
//   }

    C3.display();



//---------------------------------multi4--------------------------------
//   for(int i =0; i< 5 ; i++){
    auto t7=std::chrono::steady_clock::now(); 
    //A.multi5(B);
    Matrix C4 = A.multi_4line(B);
   
    auto t8=std::chrono::steady_clock::now(); //结束时间
    double time4=std::chrono::duration<double,std::milli>(t8-t7).count();
    cout << "(time: " << time4 << "ms)" << endl;
//   }
   C4.display();



//---------------------------------multi5--------------------------------
//   for(int i =0; i< 5 ; i++){
    auto t9=std::chrono::steady_clock::now(); 
    //A.multi6(B);
    Matrix C5 = A.multi_4Revs(B);
    auto t10=std::chrono::steady_clock::now(); //结束时间
    double time5=std::chrono::duration<double,std::milli>(t10-t9).count();
    cout << "(time: " << time5 << "ms)" << endl;
//   }
    C5.display();

/**/


    
    return 0;
}
