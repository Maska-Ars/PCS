#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <omp.h>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void sequentialQuickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        sequentialQuickSort(arr, low, pi - 1);
        sequentialQuickSort(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int low, int high) {
    if (high - low < 10000) {
        // Используем стандартную сортировку для малых подзадач
        sequentialQuickSort(arr, low, high + 1);
        return;
    }

    if (low < high) {
        int pi = partition(arr, low, high);

        // Параллелизация только для больших подзадач
#pragma omp task shared(arr)
        quickSort(arr, low, pi - 1);

#pragma omp task shared(arr)
        quickSort(arr, pi + 1, high);

#pragma omp taskwait // Ожидаем завершения задач
    }
}
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Использование: " << argv[0] << " <размер массива> <количество запусков> <количество потоков>\n";
        return 1;
    }

    int array_size = atoi(argv[1]);
    int runs = atoi(argv[2]);
    int num_threads = atoi(argv[3]);

    vector<long long> seq_times;
    vector<long long> par_times;

    omp_set_num_threads(num_threads);

    // Объявляем массивы вне цикла
    int* arr = new int[array_size];
    int* arr1 = new int[array_size];

    for (int run = 0; run < runs; run++) {
        // Заполнение массива случайными числами
        for (int i = 0; i < array_size; i++) {
            arr[i] = rand() % 50 + 1;
        }
        copy(arr, arr + array_size, arr1);

        // Последовательная сортировка
        auto start1 = high_resolution_clock::now();
        sequentialQuickSort(arr1, 0, array_size - 1);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        seq_times.push_back(duration1.count());

        // Параллельная сортировка
        auto start2 = high_resolution_clock::now();
#pragma omp parallel
        {
#pragma omp single
            quickSort(arr, 0, array_size - 1);
        }
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        par_times.push_back(duration2.count());
    }

    auto print_stats = [](const vector<long long>& times, const string& label) {
        auto min_time = *min_element(times.begin(), times.end()) / 1000;
        auto max_time = *max_element(times.begin(), times.end()) / 1000;
        double avg_time = accumulate(times.begin(), times.end(), 0.0) / times.size() / 1000;

        cout << label << ":\n";
        cout << "  Min time: " << min_time << " millieseconds\n";
        cout << "  Max time: " << max_time << " millieseconds\n";
        cout << "  Avg time: " << avg_time << " millieseconds\n";
        cout << "---------------------------\n";
    };

    print_stats(seq_times, "posledovatelnaya");
    print_stats(par_times, "paralelnaya");

    // Освобождаем память после завершения всех запусков
    delete[] arr;
    delete[] arr1;

    return 0;
}
