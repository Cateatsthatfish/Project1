#include <iostream>
#include <string> //getline()
using namespace std;
int main(){
    cout << "press \'1\' to reset matrix B with the right row number;" << endl;
    cout << "press any other key to quit;" << endl;
    string choice;
    getline(cin,choice);
    //cout << choice.length() <<endl;
    
    if(choice.length()==1 && choice[0]=='1'){
        cout << "continue!" << endl;
    }else{
        cout << "stop! "<< endl;
    }
    return 0;
}