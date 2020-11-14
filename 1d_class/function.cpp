#include <iostream>
//不知道有什么用先放着
#include <immintrin.h>
// 随机数
#include <cstdlib>
#include <ctime>
// 头文件
#include "1d_matrix.h"

const int a = -1;
const int b = 1;

using namespace std;

Matrix::Matrix(size_t r,size_t c){
    _Row = r;
    _Column = c;
    _Total = r*c;
    _Matrix = new float [_Total];

    srand((int)time(0));
    for(int i = 0 ; i<_Total;i++){
        _Matrix[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
    }
}

Matrix::Matrix(size_t r,size_t c, const float init){
    _Row = r;
    _Column = c;
    _Total = r*c;
    _Matrix = new float [_Total];

    for(int i = 0 ; i<_Total;i++){
        _Matrix[i] = init;
    }

}

void Matrix::display(){
    //基本信息：
    cout << "row = " << _Row << endl;
    cout << "column =" << _Column << endl;
    cout << "total = " << _Total << endl;
    //数组：
    for(int i = 0 ; i< _Total;i++){
        cout << _Matrix[i] << ",";
    }
    cout << endl;
    //以矩阵形式：
    for(int i = 0; i< _Row;i++){
        for(int j =0 ; j < _Column ; j++){
        cout << (*this)(i,j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    
}

Matrix Matrix::multi(const Matrix &B){
    //Matrix temp()
}
