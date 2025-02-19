/*
* 
* A header only console game engine made by sixpennyfox4 (github)
* Supported platforms: windows
* 
*/

#ifndef _WIN32
#error "Console game engine only works on windows!"
#endif

#define NOGDI

/* INCLUDES */
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <random>

/* COLORS */
#define COLOR_BLACK      30
#define COLOR_RED        31
#define COLOR_GREEN      32
#define COLOR_YELLOW     33
#define COLOR_BLUE       34
#define COLOR_MAGENTA    35
#define COLOR_CYAN       36
#define COLOR_WHITE      37

#define COLOR_BRIGHT_BLACK   90
#define COLOR_BRIGHT_RED     91
#define COLOR_BRIGHT_GREEN   92
#define COLOR_BRIGHT_YELLOW  93
#define COLOR_BRIGHT_BLUE    94
#define COLOR_BRIGHT_MAGENTA 95
#define COLOR_BRIGHT_CYAN    96
#define COLOR_BRIGHT_WHITE   97

#define BACKGROUND_BLACK    40
#define BACKGROUND_RED      41
#define BACKGROUND_GREEN    42
#define BACKGROUND_YELLOW   43
#define BACKGROUND_BLUE     44
#define BACKGROUND_MAGENTA  45
#define BACKGROUND_CYAN     46
#define BACKGROUND_WHITE    47

#define BACKGROUND_BRIGHT_BLACK   100
#define BACKGROUND_BRIGHT_RED     101
#define BACKGROUND_BRIGHT_GREEN   102
#define BACKGROUND_BRIGHT_YELLOW  103
#define BACKGROUND_BRIGHT_BLUE    104
#define BACKGROUND_BRIGHT_MAGENTA 105
#define BACKGROUND_BRIGHT_CYAN    106
#define BACKGROUND_BRIGHT_WHITE   107

#define STYLE_BOLD        1
#define STYLE_ITALIC      3
#define STYLE_UNDERLINE   4
#define STYLE_INVERSE     7
#define STYLE_HIDDEN      8

#define RESET             "\033[0m"

/* MAIN NAMESPACE */
namespace CGE {

	struct Vector2 {
		int x;
		int y;
	};
	
	struct Rectangle {
		Vector2 position;
		int height;
		int width;
	};

	/* CONSOLE GAME CLASS */
	class CG {
	private:
		int m_spaceHeight{};
		int m_spaceWidth{};
		bool m_drawT{ true };

	public:

		//
		// Sets the space of characters to be used.
		//
		void InitConsoleSpace(int height, int width, const char* consoleName) {
			m_spaceHeight = height;
			m_spaceWidth = width;

			std::string cmd{ "title " };
			cmd += consoleName;

			system(cmd.c_str());
		}

		//
		// Draws outline of the space.
		//
		void drawOutline(int color=COLOR_WHITE) {
			if (!m_drawT) return;

			std::cout << "\033[" << color << 'm';

			// Top border.
			std::cout << "+";
			for (int i{ 0 }; i < m_spaceWidth; i++) {
				std::cout << "-";
			}
			std::cout << "+\n";

			// Middle rows. (walls)
			for (int i{ 0 }; i < m_spaceHeight; i++) {
				std::cout << "|";
				for (int j{ 0 }; j < m_spaceWidth; j++) {
					std::cout << " ";
				}
				std::cout << "|\n";
			}

			// Bottom border.
			std::cout << "+";
			for (int i{ 0 }; i < m_spaceWidth; i++) {
				std::cout << "-";
			}
			std::cout << "+\n";

			std::cout << RESET;
		}

		//
		// Clears the console.
		//
		void clearConsole() {
			if (!m_drawT) return;

			system("cls");
		}

		//
		// Draws a rectangle in the space.
		//
		void drawRectangle(const Vector2& position, const int height, const int width, bool fill=true, int color=COLOR_WHITE) {
			if (!m_drawT) return;

			std::cout << "\033[" << color << 'm';

			for (int r{ 0 }; r < height; r++) {
				for (int c{ 0 }; c < width * 2; c++) {
					char ch;

					if (r == 0 || r == height - 1) {
						if (c == 0 || c == (width * 2) - 1) {
							ch = '+';
						}
						else {
							ch = '-';
						}
					}
					else {
						if (c == 0 || c == (width * 2) - 1) {
							ch = '|';
						}
						else {
							if (fill)
								ch = '#';
							else
								continue;
						}
					}

					if ((position.y + 2) + r < 2 || (position.y + 2) + r > m_spaceHeight + 1 || (position.x + 2) + c < 2 || (position.x + 2) + c > m_spaceWidth + 1)
						continue;

					std::cout << "\033[" << (position.y + 2) + r << ";" << (position.x + 2) + c << "H" << ch;
				}
			}

			std::cout << RESET;
		}

		//
		// Draws a rectangle in the space. (using Rectangle struct)
		//
		void drawRectangleRec(const Rectangle& rectangle, bool fill=true, int color=COLOR_WHITE) {
			if (!m_drawT) return;

			std::cout << "\033[" << color << 'm';

			for (int r{ 0 }; r < rectangle.height; r++) {
				for (int c{ 0 }; c < rectangle.width * 2; c++) {
					char ch;

					if (r == 0 || r == rectangle.height - 1) {
						if (c == 0 || c == (rectangle.width * 2) - 1) {
							ch = '+';
						}
						else {
							ch = '-';
						}
					}
					else {
						if (c == 0 || c == (rectangle.width * 2) - 1) {
							ch = '|';
						}
						else {
							if (fill)
								ch = '#';
							else
								continue;
						}
					}

					if ((rectangle.position.y + 2) + r < 2 || (rectangle.position.y + 2) + r > m_spaceHeight + 1 || (rectangle.position.x + 2) + c < 2 || (rectangle.position.x + 2) + c > m_spaceWidth + 1)
						continue;

					std::cout << "\033[" << (rectangle.position.y + 2) + r << ";" << (rectangle.position.x + 2) + c << "H" << ch;
				}
			}

			std::cout << RESET;
		}

		//
		// Draws a circle in the space.
		//
		void drawCircle(const Vector2& position, int radius, int color=COLOR_WHITE) {
			if (!m_drawT) return;

			std::cout << "\033[" << color << 'm';

			for (int y{ -radius }; y <= radius; y++) {
				for (int x{ -radius * 2 }; x <= radius * 2; x++) {
					if ((x / 2.0) * (x / 2.0) + y * y <= radius * radius) {
						if ((position.y + 2 + y) < 2 || (position.y + 2 + y) > m_spaceHeight + 1 || (position.x + 2 + x) < 2 || (position.x + 2 + x) > m_spaceWidth + 1)
							continue;

						std::cout << "\033[" << position.y + 2 + y << ";" << position.x + 2 + x << "H" << '*';
					}
				}
			}

			std::cout << RESET;
		}

		//
		// Checks if 2 rectangles are touching.
		// If they are it returns true else it returns false.
		//
		bool checkCollisionRecs(const Rectangle& rec1, const Rectangle& rec2) {
			if (!m_drawT) return false;

			return !(((rec1.position.x + rec1.width * 2 - 1) < rec2.position.x) || (rec1.position.x > (rec2.position.x + rec2.width * 2 - 1)) || ((rec1.position.y + rec1.height - 1) < rec2.position.y) || (rec1.position.y > (rec2.position.y + rec2.height - 1)));
		}

		//
		// Toggles console drawing. (e.g. pause/unpause game)
		//
		void toggleDrawing(bool c) {
			m_drawT = c;
		}

		//
		// Draws a simple line in the space.
		//
		void drawLine(Vector2 position, int height, int width, int color=COLOR_WHITE) {
			if (!m_drawT) return;

			std::cout << "\033[" << color << 'm';

			for (int i{ 0 }; i < height; i++) {
				for (int j{ 0 }; j < width; j++) {
					std::cout << "\033[" << position.y + 2 + i << ";" << position.x + 2 + j << "H" << '#';
				}
			}

			std::cout << RESET;
		}

		//
		// Draws a triangle in the space.
		//
		void drawTriangle(Vector2 position, int height, int width, bool fill=true, int color=COLOR_WHITE) {
			if (!m_drawT) return;

			std::cout << "\033[" << color << 'm';

			// thank you mr. chatgpt for the help.
			for (int i{ 0 }; i < height; i++) {
				int row_width{ (height > 1) ? (1 + ((width * 2 - 1 - 1) * i) / (height - 1)) : 1 };
				int left_offset{ (width * 2 - 1 - row_width) / 2 };

				for (int j{ 0 }; j < row_width; j++) {
					int draw_col{ (position.x + 2) + (left_offset + j) };
					int draw_row{ (position.y + 2) + i };
					char ch;

					if (i == 0) {
						ch = (height == 1) ? '+' : '^';
					}
					else if (i < (height - 1)) {
						if (j == 0)
							ch = '/';
						else if (j == (row_width - 1))
							ch = '\\';
						else
							if (fill)
								ch = '#';
							else
								continue;
					}
					else {
						if (j == 0 || j == (row_width - 1))
							ch = '+';
						else
							ch = '-';
					}

					if (draw_row < 2 || draw_row > (m_spaceHeight + 1) || draw_col < 2 || draw_col > (m_spaceWidth + 1))
						continue;

					std::cout << "\033[" << draw_row << ";" << draw_col << "H" << ch;
				}
			}

			std::cout << RESET;
		}

		//
		// Draws text in the space.
		//
		void drawText(Vector2 position, const char* text, int color=COLOR_WHITE) {
			if (!m_drawT) return;
			std::cout << "\033[" << color << 'm';

			std::cout << "\033[" << position.y + 2 << ";" << position.x + 2 << "H" << text;

			std::cout << RESET;
		}

	};

	//
	// Generates and returns a random number.
	// Uses std::random_device
	//
	int getRandomNumber(int min, int max) {
		std::mt19937 mt{ std::random_device{}() };
		if (min > max)
			std::swap(max, min);

		return std::uniform_int_distribution<int>{ min, max }(mt);
	}

	//
	// Shows a desktop notification.
	//
	void desktopNotify(const std::wstring& title, const std::wstring& message, const int time=5, const bool async=true) {
		NOTIFYICONDATA nid{};
		nid.cbSize = sizeof(nid);
		nid.uID = 1;
		nid.uFlags = NIF_INFO;
		nid.hWnd = GetConsoleWindow();
		nid.uCallbackMessage = WM_USER + 1;
		lstrcpy(nid.szInfoTitle, title.c_str());
		lstrcpy(nid.szInfo, message.c_str());
		nid.dwInfoFlags = NIIF_INFO;

		if (async) {
			std::thread([time, nid]() mutable {
				Shell_NotifyIcon(NIM_ADD, &nid);

				Sleep(time * 1000);

				Shell_NotifyIcon(NIM_DELETE, &nid);
			}).detach();
		}
		else {
			Shell_NotifyIcon(NIM_ADD, &nid);

			Sleep(time * 1000);

			Shell_NotifyIcon(NIM_DELETE, &nid);
		}
	}

	//
	// Writes given text to a given file.
	//
	void writeFile(const char* fileName, const char* contents) {
		std::ofstream oF(fileName);
		oF << contents;

		oF.close();
	}

	//
	// Reads and returns the contents of a given file.
	//
	std::string readFile(const char* fileName) {
		std::ifstream iF(fileName);
		std::string c((std::istreambuf_iterator<char>(iF)), std::istreambuf_iterator<char>());

		return c;
	}

	//
	// Pauses the current thread for certain amount of milliseconds.
	//
	void wait(const int milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

}
