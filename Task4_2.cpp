#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

int maindsdsa()
{
    const long int n = 10000;
    const long int m = 10000;

    long int** m1 = new long int* [n];
    long int** m2 = new long int* [n];
    long int** m3 = new long int* [n];

    cout << "Task 4.1" << endl;
    cout << "threads: " << omp_get_max_threads() << endl;
    cout << "N: " << n << endl;
    cout << "M: " << m << endl;


    for (int i = 0; i < n; i++)
    {
        m1[i] = new long int[m];
        m2[i] = new long int[m];
        m3[i] = new long int[m];

    }

    int start;
    double t;
    int i, j;

    #pragma omp parallel for private(i, j)
    for (long int k = 0; k < n*m; k++)
    {
        i = k / m;
        j = k % m;

        m1[i][j] = i + j + 1;
        m2[i][j] = 2;
    }
    t = 0;
    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for private(i, j)
        for (long int k = 0; k < n * m; k++)
        {
            i = k / m;
            j = k % m;
            m3[i][j] = m1[i][j] + m2[i][j];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time +: " << t << endl;

    t = 0;
    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for private(i, j)
        for (long int k = 0; k < n * m; k++)
        {
            i = k / m;
            j = k % m;
            m3[i][j] = m1[i][j] - m2[i][j];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time -: " << t << endl;

    t = 0;
    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for private(i, j)
        for (long int k = 0; k < n * m; k++)
        {
            i = k / m;
            j = k % m;
            m3[i][j] = m1[i][j] * m2[i][j];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time *: " << t << endl;

    t = 0;
    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for private(i, j)
        for (long int k = 0; k < n * m; k++)
        {
            i = k / m;
            j = k % m;
            m3[i][j] = m1[i][j] / m2[i][j];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time /: " << t << endl;


    return 0;
}
