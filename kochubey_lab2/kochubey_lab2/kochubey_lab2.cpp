// kochubey_lab2.cpp 

#include <stdlib.h>
#include <iostream>

using namespace std;

void fill_zero_array(int**, int);
void print_array(int**, int);
void symmetry_secondary_diagonal(int**, int);
void symmetry_main_diagonal(int**, int);
void pascals_triangle(int**, int);
void minesweeper_game(int**, int);
void put_the_mine(int**, int, int, int);


int main()
{
    int num_of_array;
    srand(time(NULL));

    cout << "Hello, user!\nEnter the values N - the size of the two-dimensional array N*N\nN = ";
    cin >> num_of_array;
    
    // creating array
    int** array = new int* [num_of_array];
    for (int i = 0;i < num_of_array; i++) {
        array[i] = new int[num_of_array];
    }

    fill_zero_array(array, num_of_array);

    cout << "Current array view:\n";

    print_array(array, num_of_array);

    while (1) {
        int answer = 0;
        cout << "What kind of array do you want?\n1.zero_array\n2.symmetry_main_diagonal\n3.symmetry_secondary_diagonal\n4.pascals_triangle\n5.minesweeper_game\n6.Exit\nYour answer: ";
        cin >> answer;
        cout << "Current array view:\n";

        switch (answer) {
        default:
            cout << "Something wenr wrong, try again./n";
            break;
        case 0:
            cout << "Something wenr wrong, try again./n";
            break;
        case 1:
            fill_zero_array(array, num_of_array);
            print_array(array, num_of_array);
            break;
        case 2:
            symmetry_main_diagonal(array, num_of_array);
            print_array(array, num_of_array);
            break;
        case 3:
            symmetry_secondary_diagonal(array, num_of_array);
            print_array(array, num_of_array);
            break;
        case 4:
            pascals_triangle(array, num_of_array);
            print_array(array, num_of_array);
            break;
        case 5:
            minesweeper_game(array, num_of_array);
            print_array(array, num_of_array);
            break;
        case 6:
            return(0);        
        }
    }
}

/*
 * Заполнение элементов массива нулями
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * Прохождение по циклу и передача элементам массива значения 0.
 */
void fill_zero_array(int** array, int num_of_array) {
    for (int i = 0; i < num_of_array; i++) {
        for (int k = 0; k < num_of_array; k++) array[i][k] = 0;
    }

}

/*
 * Создание матрицы симметричной относительно побочной диагонали
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * С помощью функции rand создаются числа до 100,
 * которые передаются в верхний треугольник матрицы относительно побочной диагонали,
 * а затем значения симметрично дублируются в нижний треугольник. 
 */
void symmetry_secondary_diagonal(int** array, int num_of_array) {
    for (int i = 0; i < num_of_array; i++) {
        for (int k = 0; k < num_of_array - i; k++) {
            array[i][k] = (int)(rand() % 100);
        }
    }
    
    for (int i = 0; i < num_of_array; i++) {
        for (int k = num_of_array - i; k < num_of_array; k++) {
            array[i][k] = array[num_of_array-k-1][num_of_array-i-1];
        }
    }
}

/*
 * Создание матрицы симметричной относительно главной диагонали
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * С помощью функции rand создаются числа до 100,
 * которые передаются в верхний треугольник матрицы относительно главной диагонали,
 * а затем значения симметрично дублируются в нижний треугольник.
 */
void symmetry_main_diagonal(int** array, int num_of_array) {
    for (int i = 0; i < num_of_array; i++) {
        for (int k = 0; k <= i; k++) {
            array[i][k] = (int)(rand() % 100);
        }
    }

    for (int i = 0; i < num_of_array; i++) {
        for (int k = i; k < num_of_array; k++) {
            array[i][k] = array[k][i];
        }
    }
}

/*
 * Создание матрицы с видом треугольника Паскаля
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * 
 * Элементы первого стобца (i=0) и диагонали(i=k) принимают значение 1;
 * Элементы ниже диагонали (i!=0) принимают значения (array[i][k-1] + array[i-1][k-1]).
 */
void pascals_triangle(int** array, int num_of_array) {
    for (int i = 0; i < num_of_array; i++) {
        for (int k = i; k < num_of_array; k++) {
            if (i == 0 || i == k) array[i][k] = 1;
            else array[i][k] = array[i][k - 1] + array[i - 1][k - 1];
        }
    }
}

/*
 * Создание поля игры в сапёра
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * 
 * С помощью функции rand определяется будуще метсоположение мины.
 * С помощью функции put_the_mine устанавливается мина.
 */
void minesweeper_game(int** array, int num_of_array) {
    int num_of_mine = ceil(pow(num_of_array, 2) / 7);
    cout << num_of_mine;
    cout << " - number of MINES\n";
    
    for (int i = 0; i < num_of_mine; i++) {
        int x;
        int y;
        do {
            x = (int)(rand() % num_of_array);
            y = (int)(rand() % num_of_array);
        } while (array[x][y] != 0);
       put_the_mine(array, num_of_array, x, y);
    }
    
   
}


/*
 * Установка "мин" и предупреждений о них в массиве
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 * @param x - точка расположение мины по оси X
 * @param y - точка расположение мины по оси Y
 * 
 * Мина обозначается как "1", предурперждения о минах как "-1" вокруг мины. 
 * Если мин рядом несколько, то "-1" суммируются в соответствии с количеством мин
 */
void put_the_mine(int** array, int num_of_array, int x, int y) {
    array[x][y] = -1;

    
    if (x != 0) {
        if(y!=0 and array[x-1][y-1] != -1) array[x - 1][y - 1] += 1;
        if (array[x-1][y] != -1)array[x - 1][y] += 1;
        if(y!= num_of_array - 1 and array[x-1][y+1] != -1) array[x - 1][y + 1] += 1;
    }
     
    if (y != num_of_array - 1 and array[x][y+1] != -1) array[x][y+1] += 1;
    if (y != 0 and array[x][y-1] != -1) array[x][y-1] += 1;
    
    if (x != num_of_array - 1) {
        if(y != 0 and array[x+1][y-1] != -1) array[x+1][y-1] += 1;
        if (array[x+1][y] != -1)array[x+1][y] += 1;
        if(y != num_of_array - 1 and array[x+1][y+1] != -1) array[x+1][y+1] += 1;
    }
    
}

/*
 * Вывод элементов массива в консоль
 *
 * @param array иходный массив.
 * @param num_of_array размер массива.
 *
 * Прохождение циклом по массиву и вывод в консоль его элементов в виде матрицы
 */
void print_array(int** array, int num_of_array) {
    for (int i = 0; i < num_of_array; i++) {
        for (int k = 0; k < num_of_array; k++) {
            if (array[k][i] < 10 and array[k][i] >= 0) cout << "  ";
            else cout << " ";
            cout << array[k][i] << " |";
        }
        cout << "\n";
    }
}

