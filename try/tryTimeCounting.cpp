#include <iostream>
#include <chrono>

using namespace std;
int main(){
    auto t1=std::chrono::steady_clock::now();
    cout << "now!" << endl;
    auto t2=std::chrono::steady_clock::now();
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout << "(time: " << time << "ms)" << endl;
    return 0;
}