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
#include <cstdint>
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
		CONSOLE_SCREEN_BUFFER_INFO CsbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CsbiInfo);
		return static_cast<ConsoleColor>(CsbiInfo.wAttributes % 16);
	};
	ConsoleColor GetBackgroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO CsbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CsbiInfo);
		return static_cast<ConsoleColor>((CsbiInfo.wAttributes - (CsbiInfo.wAttributes % 16)) / 16);
	};
	std::wstring GetTitle()
	{
		static constexpr const std::size_t StackCapacity = 64;
		{
			wchar_t StackResult[StackCapacity];
			GetConsoleTitleW(StackResult, static_cast<DWORD>(StackCapacity));
			if (wcslen(StackResult) + 1 < StackCapacity) { return StackResult; }
		}
		for (std::size_t HeapCapacity = 256; true; HeapCapacity += 128)
		{
			std::unique_ptr<wchar_t[]> HeapResult = std::make_unique<wchar_t[]>(HeapCapacity);
			GetConsoleTitleW(HeapResult.get(), static_cast<DWORD>(HeapCapacity));
			if (wcslen(HeapResult.get()) + 1 < HeapCapacity) { return HeapResult.get(); }
		}
	};
	void SetForegroundColor(ConsoleColor Col)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(Col) + static_cast<WORD>(GetBackgroundColor()) * 16);
	};
	void SetBackgroundColor(ConsoleColor Col)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(GetForegroundColor()) + static_cast<WORD>(Col) * 16);
	};
	void SetTitle(const std::wstring& Tle)
	{
		SetConsoleTitleW(Tle.data());
	};
	void PressAnyKey()
	{
		std::fflush(stdout);
		wint_t Result = _getwch();
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
