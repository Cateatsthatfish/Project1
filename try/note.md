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





