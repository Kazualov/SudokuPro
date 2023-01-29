#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Sudoku.h"

	using namespace std;
	using namespace sf;

class Game
{
	public:
		Game(void);
		void run();
	private:
		Font font;
		enum GameState { MENU, GAME, END };
		GameState state;
		void levels();
		void menu();
};


