#include <iostream>
#include <vector>
#include <chrono>
#include <numeric> // для std::accumulate
#include <random>

int main() {
    const size_t N = 1000000; // количество элементов массива
    std::vector<int> arr(N);

    // Заполнение массива случайными числами
    std::mt19937 gen(42); // фиксированный seed для воспроизводимости
    std::uniform_int_distribution<int> dist(1, 100);
    for (size_t i = 0; i < N; ++i) {
        arr[i] = dist(gen);
    }

    long long total_sum = 0;
    double total_time = 0;

    // Запускаем 100 раз и измеряем время
    for (int iter = 0; iter < 100; ++iter) {
        auto start = std::chrono::high_resolution_clock::now();

        long long sum = std::accumulate(arr.begin(), arr.end(), 0LL);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (iter == 0) {
            total_sum = sum; // запоминаем сумму для проверки
        } else {
            if (sum != total_sum) {
                std::cerr << "Ошибка: суммы не совпадают!" << std::endl;
                return 1;
            }
        }
        total_time += elapsed.count();
    }

    std::cout << "Последовательный вариант:" << std::endl;
    std::cout << "Сумма элементов: " << total_sum << std::endl;
    std::cout << "Среднее время выполнения (100 запусков): " << (total_time / 100.0) << " сек." << std::endl;

    return 0;
}
