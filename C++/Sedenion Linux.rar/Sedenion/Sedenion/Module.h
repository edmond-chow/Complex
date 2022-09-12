#include <string>
#include <regex>
#include <sstream>
#include <tuple>
#include <array>
std::wstring ToString(std::size_t Size, const double* Numbers, const std::wstring* Terms)
{
	std::wstringstream TheString;
	for (std::size_t i = 0; i < Size; ++i)
	{
		std::wstring Replace = std::to_wstring(Numbers[i]);
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
	std::wstring RetString;
	std::getline(TheString, RetString);
	RetString = std::regex_replace(RetString, std::wregex(L"^$"), L"0");
	RetString = std::regex_replace(RetString, std::wregex(L"^\\+"), L"");
	return RetString;
};
std::wstring GetInitTermRegexString(std::size_t Size, const std::wstring* Terms)
{
	std::wstringstream TheString;
	TheString << L"(^|\\+|-)(";
	for (std::size_t i = 0; i < Size; ++i)
	{
		if (Terms[i].length() > 0) { TheString << L"(?=" << Terms[i] << L")|"; }
	}
	std::wstring RetString;
	std::getline(TheString, RetString);
	return std::regex_replace(RetString, std::wregex(L"\\)\\|$"), L"))");
};
inline std::wstring GetRegexString(const std::wstring& Term, bool With)
{
	static constexpr const wchar_t RealRegExp[] = L"(-|\\+|)(\\d+)(\\.\\d+|)([Ee](-|\\+|)(\\d+)|)";
	static constexpr const wchar_t NotOthers[] = L"(-|\\+|$)";
	return std::wstring().append(RealRegExp).append(With ? Term : L"").append(L"(?=").append(With ? L"" : Term).append(NotOthers).append(L")");
};
bool TestForValid(const std::wstring& Value, std::size_t Size, const std::wstring* Terms)
{
	std::wstring Test(Value);
	for (std::size_t i = 0; i < Size; ++i)
	{
		std::wregex Regex(GetRegexString(Terms[i], true));
		Test = std::regex_replace(Test, Regex, L"");
	}
	return Test.length() == 0;
};
void SetForValue(const std::wstring& TheValue, std::size_t Size, double* Numbers, const std::wstring* Terms)
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
void ToNumbers(const std::wstring& Value, std::size_t Size, double* Numbers, const std::wstring* Terms)
{
	std::wstring TheValue = std::regex_replace(Value, std::wregex(L" "), L"");
	std::wsmatch Match;
	std::regex_search(TheValue, Match, std::wregex(GetInitTermRegexString(Size, Terms)));
	TheValue = std::regex_replace(TheValue, std::wregex(GetInitTermRegexString(Size, Terms)), Match.str() + L"1");
	if (!TestForValid(TheValue, Size, Terms)) { throw std::exception(); }
	if (TheValue.length() == 0) { throw std::exception(); }
	SetForValue(TheValue, Size, Numbers, Terms);
};
