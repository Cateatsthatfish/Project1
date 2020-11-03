////a structure designed for matrix

#include <iostream>
using namespace std;

struct Matirx{
    long long row ; //行的数量
    long long column ; //列的数量
    float * datas = new float[row*column]; ///先这么定义着？
    //用二维数组储存数据？
    //float ** datas = new float* [row];

};

long double matrix_multi (float* matrix_data1, float* matrix_data2){
    long double result = 0;
    //for(int i = 0 ; i < 1)
}

int main(){
    int row = 1;
    int column = 1;
    //float 
    return 0;
}