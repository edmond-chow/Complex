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
	std::wstringstream TheString;
	TheString << std::defaultfloat << std::setprecision(17) << Number;
	return std::regex_replace(TheString.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
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
std::wstring ToString(std::wstringstream& TheString, const std::array<double, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	if constexpr (I == N)
	{
		std::wstring RetString = TheString.str();
		RetString = std::regex_replace(RetString, std::wregex(L"^$"), L"0");
		RetString = std::regex_replace(RetString, std::wregex(L"^\\+"), L"");
		return RetString;
	}
	else
	{
		std::wstring Result = DoubleToString(std::get<I>(Numbers));
		if (std::get<I>(Numbers) > 0)
		{
			if (std::get<I>(Terms).length() > 0) { Result = std::regex_replace(Result, std::wregex(L"^1$"), L""); }
			TheString << L'+' << Result << std::get<I>(Terms);
		}
		else if (std::get<I>(Numbers) < 0)
		{
			if (std::get<I>(Terms).length() > 0) { Result = std::regex_replace(Result, std::wregex(L"^-1$"), L"-"); }
			TheString << Result << std::get<I>(Terms);
		}
		return ToString<I + 1, N>(TheString, Numbers, Terms);
	}
};
template <std::size_t N>
std::wstring ToString(const std::array<double, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	std::wstringstream TheString;
	return ToString(TheString, Numbers, Terms);
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
template <std::size_t I = 0, std::size_t N> requires (I <= N)
void ToNumbers(const std::wstring& Replaced, std::size_t& Vaild, const std::array<double*, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	if constexpr (I < N)
	{
		double Data = 0;
		std::wregex Regex(GetPattern(std::get<I>(Terms)));
		std::wstring Rest = Replaced;
		std::wsmatch Match;
		std::regex_constants::match_flag_type Flag = std::regex_constants::match_default;
		while (std::regex_search(Rest, Match, Regex, Flag))
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
		ToNumbers<I + 1, N>(Replaced, Vaild, Numbers, Terms);
	}
	else
	{
		if (Vaild > 0) { throw std::invalid_argument("The string is invalid."); }
	}
};
template <std::size_t N>
void ToNumbers(const std::wstring& Value, const std::array<double*, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	std::wstring Replaced = Replace(Value, L" ", L"");
	std::size_t Vaild = Replaced.length();
	if (Vaild == 0) { throw std::invalid_argument("The string is empty."); }
	ToNumbers(Replaced, Vaild, Numbers, Terms);
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
struct PeriodImpl
{
public:
	static constexpr const std::int64_t Size = sizeof(T) / sizeof(double);
};
template <typename T>
inline constexpr std::int64_t Period = PeriodImpl<T>::Size;
inline std::int64_t PeriodShift(std::int64_t Index, std::int64_t Length)
{
	--Index;
	Index %= Length;
	return ++Index;
};
