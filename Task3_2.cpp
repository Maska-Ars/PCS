#include <iostream>
#include <omp.h>

using namespace std;

int mainasdsad()
{
    const long int n = 10000000;
    long int* m1 = new long int[n];
    long int* m2 = new long int[n];
    long int* m3 = new long int[n];
    omp_set_num_threads(12);


    int start;
    double t = 0;

    cout << "Task 3.2" << endl;
    cout << "threads: " << omp_get_max_threads() << endl;
    cout << "N: " << n << endl;

    #pragma omp parallel for
    for (long int i = 0; i < n; i++)
    {
        m1[i] = i + 1;
        m2[i] = 2;
        m3[i] = 0;
    }


    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for
        for (long int i = 0; i < n; i++)
        {
            m3[i] = m1[i] + m2[i];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time +: " << t << endl;


    t = 0;
    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for
        for (long int i = 0; i < n; i++)
        {
            m3[i] = m1[i] - m2[i];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time -: " << t << endl;

    t = 0;
    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for
        for (long int i = 0; i < n; i++)
        {
            m3[i] = m1[i] * m2[i];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time *: " << t << endl;

    t = 0;
    for (int j = 0; j < 100; j++)
    {
        start = clock();
        #pragma omp parallel for
        for (long int i = 0; i < n; i++)
        {
            m3[i] = m1[i] / m2[i];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time /: " << t << endl;

    delete[] m1;
    delete[] m2;
    delete[] m3;


    return 0;
}
