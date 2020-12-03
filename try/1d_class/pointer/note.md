###  class define

``` c++
class Matrix{
private:
    int _Row,_Column,_Total;
    // _Total = _Row * _Column;
    float * _Matrix;
    //float * _Matrix = new float[_Total + 1];
    // +1: 这个位置用来存放refcount
    //? 
    //是否应该加一
    int * refcount;
    //refcount: 引用计数
    //refcount = (int*)(_Matirx + _Total);
    //*refcount = 1; // 最开始创建的时候，记录被引用了一次
    //?
    // int -> float?
}
```





### copy constructor: 

``` c++
 Matrix :: Matrix (const Matrix& B){
    _Row = B._Row;
    _Column = B._Column;
    _Total = B._Total;
    _Matrix = new float [_Total];
 }
//?
// m1 作为形参 传入拷贝构造函数的时候


```

需要使用拷贝构造函数的场合

-  使用一个对象去初始化一个**新建的对象**

> 1. Matrix m2 = m1;
> 2. Matrix m2(m1);
> 3. Matrix m2 =  Matrix(m1);
> 4. Matrix *pm2 = new Matrix (m1);

-  对象作为函数的参数，以**值传递的方式**传给函数

-  对象作为函数的返回值，以**值传递的方式**从函数返回调用处
- 编译器产生了一个临时对象

> call

``` C++
Matrix C2 =  A.multi_ikj(B);
//?
// 1. B 传入的时候是否调用了拷贝构造函数？
// 2. return temp 是否调用了拷贝构造函数？
// ？return 过程
// 2.1 在main里面调用拷贝构造创建了一个临时 Matrix 对象（t）
// 2.2 temp的指针复制给t，也就是他们指向一片内存
// 2.3 之后函数结束，temp生命周期结束？temp的指针被删掉了，它指向的那片内存被删掉了吗？
// 3. = 用了拷贝构造函数？

```

结论： 

1. 调用一次析构函数（math::~math() called ）
2. 调用一次带参数的初始化（math::math(int i) called）



> function 

``` c++
// C(i,j) = ∑ A(i,k)*B(k,j)
Matrix Matrix::multi_ijk(const Matrix&B){
    int M(_Row), N(_Column),P(B._Column);
    Matrix temp(M,P,0);
    for(int i = 0; i < M ; i++ ){
        for(int j = 0; j < P; j++ ){
            float c = 0; 
            for (int k = 0; k< N; k++){
                c += (*this)(i,k) * B(k,j);                
                }
            temp(i,j) = c;
        }
    }
    return temp;  
}
```







### operator= 