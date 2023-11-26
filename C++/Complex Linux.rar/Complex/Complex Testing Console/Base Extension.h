#pragma once
/* ============= */
/*               */
/*   Extension   */
/*               */
/* ============= */
#include <string>
namespace CmplxConExt
{
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
	ConsoleColor GetForegroundColor();
	ConsoleColor GetBackgroundColor();
	std::wstring GetTitle();
	void SetForegroundColor(ConsoleColor Color);
	void SetBackgroundColor(ConsoleColor Color);
	void SetTitle(const std::wstring& Text);
	void Clear();
	void PressAnyKey();
}
