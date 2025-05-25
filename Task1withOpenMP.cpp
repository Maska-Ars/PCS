#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <omp.h>

int main() {
    const size_t N = 1000000; // количество элементов массива
    std::vector<int> arr(N);

    // Заполнение массива случайными числами
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 100);
    for (size_t i = 0; i < N; ++i) {
        arr[i] = dist(gen);
    }

    // Массив с количеством потоков, которые будем использовать
    int thread_counts[] = {1, 2, 4, 8};

    for (int t = 0; t < 4; ++t) {
        int num_threads = thread_counts[t];
        omp_set_num_threads(num_threads);

        long long total_sum = 0;
        double total_time = 0;
        bool correct = true;

        for (int iter = 0; iter < 100; ++iter) {
            auto start = std::chrono::high_resolution_clock::now();

            long long sum = 0;

            #pragma omp parallel for reduction(+:sum)
            for (size_t i = 0; i < N; ++i) {
                sum += arr[i];
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            if (iter == 0) {
                total_sum = sum;
            } else {
                if (sum != total_sum) {
                    std::cerr << "Ошибка: суммы не совпадают при " << num_threads << " потоках!" << std::endl;
                    correct = false;
                    break;
                }
            }
            total_time += elapsed.count();
        }

        if (correct) {
            std::cout << "Параллельный вариант с " << num_threads << " потоками:" << std::endl;
            std::cout << "Сумма элементов: " << total_sum << std::endl;
            std::cout << "Среднее время выполнения (100 запусков): " << (total_time / 100.0) << " сек." << std::endl;
        } else {
            std::cout << "Результаты неконсистентны при " << num_threads << " потоках." << std::endl;
        }
        std::cout << "------------------------------------------" << std::endl;
    }

    return 0;
}
