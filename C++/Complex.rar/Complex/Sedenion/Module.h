#include <cmath>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <tuple>
#include <array>
#include <functional>
#include <stdexcept>
static constexpr const wchar_t SignBefore[] = LR"((-|\+|^))";
static constexpr const wchar_t UnsignedReal[] = LR"((\d+)(\.\d+|)([Ee](-|\+|)(\d+)|))";
static constexpr const wchar_t SignAfter[] = LR"((-|\+|$))";
inline std::wstring DoubleToString(double Number)
{
	std::wstringstream Result;
	Result << std::defaultfloat << std::setprecision(17) << Number;
	return std::regex_replace(Result.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
};
inline std::wstring Replace(const std::wstring& Input, const std::wstring& Search, const std::wstring& Replacement)
{
	std::wstring Result = Input;
	std::size_t Position = Result.find(Search);
	while (Position != std::wstring::npos)
	{
		Result = Result.replace(Position, Search.size(), Replacement);
		Position = Result.find(Search, Position + Replacement.size());
	}
	return Result;
};
inline std::wstring ToString(std::size_t Size, const double* Numbers, const std::wstring* Terms)
{
	std::wstringstream Result;
	bool First = true;
	for (std::size_t i = 0; i < Size; ++i)
	{
		if (Numbers[i] == 0) { continue; }
		if (Numbers[i] > 0 && First == false) { Result << L"+"; }
		else if (Numbers[i] == -1) { Result << L"-"; }
		if (Numbers[i] != 1 && Numbers[i] != -1) { Result << DoubleToString(Numbers[i]); }
		else if (Terms[i].empty()) { Result << L"1"; }
		if (!Terms[i].empty()) { Result << Terms[i]; }
		First = false;
	}
	if (First == true) { Result << L"0"; }
	return Result.str();
};
inline std::wstring AddGroup(const std::wstring& Pattern, bool Optional)
{
	return L"(" + Pattern + (Optional ? L"|" : L"") + L")";
};
inline std::wstring FollowedBy(const std::wstring& Pattern, const std::wstring& Text)
{
	return Pattern + L"(?=" + Text + L")";
};
inline std::wstring GetPattern(const std::wstring& Term)
{
	return FollowedBy(SignBefore + AddGroup(UnsignedReal, !Term.empty()), Term + SignAfter);
};
inline void ToNumbers(const std::wstring& Value, std::size_t Size, double* Numbers, const std::wstring* Terms)
{
	std::size_t Vaild = Value.length();
	if (Vaild == 0) { throw std::invalid_argument("The string is empty."); }
	for (std::size_t i = 0; i < Size; ++i)
	{
		double Data = 0;
		std::wstring Rest = Value;
		std::wsmatch Match;
		std::regex_constants::match_flag_type Flag = std::regex_constants::match_default;
		while (std::regex_search(Rest, Match, std::wregex(GetPattern(Terms[i])), Flag))
		{
			std::wstring Captured = Match.str();
			Vaild -= Captured.length() + Terms[i].length();
			if (Captured.empty() || Captured == L"+") { ++Data; }
			else if (Captured == L"-") { --Data; }
			else { Data += std::stod(Captured); }
			Rest = Match.suffix().str();
			Flag |= std::regex_constants::match_not_bol;
		}
		Numbers[i] = Data;
	}
	if (Vaild > 0) { throw std::invalid_argument("The string is invalid."); }
};
