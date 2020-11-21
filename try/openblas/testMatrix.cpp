#include <iostream>
#include<chrono> 
#include <cstdlib>
#include <immintrin.h>
//#include "Matrix.h"
#include "my_Matrix.h"
//#pragma GCC optimize(3, "Ofast", "inline") 

using namespace std;

#define N 1000
const size_t N1 = 4;
const size_t N2 = 8;
int main(int argc,char* argv[]){
    /*
    Matrix m(0,0);
    cout << "end!" << endl;
    */
    
//    Matrix A(N,N,1),B(N,N,2);
	Matrix A(N1,N2,1),B(N2,N1,2);
    //Matrix B(N1,N2,1),A(N2,N1,2);
/*    A.display_Matrix();
    cout << endl;
    B.display_Matrix();
*/    

  
//---------------------------------multi1--------------------------------
    auto t1=std::chrono::steady_clock::now(); 
    cout << "multi1" <<endl;
//    A.multi1(B);
    Matrix C1 = A.multi1(B);
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time1=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time1 << "ms)" << endl;

    C1.display_Matrix();

//---------------------------------multi2--------------------------------
    auto t3=std::chrono::steady_clock::now(); 
//    A.multi2(B); 
    Matrix C2 =  A.multi2(B);
    auto t4=std::chrono::steady_clock::now(); //结束时间
    double time2=std::chrono::duration<double,std::milli>(t4-t3).count();
    cout << "(time: " << time2 << "ms)" << endl;

    //(time: 8399.18ms)(time: 34763.2ms)
    C2.display_Matrix();
    


//---------------------------------multi3--------------------------------
//   for(int i =0; i< 5 ; i++){
    auto t5=std::chrono::steady_clock::now(); 
//    A.multi3(B);
    Matrix C3 = A.multi3(B);
    auto t6=std::chrono::steady_clock::now(); //结束时间
    double time3=std::chrono::duration<double,std::milli>(t6-t5).count();
    cout << "(time: " << time3 << "ms)" << endl;
//   }

    C3.display_Matrix();


/**/
//---------------------------------multi4--------------------------------
//   for(int i =0; i< 5 ; i++){
    auto t7=std::chrono::steady_clock::now(); 
    //A.multi5(B);
    Matrix C4 = A.multi4(B);
   
    auto t8=std::chrono::steady_clock::now(); //结束时间
    double time4=std::chrono::duration<double,std::milli>(t8-t7).count();
    cout << "(time: " << time4 << "ms)" << endl;
//   }
   C4.display_Matrix();


/**/

/*
//---------------------------------multi5--------------------------------
//   for(int i =0; i< 5 ; i++){
    auto t9=std::chrono::steady_clock::now(); 
    //A.multi6(B);
    Matrix C5 = A.multi5(B);
    cout << "after" <<endl;
    auto t10=std::chrono::steady_clock::now(); //结束时间
    double time5=std::chrono::duration<double,std::milli>(t10-t9).count();
    cout << "(time: " << time5 << "ms)" << endl;
//   }
    C5.display_Matrix();

/**/


	return 0;
}