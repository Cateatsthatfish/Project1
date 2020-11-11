#include <iostream>
#include<chrono> 
#include <cstdlib>
#include <immintrin.h>
#include "Matrix.h"

using namespace std;
#define N 1400
int main(int argc,char* argv[]){
	Matrix A(N,N,1),B(N,N,2);
	double dt;
    auto t1=std::chrono::steady_clock::now(); 
    //A.multi1(B); //(time: 13011.4ms)
    A.multi2(B); //(time: 8399.18ms)
    auto t2=std::chrono::steady_clock::now(); //结束时间
//毫秒级
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;


	return 0;
}