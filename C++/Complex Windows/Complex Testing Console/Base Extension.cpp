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
#include <conio.h>
#include <Windows.h>
#include <memory>
#include <string>
#include <iostream>
#include "Base.h"
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
	ConsoleColor GetForegroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return static_cast<ConsoleColor>(csbiInfo.wAttributes % 16);
	};
	ConsoleColor GetBackgroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return static_cast<ConsoleColor>((csbiInfo.wAttributes - (csbiInfo.wAttributes % 16)) / 16);
	};
	std::wstring GetTitle()
	{
		static constexpr const std::size_t stack_capacity = 64;
		{
			wchar_t stack_result[stack_capacity];
			GetConsoleTitleW(stack_result, static_cast<DWORD>(stack_capacity));
			if (wcslen(stack_result) + 1 < stack_capacity) { return stack_result; }
		}
		for (std::size_t heap_capacity = 256; true; heap_capacity += 128)
		{
			std::unique_ptr<wchar_t[]> heap_result = std::make_unique<wchar_t[]>(heap_capacity);
			GetConsoleTitleW(heap_result.get(), static_cast<DWORD>(heap_capacity));
			if (wcslen(heap_result.get()) + 1 < heap_capacity) { return heap_result.get(); }
		}
	};
	void SetForegroundColor(ConsoleColor Color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(Color) + static_cast<WORD>(GetBackgroundColor()) * 16); };
	void SetBackgroundColor(ConsoleColor Color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(GetForegroundColor()) + static_cast<WORD>(Color) * 16); };
	void SetTitle(const std::wstring& Text) { SetConsoleTitleW(Text.c_str()); };
	void PressAnyKey()
	{
		std::fflush(stdout);
		wint_t result = _getwch();
	};
	void Clear()
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
}
int main()
{
	ComplexTestingConsole::Base::Main();
	return EXIT_SUCCESS;
};
