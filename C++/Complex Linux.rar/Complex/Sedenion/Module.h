#include <cmath>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <tuple>
#include <array>
#include <functional>
#include <stdexcept>
inline std::wstring double_to_wstring(double Number)
{
	std::wstringstream TheString;
	TheString << std::defaultfloat << std::setprecision(17) << Number;
	return std::regex_replace(TheString.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
};
inline std::wstring ToString(std::size_t Size, const double* Numbers, const std::wstring* Terms)
{
	std::wstringstream TheString;
	for (std::size_t i = 0; i < Size; ++i)
	{
		std::wstring Replace = double_to_wstring(Numbers[i]);
		if (Numbers[i] > 0)
		{
			if (Terms[i].length() > 0) { Replace = std::regex_replace(Replace, std::wregex(L"^1$"), L""); }
			TheString << L'+' << Replace << Terms[i];
		}
		else if (Numbers[i] < 0)
		{
			if (Terms[i].length() > 0) { Replace = std::regex_replace(Replace, std::wregex(L"^-1$"), L"-"); }
			TheString << Replace << Terms[i];
		}
	}
	std::wstring RetString = TheString.str();
	RetString = std::regex_replace(RetString, std::wregex(L"^$"), L"0");
	RetString = std::regex_replace(RetString, std::wregex(L"^\\+"), L"");
	return RetString;
};
inline std::wstring GetInitTermRegexString(std::wstring* TheValue, std::size_t Size, const std::wstring* Terms)
{
	for (std::size_t i = 0; i < Size; ++i)
	{
		if (Terms[i] != L"")
		{
			std::wstring PlusSour = L"+" + Terms[i];
			std::wstring PlusRepl = L"+1" + Terms[i];
			std::size_t PlusPos = TheValue->find(PlusSour);
			while (PlusPos != std::wstring::npos)
			{
				*TheValue = TheValue->replace(PlusPos, PlusSour.size(), PlusRepl);
				PlusPos = TheValue->find(PlusSour, PlusPos + PlusRepl.size());
			}
			std::wstring MinusSour = L"-" + Terms[i];
			std::wstring MinusRepl = L"-1" + Terms[i];
			std::size_t MinusPos = TheValue->find(MinusSour);
			while (MinusPos != std::wstring::npos)
			{
				*TheValue = TheValue->replace(MinusPos, MinusSour.size(), MinusRepl);
				MinusPos = TheValue->find(MinusSour, MinusPos + MinusRepl.size());
			}
		}
	}
	return *TheValue;
};
inline std::wstring GetInitTermRegexString(const std::wstring& Value, std::size_t Size, const std::wstring* Terms)
{
	std::wstring RetString = (Value[0] != L'-' && Value[0] != L'+' ? L"+" : L"") + Value;
	return GetInitTermRegexString(&RetString, Size, Terms);
};
inline std::wstring GetRegexString(const std::wstring& Term, bool With)
{
	static constexpr const wchar_t RealRegExp[] = L"(-|\\+|^)(\\d+)(\\.\\d+|)([Ee](-|\\+|)(\\d+)|)";
	static constexpr const wchar_t NotOthers[] = L"(-|\\+|$)";
	return std::wstring().append(RealRegExp).append(With ? Term : L"").append(L"(?=").append(With ? L"" : Term).append(NotOthers).append(L")");
};
inline bool TestForValid(const std::wstring& Value, std::size_t Size, const std::wstring* Terms)
{
	std::wstring Test(Value);
	for (std::size_t i = 0; i < Size; ++i)
	{
		std::wregex Regex(GetRegexString(Terms[i], true));
		Test = std::regex_replace(Test, Regex, L"");
	}
	return Test.length() == 0;
};
inline void SetForValue(const std::wstring& TheValue, std::size_t Size, double* Numbers, const std::wstring* Terms)
{
	for (std::size_t i = 0; i < Size; ++i)
	{
		double Data = 0;
		std::wregex Regex(GetRegexString(Terms[i], false));
		std::wstring TheString = TheValue;
		std::wsmatch Match;
		while (std::regex_search(TheString, Match, Regex))
		{
			Data += std::stod(Match.str());
			TheString = Match.suffix().str();
		}
		Numbers[i] = Data;
	}
};
inline void ToNumbers(const std::wstring& Value, std::size_t Size, double* Numbers, const std::wstring* Terms)
{
	std::wstring TheValue = GetInitTermRegexString(std::regex_replace(Value, std::wregex(L" "), L""), Size, Terms);
	if (!TestForValid(TheValue, Size, Terms)) { throw std::invalid_argument("The string is invalid."); }
	if (TheValue.length() == 0) { throw std::invalid_argument("The string is empty."); }
	SetForValue(TheValue, Size, Numbers, Terms);
};
