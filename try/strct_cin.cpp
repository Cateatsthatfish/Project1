#include <iostream>
using namespace std;
int main(){
    int n1,m1;
    cout << "Please initialize the first matrix with (n1,m1):" << endl;
    cout << "n1= ";
    cin >> n1;
    cout << "m1= ";
    cin >> m1;
    if(!cin){
        cout << "wrong input" << endl;
    }else{
        cout <<"n1 = " << n1 << endl;
    }
    return 0;
}
/*
test:
Please initialize the first matrix with (n1,m1):
n1= 123.23
m1= wrong input
*/