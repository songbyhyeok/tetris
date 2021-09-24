#include "ConsoleHelper.h"

void ConsoleHelper::SetCursorPosition(int x, int y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(output, pos);
}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, static_cast<int>(color));
}

void ConsoleHelper::ShowConsoleCursor(bool flag)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(output, &cursorInfo);
}


void ConsoleHelper::UpLinePrompt(int count)
{
	for (int i = 0; i < count; ++i) {
		cout << "\33[2K"; //line clear
		cout << "\x1b[A"; //up line (ESC [ A) must be support VT100 escape seq
	}
}