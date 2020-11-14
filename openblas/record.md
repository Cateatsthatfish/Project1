# 2020.11.14

## 0：34

[待完成事项]

仿照my_Matrix.h里面的mult3和multi4kernel的方法写一个函数放在strct_multi里面

# 2020.11.13

## 23:19

问题记录

1. float **_Matrix 能不能用一维的代替？

2. ```c++
   Matrix(size_t r,size_t c):_Row(r),_Column(c){//构造r行、c列的矩阵
           if(!_Column||!_Row) return;
       ……}
   ```

3.  new会比malloc快嘛？好像并不会，替换了尝试一下感觉没有问题

   ```c++
   p = *(pr++) = new float[_Row];
   p = *(pr++)=(float*)malloc(_Row*sizeof(float));
   ```

4.  头文件的作用？ 把头文件注释掉了竟然还能正常运行而且不报错？

   ```c++
   #include <cstdlib>
   #include <immintrin.h>
   ```

5. 

## 22：54

### [测试数据]
const size_t N1 = 100;
const size_t N2 = 10000;
Matrix A(N1,N2,1),B(N2,N1,2);
(time: 12.0845ms)
(time: 13.1199ms)
(time: 9.9276ms)
(time: 11.0601ms)
(time: 11.9484ms)

(time: 8.0004ms)
(time: 10.5135ms)
(time: 10.9735ms)
(time: 11.6321ms)
(time: 13.7218ms)

Matrix B(N1,N2,1),A(N2,N1,2);
2 [main] testMatrix 774 cygwin_exception::open_stackdumpfile: Dumping stack trace to testMatrix.exe.stackdump

#define N 1000
Matrix A(N,N,1),B(N,N,2);
(time: 1038.02ms)
(time: 824.736ms)
(time: 756.769ms)
(time: 754.073ms)
(time: 805.053ms)

(time: 1038.02ms)
(time: 824.736ms)
(time: 756.769ms)
(time: 754.073ms)
(time: 805.053ms)

(time: 873.479ms)   
(time: 894.648ms)   
(time: 751.987ms)   
(time: 749.108ms)   
(time: 756.439ms)


## 21：30
### [Matrix.h]
完成：读完了并且基本理解代码的意思以及作用
待续：

1. 改写.h
2. 改写成函数？
3. 全部改成类？
   
## 0:17
mult1,2,3:
+o3
(time: 68362.3ms)
(time: 35018.6ms)
(time: 2652.71ms)

mult3:
+o3
(time: 2129.07ms)
(time: 2391.39ms)
(time: 2322.63ms)
(time: 2625.52ms)
(time: 2276.04ms)
-o3
(time: 3533.19ms)
(time: 5076.2ms)
(time: 5540.66ms)
(time: 5558.93ms)
(time: 5320.13ms)
# 2020.11.11
## 19:07
source:
https://blog.csdn.net/artorias123/article/details/86527456

## outcome
N = 1400:
(time: 28413.1ms)