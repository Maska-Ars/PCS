#include <iostream>

using namespace std;

int main()
{
    const long int n = 10000000;
    long int* m1 = new long int[n];
    long int* m2 = new long int[n];
    long int* m3 = new long int[n];


    int start;
    double t = 0;

    cout << "Task 3.1" << endl;
    cout << "N: " << n << endl;

    for (long int i = 0; i < n; i++)
    {
        m1[i] = i + 1;
        m2[i] = 2;
        m3[i] = 0;
    }


    for (int j = 0; j < 100; j++)
    {
        start = clock();
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
        for (long int i = 0; i < n; i++)
        {
            m3[i] = m1[i] / m2[i];
        }
        t += double(clock() - start) / CLOCKS_PER_SEC;
    }
    t /= 100;
    cout << "time /: " << t << endl;
    cout << m3[1] << endl;
    delete[] m1;
    delete[] m2;
    delete[] m3;


    return 0;
}
