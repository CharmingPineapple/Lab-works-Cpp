// kochubey_lab1.cpp

#include <stdlib.h>
#include <iostream>

using namespace std;

void gen_array(double*, int);
void sort_comb(double*, int);
void check_for_correct_sort(double*, int);
void print_array(double*, int);

int main() {
    std::cout << "Hello World!\n";

    const int NUMBER_OF_ARRAY = 100;
    double array[NUMBER_OF_ARRAY];
    srand(time(NULL));

    gen_array(array, NUMBER_OF_ARRAY);
    sort_comb(array, NUMBER_OF_ARRAY);
    check_for_correct_sort(array, NUMBER_OF_ARRAY);
    print_array(array, NUMBER_OF_ARRAY);
}

/*
 * Генерация значений элементов массива
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * С помощью функции rand создаются числа до 100 и длятся на 100 
 * для заполнения массива вещественными числами с двойной точностью.
 */
void gen_array(double *array, int num_of_array) {
    for (int i = 0; i < num_of_array; i++) {
        array[i] = (double)(rand() % 100)*0.01;
        std::cout << array[i] << "\n";
    }
}

/*
 * Сортировка массива методом расчёски
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * @param shrink_factor фактор уменьшения шага метода.
 * Прохождение по циклу и сравнения элементов с индексами i и (i+step)
 * В случае array[i] > array[i+step] - элементы меняются значениями с помощью функции swap
 */
void sort_comb(double* array, int num_of_array) {
    double shrink_factor = 1.2473309;
    int step = num_of_array - 1;

    while (step >= 1) {
        for (int i = 0; i + step < num_of_array; i++) {
            if (array[i] > array[i + step]) swap(array[i], array[i + step]);
        }
        step /= shrink_factor;
    }
}

/*
 * Проверка на правильность сортировки
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * 
 * Прохождение циклом по массиву и проверка на то, что элементы расположены в порядке возрастания
 * В противном случае - выход из программы
 */
void check_for_correct_sort(double* array, int num_of_array) {
    for (int i = 0; i + 1 < num_of_array; i++) 
        if (array[i] > array[i + 1]) {
            cout << "-----------------------------------------------------Sort Failed-----------------------------------------------------" << endl;
            exit(1);
        }
    cout << "------------------------------------------------------Success sort----------------------------------------------------" << endl;
}
/*
 * Вывод элементов массива в консоль
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 *
 * Прохождение циклом по массиву и вывод в консоль его элементов
 */
void print_array(double* array, int num_of_array) {
    for (int i = 0; i < num_of_array; i++) {
        cout << array[i] << "\n";
    }
}

