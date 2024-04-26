﻿// Пятнашки (barley-break).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <ctime> 
#include <iomanip> // для использования setw

using namespace std;

void initArray(int**& m, int& H, int& W) //инициализация массива
{
    m = new int*[H]; // выделяем память для H указателей на строки

    for (int i = 0; i < H; i++)
    {
        m[i] = new int[W]; //для каждой строки выделяем память под W элементов
    }
}

void deleteArray(int** m, int& H, int& W) //освобождение памяти
{
    for (int i = 0; i < W; i++)
    {
        delete[] m[i]; //освобождаем память каждой строки
    }
    delete[] m; //освобождаем память, выделенную под указатели на строки
}


void fillArray(int** m, int& H, int& W) //функция заполнения массива
{
    int t = 0;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            m[i][j] = t;
            t++;
        }
    }
}

void showArray(int** m, int& H, int& W) // функция вывода на экран
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (m[i][j] != 0)
                cout << setw(8) << m[i][j];
            else
                cout << setw(8) << " "; //не отображает "0" на экране
        }
        cout << "\n\n";
    }
}

void mixingNumbers(int** m, int& H, int& W) // перемешивание чисел
{
    int t = 0;
    int i1, j1;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            i1 = rand() % H;
            j1 = rand() % W;
            t = m[i][j];
            m[i][j] = m[i1][j1];
            m[i1][j1] = t;
        }
    }
}

void findZero(int** m, int& H, int& W, int& zeroX, int& zeroY) //поиск пустой ячейки
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (m[i][j] == 0)
            {
                zeroX = i;
                zeroY = j;
            }
        }
    }
}

void buttonUp(int** m, int& H, int& W, int& zeroX, int& zeroY) //перемещение пустой ячейки вверх
{
    if (zeroY > 0)
    {
        swap(m[zeroX][zeroY], m[zeroX][zeroY - 1]);
    }
}

void buttonDown(int** m, int& H, int& W, int& zeroX, int& zeroY) //перемещение пустой ячейки вниз
{
    if (zeroY > W)
    {
        swap(m[zeroX][zeroY], m[zeroX][zeroY + 1]);
    }
}

void buttonLeft(int** m, int& H, int& W, int& zeroX, int& zeroY) //перемещение пустой ячейки вверх
{
    if (zeroX > 0)
    {
        swap(m[zeroX][zeroY], m[zeroX - 1][zeroY]);
    }
}

void buttonRight(int** m, int& H, int& W, int& zeroX, int& zeroY) //перемещение пустой ячейки вверх
{
    if (zeroX < H)
    {
        swap(m[zeroX][zeroY], m[zeroX + 1][zeroY]);
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    //размерность массива
    int W = 4;
    int H = 4;

    int zeroX = 0;
    int zeroY = 0;

    int Button; //кнопка управления

    int** m = nullptr; //объявляем указатель на двумерный массив
    initArray (m, H, W); //инициализируем массив

    fillArray (m, H, W); //заполняем массив целыми числами от 0 до 15
    cout << "\n\n\n";
    //showArray (m, H, W); //вывод массива на экран

    mixingNumbers (m, H, W); // перемешиваем числа в массиве

    cout << "\n\n\n";
    showArray (m, H, W); //вывод массива на экран

    
    
    deleteArray(m, H, W); //освобождаем память 

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
