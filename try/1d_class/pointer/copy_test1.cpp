//值拷贝
#include <iostream>
#include <string>

using namespace std;

int i;

class math{
    private:
    int * matrix;
    int length;
    string name;

    public:
    math():matrix(nullptr),length(0),name("not given"){cout <<"math() called" << endl;}
    math(string n):matrix(nullptr),length(0),name(n){cout <<n << ": math(string n) called" << endl;}
    math(string n , int i);
    math(const math& m);
    ~math();

    // 赋值
    math & operator = (const math & m);
    // 移动赋值
    //math & operator = (math && m);
    // <<
    friend ostream & operator << (ostream & os, const math & m );
    // multi_ijk
    math plus(const math & m) const;

};


math::math(string n, int i){
    name = n;
    cout << name << ": math::math(int i) called" << endl;
    length = i;
    matrix = new int[i];
    
    for(int j = 0; j<i;j++){
        matrix[j] = j;
    }
}

// copy constructor
// 值复制
// 一定会构造一个新的类
math::math(const math & m){
    
    name = name.append("&").append(m.name);
    cout << name << ": math::math(const math & m) called "<< endl;
    length = m.length;
    matrix = new int [length];
    
    for(int i = 0; i< length; i++){
        matrix[i] = m.matrix[i];
    }      
}

math::~math(){
    cout << name << ": math::~math() called "<< endl;
    length = 0;
    delete [] matrix;
}

// =
math & math::operator=(const math & m){
    cout << "math & math::operator=(const math & m) called "<< endl;
    if(this != &m){
    length = m.length;
    name = name.append("&").append(m.name);

    if(matrix){
        delete[] matrix;
    }

    matrix = new int[length];
    for(int i = 0; i < length;i++){
        matrix[i] = m.matrix[i];
    }
    }else{
        return *this;
    }
}

// 移动赋值
/*
math & math::operator=(math && m){
    cout << "math & math::operator=(math && m) called "<< endl;
    if(matrix){
        delete [] matrix;
    }
    length = m.length;
    matrix = m.matrix;
    m.length = 0;
    m.matrix = nullptr;
    return *this;
}
*/

ostream & operator << (ostream & os, const math & m ){
    os << m.name << ": m.lenght = " << m.length << endl;
    if(m.length==0){
        cout << "no thing here!" << endl;
    }else{
    for(int i = 0; i< m.length; i++){
        cout << m.matrix[i] << " ";
    }
    }
    return os;
}

math math::plus(const math & m) const{
    i = i+1;
    string tn = "temp";
    cout << "------function starts------" <<endl;
    if(i==1){
        tn = "temp1";        
    }if(i==2){
        tn = "temp2";
    }
    math temp(tn,m.length);

    for(int i =0 ;i <length;i++){
        temp.matrix[i] = this->matrix[i]+m.matrix[i];
    }
    cout << "------function ends -------" << endl;

    return temp;
}   

int main(){
    
    i = 0;
    math a("a",4),b("b",4);
    math c = a.plus(b);
    // 一次带参数的构造函数
    math d("d"); 
    // 一次不带参的构造函数
    d = a.plus(b);
    // 一次带参数的构造函数（构造临时对象）
    // 一次=
    // 一次析构函数（销毁临时对象）

    cout << "-------a------"<< endl;    
    cout << a << endl;
    cout << "-------b------"<< endl;
    cout << b << endl;
    cout << "-------c------"<< endl;
    cout << c << endl;
    cout << "-------d------"<< endl;
    cout << d << endl;

    return 0;
}