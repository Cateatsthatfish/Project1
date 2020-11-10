/*
https://blog.csdn.net/qq_40515692/article/details/106749232
others_multiline1.cpp的优化版本
B[k*P+j]->B[j*P+k]


*/
#include <windows.h>
#include <iostream>
#include <ctime>

using namespace std;

struct MYDATA {
    int begin, end;
    int *A, *B, *C;
    int P, N;
};

DWORD ThreadProc(LPVOID IpParam) {
    MYDATA *pmd = (MYDATA *) IpParam;
    int *A = pmd->A, *B = pmd->B, *C = pmd->C;
    int begin = pmd->begin, end = pmd->end, P = pmd->P, N = pmd->N;

    // 线程多的话，这个最好应该提出来
    int sizeB = N * P;
    int *revB = new int[sizeB];
    for (int index = 0; index < sizeB; index++) {
        int i = index / P, j = index % P;
        revB[i * P + j] = B[j * P + i];
    }

    for (int index = begin; index < end; index++) {
        int i = index / P, j = index % P;
        C[i * P + j] = 0;
        for (int k = 0; k < N; ++k) {
            C[i * P + j] += A[i * N + k] * revB[j * P + k];
        }
    }
    delete[]revB;
    return 0;
}

void func(int *A, int *B, int *C, int M, int P, int N) {
    // C(M,P) = A(M,N) * B(N,P)
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < P; ++j) {
            C[i * P + j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i * P + j] += A[i * N + k] * B[k * P + j];
            }
        }
    }
}

void printM(int *A, int M, int N) {
    // print A(M,N)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            cout << A[i * N + j] << " ";
        cout << endl;
    }
    cout << endl;
}

const int M = 1000, N = 1000, P = 1000;
int A[M * N], B[N * P], C[M * P];

int main() {
    clock_t startTime, endTime;
    startTime = clock();//计时开始

    for (int i = 0; i < M * N; i++) A[i] = i;
    for (int i = 0; i < N * P; i++) B[i] = i;

    // ----------------------------------- 多线程
    const int m = 4;
    HANDLE hThread[m];
    static MYDATA mydt[m];
    int temp = (M * P) / m;
    for (int i = 0; i < m; ++i) {
        mydt[i].A = A, mydt[i].B = B, mydt[i].C = C;
        mydt[i].begin = i * temp, mydt[i].end = i * temp + temp, mydt[i].P = P, mydt[i].N = N;
        if (i == m - 1) // 最后一个线程计算剩余的
            mydt[i].end = M * P;
        hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc, &mydt[i], 0, NULL);
    }
    WaitForMultipleObjects(m, hThread, TRUE, INFINITE);

    // ----------------------------------- 串行
//    func(A, B, C, M, P, N);
//    printM(A, M, N);
//    printM(B, N, P);
//    printM(C, M, P);

    endTime = clock();//计时结束
    cout << "use time: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << endl;
    return 0;
}