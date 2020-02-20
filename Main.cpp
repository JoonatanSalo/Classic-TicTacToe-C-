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
	bool OnUserCreate() override
	{
		return true;
	}

	/*std::vector<std::string> GameField = 
	{" ", " ", " ",
	 " ", " ", " ",
	 " ", " ", " ",};
	 */

	/*int GameField[3][3] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1},
	};
	*/

	char GameField[3][3] = {
		{' ', ' ', 'x'},
		{'o', 'x', ' '},
		{' ', ' ', 'o'},
	};

	int x;
	int y;

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

	bool OnUserUpdate(float fElapsedTime) override
	{

		if (fElapsedTime <= 0.0001f) return true;
		Clear(olc::BLACK);

		FillRect(0, 0, 239, 239, olc::GREY);
		DrawRect(0, 0, 239, 239, olc::WHITE);

		DrawBoard();

		if (GetMouse(0).bPressed)
		{
			//x = GetMouseX() / 85;
			//y = GetMouseY() / 85;

			x, y = GetMouseXY();

			if (GameField[y][x] == ' ')
			{
				pop(GameField, x, y, 'x');
			}

			else if (GameField[y][x] == ' ')
			{
				pop(GameField, x, y, 'x');
			}

		}
		DrawString(1, 2, "x: " + std::to_string(x), olc::RED, 1);
		DrawString(1, 13, "y: " + std::to_string(y), olc::BLACK, 1);


		
			
		return true;
	}
};


int main()
{
	TicTacToe demo;
	if (demo.Construct(240, 240, 4, 4)) 
		demo.Start();

	return 0;
}