// 2020.11.14
// from test_1d.cpp

using namespace std;

class Matrix{
private:
    int _Row,_Column,_Total;
    float * _Matrix;

public:
    Matrix():_Matrix(nullptr),_Row(0),_Column(0){}//默认构造
    //!
    // 初始化之前需要验证r,c的合理性
    Matrix(int r,int c);//构造r行、c列的矩阵, 里面元素为随机数
    Matrix(int r,int c,const float init);//构造r行、c列的矩阵, 里面元素为init
    Matrix(const Matrix&B);
    ~Matrix(){
    if(!_Matrix) return;
    delete [] _Matrix;
    _Column = _Row = _Total = 0;
    };
    
    float& operator()(int i,int j){return _Matrix[i*(_Column)+j];}
    const float operator()(int i,int j)const{return _Matrix[i*(_Column)+j];}
    Matrix& operator=(Matrix&& B){
        if(_Matrix){
            delete [] _Matrix;
        }
        _Row=B._Row;
        _Column=B._Column;
        _Total = B._Total;
        _Matrix=B._Matrix;
        B._Matrix=nullptr;
    }

    void display();
    void kernel(Matrix &c, float *a , float*b, int row, int col);

    //!
    // 相乘之前要验证相乘的条件
    Matrix multi(const Matrix &B);

};