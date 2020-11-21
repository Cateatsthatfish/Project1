#include <iostream>
using namespace std;

int a,b;
void display();
int main(){
    a = 10;
    cout << a << endl;
    display();
    //cout << b << endl;
    return 0;
}
void display(){
    cout <<"a=" << a << endl;

}