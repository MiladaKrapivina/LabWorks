#include <iostream>
#include "Lab4Header.h"
#include <ctime> 

using namespace std;

int main() {
	cout << "Lets play" << endl;
	setlocale(LC_ALL, "Russian");
	srand(std::time(NULL));
	char h;
	while (1) {
		cout << "Plese choise 0 or x" << endl;
		cin >> h;
		if (h == 'X' || h == 'O' || h == '0' || h == 'x') break;
	}



	Game game = initGame(h);

	if (game.isUserTurn) {
		while (1) {
			userTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) {
				break;
			}
			botTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) {
				break;
			}
		}
	}
	else {
		while (1) {
			botTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) {
				break;
			}
			userTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) {
				break;
			}
		}
	}
	switch (game.status) {
	case USER_WIN:
		cout << "Вы победили";
		break;
	case BOT_WIN:
		cout << "Вы проиграли";
		break;
	case NOT_WIN:
		cout << "Ничья";
		break;
	}
	return  0;
}
