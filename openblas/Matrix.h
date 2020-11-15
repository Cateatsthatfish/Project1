// 2020.11.12
// 需要把double->int
// malloc-> new
#include <iostream>

#include <cstdlib>
//#include "immintrin.h"
#include <immintrin.h>


using namespace std;
class Matrix{
    private:
    double **_Matrix; 
    // float ** _Matrix
    //这里能不能用一维的代替？

    size_t _Row,_Column;

    public:
    Matrix():_Matrix(nullptr),_Row(0),_Column(0){}//默认构造
    //nullptr: 空指针
    //C++构造函数初始化列表:http://c.biancheng.net/view/2223.html

    Matrix(size_t r,size_t c):_Row(r),_Column(c){//构造r行、c列的矩阵
        if(!_Column||!_Row) return;
        //当column 或row = 0 时 return
        //如果return 下面这一行就不会cout，但是main也不会退出
        //cout <<"in constructor!" << endl;
        //+
        //优化和报错？
        

        _Matrix=(double**)malloc(_Column*sizeof(double*));
        //_Matrix 是一个二重指针, 长度为_Column
        //?
        //C++
        //_Matrix = new float * [_Column]; 

        double **p=_Matrix;
        //等号右边是不变的，左边是可以变的
        //float **p = _Matrix;       

        double **end=_Matrix+_Column;
        //标记_Matrix 的末端
        // float **end = _Matrix + _Column;
        
        do{
            *(p++)=(double*)malloc(_Row*sizeof(double));
            //创建行的位置
            //*(p++)=(float*)malloc(_Row*sizeof(float));
            //?
            //1. 为什么先创建列再创建行？两种有区别吗还是都可以？
            //2. 这些空间储存在哪里？_Matrix里面嘛？
            //?
            //C++
            //*(p++) = new float[_Row];

        }while(p!=end);
        // 循环条件
    }
    Matrix(size_t r,size_t c,const double init):_Row(r),_Column(c){//构造r行、c列的矩阵并用init初始化
        if(!_Column||!_Row) return;
        _Matrix=(double**)malloc(_Column*sizeof(double*));
        // _Matrix = new float * [_Column];
        double **pr=_Matrix ;
        double **endr=_Matrix+_Column;

        double *p;
        double *end;

        do{
            p = *(pr++)=(double*)malloc(_Row*sizeof(double));
            // p = *(pr++) = new float[_Row];
            end=p+_Row;
            do{
                *(p++)=init;
            }while(p!=end);
            //把每一个元素都赋值为init
        }while(pr!=endr);
        _Matrix[0][2] = 3;
        
    }
    Matrix(const Matrix& B){//拷贝构造
        _Row=B._Row;
        _Column=B._Column;
        _Matrix=(double**)malloc(_Column*sizeof(double*));

        double **pbr=B._Matrix;
        double **endbr=B._Matrix+_Column;
        double *pb;
        double *endb;

        double **par=_Matrix;
        double **endar=_Matrix+_Column;
        double *pa;
        double *enda;

        do{
            pa=*(par++)=(double*)malloc(_Row*sizeof(double));
            //pa = *(par++) = new float [_Row];
            enda=pa+_Row;

            pb=*(pbr++);
            endb=pb+_Row;

            do{
                *(pa++)=*(pb++);
            }while(pa!=enda);
        }while(par!=endar);
    }
    // 如果没有这个拷贝构造，后面的所有return temp 都实现不了
    ~Matrix(){//析构
        if(!_Matrix) return;
        //?
        double **p=_Matrix,**end=_Matrix+_Column;
        do{
            free(*(p++));
        }while(p!=end);
        _Column=_Row=0;
        free(_Matrix);
    }
    //new 需要重新写析构吗？
    /*
    ~Matrix(){
        if(!_Matrix) return;
        for(int i = 0; i<_Column ;i++)
        {
            delete []_Matrix[i];

        }
        delete []_Matrix;
        _Column = _Row = 0;
    }
    */
    

    // 重载操作符
    double& operator()(size_t i,size_t j){return _Matrix[j][i];}//访问第i行、第j列的元素
    //?
    //返回地址？
    //改写括号
    const double operator()(size_t i,size_t j)const{return _Matrix[j][i];}//访问第i行、第j列的元素
    //?
    //返回值？
    //只是能修改和不能修改的区别吗？
    //改写括号


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
    //重载等号

        if(_Matrix){
            double **p=_Matrix,**end=_Matrix+_Row;
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
    
    //按照列求解 jik
    Matrix multi1(const Matrix &B){
        
        if(_Column!=B._Row) return *this;
        //判断是否可以相乘
        //这里返回的是克隆
        Matrix tmp(_Row,B._Column,0);
        //结果函数
        //全部赋值为0
        int i,j(0),k;
        //? 为什么j=0?
        //? do while 和for 循环有差别吗？

        do{
            i=0;
            do{
                k=0;
                do{
                    tmp(i,j)+=(*this)(i,k)*B(k,j);
                    //tmp(i,j): double& operator()(size_t i, size_t j)
                    //B(k,j): const double operator()(size_t i, size_t j) const
                    k++;
                }while(k<_Column);
                i++;
            }while(i<_Row);
            j++;
        }while(j<B._Column);

        /* 用for循环写的

        for(int j=0; j<B._Column; j++){
            for(int i = 0; i<B._Row; i++){
                for(int k = 0; k < _Column; k++){
                    tmp(i,j)+=(*this)(i,k)*B(k,j);
                    
                }
            }

        }
        */


        return tmp;
    }
 
    //按照行求解 ijk
    Matrix multi2(const Matrix &B){
        if(_Column!=B._Row) return *this;
        Matrix tmp(_Row,B._Column,0);
        int i(0),j,k;
        do{
            j=0;
            do{
                k=0;
                do{
                    tmp(i,j)+=(*this)(i,k)*B(k,j);
                    k++;
                }while(k<_Column);
                j++;
            }while(j<B._Column);
            i++;
        }while(i<_Row);
        
        /* 用for循环写的
        for(int i = 0; i<B._Row; i++){
            for(int j=0; j<B._Column; j++){            
                for(int k = 0; k < _Column; k++){
                    tmp(i,j)+=(*this)(i,k)*B(k,j);                    
                }
            }
        }
        */

        return tmp;
    } 
    
    // 打包计算
    // n = B._Row = this._Column
    // (4*n) * (n*4) = (4*4)

    void multi3kernel(double **c,double **a,double **b,int row,int col){
        // double **c = tmp_Matrix : 结果矩阵 (_Row, B._Column)
        // double **a = tr ： this_Matrix 的前四行(4,_Column)
        // double **b = B._Matrix ：输入的矩阵 (B._Row, B._Column)
        // B._Row = this._Column
        // int row = j : 0 <= j < _Row
        // int col = i : 0 <= i < B._Column

        register double t0(0),t1(0),t2(0),t3(0),t4(0),t5(0),t6(0),t7(0),
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


        double *a0(a[0]),*a1(a[1]),*a2(a[2]),*a3(a[3]),
               *b0(b[col]),*b1(b[col+1]),*b2(b[col+2]),*b3(b[col+3]),
               *end=b0+_Column; 
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
        double *tr[4]; 
        //?
        //这应该是是一个二维数组
        // 长度为4，每个里面放一个double类型的指针
        //https://blog.csdn.net/u012247980/article/details/79988745
        //https://www.zhihu.com/question/363817986/answer/957038360

        // ?
        // 这里为什么能确定一定this._Row以及B._Column是4的倍数？
        // 当他们不是4的倍数会怎么样？
        // 越界？
        
        int i(0),j(0);
        do{
            tr[i++]=(double*)malloc(sizeof(double)*_Column);
        }while(i<4);

        do{
            i=0;
            do{
                tr[0][i]=_Matrix[i][j];
                tr[1][i]=_Matrix[i][j+1];
                tr[2][i]=_Matrix[i][j+2];
                tr[3][i]=_Matrix[i][j+3];
            }while((++i)<_Column);
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

            i=0;
            do{
                multi3kernel(tmp._Matrix,tr,B._Matrix,j,i);

                // tmp._Matrix: _Row * B._Column；元素都为零的矩阵
                // void multi4kernel(double **c,double **a,double **b,int row,int col)
                // row = j : 0 <= j < _Row
                // j+=4
                // col = i : 0 <= i < B._Column
                // i+=4
                
                // j = 0
                // i = 0 : tmp._Matrix(0,0)->(3,3)
                // i = 4 : tmp._Matrix(0,4)->(3,7)
                // ……
                // M的前四行                            

                i+=4;
                // i 的循环是横向填满tmp._Matrix 的每一行            
            }while(i<B._Column);

            j+=4;
            // j 的循环是纵向填满 tmp._Matrix 的每一列 
        }while(j<_Row);
        return tmp;
    }

    void display_Matrix(){
        for(int i = 0; i< _Row; i++){
            for( int j = 0 ; j < _Column; j++){
                cout << (*this)(i,j) << " ";
            }
            cout << endl;
        }

    }

    //SIMD SSE 加速乘法的运算。
    //https://www.cnblogs.com/wangguchangqing/p/5466301.html
/*note
1. SSE指令集正如其名字 Streaming SIMD Extensions，最强大的是其能够在一条指令并行的对多个操作数进行相同的运算，根据操作数长度和寄存器长度的不同能够同时运算的个数也不同。
以32位有符号整数为例，128位寄存器（也是最常用的SSE指令集的寄存器）能够同时运算4个；AVX指令集的256位寄存器能够同时运算8个；AVX-512 的512位寄存器能够同时运算16个。
2. 在使用SSE指令时要特别主要操作数的类型，整型则要区分是有符号还是无符号；浮点数则注意其精度是单精度还是双精度
3. 另外就是操作数的长度。即使是同样的128位二进制串，根据其类型和长度也有多种不同的解释。
4. 前面多次提到，编译器的优化能力是很强的，不要刻意的使用SSE指令优化。而在要必须使用SSE的时候，要谨记SSE的强大之处是其并行能力。   
*/
    
    void multi4kernel(double **c,double **a,double **b,int row,int col){
        // double ** c 
        __m128d t01_0,t01_1,t01_2,t01_3,t23_0,t23_1,t23_2,t23_3,
                a0,a1,b0,b1,b2,b3;
        //_m128d : 128位紧缩双精度（SSE2）
        //_m128 :  128位紧缩单精度（AVX）
        t01_0=t01_1=t01_2=t01_3=t23_0=t23_1=t23_2=t23_3=_mm_set1_pd(0);
        //__m128d _mm_set1_pd (double a)
        //#include <emmintrin.h>
        //SSE2
        //Broadcast double-precision (64-bit) floating-point value a to all elements of dst.

        //__m128 _mm_set1_ps (float a)
        //#include <xmmintrin.h>
        //SSE
        //Broadcast single-precision (32-bit) floating-point value a to all elements of dst.
        double *pb0(b[col]),*pb1(b[col+1]),*pb2(b[col+2]),*pb3(b[col+3]),
                *pa0(a[0]),*pa1(a[1]),
                *endb0=pb0+_Column;
        do{
            a0=_mm_load_pd(pa0);
            a1=_mm_load_pd(pa1);
            //__m128d _mm_load_pd (double const* mem_addr)
            //<emmintrin.h>
            //SSE2
            //Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) 
            //from memory into dst. mem_addr :内存-》寄存器
            //must be aligned on a 16-byte boundary or a general-protection exception may be generated.

            //__m128 _mm_load_ps (float const* mem_addr)
            //<xmmintrin.h>
            //SSE
            //Load 128-bits (composed of 4 packed single-precision (32-bit) floating-point elements)
            //from memory into dst. mem_addr :内存-》寄存器
            //must be aligned on a 16-byte boundary or a general-protection exception may be generated.
            
            b0=_mm_set1_pd(*(pb0++));
            b1=_mm_set1_pd(*(pb1++));
            b2=_mm_set1_pd(*(pb2++));
            b3=_mm_set1_pd(*(pb3++));
            //*pb0->b0
/*
            t01_0+=a0*b0;
            t01_1+=a0*b1;
            t01_2+=a0*b2;
            t01_3+=a0*b3;
            t23_0+=a1*b0;
            t23_1+=a1*b1;
            t23_2+=a1*b2;
            t23_3+=a1*b3;
*/
            t01_0 = _mm_add_pd(t01_0,_mm_mul_pd(a0,b0));
            t01_1 = _mm_add_pd(t01_1,_mm_mul_pd(a0,b1));
            t01_2 = _mm_add_pd(t01_2,_mm_mul_pd(a0,b2));
            t01_3 = _mm_add_pd(t01_3,_mm_mul_pd(a0,b3));
            t23_0 = _mm_add_pd(t23_0,_mm_mul_pd(a1,b0));
            t23_1 = _mm_add_pd(t23_1,_mm_mul_pd(a1,b1));
            t23_2 = _mm_add_pd(t23_2,_mm_mul_pd(a1,b2));
            t23_3 = _mm_add_pd(t23_3,_mm_mul_pd(a1,b3));

            pa0+=2;
            pa1+=2;
        }while(pb0!=endb0);
        _mm_store_pd(&c[col][row],t01_0);
        _mm_store_pd(&c[col+1][row],t01_1);
        _mm_store_pd(&c[col+2][row],t01_2);
        _mm_store_pd(&c[col+3][row],t01_3);
        _mm_store_pd(&c[col][row+2],t23_0);
        _mm_store_pd(&c[col+1][row+2],t23_1);
        _mm_store_pd(&c[col+2][row+2],t23_2);
        _mm_store_pd(&c[col+3][row+2],t23_3);

        //void _mm_store_pd (double* mem_addr, __m128d a)
        //#include <emmintrin.h>
        //SSE2
        //Store 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) 
        //from a into memory. mem_addr 
        //must be aligned on a 16-byte boundary or a general-protection exception may be generated.
    }
    Matrix multi4(const Matrix &B){
        // A: M*N    B: N*P    C: M*P
        // M: _Row
        // N: _Column = B._Row
        // P: B._Column

        if(_Column!=B._Row) return *this;
        Matrix tmp(_Row,B._Column,0);
        double *ta[2];
        ta[0]=(double*)malloc(sizeof(double)*2*_Column);
        ta[1]=(double*)malloc(sizeof(double)*2*_Column);
        double* tb=(double*)malloc(sizeof(double)*4*B._Row);
        double* end=tb+4*B._Row;
        //tb 的尾部
        int i(0),j(0),k,t;
        do{
            k=0;i=0;
            do{
                ta[0][k]=_Matrix[i][j];       //A(j.i)
                ta[1][k++]=_Matrix[i][j+2];   //A(j+2.i)
                ta[0][k]=_Matrix[i][j+1];     //A(j+1.i)
                ta[1][k++]=_Matrix[i++][j+3]; //A(j+3.i)
                
                // j = 0
                // i : 0->N-1
                //(0,0): A(0,0)
                //ta[0]: (0,0) (1,0) (0,1) (1,1) ... (j,i) (j+1,i) ... (0,N-1) (1,N-1) 
                //ta[1]: (2,0) (3,0) (2,1) (3,1) ... (j+2,i) (j+3,i) ... (2,N-1) (3,N-1)


            }while(i<_Column);

            i=0;
            do{
                multi4kernel(tmp._Matrix,ta,B._Matrix,j,i);
                // i: 0->P-1 
                // j: 0->M-1 

                i+=4;
            }while(i<B._Column);
            j+=4;
        }while(j<_Row);

        free(tb);
        free(ta[0]);
        free(ta[1]);
        return tmp;
    }


    //AVX2.0
    //使用AVX2.0可以一次处理256bit的数据，即4个双精度浮点数
void multi5kernel(double **c,double **a,double **b,int row,int col){
        __m256d t04_0,t04_1,t04_2,t04_3,t58_0,t58_1,t58_2,t58_3,
                a0,a1,b0,b1,b2,b3;
        t04_0=t04_1=t04_2=t04_3=t58_0=t58_1=t58_2=t58_3=_mm256_set1_pd(0);
        double *pb0(b[col]),*pb1(b[col+1]),*pb2(b[col+2]),*pb3(b[col+3]),
                *pa0(a[0]),*pa1(a[1]),
                *endb0=pb0+_Column;
        do{
            a0=_mm256_loadu_pd(pa0);
            a1=_mm256_loadu_pd(pa1);
            b0=_mm256_set1_pd(*(pb0++));
            b1=_mm256_set1_pd(*(pb1++));
            b2=_mm256_set1_pd(*(pb2++));
            b3=_mm256_set1_pd(*(pb3++));
            /*
            t04_0+=a0*b0;
            t04_1+=a0*b1;
            t04_2+=a0*b2;
            t04_3+=a0*b3;
            t58_0+=a1*b0;
            t58_1+=a1*b1;
            t58_2+=a1*b2;
            t58_3+=a1*b3;
            */

            t04_0 = _mm256_add_pd(t04_0,_mm256_mul_pd(a0,b0));
            t04_1 = _mm256_add_pd(t04_1,_mm256_mul_pd(a0,b1));
            t04_2 = _mm256_add_pd(t04_2,_mm256_mul_pd(a0,b2));
            t04_3 = _mm256_add_pd(t04_3,_mm256_mul_pd(a0,b3));
            t58_0 = _mm256_add_pd(t58_0,_mm256_mul_pd(a1,b0));
            t58_1 = _mm256_add_pd(t58_1,_mm256_mul_pd(a1,b1));
            t58_2 = _mm256_add_pd(t58_2,_mm256_mul_pd(a1,b2));
            t58_3 = _mm256_add_pd(t58_3,_mm256_mul_pd(a1,b3));            
            pa0+=4;
            pa1+=4;
        }while(pb0!=endb0);
        _mm256_storeu_pd(&c[col][row],t04_0);
        _mm256_storeu_pd(&c[col+1][row],t04_1);
        _mm256_storeu_pd(&c[col+2][row],t04_2);
        _mm256_storeu_pd(&c[col+3][row],t04_3);
        _mm256_storeu_pd(&c[col][row+4],t58_0);
        _mm256_storeu_pd(&c[col+1][row+4],t58_1);
        _mm256_storeu_pd(&c[col+2][row+4],t58_2);
        _mm256_storeu_pd(&c[col+3][row+4],t58_3);
    }
    Matrix multi5(const Matrix &B){
        if(_Column!=B._Row) return *this;
        Matrix tmp(_Row,B._Column,0);
        double *ta[2];
        ta[0]=(double*)malloc(sizeof(double)*4*_Column);
        ta[1]=(double*)malloc(sizeof(double)*4*_Column);
        int i(0),j(0),k,t;
        do{
            k=0;i=0;
            do{
                ta[0][k]=_Matrix[i][j];
                ta[1][k++]=_Matrix[i][j+4];
                ta[0][k]=_Matrix[i][j+1];
                ta[1][k++]=_Matrix[i][j+5];
                ta[0][k]=_Matrix[i][j+2];
                ta[1][k++]=_Matrix[i][j+6];
                ta[0][k]=_Matrix[i][j+3];
                ta[1][k++]=_Matrix[i++][j+7];
            }while(i<_Column);
            i=0;
            do{
                multi5kernel(tmp._Matrix,ta,B._Matrix,j,i);
                i+=4;
            }while(i<B._Column);
            j+=8;
        }while(j<_Row);
        free(ta[0]);
        free(ta[1]);
        return tmp;
    }
};


