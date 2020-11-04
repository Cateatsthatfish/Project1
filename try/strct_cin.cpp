#include <iostream>
#include <string>


using namespace std;
bool isValid_int(string in);

int main(){
    string n1_in, m1_in; 
    int n1,m1;
    cout << "initialize a m*n matrix:(m,n are positive integers)" << endl;
    cout << "m1= ";
    getline(cin,m1_in);
    while(!isValid_int(m1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "m1= ";
    getline(cin,m1_in);    
        }

    cout << "n1= ";
    getline(cin,n1_in);
    while(!isValid_int(n1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "n1= ";
    getline(cin,n1_in);      
        }

    m1 = atoi(m1_in.c_str());
    n1 = atoi(n1_in.c_str());
    
    return 0;
}
bool isValid_int(string in)
{
    bool len = true;
    if(in.length()==0){
        len = false;
    
    }
    // 不允许第一位是0的情况,与不允许输入0
    if(in[0]=='0'){
        len = false;
    }
    for(int i = 0 ; i< in.length();i++){
        if(in[i]>'9'||in[i]<'0')
        {
            len = false;
            break;
        }
    }
       
    
    return len;
}
/*
test:
Please initialize the first matrix with (n1,m1):
n1= 123.23
m1= wrong input
*/