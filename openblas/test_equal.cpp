#include <iostream>
using namespace std;
int main(){
    int * arr = new int[2];
    arr[0] = 1;
    arr[1] = 2;
    int * arr01 = arr;
    //地址是一样的
    cout << arr << endl;
    cout << arr01 <<endl;

    delete [] arr;
    //delete [] arr01;
    //因为它的初始化不是new



    return 0;
}