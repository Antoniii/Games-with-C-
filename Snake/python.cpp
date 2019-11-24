#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#ifdef WINDOWS
	#include <windows.h> // для функции Sleep()
	#include <conio.h> // для функций kbhit() и getch()
#else
	#include <unistd.h>
	#include <termios.h>
	#include <sys/select.h>

#define STDIN_FILENO 0
#define NB_DISABLE 0
#define NB_ENABLE 1

#define Sleep(x) usleep(x*1000)

int kbhit()
{
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock(int state)
{
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate); // получаем состояние терминала

	if (state == NB_ENABLE)
	{
		// выключаем ICANON-режим
		ttystate.c_lflag &= ~ICANON;
		ttystate.c_cc[VMIN] = 1;
	}
	else if (state == NB_DISABLE)
	{
		// включаем ICANON-режим
		ttystate.c_lflag |= ICANON;
	}
	// устанавливаем атрибуты терминала
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int getch()
{
	return fgetc(stdin);
}

#endif

// snake_size - размер змейки
// change_x, change_y - в какую сторону движется змейка
// coordinates_x[1000], coordinates_y[1000] - массивы, хранящие координаты
// частей тела змейки
// координатыголовы в coordinates_x[1], coordinates_y[1]
// food_x, food_y - координаты еды

int snake_size, change_x, change_y, coordinates_x[1000], coordinates_y[1000];
int food_x = -1, food_y = -1;

// symbol - хранит в себе ASCII код нажатой клавиши
// a[1000][1000] - таблица, в которой разворачивается игра

char symbol, a[1000][1000];

// Константы:
// N - высота таблицы
// M - штрина таблицы
// INTERVAL - в мс, через который будет передвигаться змейка

const int N = 13, M = 17, INTERVAL = 200;

void change_direction() // считывает нажатую клавишу
{
	symbol = getch();
	switch (symbol) // управление движением
	{
		case 'w' : if (change_x != 1 || change_y != 0)
					{
						change_x = -1;
						change_y = 0;
					}
					break;
		case 'a' : if (change_x != 0 || change_y != 1)
					{
						change_x = 0;
						change_y = -1;
					}
					break;
		case 's' : if (change_x != -1 || change_y != 0)
					{
						change_x = 1;
						change_y = 0;
					}
					break;
		case 'd' : if (change_x != 0 || change_y != -1)
					{
						change_x = 0;
						change_y = 1;
					}
					break;
	#ifdef WINDOWS
		case 'q' : nonblock(NB_DISABLE);
		std::exit(0);
	#endif
		default : break;							
	}
}

void show_table()
{
	#ifdef WINDOWS
		system("cls"); // очищаем консоль
	#else
		system("clear");
	#endif

	// вывод таблицы и краёв
	for (int i = 0; i <= N + 1; ++i)
		for (int j = 0; j <= M + 1; ++j)
			std::cout
				<< (i == 0 || j == 0 || i == N + 1 || j == M + 1 ? '#' : a[i][j])
				<< (j <= M ? "" : "\n");
}

void clear_snake_on_table() // очищаем координаты, где была змейка
{
	for (int i = 1; i <= snake_size; ++i)
		a[coordinates_x[i]][coordinates_y[i]] = ' ';
}

void show_snake_on_table() // закрашиваем текущее положение змейки
{
	// изменяем тип головы
	if (change_x == 1 && change_y == 0)
		a[coordinates_x[1]][coordinates_y[1]] = 'v';
	if (change_x == -1 && change_y == 0)
		a[coordinates_x[1]][coordinates_y[1]] = '^';
	if (change_x == 0 && change_y == 1)
		a[coordinates_x[1]][coordinates_y[1]] = '>';
	if (change_x == 0 && change_y == -1)
		a[coordinates_x[1]][coordinates_y[1]] = '<';

	// рисуем тело
	for (int i = 2; i <= snake_size; ++i)
		a[coordinates_x[1]][coordinates_y[1]] = '@';
}

bool game_over() // проверка на самоедство
{
	for (int i = 2; i <= snake_size; ++i)
		if (coordinates_x[1] == coordinates_x[i] &&
			coordinates_y[1] == coordinates_y[i])
			return true;
	return false;
}

void check_coordinates() // проверка выхода за границы поля
{
	if (coordinates_x[1] > N) coordinates_x[1] = 1;
	if (coordinates_x[1] < 1) coordinates_x[1] = N;
	if (coordinates_y[1] > M) coordinates_y[1] = 1;
	if (coordinates_y[1] < 1) coordinates_y[1] = M;
}

void next_step()
{
	clear_snake_on_table();

	// передвигаем тело
	for (int i = snake_size; i >= 2; --i)
	{
		coordinates_x[i] = coordinates_x[i - 1];
		coordinates_y[i] = coordinates_y[i - 1];
	}

	// передвигаем голову
	coordinates_x[1] += change_x;
	coordinates_y[1] += change_y;

	check_coordinates();

	// если доползли до еды, то увеличиваем размер змейки
	if (coordinates_x[1] == food_x && coordinates_y[1] == food_y)
	{
		snake_size++;
		food_x = -1;
		food_y = -1;
	}

	show_snake_on_table();

	// если змея занялась самоедством
	if (game_over())
	{
		std::cout << "You're looser! \n"; // сообщаем всю правду об игроке
		#ifdef WINDOWS
			system("pause");
		#endif
		std::exit(0);
	}
}

bool food_check() // наличие еды на карте
{
	if (food_x == -1 && food_y == -1) return false;
	return true;
}

void place_food() // добавление еды 
{
	std::srand(std::time(NULL));
	for (int i = 1; i <= 9; ++i)
	{
		int x = std::rand(), y = std::rand();
		if (x < 0) x *= -1;
		if (y < 0) y *= -1;
		x %= (N + 1);
		y %= (M + 1);
		if (x == 0) ++x;
		if (y == 0) ++y;
		if (a[x][y] != '@' && a[x][y] != 'v' && a[x][y] != '^' &&
			a[x][y] != '<' && a[x][y] != '>')
		{
			food_x = x;
			food_y = y;
			a[x][y] = '+';
			return;
		}
	}
}

void standart_setting()
{
	snake_size = 2;
	
	coordinates_x[1] = 1;
	coordinates_y[1] = 2;
	coordinates_x[2] = 1;
	coordinates_y[2] = 1;

	change_x = 0;
	change_y = 1;
}

int main()
{
	standart_setting();

	#ifdef WINDOWS
		std::memset(a, ' ', sizeof(a));
		nonblock(NB_ENABLE);
	#endif

	while(true)
	{
		if (kbhit() != 0)
			change_direction();

		next_step();

		if (!food_check())
			place_food();

		show_table();

		Sleep(INTERVAL);
	}
}
