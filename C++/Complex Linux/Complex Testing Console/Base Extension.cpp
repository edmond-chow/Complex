/*
 *   Copyright 2022 Edmond Chow
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
/* ============= */
/*               */
/*   Extension   */
/*               */
/* ============= */
#include <unistd.h>
#include <termios.h>
#include <string>
#include <iostream>
#include "Base.h"
namespace CmplxConExt
{
	static char getch()
	{
		if (std::fflush(stdout) != 0) { return EOF; }
		char result{};
		termios captured{};
		tcgetattr(0, &captured);
		termios current = captured;
		current.c_lflag &= ~ICANON;
		current.c_lflag &= ~ECHO;
		current.c_cc[VTIME] = 0;
		current.c_cc[VMIN] = 1;
		tcsetattr(0, TCSANOW, &current);
		ssize_t count = read(0, &result, 1);
		if (count == 0 || count == -1) { result = EOF; }
		tcsetattr(0, TCSANOW, &captured);
		return result;
	};
	enum class ConsoleColor : std::uint8_t
	{
		Default = 0xff,
		Black = 0,
		DarkBlue = 1,
		DarkGreen = 2,
		DarkCyan = 3,
		DarkRed = 4,
		DarkMagenta = 5,
		DarkYellow = 6,
		Gray = 7,
		DarkGray = 8,
		Blue = 9,
		Green = 10,
		Cyan = 11,
		Red = 12,
		Magenta = 13,
		Yellow = 14,
		White = 15,
	};
	static thread_local ConsoleColor ForegroundColor{ ConsoleColor::Gray };
	static thread_local ConsoleColor BackgroundColor{ ConsoleColor::Default };
	static thread_local std::wstring Title{ L"" };
	ConsoleColor GetForegroundColor() { return ForegroundColor; };
	ConsoleColor GetBackgroundColor() { return BackgroundColor; };
	std::wstring GetTitle() { return Title; };
	void SetForegroundColor(ConsoleColor Color)
	{
		switch (Color)
		{
		case ConsoleColor::Black:
			std::wcout << L"\033[30m";
			break;
		case ConsoleColor::DarkRed:
			std::wcout << L"\033[31m";
			break;
		case ConsoleColor::DarkGreen:
			std::wcout << L"\033[32m";
			break;
		case ConsoleColor::DarkYellow:
			std::wcout << L"\033[33m";
			break;
		case ConsoleColor::DarkBlue:
			std::wcout << L"\033[34m";
			break;
		case ConsoleColor::DarkMagenta:
			std::wcout << L"\033[35m";
			break;
		case ConsoleColor::DarkCyan:
			std::wcout << L"\033[36m";
			break;
		case ConsoleColor::Gray:
			std::wcout << L"\033[37m";
			break;
		case ConsoleColor::DarkGray:
			std::wcout << L"\033[90m";
			break;
		case ConsoleColor::Red:
			std::wcout << L"\033[91m";
			break;
		case ConsoleColor::Green:
			std::wcout << L"\033[92m";
			break;
		case ConsoleColor::Yellow:
			std::wcout << L"\033[93m";
			break;
		case ConsoleColor::Blue:
			std::wcout << L"\033[94m";
			break;
		case ConsoleColor::Magenta:
			std::wcout << L"\033[95m";
			break;
		case ConsoleColor::Cyan:
			std::wcout << L"\033[96m";
			break;
		case ConsoleColor::White:
			std::wcout << L"\033[97m";
			break;
		default:
			std::wcout << L"\033[39m";
			return;
		}
		ForegroundColor = Color;
	};
	void SetBackgroundColor(ConsoleColor Color)
	{
		switch (Color)
		{
		case ConsoleColor::Black:
			std::wcout << L"\033[40m";
			break;
		case ConsoleColor::DarkRed:
			std::wcout << L"\033[41m";
			break;
		case ConsoleColor::DarkGreen:
			std::wcout << L"\033[42m";
			break;
		case ConsoleColor::DarkYellow:
			std::wcout << L"\033[43m";
			break;
		case ConsoleColor::DarkBlue:
			std::wcout << L"\033[44m";
			break;
		case ConsoleColor::DarkMagenta:
			std::wcout << L"\033[45m";
			break;
		case ConsoleColor::DarkCyan:
			std::wcout << L"\033[46m";
			break;
		case ConsoleColor::Gray:
			std::wcout << L"\033[47m";
			break;
		case ConsoleColor::DarkGray:
			std::wcout << L"\033[100m";
			break;
		case ConsoleColor::Red:
			std::wcout << L"\033[101m";
			break;
		case ConsoleColor::Green:
			std::wcout << L"\033[102m";
			break;
		case ConsoleColor::Yellow:
			std::wcout << L"\033[103m";
			break;
		case ConsoleColor::Blue:
			std::wcout << L"\033[104m";
			break;
		case ConsoleColor::Magenta:
			std::wcout << L"\033[105m";
			break;
		case ConsoleColor::Cyan:
			std::wcout << L"\033[106m";
			break;
		case ConsoleColor::White:
			std::wcout << L"\033[107m";
			break;
		default:
			std::wcout << L"\033[49m";
			return;
		}
		BackgroundColor = Color;
	};
	void SetTitle(const std::wstring& Text)
	{
		std::wcout << L"\033]0;" << Text << L"\007";
		Title = Text;
	};
	void PressAnyKey() { getch(); };
	void Clear() { [[maybe_unused]]int result = std::system("clear"); };
}
int main()
{
	ComplexTestingConsole::Base::Main();
	return EXIT_SUCCESS;
};
