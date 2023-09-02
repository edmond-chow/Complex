#include <cmath>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <tuple>
#include <array>
#include <functional>
#include <stdexcept>
template <typename CharT, typename Traits, typename Allocator, typename RegexTraits, typename FuncT>
std::basic_string<CharT, Traits, Allocator> regex_search_and_replace(const std::basic_string<CharT, Traits, Allocator>& String, const std::basic_regex<CharT, RegexTraits>& Regex, FuncT Function)
{
	using StringT = std::basic_string<CharT, Traits, Allocator>;
	StringT Input = String;
	StringT Output{};
	bool NotBol = false;
	while (Input.empty() == false)
	{
		bool matched = false;
		std::size_t Cursor = 0;
		while (Cursor <= Input.size())
		{
			std::regex_constants::match_flag_type Type = std::regex_constants::match_default;
			if (NotBol == true) { Type = Type | std::regex_constants::match_not_bol; }
			if (Cursor > 0) { Type = Type | std::regex_constants::match_not_eol; }
			std::match_results<typename StringT::const_iterator> Match;
			StringT SubInput = Input.substr(0, Input.size() - Cursor);
			if (std::regex_search(SubInput, Match, Regex, Type))
			{
				Output.append(Match.prefix().str()).append(Function(std::cref(Match)));
				if (Match.str().empty() == false)
				{
					Input = Match.suffix().str();
					NotBol = true;
					matched = true;
				}
				break;
			}
			++Cursor;
		}
		if (matched == false)
		{
			Output.append(Input.substr(0, 1));
			Input = Input.substr(1);
			NotBol = true;
		}
	}
	return Output;
};
inline std::wstring double_to_wstring(double Number)
{
	std::wstringstream TheString;
	TheString << std::defaultfloat << std::setprecision(17) << Number;
	return std::regex_replace(TheString.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
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
		std::wstring Replace = double_to_wstring(std::get<I>(Numbers));
		if (std::get<I>(Numbers) > 0)
		{
			if (std::get<I>(Terms).length() > 0) { Replace = std::regex_replace(Replace, std::wregex(L"^1$"), L""); }
			TheString << L'+' << Replace << std::get<I>(Terms);
		}
		else if (std::get<I>(Numbers) < 0)
		{
			if (std::get<I>(Terms).length() > 0) { Replace = std::regex_replace(Replace, std::wregex(L"^-1$"), L"-"); }
			TheString << Replace << std::get<I>(Terms);
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
template <std::size_t I = 0, std::size_t N> requires (I <= N)
std::wstring GetInitTermRegexString(std::wstringstream& TheString, const std::array<std::wstring, N>& Terms)
{
	if constexpr (I == N) { return std::regex_replace(TheString.str(), std::wregex(L"\\)\\|$"), L"))"); }
	else
	{
		if (std::get<I>(Terms).length() > 0) { TheString << L"(?=" << std::get<I>(Terms) << L")|"; }
		return GetInitTermRegexString<I + 1, N>(TheString, Terms);
	}
};
template <std::size_t N>
std::wstring GetInitTermRegexString(const std::array<std::wstring, N>& Terms)
{
	std::wstringstream TheString;
	TheString << L"(^|\\+|-)(";
	return GetInitTermRegexString(TheString, Terms);
};
inline std::wstring GetRegexString(const std::wstring& Term, bool With)
{
	static constexpr const wchar_t RealRegExp[] = L"(-|\\+|)(\\d+)(\\.\\d+|)([Ee](-|\\+|)(\\d+)|)";
	static constexpr const wchar_t NotOthers[] = L"(-|\\+|$)";
	return std::wstring().append(RealRegExp).append(With ? Term : L"").append(L"(?=").append(With ? L"" : Term).append(NotOthers).append(L")");
};
template <std::size_t I = 0, std::size_t N> requires (I <= N)
bool TestForValid(std::wstring&& Test, const std::array<std::wstring, N>& Terms)
{
	if constexpr (I == N) { return Test.length() == 0; }
	else
	{
		std::wregex Regex(GetRegexString(std::get<I>(Terms), true));
		Test = std::regex_replace(Test, Regex, L"");
		return TestForValid<I + 1, N>(std::move(Test), Terms);
	}
};
template <std::size_t N>
bool TestForValid(const std::wstring& Value, const std::array<std::wstring, N>& Terms)
{
	return TestForValid(std::wstring(Value), Terms);
};
template <std::size_t I = 0, std::size_t N> requires (I <= N)
void SetForValue(const std::wstring& TheValue, const std::array<double*, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	if constexpr (I < N)
	{
		double Data = 0;
		std::wregex Regex(GetRegexString(std::get<I>(Terms), false));
		std::wstring TheString = TheValue;
		std::wsmatch Match;
		while (std::regex_search(TheString, Match, Regex))
		{
			Data += std::stod(Match.str());
			TheString = Match.suffix().str();
		}
		*std::get<I>(Numbers) = Data;
		SetForValue<I + 1, N>(TheValue, Numbers, Terms);
	}
};
template <std::size_t N>
void ToNumbers(const std::wstring& Value, const std::array<double*, N>& Numbers, const std::array<std::wstring, N>& Terms)
{
	std::wstring TheValue = std::regex_replace(Value, std::wregex(L" "), L"");
	TheValue = regex_search_and_replace(TheValue, std::wregex(GetInitTermRegexString(Terms)), [](const std::wsmatch& Match) -> std::wstring {
		return Match.str() + L"1";
	});
	if (!TestForValid(TheValue, Terms)) { throw std::invalid_argument("The string is invalid."); }
	if (TheValue.length() == 0) { throw std::invalid_argument("The string is empty."); }
	SetForValue(TheValue, Numbers, Terms);
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
