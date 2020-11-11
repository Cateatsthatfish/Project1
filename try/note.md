# 2020.11.11
## 10：57

[**strct_reorderML.cpp**]

在调整b中元素的基础上减少循环次数（通过展开最内层循环），结果时间反而翻翻了，而且波动性很大
当只展开两层感觉速度没有很大的提升


## 10.18

[**strct_reorder.cpp**]没有调整循环的顺序而是调整b中元素的顺序

测试数据：

A(2\*4) , B(4\*2), C(2\*2)

A.datas[8]={0,1,2,3,4,5,6,7}

**B.datas[8]  ={0,2,4,6,1,3,5,7,}**

C.datas[4]  ={28,34,76,98}

A:

0 1 2 3
4 5 6 7

B：

0 1
2 3
4 5
6 7

C:

28  34
76  98

[**strct_multi.cpp**] (对比测试)

测试数据：

A(2\*4) , B(4\*2), C(2\*2)

A.datas[8]={0,1,2,3,4,5,6,7}

**B.datas[8]  ={0,1,2,3,4,5,6,7,}**

C.datas[4]  ={28,34,76,98}

A:

0 1 2 3
4 5 6 7

B：

0 1
2 3
4 5
6 7

C:

28  34
76  98

# 2020.11.10
## 20:46

[others_ML1reorder.cpp]关于调整B中元素的顺序来进行优化的问题，仍然迷惑

## 15:25

【做的事情】

1. 创建一个文件夹learn（主要是放学习到的加速的知识？代码
2. my_multiline1.cpp->把多线程的代码插入strct_multi.cpp
3. test_int_mm1.cpp->long long -> int
4. others_ML1reorder.cpp-> others_multiline.cpp的优化版本B[k\*P+j]->B[j\*P+k]

## 1:39

不如百度……

## 0:04

**提速：**

**设想：**

改变B中的数据的排列方式（由行改为列）是否能加速

**实施 ：**

测试：

**(strct_multi.cpp)**

矩阵定位和数组定位

A: m\*n -> A(i,k)=datas[i\*n+k]

B: n\*l -> B(k,j)=datas[k\*l+j]

C: m\*l -> C(i,j)=datas[i\*l+j]



A(4\*3) , B(3\*2), C(4\*2)

A.datas[12]={0,1,2,3,4,5,6,7,8,9,10,11}

**B.datas[6]  ={0,1,2,3,4,5}**

C.datas[8]  ={10,13,28,40,46,67,64,94}

A:

0  1  2
3  4  5
6  7  8
9  10  11

B:

0  1
2  3
4  5

C:

10  13
28  40
46  67
64  94

**su_reorder.cpp**



矩阵定位和数组定位

A：m\*n -> A(i,k)=datas[i*n+k]

B：n\*l -> B(k,j)=datas[j*n+k]

C: m\*l -> C(i,j)=datas[i*l+j]



0,1,2,3,4,5,6,7,8,9,10,11,
0 1 2 
3 4 5
6 7 8
9 10 11

**0,2,4,1,3,5,**
0 1
2 3
4 5


(time: 2.6001ms)
10,13,28,40,46,67,64,94,
10 13
28 40
46 67
64 94



# 2020.11.9

## 21:23

1. 矩阵形状和计算速度的关系
   1. (14000*14000)*(14000*14000) ->(14000*14000)
   2. (1*196000000)*(1*196000000) ->(1*1)
   3. (14000*1)*(1*14000) ->(14000*14000)
2. 提速的方法
   1. o3
   2. 多线程
   3. openmp？【看老师的代码】
3. openblas【需要等到优化结束之后再进行】
4. 读入方法
   1. 在程序里面生成
   2. 读二进制文件
   3. 手动输入
5. 怎么分析处理数据
【数据记录】https://shimo.im/docs/wvgHKjjVTXQd9HJc/ 「project1」，可复制链接后用石墨文档 App 或小程序打开
# 2020.11.5
## 22:16 
**【更新】**
strct_multi.cpp ：修改了之前的错误的相乘逻辑（我希望这次应该没问题了）
project1.cpp ： 更新了乘法的函数和display的函数
**【测试】**
strct_multi.cpp：（没有o3加速）
A：200000 * 3, B : 3 * 20000 -> C:200000 * 20000
(time: 71565.3ms)
(time: 67980.8ms)
**【遗留问题】**
计算的速度是否和和矩阵的形状有关系？
如果是20000*20000的两个矩阵相乘，会得到一个20000*20000的矩阵，但如果是200M*1和1*200M，最后得到的M就是一个数

## 20:27
【测试结果】
(2000*200)*(200*2000)
不报错，耗时(time: 251.829ms)

(1*20000)*(20000*1)
报错：
 0 [main] project1 134 cygwin_exception::open_stackdumpfile: Dumping stack trace to project1.exe.stackdump

(1*200)*(200*1)
报错：
 0 [main] project1 134 cygwin_exception::open_stackdumpfile: Dumping stack trace to project1.exe.stackdump

# 2020.11.4
## 22：34
【完成】
1. 随机生成矩阵中的数
2. 判断两个矩阵是否能相乘

【测试结果】
两个2000*2000的矩阵相乘：(o3加速的前提下)
31794.4ms
70791.2ms
两个200*200的矩阵相乘：(o3加速的前提下)
6.193ms
(2000000,1)*(1,2000000):bad_alloc

## 10：15
【完成】
输入方式/矩阵初始化方式：提示用户输入两个整数分别记成矩阵的row和column【这里输入的准确已经保证了】，之后就生成一个在每个（i,j）位置上的数为i+j的矩阵（float*）  
【待完成】  
1. 随即生成矩阵中的数
2. 储存随即生成的200M个数
3. 验证200M个数会不会崩掉

# 2020.11.3
## 21:33 
把之前试着写的部分加了上来

strct_intial1.cpp 直接在main里面赋值   
strct_intial2.cpp 通过initial_Matrix 进行初始化   
strct_return.cpp 用函数返回一个struct  

## 22:55
【problem】一加上测量时间的就会报bad_alloc的问题，但是如果没有那几行代码就不会出错   
【solved】struct中的用来储存元素的float*不应该在struct里面初始化，而应该在initial_Matrix和multi_Matrix里面初始化  

# 2020.10.28 2:12
## strct_multi.cpp
1. Matrix & multiplication(const Matrix & A, const Matrix & B, Matrix &C);
矩阵相乘
2. void display_Matrix(const Matrix & A);
把矩阵中的数一行展示
3. void initial_Matrix(Matrix &A);
初始化矩阵A,B（现在还是默认设定）





