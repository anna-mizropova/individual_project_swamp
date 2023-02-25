#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>

#define UP 56
#define DOWN 50
#define RIGHT 54
#define LEFT 52
#define ESC 27
#define ENTER 13
#define DIAGONAL_UP_LEFT 55
#define DIAGONAL_UP_RIGHT 57
#define DIAGONAL_DOWN_LEFT 49
#define DIAGONAL_DOWN_RIGHT 51
#define K5 53
#define limit 219
#define swamp 126
#define bumps 254

struct block
{
    int index;
    bool moskito = false;
    bool froge = false;
};

HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
void go_to_xy(short x, short y)
{
    SetConsoleCursorPosition(Console, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(Console, &CursorInfo);
    CursorInfo.bVisible = show;
    CursorInfo.dwSize = size;
    SetConsoleCursorInfo(Console, &CursorInfo);
}
void input_massiv(block** map, int lenght, int width)
{
    setlocale(LC_ALL, "C");
    for (int i = 0; i < lenght; i++)
    {
        map[i] = new block[width];
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == lenght - 1 || j == width - 1) {
                map[i][j].index = limit;
            }
            else
            {
                map[i][j].index = swamp;
                if (rand() % 100 < 25)
                    map[i][j].index = bumps;
            }
        }
    }
    map[1][1].froge = true;
    map[1][1].index = bumps;
    map[rand() % (lenght - 5) + 3][rand() % (width - 5) + 3].moskito = char(42);
}
void output_massiv(block** map, int lenght, int width)
{
    for (int i = 0; i < lenght; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j].index == swamp)
                SetConsoleTextAttribute(Console, 8);
            if (map[i][j].index == bumps)
                SetConsoleTextAttribute(Console, 14);
            if (map[i][j].froge)
            {
                SetConsoleTextAttribute(Console, 2);
                cout << char(254);
                SetConsoleTextAttribute(Console, 7);
            }
            else if (map[i][j].moskito)
            {
                SetConsoleTextAttribute(Console, 4);
                cout << char(42);
                SetConsoleTextAttribute(Console, 7);
            }
            else {
                cout << char(map[i][j].index);
                SetConsoleTextAttribute(Console, 7);
            }
        }
        cout << endl;
    }
}
void move_to_coordinate(char ch, int& k)
{
    ch = _getch();
    switch (ch)
    {
    case ESC:
        exit(0);
    case DIAGONAL_DOWN_LEFT: // 1
        k = 1;
        break;
    case DOWN: // 2
        k = 2;
        break;
    case DIAGONAL_DOWN_RIGHT: // 3
        k = 3;
        break;
    case LEFT: //4
        k = 4;
        break;
    case K5: //5
        k = 5;
        break;
    default:
        setlocale(LC_ALL, "rus");
        k = 0;
        go_to_xy(40, 8);
        cout << "Нажмите кпонку обозначающую направление и кпонку значения длины (1-5)" << endl;
        go_to_xy(40, 9);
        system("pause");
        break;
    }
    setlocale(LC_ALL, "C");
}
void input_win()
{
    system("cls");
    go_to_xy(40, 8);
    setlocale(LC_ALL, "");
    cout << "Лягушка съела комара! Вы выиграли.";
    go_to_xy(40, 9);
    system("pause");
    exit(0);
}
void coordinate_to_MosquitoFrog(block** map, int length, int width, char ch, int& k)
{
    int mosqX, mosqY, frogeX, frogeY;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j].moskito) {
                mosqX = j;
                mosqY = i;
            }
            if (map[i][j].froge) {
                frogeX = j;
                frogeY = i;
            }
        }
    }
    for (int p = 0; p <= k; p++)
    {
        if (ch == UP)
        {
            if ((frogeY + p) == mosqY && frogeX == mosqX)
                input_win();
        }
        if (ch == DOWN)
        {
            if ((frogeY - p) == mosqY && frogeX == mosqX)
                input_win();
        }
        if (ch == LEFT)
        {
            if (frogeY == mosqY && (frogeX + p) == mosqX)
                input_win();
        }
        if (ch == RIGHT)
        {
            if (frogeY == mosqY && (frogeX - p) == mosqX)
                input_win();
        }
        if (ch == DIAGONAL_UP_LEFT)
        {
            if ((frogeY + p) == mosqY && (frogeX + p) == mosqX)
                input_win();
        }
        if (ch == DIAGONAL_UP_RIGHT)
        {
            if ((frogeY + p) == mosqY && (frogeX - p) == mosqX)
                input_win();
        }
        if (ch == DIAGONAL_DOWN_LEFT)
        {
            if ((frogeY - p) == mosqY && (frogeX + p) == mosqX)
                input_win();
        }
        if (ch == DIAGONAL_DOWN_RIGHT)
        {
            if ((frogeY - p) == mosqY && (frogeX - p) == mosqX)
                input_win();
        }
    }
}
void input_lose(block** map, int lenght, int width)
{
    for (int i = 0; i < lenght; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j].index == swamp && map[i][j].froge)
            {
                system("cls");
                go_to_xy(40, 8);
                setlocale(LC_ALL, "");
                cout << "Лягушка утонула! Вы проиграли";
                go_to_xy(40, 9);
                system("pause");
                exit(0);
                break;
            }
        }
    }
    setlocale(LC_ALL, "C");
}
void move_the_frog(block** map, int& k, char ch, int length, int width)
{
    bool breakpoint = false;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j].froge)
            {
                map[i][j].froge = false;
                if (ch == UP)
                {
                    if (i - k <= 0)
                        map[1][j].froge = true;
                    else
                        map[i - k][j].froge = true;
                }
                else if (ch == DOWN)
                {
                    if (i + k >= length - 1)
                        map[length - 2][j].froge = true;
                    else
                        map[i + k][j].froge = true;
                }
                else if (ch == LEFT)
                {
                    if (j - k <= 0)
                        map[i][1].froge = true;
                    else
                        map[i][j - k].froge = true;
                }
                else if (ch == RIGHT)
                {
                    if (j + k >= width - 1)
                        map[i][width - 2].froge = true;
                    else
                        map[i][j + k].froge = true;
                }
                else if (ch == DIAGONAL_UP_LEFT)
                {
                    if (i - k <= 0 || j - k <= 0) {
                        while (i - k <= 0 || j - k <= 0) {
                            k--;
                        }
                    }
                    map[i - k][j - k].froge = true;
                }
                else if (ch == DIAGONAL_UP_RIGHT) {
                    if (i - k <= 0 || j + k >= width - 1) {
                        while (i - k <= 0 || j + k >= width - 1) {
                            k--;
                        }
                    }
                    map[i - k][j + k].froge = true;
                }
                else if (ch == DIAGONAL_DOWN_LEFT)
                {
                    if (i + k >= length - 1 || j - k <= 0) {
                        while (i + k >= length - 1 || j - k <= 0) {
                            k--;
                        }
                    }
                    map[i + k][j - k].froge = true;
                }
                else if (ch == DIAGONAL_DOWN_RIGHT)
                {
                    if (i + k >= length - 1 || j + k >= width - 1) {
                        while (i + k >= length - 1 || j + k >= width - 1) {
                            k--;
                        }
                    }
                    map[i + k][j + k].froge = true;
                }
                breakpoint = true;
                break;
            }
        }
        if (breakpoint) {
            break;
        }
    }
}
void move_mosquito(block** map, int length, int width)
{
    bool breakpoint = false;
    int moskito_coordinate = rand() % 4;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j].moskito)
            {
                map[i][j].moskito = false;
                switch (moskito_coordinate)
                {
                case 0:
                    if (i + 1 >= length - 1)
                        map[length - 2][j].moskito = true;
                    else
                        map[i + 1][j].moskito = true;
                    break;
                case 1:
                    if (i - 1 <= 0)
                        map[1][j].moskito = true;
                    else
                        map[i - 1][j].moskito = true;
                    break;
                case 2:
                    if (j - 1 <= 0)
                        map[i][1].moskito = true;
                    else
                        map[i][j - 1].moskito = true;
                    break;
                case 3:
                    if (j + 1 >= width - 1)
                        map[i][width - 2].moskito = true;
                    else
                        map[i][j + 1].moskito = true;
                    break;
                }
                breakpoint = true;
                break;
            }
        }
        if (breakpoint)
            break;
    }
}
void full_move(char ch, int& k, block** map, int lenght, int width)
{
    move_to_coordinate(ch, k);
    move_the_frog(map, k, ch, lenght, width);
    coordinate_to_MosquitoFrog(map, lenght, width, ch, k);
    input_lose(map, lenght, width);
    move_mosquito(map, lenght, width);
    coordinate_to_MosquitoFrog(map, lenght, width, ch, k);
    system("cls");
    output_massiv(map, lenght, width);
}
int main()
{
    setlocale(LC_ALL, "");
    system("title Игра Болото");
    ConsoleCursorVisible(false, 100);
    srand(time(NULL));
    string Menu_Ruls[] = { "~—-   ---    ~    ---  ——-  ——-",
                           "| _  |   |  / |  |   |  |  |   |",
                           "|__| |___| /  |  |___|  |  |___|", " ",
    "Вы играете за лягушку.", "Ваша цель поймать комара.",
    "Передвигайтесь на кпонки правой клавиатуры.",
    "Вверх - 8", "Вниз - 2" , "Вправо - 6", "Влево - 4", "Вправо вверх по диагонали - 7","Влево вверх по диагонали - 9",
    "Вправо вниз по диагонали - 3","Влево вниз по диагонали - 1"," + кпонку от 1 до 5 - размер прыжка", "Чтобы начать игру нажмите ENTER ... " };
    int x = 40, y = 8, k = 0, l = 0;
    int lenght = rand() % (30 - 10 + 1) + 10;
    int width = rand() % (40 - 20 + 1) + 20;
    char ch = 0;
    block** map = new block * [lenght];
    go_to_xy(x, y);
    for (int i = 0; i < size(Menu_Ruls); i++)
    {
        go_to_xy(x, y++);
        cout << Menu_Ruls[i] << endl;
    }
    while (ch != ENTER)
    {
        ch = _getch();
        system("cls");
    }
    input_massiv(map, lenght, width);
    output_massiv(map, lenght, width);

    while (true)
    {
        ch = _getch();
        switch (ch)
        {
        case ESC:
            exit(0);
        case UP:
            full_move(ch, k, map, lenght, width);
            break;
        case DOWN:
            full_move(ch, k, map, lenght, width);
            break;
        case RIGHT:
            full_move(ch, k, map, lenght, width);
            break;
        case LEFT:
            full_move(ch, k, map, lenght, width);
            break;
        case DIAGONAL_UP_LEFT:
            full_move(ch, k, map, lenght, width);
            break;
        case DIAGONAL_UP_RIGHT:
            full_move(ch, k, map, lenght, width);
            break;
        case DIAGONAL_DOWN_LEFT:
            full_move(ch, k, map, lenght, width);
            break;
        case DIAGONAL_DOWN_RIGHT:
            full_move(ch, k, map, lenght, width);
            break;
        }
    }
    for (int i = 0; i < lenght; i++)
        delete[]map[i];
    delete[]map;
    _getch();
}