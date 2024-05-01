// Пятнашки (barley-break).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <ctime> 
#include <iomanip> // для использования setw
#include <conio.h> // для _getch()

using namespace std;

const static void Configure_Console_Window(void) {

    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo); // отключение каретки

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); // установка кириллицы

    const std::string Title = "title Barley-break"; // текст заголовка окна

    system("color E"); // установка основного цвета текста
    system("mode con cols=125 lines=30"); // установка разрешения консоли, отключения бокового скрола
    system(Title.c_str()); // установка заголовка консоли
    system("@echo off"); // переключение режима отображения команд на экране

} // Функция настроек консольного окна

void mainMenu(int& H, int& W)
{
    cout << "  ____    _    __  __ _____      _            _ ____ \n";
    cout << " / ___|  / \\  |  \\/  | ____|    (_)_ __      / | ___| \n";
    cout << "| |  _  / _ \\ | |\\/| |  _|      | | '_ \\     | |___ \\ \n";
    cout << "| |_| |/ ___ \\| |  | | |___     | | | | |    | |___) | \n";
    cout << " \\____/_/   \\_\\_|  |_|_____|    |_|_| |_|    |_|____/ \n";
    cout << "\n\n\n";
    cout << "        Для старта игры выберите размер поля:\n";
    cout << "                    1. 3 х 3\n";
    cout << "                    2. 4 х 4\n";
    cout << "                    0. Выход\n";
    int select;
    while (true)
    {
        cin >> select;
        if (select == 1)
        {
            H = 3;
            W = 3;
            break;
        }
        else if (select == 2)
        {
            H = 4;
            W = 4;
            break;
        }
        else if (select == 0)
        {
            return;
        }
    }

    
}
void subMenu()
{
    
}

void initArray(int**& m, int H, int W) //инициализация массива
{
    m = new int*[H]; // выделяем память для H указателей на строки

    for (int i = 0; i < H; i++)
    {
        m[i] = new int[W]; //для каждой строки выделяем память под W элементов (столбцы)
    }
}

void deleteArray(int** m, int& H, int& W) //освобождение памяти
{
    for (int i = 0; i < H; i++)
    {
        delete[] m[i]; //освобождаем память каждой строки
    }
    delete[] m; //освобождаем память, выделенную под указатели на строки
}


void fillArray(int** m, int H, int W) //функция заполнения массива
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

void showArray(int** m, int H, int W) // функция вывода на экран
{
    /*/HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE); //получаем окно, в котором нужно изменить цвет
    SetConsoleTextAttribute(h, 14); // меняем цвет названия программы на желтый
    */
    cout << "\n\n\n";    
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
    //SetConsoleTextAttribute(h, 15);
    cout << "\n\nУправление (пустой клеткой) осуществляется стрелками вверх, вниз, вправо, влево.\nДля Выхода нажмите ESC.\n";
}

void mixingNumbers(int** m, int H, int W) // перемешивание чисел
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

void findZero(int** m, int H, int W, int& zeroX, int& zeroY) //поиск пустой ячейки
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

void Continue(void)
{
    //cout << "\n\nУправление осуществляется стрелками вверх, вниз, вправо, влево.\nДля Выхода нажмите ESC.\n";
    _getch();
} // функция ожидания

void buttonUp(int** m, int H, int W, int& zeroX, int zeroY) //перемещение пустой ячейки вверх
{
    if (zeroX > 0)
    {
        swap(m[zeroX][zeroY], m[zeroX - 1][zeroY]);
        zeroX--;
    }
    else if (zeroX == 0) Continue();
}

void buttonDown(int** m, int H, int W, int& zeroX, int zeroY) //перемещение пустой ячейки вниз
{
    if (zeroX < H - 1)
    {
        swap(m[zeroX][zeroY], m[zeroX + 1][zeroY]);
        zeroX++;
    }
    else if (zeroX == H) Continue();
}

void buttonLeft(int** m, int H, int W, int zeroX, int& zeroY) //перемещение пустой ячейки влево
{
    if (zeroY > 0)
    {
        swap(m[zeroX][zeroY], m[zeroX][zeroY - 1]);
        zeroY--;
    }
    else if (zeroY == 0) Continue();
}

void buttonRight(int** m, int H, int W, int zeroX, int& zeroY) //перемещение пустой ячейки вправо
{
    if (zeroY < W - 1)
    {
        swap(m[zeroX][zeroY], m[zeroX][zeroY + 1]);
        zeroY++;
    }
    else if (zeroY == W) Continue();
}

bool verification (int** m, int H, int W) //проверка массива на упорядоченность элементов по возрастанию
{
    int version = 0, version_1 = 0;
    for (int i = 0; i < H; i++)
    {
        int n = 0;
        for (int j = 0; j < W; j++)
        {
            if (m[i][j] != n)
            {
                version++;
                break;
            }
            else
                n++;
        }
    }
    for (int i = 0; i < H; i++)
    {
        int n = 1;
        for (int j = 0; j < W; j++)
        {
            if (m[i][j] != n)
            {
                version_1++;
            }
            else
                n++;
        }
    }

    if (version == 0 || (m[3][3]) == 0 && version_1 == 1)
        return true;
}

int main()
{
    Configure_Console_Window();
    srand(time(0));

    //размерность массива
    int W;
    int H;
    
    int zeroX = 0;
    int zeroY = 0;

    mainMenu(H, W);

    system("cls");

    int Button; //кнопка управления

    int** m = nullptr; //объявляем указатель на двумерный массив
    initArray (m, H, W); //инициализируем массив

    fillArray (m, H, W); //заполняем массив целыми числами от 0 до 15
    //cout << "\n\n\n";
    //showArray (m, H, W); //вывод массива на экран

    mixingNumbers (m, H, W); // перемешиваем числа в массиве

    //cout << "\n\n\n";
    showArray (m, H, W); //вывод массива на экран

    findZero(m, H, W, zeroX, zeroY); //поиск пустой ячейки

    while (true)
    {
        Button = _getch(); //ожидание нажатия клавиши

        if (Button == 27)
            break;

        else if (Button == 72) { //перемещение пустой ячейки вверх

             buttonUp(m, H, W, zeroX, zeroY);
             system("cls");             
             showArray (m, H, W);
             if (verification(m, H, W) == true)
             {
                 cout << "\n\nПоздравляем! Вы выиграли!!!";
                 return 0;
             }
             else
                 Continue();
        }

        else if (Button == 80) { //перемещение пустой ячейки вниз

            buttonDown(m, H, W, zeroX, zeroY); 
            system("cls");
            showArray(m, H, W);
            if (verification(m, H, W) == true)
            {
                cout << "\n\nПоздравляем! Вы выиграли!!!";
                return 0;
            }
            else
                Continue();
        }

        else if (Button == 77) { //перемещение пустой ячейки вправо

            buttonRight(m, H, W, zeroX, zeroY);
            system("cls");
            showArray(m, H, W);
            if (verification(m, H, W) == true)
            {
                cout << "\n\nПоздравляем! Вы выиграли!!!";
                return 0;
            }
            else
                Continue();
        }

        else if (Button == 75) { //перемещение пустой ячейки влево

            buttonLeft(m, H, W, zeroX, zeroY);
            system("cls");
            showArray(m, H, W);
            if (verification(m, H, W) == true)
            {
                cout << "\n\nПоздравляем! Вы выиграли!!!";
                return 0;
            }
            else
                Continue();
        }
    }    
    
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
