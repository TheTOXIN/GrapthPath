#include "iostream"
#include "string" 
#include "conio.h"
#include "time.h"
#include "windows.h"
#include "iomanip"

using namespace std;

COORD position = { 0, 0 };
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

bool isWork = true;
const int N = 28;

int count_M = 6;
int count_P = 10;

int P[N];
int M[N][N] = {
	{ 0, 1, 0, 1, 0, 0 },
	{ 1, 0, 3, 2, 3, 3 },
	{ 0, 3, 0, 1, 0, 2 },
	{ 1, 2, 1, 0, 2, 0 },
	{ 0, 1, 0, 2, 0, 3 },
	{ 0, 3, 2, 0, 3, 0 },
};

int path_A = 0;
int path_B = 0;

int cursor_menu = 0;
int cursor_alg = 0;
int cursor_liter_1 = 0;
int cursor_liter_2 = 0;

const int length_menu = 8;
string list_menu[length_menu] = {
	"Заполнить случайно",
	"Изменить выборочно",
	"Алгоритм = ",
	"Вершина 1 = ",
	"Вершина 2 = ",
	"Кол-во вершин = ",
	"Очистить",
	"Выход"
};

const int length_litera = 28;
string list_litera[length_litera] = {
	"A","B","C","D","E","F","G","H","I","J","K","L","M",
	"N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
};

const int length_alg = 2;
string list_alg[length_alg] = {
	"Дейкстра",
	"Флойд"
};

int egg = 0;
int secret[5] = {107, 106, 113, 114, 102};

void console_pos(int x, int y)
{
	position.Y = x;
	position.X = y;
	SetConsoleCursorPosition(console, position);
}

void deikstra()
{
	system("cls");
	cout << "ДЕЙКСТРА" << endl;

	int inf = 10000;
	int non = -1;
	int res[N][N];
	int mrk[N];
	bool vis[N];
	int s = 0;
	bool f = true;

	for (int i = 0; i < count_M; i++)
		vis[i] = false;

	for (int i = 0; i < count_M; i++)
		for (int j = 0; j < count_M; j++)
			res[j][i] = inf;
	res[s][cursor_liter_1] = 0;

	do
	{
		int v = 0;
		for (int i = 0; i < count_M; i++)
			if (res[s][i] < res[s][v] && !vis[i])
				v = i;

		s++;

		for (int i = 0; i < count_M; i++)
		{
			if (i != v && M[v][i] != 0 && !vis[i])
			{
				if (M[v][i] < res[s - 1][i])
					res[s][i] = M[v][i] + res[s - 1][v];
				else
					res[s][i] = res[s - 1][i];
			}
		}

		vis[v] = true;

		for (int i = 0; i < count_M; i++)
			f &= vis[i];

	} while (!f);

	for (int i = 0; i < count_M; i++)
	{
		for (int j = 0; j < count_M; j++)
		{
			if (res[i][j] == 10000)
				cout << "# ";
			else
				cout << res[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	system("pause");
	system("cls");
}

void floid()
{
	system("cls");
	cout << "ФЛОЙДА" << endl;
	
	int R[N][N];

	//Пробегаемся по всем вершинам и ищем более короткий путь
	//через вершину k
	for (int k = 0; k < count_M; k++) {
		for (int i = 0; i < count_M; i++) {
			for (int j = 0; j < count_M; j++) {
				//Новое значение ребра равно минимальному между старым
				//и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
				R[i][j] = min(M[i][j], M[i][k] + M[k][j]);
			}
		}
	}

	for (int i = 0; i < count_M; i++)
	{
		for (int j = 0; j < count_M; j++)
		{
			cout << setw(3) << R[i][j];
		}
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < count_M; i++)
	{
		for (int j = i; j < count_M; j++)
		{
			if (i != j)
				cout << list_litera[j] << " -> " << list_litera[i] << " = " << R[i][j] << endl;
		}
	}

	system("pause");
	system("cls");
}

void compute()
{
	if (cursor_alg == 0)
		deikstra();
	else if (cursor_alg == 1)
		floid();
}

void rand_matr()
{
	for (int i = 0; i < count_M; i++)
	{
		for (int j = 0; j < count_M; j++)
		{
			if (rand() % 2 == 1)
			{
				int v = rand() % 100;
				M[i][j] = v;
				M[j][i] = v;
			}
			else
			{
				M[i][j] = 0;
				M[j][i] = 0;
			}
		}
	}
}

void init()
{
	//test
	for (int i = 0; i < count_P; i++)
		P[i] = rand() % 100;
}

void dflt()
{
	for (int i = 0; i < count_M; i++)
	{
		for (int j = 0; j < count_M; j++)
		{
			M[i][j] = 0;
		}
	}
}

void change_matr()
{
	int x;
	int y;
	int v;

	console_pos(count_M + 5, 5 * count_M + 3);
	cout << "INPUT X:";
	cin >> x;

	console_pos(++position.Y, 5 * count_M + 3);
	cout << "INPUT Y:";
	cin >> y;

	console_pos(++position.Y, 5 * count_M + 3);
	cout << "INPUT VALUE:";
	cin >> v;

	x--;
	y--;

	M[y][x] = v;
}

void show_matr()
{
	console_pos(2, 2);

	cout << "MATRIX:" << endl;
	cout << "  ";
	for (int i = 0; i < count_M; i++)
		cout <<  setw(3) << list_litera[i];
	cout << endl;

	for (int i = 0; i < count_M; i++)
	{
		for (int j = 0; j < count_M; j++)
		{
			if (j == 0)
				cout << " " << list_litera[i] << "|";
			cout << setw(3) << M[i][j];
		}
		cout << endl;
	}
}

void show_menu()
{
	console_pos(count_M + 5, 2);

	for (int i = 0; i < length_menu; i++)
	{
		if (i == cursor_menu)
			cout << "=> ";
		else
			cout << "   ";
		cout << i + 1 << ". " << list_menu[i] << " ";

		switch (i)
		{
		case 2: cout << list_alg[cursor_alg] << "             "; break;
		case 3: cout << list_litera[cursor_liter_1] << "             "; break;
		case 4: cout << list_litera[cursor_liter_2] << "             "; break;
		case 5: cout << count_M; break;
		}

		cout << endl;
	}
}

void show_egg()
{
	system("cls");

	cout << "             \m/(>.<)\m/ " << endl;
	
	string hey_1 =
		"─────────────██  \n"
		"██─██──███──█──█ \n"
		"─███───█────█──█ \n"
		"──█────███──█─██ \n"
		"─███───█────██─█ \n"
		"██─██──███──█──█ \n";

	cout << hey_1 << endl;

	system("pause");

}

void check_key()
{
	if (_kbhit())
	{
		int key = _getch();
		if (key == 72) 
		{
			cursor_menu--; 
			if (cursor_menu < 0)
				cursor_menu++;
			egg = 0;
		}
		else if (key == 80) 
		{
			cursor_menu++;
			if (cursor_menu >= length_menu)
				cursor_menu--;
			egg = 0;
		}
		else if (key == 75 || key == 77) 
		{
			switch (cursor_menu)
			{
			case 0: rand_matr();  break;
			case 1: change_matr();  break;
			case 2: cursor_alg++; if (cursor_alg >= length_alg) cursor_alg = 0; break;
			case 3: cursor_liter_1++; if (cursor_liter_1 >= count_M) cursor_liter_1 = 0; break;
			case 4: cursor_liter_2++; if (cursor_liter_2 >= count_M) cursor_liter_2 = 0; break;
			case 5: system("cls"); count_M++; if (count_M >= N) count_M = 0; break;
			case 6: dflt(); break;
			case 7: isWork = false; break;
			}
			egg = 0;
		}
		else if (key == 13)
		{
			compute();
			egg = 0;
		}
		else if (key == secret[egg]) 
		{
			egg++;
			Beep(1000, 100 * egg);
		}
		else
		{
			egg = 0;
		}

		if (egg == 5)
			show_egg();
	}
}

int main()
{
	srand(time(NULL));
	setlocale(0, "RUS");

	cout << "------------={GrapthPath}=-------------" << endl;

	init();
	while (isWork)
	{
		show_menu();
		show_matr();

		check_key();

		Sleep(1000 / 60);
	}

	return 1;
}