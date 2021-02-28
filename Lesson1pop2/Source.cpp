#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

void setColor(char, int);

struct Options {
	// Размеры карты
	int mapSizeX,
		mapSizeY;

	// Текстуры
	char mapTextureWall;
	int mapTextureWallColor;

	char mapTextureField;
	int mapTextureFieldColor;

	// Игрок позиция
	int playerPositionX,
		playerPositionY;
	// Игрок модель
	char playerModel;
	// Цвет модели
	int playerColor;
	// Очки игрока
	int playerPoints;

	// Игрок 2
	int player2PositionX,
		player2PositionY;
	// Игрок модель
	char player2Model;
	// Цвет модели
	int player2Color;
	// Очки игрока
	int player2Points;

	// Яблоко позиция
	int applePositionX[50],
		applePositionY[50];
	// Яблоко модель
	char appleModel;
	// Цвет яблока
	int appleColor;
	// Количество яблок
	int appleNum;

};

void showMap(Options& game) {
	// Кушаем яблоко

	if (game.playerPoints > game.player2Points + 5) {
		if (game.playerPositionX == game.player2PositionX &&
			game.playerPositionY == game.player2PositionY) {
			game.player2PositionX = 0;
			game.player2PositionY = 0;
		}
	}
	else if (game.player2Points > game.playerPoints + 5) {
		if (game.playerPositionX == game.player2PositionX &&
			game.playerPositionY == game.player2PositionY) {
			game.playerPositionX = 0;
			game.playerPositionY = 0;
		}
	}


	for (int i = 0; i < game.appleNum; i++)
	{
		if (game.playerPositionX == game.applePositionX[i] &&
			game.playerPositionY == game.applePositionY[i]) {

			game.applePositionX[i] = 0;
			game.applePositionY[i] = 0;

			game.playerPoints++;
		}
		if (game.player2PositionX == game.applePositionX[i] &&
			game.player2PositionY == game.applePositionY[i]) {

			game.applePositionX[i] = 0;
			game.applePositionY[i] = 0;

			game.player2Points++;
		}
	}



	for (int y = 0; y < game.mapSizeY; y++)
	{
		for (int x = 0; x < game.mapSizeX; x++)
		{
			if (y == 0 || y == game.mapSizeY - 1 ||
				x == 0 || x == game.mapSizeX - 1)
			{
				setColor(game.mapTextureWall, game.mapTextureWallColor);
			}
			else if (x == game.playerPositionX && y == game.playerPositionY) {
				setColor(game.playerModel, game.playerColor);
			}
			else if (x == game.player2PositionX && y == game.player2PositionY) {
				setColor(game.player2Model, game.player2Color);
			}
			else {
				bool isFind = false;
				for (int i = 0; i < game.appleNum; i++)
				{
					if (x == game.applePositionX[i] && y == game.applePositionY[i]) {
						setColor(game.appleModel, game.appleColor);
						isFind = true;
						break;
					}
				}
				if (!isFind) {
					setColor(game.mapTextureField, game.mapTextureFieldColor);
				}
			}
		}
		cout << endl;
	}

	// !!!!!!!!!!!!!!!!
	cout << "\n[-] Player: \t" << game.playerPoints << endl;
	cout << "\n[-] Player2: \t" << game.player2Points << endl;
	// !!!!!!!!!!!!!!!!
}

void movement(Options& game) {
	bool isStop = false;
	while (!isStop) {
		switch (_getch()) {
		case 'd':
			if (game.playerPositionX < game.mapSizeX - 2)
				game.playerPositionX++;
			isStop = true; // *
			break;
		case 'a':
			if (game.playerPositionX > 1)
				game.playerPositionX--;
			isStop = true; // *
			break;
		case 'w':
			if (game.playerPositionY > 1)
				game.playerPositionY--;
			isStop = true; // *
			break;
		case 's':
			if (game.playerPositionY < game.mapSizeY - 2)
				game.playerPositionY++;
			isStop = true; // *
			break;
		case 72:
			if (game.player2PositionY > 1)
				game.player2PositionY--;
			isStop = true; // *
			break;
		case 80:
			if (game.player2PositionY < game.mapSizeY - 2)
				game.player2PositionY++;
			isStop = true; // *
			break;
		case 75:
			if (game.player2PositionX > 1)
				game.player2PositionX--;
			isStop = true; // *
			break;
		case 77:
			if (game.player2PositionX < game.mapSizeX - 2)
				game.player2PositionX++;
			isStop = true; // *
			break;
		}
	}

}

int main() {
	setlocale(0, "");
	srand(time(NULL));
	Options game;
	// Карта
	game.mapSizeX = 25;
	game.mapSizeY = 20;
	game.mapTextureWall = ' ';
	game.mapTextureWallColor = 5105;
	game.mapTextureField = '.';
	game.mapTextureFieldColor = 8;

	// Игрок
	game.playerModel = ' ';
	game.playerColor = 144;
	game.playerPositionX = 3;
	game.playerPositionY = game.mapSizeY / 2;
	game.playerPoints = 0;

	// Игрок 2
	game.player2Model = ' ';
	game.player2Color = 312;
	game.player2PositionX = game.mapSizeX - 3;
	game.player2PositionY = game.mapSizeY / 2;
	game.player2Points = 0;

	// Яблоко
	game.appleModel = ' ';
	game.appleColor = 1010;
	game.appleNum = 10;

	for (int i = 0; i < game.appleNum; i++)
	{
		game.applePositionX[i] = (rand() % (game.mapSizeX - 2)) + 1;
		game.applePositionY[i] = (rand() % (game.mapSizeY - 2)) + 1;

	}

	// Курсов выключен
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);

	while (true) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
		showMap(game);
		movement(game);

	}
	int _; cin >> _;
	return 0;
}


void setColor(char texture, int colorTexture) {
	HANDLE _hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_hColor, colorTexture);
	cout << texture << " ";
	SetConsoleTextAttribute(_hColor, 15);
}