#include <iostream>
using namespace std;
class candy{
    private:
    int number;
    public:
    candy();
    int setnum(int n){number = n; }
    int getnum(){return this->number;}
    //~candy();
};

int main(){
    candy c;
    c.setnum(3);
    cout << c.getnum();
    return 0;
}