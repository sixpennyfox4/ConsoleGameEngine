// Example Project 1 (catch the cube)
// Used V0.1

#include "ConsoleGameEngine.hpp"

using namespace CGE;

int main() {
	int score{ 0 };

	CG game;
	game.InitConsoleSpace(40, 80, "Catch the cube");

	Rectangle plr{ Vector2{ 20, 10 }, 5, 5 };
	Rectangle movingRec{ Vector2{ getRandomNumber(10, 75), getRandomNumber(10, 35) }, 5, 5 };
	while (true) {
		// We will use GetAsyncKeyState which isnt good but if it works it works.
		if (GetAsyncKeyState('W')) plr.position.y -= 2;
		if (GetAsyncKeyState('S')) plr.position.y += 2;
		if (GetAsyncKeyState('A')) plr.position.x -= 2;
		if (GetAsyncKeyState('D')) plr.position.x += 2;

		game.drawOutline(COLOR_GREEN);
		std::cout << "Score: " << score;

		game.drawRectangleRec(movingRec, true, COLOR_RED);
		game.drawRectangleRec(plr, true, COLOR_BLUE);

		if (game.checkCollisionRecs(plr, movingRec)) {
			score++;

			movingRec.position = Vector2{ getRandomNumber(10, 75), getRandomNumber(10, 35) };
			plr.position = Vector2{ 20, 10 };
		}

		wait(100);
		game.clearConsole();
	}

	return 0;
}
