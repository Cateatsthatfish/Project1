// 2020.11.12
// 需要把float->int
// malloc-> new
#include <iostream>
#include <cstdlib>
#include <immintrin.h>


using namespace std;
class Matrix{
    private:
    float **_Matrix; 
    //?
    //这里能不能用一维的代替？

    size_t _Row,_Column;

    public:
    Matrix():_Matrix(nullptr),_Row(0),_Column(0){}//默认构造
    //nullptr: 空指针
    //C++构造函数初始化列表:http://c.biancheng.net/view/2223.html


    Matrix(size_t r,size_t c):_Row(r),_Column(c){//构造r行、c列的矩阵
        if(!_Column||!_Row) return;
        //当column 或row = 0 时return

        //?
        //如果column 或row = 0 -》报错？
        //如果return 下面这一行就不会cout，但是main也不会退出
        //cout <<"in constructor!" << endl;
        

        //?
        // r,c 的异常处理？-> cin的时候解决
        // r,c <0
        // r,c 不是size_t?
        //……

        _Matrix = new float * [_Column]; 
        //_Matrix 是一个二重指针, 长度为_Column

        float **p=_Matrix;
        //等号右边是不变的，左边是可以变的     

        float **end=_Matrix+_Column;
        //标记_Matrix 的末端
        
        do{

            *(p++) = new float[_Row];
            //创建行的位置
            //?
            //1. 为什么先创建列再创建行？两种有区别吗还是都可以？

            //+
            //随机数赋值

        }while(p!=end);
        // 循环条件
    }
    Matrix(size_t r,size_t c,const float init):_Row(r),_Column(c){//构造r行、c列的矩阵并用init初始化
        if(!_Column||!_Row) return;
        _Matrix = new float * [_Column];
        float **pr=_Matrix ;
        float **endr=_Matrix+_Column;

        float *p;
        float *end;

        do{
            p = *(pr++) = new float[_Row];
            end=p+_Row;
            do{
                *(p++)=init;
            }while(p!=end);
            //把每一个元素都赋值为init
        }while(pr!=endr);
    }
    Matrix(const Matrix& B){//拷贝构造
        _Row=B._Row;
        _Column=B._Column;
        _Matrix = new float * [_Column];

        float **pbr=B._Matrix;
        float **endbr=B._Matrix+_Column;
        float *pb;
        float *endb;

        float **par=_Matrix;
        float **endar=_Matrix+_Column;
        float *pa;
        float *enda;

        do{
            pa = *(par++) = new float [_Row];
            enda=pa+_Row;

            pb=*(pbr++);
            endb=pb+_Row;

            do{
                *(pa++)=*(pb++);
            }while(pa!=enda);
        }while(par!=endar);
    }
    /*
    ~Matrix(){//析构
        if(!_Matrix) return;
        //?
        float **p=_Matrix,**end=_Matrix+_Column;
        do{
            free(*(p++));
        }while(p!=end);
        _Column=_Row=0;
        free(_Matrix);
    }
    */
    //new 需要重新写析构吗？
    
    ~Matrix(){
        if(!_Matrix) return;
        for(int i = 0; i<_Column ;i++)
        {
            delete []_Matrix[i];

        }
        delete []_Matrix;
        _Column = _Row = 0;
    }
    
    

    // 重载操作符
    float& operator()(size_t i,size_t j){return _Matrix[j][i];}//访问第i行、第j列的元素
    //?
    //返回地址？
    const float operator()(size_t i,size_t j)const{return _Matrix[j][i];}//访问第i行、第j列的元素
    //?
    //返回值？
    //只是能修改和不能修改的区别吗？


    Matrix& operator=(Matrix&& B){//移动赋值
    //?
    //Matrix&& B 是什么？
    //左值和右值：
    //https://www.k2zone.cn/?p=1880
    //https://www.cnblogs.com/SZxiaochun/p/8017475.html
    //https://blog.csdn.net/weixin_40539125/article/details/84107068
    //&& : 即销毁的值
    //大概是因为B是要被销毁的吧
    //返回的Matrix& 又是什么？-》返回一个Matrix的对象的引用？
    //这个有什么用？

        if(_Matrix){
            float **p=_Matrix,**end=_Matrix+_Row;
            do{
                free(*(p++));
            }while(p!=end);
            free(_Matrix);
        }
        //如果之前有值，那么就把
        _Row=B._Row;
        _Column=B._Column;
        _Matrix=B._Matrix;
        //_Matrix和B._Matrix的地址应该是一样的
        B._Matrix=nullptr;
        //将B._Matrix这个指针无效化？

        return *this;
        // 返回当前对象本身
        //https://blog.csdn.net/u011846436/article/details/45222905
        //https://blog.csdn.net/q357010621/article/details/73771000
    }
 

    // 打包计算
    // n = B._Row = this._Column
    // (4*n) * (n*4) = (4*4)

    void multi4kernel(float **c,float **a,float **b,int row,int col){
        // float **c = tmp_Matrix : 结果矩阵 (_Row, B._Column)
        // float **a = tr ： this_Matrix 的前四行(4,_Column)
        // float **b = B._Matrix ：输入的矩阵 (B._Row, B._Column)
        // B._Row = this._Column
        // int row = j : 0 <= j < _Row
        // int col = i : 0 <= i < B._Column

        register float t0(0),t1(0),t2(0),t3(0),t4(0),t5(0),t6(0),t7(0),
                        t8(0),t9(0),t10(0),t11(0),t12(0),t13(0),t14(0),t15(0);
        // register: 关键字请求“编译器”将局部变量存储于寄存器中
        //https://www.cnblogs.com/Liu-Jing/p/7662002.html

        /*
        c: 4*4 矩阵临时储存        
        c[col][row]-> c[col+3][row+3]
        c[i][j]    -> c[i+3][j+3]
        c(j,i)     -> c(j+3,i+3)
                
        t0,  t1,  t2,  t3
        t4,  t5,  t6,  t7
        t8,  t9,  t10, t11
        t12, t13, t14, t15
        */


        float *a0(a[0]),*a1(a[1]),*a2(a[2]),*a3(a[3]),
               *b0(b[col]),*b1(b[col+1]),*b2(b[col+2]),*b3(b[col+3]),
               *end=b0+_Row; 
        /*
        // 这里的a,b都是逐渐移动的类似坐标的东西
        
        // this._Matrix 的行（只有四行:j->j+3）
        // *a0 = tr[0] = M(j,0->n-1)
        // *a1 = tr[1] = M(j+1,0->n-1) 
        // *a2 = tr[2] = M(j+2,0->n-1)
        // *a3 = tr[3] = M(j+3,0->n-1)

        // B._Matrix 的列 （只有四列:i->i+3）
        // *b0 = B._Matrix[i] = B(0->n-1, i)
        // *b1 = B._Matrix[i+1] = B(0->n-1, i+1)
        // *b2 = B._Matrix[i+2] = B(0->n-1, i+2)
        // *b3 = B._Matrix[i+3] = B(0->n-1, i+3)

        // *end : 标记一列元素的末尾
        */


        do{
            t0+=*(a0)**(b0);
            t1+=*(a0)**(b1);
            t2+=*(a0)**(b2);
            t3+=*(a0++)**(b3);
            

            t4+=*(a1)**(b0);
            t5+=*(a1)**(b1);
            t6+=*(a1)**(b2);
            t7+=*(a1++)**(b3);

            t8+=*(a2)**(b0);
            t9+=*(a2)**(b1);
            t10+=*(a2)**(b2);
            t11+=*(a2++)**(b3);

            t12+=*(a3)**(b0++);
            t13+=*(a3)**(b1++);
            t14+=*(a3)**(b2++);
            t15+=*(a3++)**(b3++);
            
        }while(b0!=end);

        //row 1 
        c[col][row]=t0;
        c[col+1][row]=t1;
        c[col+2][row]=t2;
        c[col+3][row]=t3;
        
        //row2
        c[col][row+1]=t4;
        c[col+1][row+1]=t5;
        c[col+2][row+1]=t6;
        c[col+3][row+1]=t7;

        //row3
        c[col][row+2]=t8;
        c[col+1][row+2]=t9;
        c[col+2][row+2]=t10;
        c[col+3][row+2]=t11;
        
        //row4
        c[col][row+3]=t12;
        c[col+1][row+3]=t13;
        c[col+2][row+3]=t14;
        c[col+3][row+3]=t15;


    }

    Matrix multi3(const Matrix &B){
        if(_Column!=B._Row) return *this;
        Matrix tmp(_Row,B._Column,0);
        float *tr[4]; 
        //?
        //这应该是是一个二维数组
        // 长度为4，每个里面放一个float类型的指针
        //https://blog.csdn.net/u012247980/article/details/79988745
        //https://www.zhihu.com/question/363817986/answer/957038360

        // ?
        // 这里为什么能确定一定this._Row以及B._Column是4的倍数？
        // 当他们不是4的倍数会怎么样？
        // 越界？
        
        int i(0),j(0);
        do{
            tr[i++] = new float[_Column];
        }while(i<4);

        do{
            i=0;
            do{
                tr[0][i]=_Matrix[i][j];
                tr[1][i]=_Matrix[i][j+1];
                tr[2][i]=_Matrix[i][j+2];
                tr[3][i]=_Matrix[i][j+3];
            }while((++i)<_Column);
            /*
            //packing过程，把行数据打包到连续空间
            //tr[i][j] = M(i,j) = M[j][i]
            // 0 <= i < 4
            // 0 <= j < _Column
            // 这里的i,j 对应的和dowhile 循环里面的并不一致
            // M : this._Matrix



            // 下面的j是和dowhile循环里面对应的
            // 0 <= j < _Row
            // j += 4 : 4行4行一取值

            // j = 0            
            //tr[0] = {M(0,0),M(0,1),M(0,2),...,M(0,n-1)}
            //tr[1] = {M(1,0),M(1,1),M(1,2),...,M(1,n-1)}
            //tr[2] = {M(2,0),M(2,1),M(2,2),...,M(2,n-1)}
            //tr[3] = {M(3,0),M(3,1),M(3,2),...,M(3,n-1)}

            // j = 4
            //tr[0] = {M(4,0),M(4,1),M(4,2),...,M(4,n-1)}
            //tr[1] = {M(5,0),M(5,1),M(5,2),...,M(5,n-1)}
            //tr[2] = {M(6,0),M(6,1),M(6,2),...,M(6,n-1)}
            //tr[3] = {M(7,0),M(7,1),M(7,2),...,M(7,n-1)}       
            */    

            i=0;
            do{
                multi4kernel(tmp._Matrix,tr,B._Matrix,j,i);

                /*

                // tmp._Matrix: _Row * B._Column；元素都为零的矩阵
                // void multi4kernel(float **c,float **a,float **b,int row,int col)
                // row = j : 0 <= j < _Row
                // j+=4
                // col = i : 0 <= i < B._Column
                // i+=4
                
                // j = 0
                // i = 0 : tmp._Matrix(0,0)->(3,3)
                // i = 4 : tmp._Matrix(0,4)->(3,7)
                // ……
                // M的前四行   
                */                         

                i+=4;
                // i 的循环是横向填满tmp._Matrix 的每一行            
            }while(i<B._Column);

            j+=4;
            // j 的循环是纵向填满 tmp._Matrix 的每一列 
        }while(j<_Row);
        return tmp;
    }
};


