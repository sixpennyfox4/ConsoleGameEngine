ConsoleGameEngine V0.1
======================

A C++ header only console game engine.

> [!IMPORTANT]
> This game engine is still in early development.
>
> Only works on windows.
>
> Also its a library instead of game engine but too lazy to rename.

> [!WARNING]
> Includes Windows.h which may interfere with other third party libraries!

Simple examples
---------------

![image](https://github.com/user-attachments/assets/5d19075d-a71d-4e06-ac3a-3af8a4a5aad6)

You can make things like the image above but I will give quick examples.

```c++
#include "ConsoleGameEngine.hpp"

int main() {
	CGE::CG game; // Console game class.
	game.InitConsoleSpace(20, 40, "Example"); // Set the space of characters to be used.

	while (true) {
		game.drawOutline(); // Draws outline of the space.
		game.drawText(CGE::Vector2{ 12, 9 }, "Hello, World!", COLOR_RED);

		CGE::wait(100);
		game.clearConsole();
	}

	return 0;
}
```

Another example is simple collision detection. (works only with a normal rectangle)

```c++
#include "ConsoleGameEngine.hpp"

int main() {
	CGE::CG game;
	game.InitConsoleSpace(20, 40, "Example");

	CGE::Rectangle rec1{ CGE::Vector2{ 10, 10 }, 4, 4 };
	CGE::Rectangle rec2{ CGE::Vector2{ 20, 10 }, 4, 4 };
	while (true) {
		if (GetAsyncKeyState('W')) rec1.position.y--;
		if (GetAsyncKeyState('S')) rec1.position.y++;
		if (GetAsyncKeyState('A')) rec1.position.x--;
		if (GetAsyncKeyState('D')) rec1.position.x++;

		game.drawOutline();
		if (game.checkCollisionRecs(rec1, rec2)) std::cout << "TOUCHING!";

		game.drawRectangleRec(rec1);
		game.drawRectangleRec(rec2);

		CGE::wait(100);
		game.clearConsole();
	}

	return 0;
}
```

Cheatsheet
==========

```c++
//
// CG Class functions:
//

void InitConsoleSpace(int height, int width, const char* consoleName); // Sets the space of characters to be used.
void drawOutline(int color=COLOR_WHITE); // Draws outline of the space.
void clearConsole(); // Clears the console.
void drawRectangle(const Vector2& position, const int height, const int width, bool fill=true, int color=COLOR_WHITE); // Draws a rectangle in the space.
void drawRectangleRec(const Rectangle& rectangle, bool fill=true, int color=COLOR_WHITE);  // Draws a rectangle in the space. (using Rectangle struct)
void drawCircle(const Vector2& position, int radius, int color=COLOR_WHITE); // Draws a circle in the space.
bool checkCollisionRecs(const Rectangle& rec1, const Rectangle& rec2); // Checks if 2 rectangles are touching.
void toggleDrawing(bool c); // Toggles console drawing. (e.g. pause/unpause game)
void drawLine(Vector2 position, int height, int width, int color=COLOR_WHITE); // Draws a simple line in the space.
void drawTriangle(Vector2 position, int height, int width, bool fill=true, int color=COLOR_WHITE); // Draws a triangle in the space.
void drawText(Vector2 position, const char* text, int color=COLOR_WHITE); // Draws text in the space.

//
// CGE Namespace functions:
//

int getRandomNumber(int min, int max); // Generates and returns a random number.
void desktopNotify(const std::wstring& title, const std::wstring& message, const int time=5, const bool async=true); // Shows a desktop notification.
void writeFile(const char* fileName, const char* contents); // Writes given text to a given file.
std::string readFile(const char* fileName); // Reads and returns the contents of a given file.
void wait(const int milliseconds); // Pauses the current thread for certain amount of milliseconds.
```
