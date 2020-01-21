// Вспомогательный файл
#include <iostream>


using namespace std;
enum Status {
	PLAY,            // Игра продолжается
	USER_WIN,        // Игрок победил
	BOT_WIN,         // Бот победил
	NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
};

struct Game {
	char bord[3][3];  // Игровое поле
	bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
	char userChar;    // Символ которым играет пользователь
	char botChar;     // Символ которым играет бот
	Status status;
};

Game initGame(char userChar) {
	Game game;
	//очистить масссив
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			game.bord[i][j] = ' ';
		}
	}
	if (rand() % 2)   game.isUserTurn = true;//определяем чей ход
	game.userChar = userChar; //Устанавливает символ для Игрока (Задаётся параметром userChar)
	switch (game.userChar) { //устанавливает символ бота
	case 'O':
		game.botChar = 'X';
		break;
	case 'X':
		game.botChar = 'O';
		break;

	case '0':
		game.botChar = 'x';
		break;
	case 'x':
		game.botChar = '0';
		break;
	}
	return game;
}

void updateDisplay(const Game game) {
	system("cls");
	cout << "0  1  2" << endl;
	// вывод игрового поля
	cout << "----------" << std::endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << game.bord[i][j] << "|  ";
		}
		cout << i << endl << "----------" << endl;
	}
}

/*
Выполняет ход бота. В выбранную ячейку устанавливается символ которым играет бот.
Бот должен определять строку, столбец или диагональ в которой у игрока больше всего иксиков/ноликов и ставить туда свой символ. Если на поле ещё нет меток, бот должен ставить свой знак в центр. В остальных случаях бот ходит рандомно.
*/
void botTurn(Game* game) {
	bool empty = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->bord[i][j] != ' ') {
				empty = false;
				break;
			}
		}
	}
	if (empty) 	game->bord[1][1] = game->botChar;
	
	else {

		for (int i = 0; i < 3; i++) {
			int val = 0;
			int len = 0;
			bool flag = false;
			for (int j = 0; j < 3; j++) {
				if (game->bord[j][i] == game->userChar) {
					len++;
				}
				else if (game->bord[j][i] != game->botChar) {
					val = j;
					flag = true;
				}
			}
			if ((len == 2) && flag) {
				game->bord[val][i] = game->botChar;
				return;
			}
		}// по столбцам

		for (int j = 0; j < 3; j++) {
			int val = 0;
			int len = 0;
			bool flag = false;
			for (int i = 0; i < 3; i++) {
				if (game->bord[j][i] == game->userChar) {
					len++;
				}
				else if (game->bord[j][i] != game->botChar) {
					val = i;
					flag = true;
				}
			}
			if ((len == 2) && flag) {
				game->bord[val][j] = game->botChar;
				return;
			}
		}

		{
			int val = 0;
			int len = 0;
			bool flag = false;
			for (int i = 0; i < 3; i++) {
				if (game->bord[i][i] == game->userChar) {
					len++;
				}
				else if (game->bord[i][i] != game->botChar) {
					val = i;
					flag = true;
				}
			}
			if ((len == 2) && flag) {
				game->bord[val][val] = game->botChar;
				return;
			}
		}// по главной диагонали

		{
			int val = 0;
			int len = 0;
			bool flag = false;
			for (int i = 0; i < 3; i++) {
				if (game->bord[i][2 - i] == game->userChar) {
					len++;
				}
				else  if (game->bord[i][2 - i] != game->botChar) {
					val = i;
					flag = true;
				}
			}
			if ((len == 2) && flag) {
				game->bord[val][2 - val] = game->botChar;
				return;
			}
		} //по побочной диагонали

		int i = 0, j = 0;
		while (game->bord[i][j] != ' ') {
			i = rand() % 3;
			j = rand() % 3;
		}
		game->bord[i][j] = game->botChar;
	}
}




void userTurn(Game* game) {
	int i, j;
	while (1) {
		cout << "Введите координаты x и у, соответственно:";
		cin >> i >> j;

		if (i < 0 || j < 0 || i>3 || j>3 || &game->bord[i][j] == " ")
			cout << "Retry!!! " ;
		else {
			game->bord[j][i] = game->userChar;
			break;
		}


	}
}
/*
Функция определяет как изменилось состояние игры после последнего хода.

Функция сохраняет новое состояние игры в структуре game и передаёт ход другому
игроку.
Функция возвращает true, если есть победитель или ничья, иначе false.
*/

bool updateGame(Game* game) {

	for (int i = 0; i < 3; i++) {
		int len2 = 0;
		int len1 = 0;
		

		for (int j = 0; j < 3; j++) {
			if (game->bord[i][j] == game->userChar) {
				len1++;
			}
			else if (game->bord[i][j] == game->botChar) {
				len2++;
			}
		}
		if ((len1 == 3) || (len2 == 3)) {
			game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
			return true; // есть победитель
		}

		 
		int 	len5 = 0;
		int 	len6 = 0;
			if (game->bord[i][i] == game->userChar) {
				len5++;
			}
			else if (game->bord[i][i] == game->botChar) {
				len6++;
			}
		
		 if ((len5 == 3) || (len6 == 3)) {
			 game->status = (len5 == 3 ? USER_WIN : BOT_WIN);
			 return true; // есть победитель
		 }

		 
			int  len3 = 0;
			 int len4 = 0;
			 if (game->bord[i][2-i] == game->userChar) {
				 len3++;
			 }
			 else if (game->bord[i][2-i] == game->botChar) {
				 len4++;
			 }
		 
		 if ((len3 == 3) || (len4 == 3)) {
			 game->status = (len3 == 3 ? USER_WIN : BOT_WIN);
			 return true; // есть победитель
		 }

		
	}
	int len = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->bord[i][j] != ' ') {
				len++;
			}
		}
	}
	if (len == 9) {
		game->status = NOT_WIN;
		return true;//ничья
	}
	game->status = PLAY;
	return false;// победителя нет

}
