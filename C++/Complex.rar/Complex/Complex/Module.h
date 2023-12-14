#include <cmath>
#include <limits>
#include <numbers>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <tuple>
#include <array>
#include <algorithm>
#include <stdexcept>
#include "Cayley Dickson Algebra.h"
inline constexpr const wchar_t SignBefore[] = LR"((-|\+|^))";
inline constexpr const wchar_t UnsignedReal[] = LR"((\d+)(\.\d+|)([Ee](-|\+|)(\d+)|))";
inline constexpr const wchar_t SignAfter[] = LR"((-|\+|$))";
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
template <std::size_t I = 0, std::size_t N> requires (I <= N)
std::wstring ToString(std::wstringstream& Result, bool& First, const std::array<double, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	if constexpr (I == N)
	{
		if (First == true) { Result << L"0"; }
		return Result.str();
	}
	else
	{
		if (std::get<I>(Numbers) != 0)
		{
			if (std::get<I>(Numbers) > 0 && First == false) { Result << L"+"; }
			else if (std::get<I>(Numbers) == -1) { Result << L"-"; }
			if (std::get<I>(Numbers) != 1 && std::get<I>(Numbers) != -1) { Result << DoubleToString(std::get<I>(Numbers)); }
			else if (std::get<I>(Terms).empty()) { Result << L"1"; }
			if (!std::get<I>(Terms).empty()) { Result << std::get<I>(Terms); }
			First = false;
		}
		return ToString<I + 1, N>(Result, First, Numbers, Terms);
	}
};
template <std::size_t N>
std::wstring ToString(const std::array<double, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	std::wstringstream Result;
	bool First = true;
	return ToString(Result, First, Numbers, Terms);
};
template <typename Args, std::size_t... I> requires (std::tuple_size_v<Args> == 2 * sizeof...(I))
std::wstring ToString(Args&& args, std::integer_sequence<std::size_t, I...>)
{
	std::array<double, sizeof...(I)> Numbers{ std::get<2 * I>(args)... };
	std::array<std::wstring, sizeof...(I)> Terms{ std::get<2 * I + 1>(args)... };
	return ToString(Numbers, Terms);
};
template <typename... Args>
std::wstring ToString(Args&&... args) requires (sizeof...(Args) % 2 == 0)
{
	return ToString(std::forward_as_tuple(std::forward<Args>(args)...), std::make_index_sequence<sizeof...(Args) / 2>{});
};
template <std::size_t I = 0, std::size_t N> requires (I <= N)
void ToNumbers(const std::wstring& Value, std::size_t& Vaild, const std::array<double*, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	if constexpr (I < N)
	{
		double Data = 0;
		std::wstring Rest = Value;
		std::wsmatch Match;
		std::regex_constants::match_flag_type Flag = std::regex_constants::match_default;
		while (std::regex_search(Rest, Match, std::wregex(GetPattern(std::get<I>(Terms))), Flag))
		{
			std::wstring Captured = Match.str();
			Vaild -= Captured.length() + std::get<I>(Terms).length();
			if (Captured.empty() || Captured == L"+") { ++Data; }
			else if (Captured == L"-") { --Data; }
			else { Data += std::stod(Captured); }
			Rest = Match.suffix().str();
			Flag |= std::regex_constants::match_not_bol;
		}
		*std::get<I>(Numbers) = Data;
		ToNumbers<I + 1, N>(Value, Vaild, Numbers, Terms);
	}
	else
	{
		if (Vaild > 0) { throw std::invalid_argument("The string is invalid."); }
	}
};
template <std::size_t N>
void ToNumbers(const std::wstring& Value, const std::array<double*, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	std::size_t Vaild = Value.length();
	if (Vaild == 0) { throw std::invalid_argument("The string is empty."); }
	ToNumbers(Value, Vaild, Numbers, Terms);
};
template <typename Args, std::size_t... I> requires (std::tuple_size_v<Args> == 2 * sizeof...(I))
void ToNumbers(const std::wstring& Value, Args&& args, std::integer_sequence<std::size_t, I...>)
{
	std::array<double*, sizeof...(I)> Numbers{ &std::get<2 * I>(args)... };
	std::array<std::wstring, sizeof...(I)> Terms{ std::get<2 * I + 1>(args)... };
	ToNumbers(Value, Numbers, Terms);
};
template <typename... Args> requires (sizeof...(Args) % 2 == 0)
void ToNumbers(const std::wstring& Value, Args&&... args)
{
	ToNumbers(Value, std::forward_as_tuple(args...), std::make_index_sequence<sizeof...(Args) / 2>{});
};
template <typename T> requires (sizeof(T) % sizeof(double) == 0)
inline constexpr std::size_t Period = sizeof(T) / sizeof(double);
template <std::size_t Length, bool Shift> requires (Length > 0)
void Adjust(std::size_t& Index) noexcept
{
	Index %= Length;
	if constexpr (Shift)
	{
		if (Index == 0) { Index = Length; }
	}
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
