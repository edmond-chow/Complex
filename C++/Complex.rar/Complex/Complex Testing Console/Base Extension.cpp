/* ============= */
/*               */
/*   Extension   */
/*               */
/* ============= */
#include <conio.h>
#include <Windows.h>
#include <string>
#include <iostream>
#pragma push_macro("max")
#undef max
#include "Base.h"
#pragma pop_macro("max")
namespace CmplxConExt
{
	enum class ConsoleColor : std::uint8_t
	{
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
	ConsoleColor getForegroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return static_cast<ConsoleColor>(csbiInfo.wAttributes % 16);
	};
	ConsoleColor getBackgroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return static_cast<ConsoleColor>((csbiInfo.wAttributes - (csbiInfo.wAttributes % 16)) / 16);
	};
	std::wstring getTitle()
	{
		constexpr const std::size_t stack_size = 64;
		wchar_t stack_str[stack_size];
		GetConsoleTitleW(stack_str, static_cast<DWORD>(stack_size));
		if (wcslen(stack_str) + 1 < stack_size) { return std::wstring(stack_str); }
		std::size_t capacity = 256;
		const std::size_t increase = 128;
		wchar_t* heap_str = nullptr;
		while (true)
		{
			heap_str = new wchar_t[capacity];
			GetConsoleTitleW(heap_str, static_cast<DWORD>(capacity));
			if (wcslen(heap_str) + 1 < capacity) { return std::wstring(heap_str); }
			delete[] heap_str;
			capacity += increase;
		}
	};
	void setForegroundColor(ConsoleColor color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color) + static_cast<WORD>(getBackgroundColor()) * 16); };
	void setBackgroundColor(ConsoleColor color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(getForegroundColor()) + static_cast<WORD>(color) * 16); };
	void setTitle(const std::wstring& title) { SetConsoleTitleW(title.c_str()); };
	void clear()
	{
		COORD TopLeft{ 0, 0 };
		HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO Screen;
		GetConsoleScreenBufferInfo(Console, &Screen);
		DWORD Written;
		FillConsoleOutputCharacterW(Console, L' ', Screen.dwSize.X * Screen.dwSize.Y, TopLeft, &Written);
		FillConsoleOutputAttribute(Console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, Screen.dwSize.X * Screen.dwSize.Y, TopLeft, &Written);
		SetConsoleCursorPosition(Console, TopLeft);
	};
	void pressAnyKey() { int ret = _getwch(); };
	static const struct Original {
		ConsoleColor ForegroundColor;
		ConsoleColor BackgroundColor;
		std::wstring Title;
		Original() : ForegroundColor(getForegroundColor()), BackgroundColor(getBackgroundColor()), Title(getTitle()) {};
		~Original()
		{
			setForegroundColor(ForegroundColor);
			setBackgroundColor(BackgroundColor);
			setTitle(Title);
		};
	} Store{};
}
int main()
{
	ComplexTestingConsole::Base::Main();
	return EXIT_SUCCESS;
};
