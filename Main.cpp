#define OLC_PGE_APPLICATION
#include <random>
#include "C:\Users\joona\Desktop\olcPixelGameEngine-master\olcPixelGameEngine.h"

class TicTacToe : public olc::PixelGameEngine
{
public:
	TicTacToe()
	{
		sAppName = "Tic Tac Toe";
	}

public:

	char GameField[3][3] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '},
	};

	int x;
	int y;

	enum gameState { inProgress, Won, Lost, Draw };
	gameState state;

	int GetMouseXY()
	{
		x = GetMouseX() / 85;
		y = GetMouseY() / 85;

		return x, y;
	};

	void pop(char array[3][3], int x, int y, char replace) {
		char tmp = array[y][x];
		array[y][x] = replace;
	};

	bool BoardHasSpace()
	{
		bool hasSpace = false;

		for (int m = 0; m < 3; m++)
			for (int n = 0; n < 3; n++)
			{
				if (GameField[n][m] == ' ')
				{
					hasSpace = true;
				}
			}
		if (hasSpace)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CheckForWin(char z, gameState check)
	{
		int flag = 0;
		
		//rows
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++){
				if (GameField[y][x] == z) {
					flag++;
				}
				else {
					flag = 0;
				}

				if (flag == 3) {
					state = check;
					return true;
				}
			}

		//columns
		flag = 0;
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++) {
				if (GameField[y][x] == z) {
					flag++;
				}
				else {
					flag = 0;
				}

				if (flag == 3) {
					state = check;
					return true;
				}
			}

		//cross
		flag = 0;
		for (int x = 0; x < 3; x++) {
			if (GameField[x][x] == z) {
				flag++;
			}
			else {
				flag = 0;
			}

			if (flag == 3) {
				state = check;
				return true;
			}
		}

		flag = 0;
		for (int x = 0; x < 3; x++) {
			int i = 2 - x;
			if (GameField[i][x] == z) {
				flag++;
			}
			else {
				flag = 0;
			}

			if (flag == 3) {
				state = check;
				return true;
			}
		}

		return false;
	}
	
	void DrawBoard()
	{
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
			{
				if (GameField[y][x] == 'x')
				{
					DrawLine(25 + x * 60, 25 + y * 60, 25 + x * 60 + 60, 25 + y * 60 + 60, olc::DARK_GREY);
					DrawLine(25 + x * 60, 25 + y * 60 + 60, 25 + x * 60 + 60, 25 + y * 60, olc::DARK_GREY);
				}
				else if (GameField[y][x] == 'o')
				{
					DrawCircle(55 + x * 60, 55 + y * 60, 24, olc::DARK_GREY);
				}
				else
				{
					FillRect(25 + x * 60, 25 + y * 60, 60, 60, olc::GREY);
					DrawRect(25 + x * 60, 25 + y * 60, 60, 60, olc::WHITE);
				}
			}
	};

	void OpponentsTurn()
	{
		while (true)
		{
			int i = rand() % 3;
			int j = rand() % 3;

			if (GameField[j][i] == ' ')
			{
				pop(GameField, i, j, 'o');
				break;
			}
		}
	};

	bool OnUserCreate() override
	{
		state = inProgress;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		if (fElapsedTime <= 0.0001f) return true;
		Clear(olc::BLACK);

		FillRect(0, 0, 239, 239, olc::GREY);
		DrawRect(0, 0, 239, 239, olc::WHITE);

		DrawBoard();


		switch (state)
		{
		case (inProgress):
			if (GetMouse(0).bPressed)
			{
				x, y = GetMouseXY();

				if (GameField[y][x] == ' ')
				{
					pop(GameField, x, y, 'x');
					if (!CheckForWin('x', Won))
					{
						if (BoardHasSpace())
						{
							OpponentsTurn();
							//CheckForWin('o', Lost);
						}
						else if (!BoardHasSpace())
						{
							state = Draw;
						}
					}
				}
			}
			break;
		case Draw:
			DrawString(1, 2, "It's a draw!", olc::BLACK, 1);
			DrawString(1, 13, "Press 'space' for a new game.", olc::RED, 1);

			if (GetKey(olc::SPACE).bPressed)
			{
				for (int x = 0; x < 3; x++)
					for (int y = 0; y < 3; y++)
					{
						pop(GameField, x, y, ' ');
					}
				state = inProgress;
			}
			break;

		case Won:
			DrawString(1, 2, "You won!", olc::BLACK, 1);
			DrawString(1, 13, "Press 'space' for a new game.", olc::RED, 1);

			if (GetKey(olc::SPACE).bPressed)
			{
				for (int x = 0; x < 3; x++)
					for (int y = 0; y < 3; y++)
					{
						pop(GameField, x, y, ' ');
					}
				state = inProgress;
			}
			break;

		case Lost:
			DrawString(1, 2, "You lost!", olc::BLACK, 1);
			DrawString(1, 13, "Press 'space' for a new game.", olc::RED, 1);

			if (GetKey(olc::SPACE).bPressed)
			{
				for (int x = 0; x < 3; x++)
					for (int y = 0; y < 3; y++)
					{
						pop(GameField, x, y, ' ');
					}
				state = inProgress;
			}
			break;


			//DrawString(1, 2, "x: " + std::to_string(x), olc::BLACK, 1);
			//DrawString(1, 13, "y: " + std::to_string(y), olc::RED, 1);

			return true;
		}
	}
};


	int main()
	{
		TicTacToe demo;
		if (demo.Construct(240, 240, 4, 4))
			demo.Start();

		return 0;
	}