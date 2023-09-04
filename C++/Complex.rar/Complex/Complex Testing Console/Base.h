#pragma once
#ifndef CMPLX_UNIT_TEST
#define CMPLX_UNIT_TEST
#include <cstdint>
#include <array>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <functional>
inline std::int64_t wtoi64_t(const wchar_t* str)
{
	if (str[0] == L'\0') { throw std::invalid_argument("The string cannot not be converted as an integer."); }
	const wchar_t* number = str;
	if (str[0] == L'-' || str[0] == L'+')
	{
		if (str[1] == L'\0') { throw std::invalid_argument("The string cannot not be converted as an integer."); }
		++number;
	}
	std::size_t number_size = 0;
	const wchar_t* number_end = number;
	while (*number_end != L'\0')
	{
		if (static_cast<std::uint16_t>(*number_end) < 48 || static_cast<std::uint16_t>(*number_end) > 57) { throw std::invalid_argument("The string cannot not be converted as an integer."); }
		++number_end;
		++number_size;
	}
	const wchar_t wcharsPlus[] = L"9223372036854775807";
	const wchar_t wcharsMinus[] = L"9223372036854775808";
	wchar_t digitsCheck[20]{ L'\0' };
	if (number_size > 20)
	{
		throw std::out_of_range("An integer is exceeded the limit.");
	}
	std::int64_t accumulate = 1;
	std::int64_t output = 0;
	for (std::size_t i = 0; i < number_size; ++i)
	{
		wchar_t wchar = number[number_size - i - 1];
		digitsCheck[number_size - i - 1] = wchar;
		std::uint16_t digit = static_cast<std::uint16_t>(wchar) - 48;
		if (str[0] == L'-') { output -= digit * accumulate; }
		else { output += digit * accumulate; }
		accumulate = accumulate * 10;
	}
	if (number_size == 20)
	{
		for (std::size_t i = 0; i < 20; ++i)
		{
			if (str[0] == L'-')
			{
				if (digitsCheck[i] < wcharsMinus[i]) { break; }
				else if (digitsCheck[i] > wcharsMinus[i]) { throw std::out_of_range("An integer is exceeded the limit."); }
			}
			else
			{
				if (digitsCheck[i] < wcharsPlus[i]) { break; }
				else if (digitsCheck[i] > wcharsPlus[i]) { throw std::out_of_range("An integer is exceeded the limit."); }
			}
		}
	}
	return output;
};
inline std::int64_t stoi64_t(const std::wstring& str)
{
	std::wstring result = std::regex_replace(str, std::wregex(L" "), L"");
	return wtoi64_t(result.c_str());
};
inline std::wstring double_to_wstring(double Number)
{
	std::wstringstream TheString;
	TheString << std::defaultfloat << std::setprecision(17) << Number;
	return std::regex_replace(TheString.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
};
template <typename T>
inline std::wstring to_wstring(T o) { return T::GetString(o); };
template <>
inline std::wstring to_wstring<double>(double o) { return double_to_wstring(o); };
template <>
inline std::wstring to_wstring<std::size_t>(std::size_t o) { return std::to_wstring(o); };
template <>
inline std::wstring to_wstring<std::int64_t>(std::int64_t o) { return std::to_wstring(o); };
template <>
inline std::wstring to_wstring<bool>(bool o) { return o ? L"true" : L"false"; };
namespace ComplexTestingConsole
{
	class Base final
	{
	private:
		constexpr Base() noexcept = delete;
		constexpr ~Base() noexcept = delete;
		///
		/// Base
		///
	public:
		static std::wstring GetTitle();
		static std::wstring GetStartupLine();
		static bool IsSwitchTo(const std::wstring& Option);
		///
		/// Main Thread
		///
		static void Main();
		///
		/// Console Line Materials
		///
		static std::wstring Exception(const std::exception& Exception);
		static std::wstring Exception();
		static std::wstring Selection(const std::wstring& Content);
		static std::wstring Selection();
		static std::wstring Input(const std::wstring& Content);
		static std::wstring Input();
		static std::wstring Output(const std::wstring& Preceding, const std::wstring& Content);
		static std::wstring Output(const std::wstring& Content);
		static std::wstring Output();
		static std::wstring Comment(const std::wstring& Preceding, const std::wstring& Content);
		static std::wstring Comment(const std::wstring& Content);
		static std::wstring Comment();
		static void Startup(const std::wstring& Title);
	};
	template <std::size_t I, std::size_t S>
	std::wstring get_angle_name(std::integral_constant<std::size_t, I>, const std::array<const wchar_t*, S>& Angle)
	{
		return I < S ? std::get<I>(Angle) : L"Angle" + to_wstring(I);
	};
	template <typename... Args>
	std::wstring get_output_prepend_impl(const std::wstring& prepend, const std::wstring& midend, const std::wstring& append, std::int64_t arg)
	{
		return prepend + to_wstring(arg) + append;
	};
	template <typename... Args>
	std::wstring get_output_prepend_impl(const std::wstring& prepend, const std::wstring& midend, const std::wstring& append, std::int64_t arg, Args... args)
	{
		return get_output_prepend_impl(prepend + to_wstring(arg) + midend, midend, append, args...);
	};
	template <typename... Args>
	std::wstring get_output_prepend(const std::wstring& RightValue, Args... Temp)
	{
		return get_output_prepend_impl(RightValue + L"(", L", ", L") = ", Temp...);
	};
	template <typename T, std::size_t I = 0, std::size_t A, std::size_t S>
	void power_get_impl(std::array<T, A>& Data, const std::array<const wchar_t*, S>& Angle)
	{
		if constexpr (I < A)
		{
			const wchar_t* Assign = L" = ";
			if constexpr (std::is_same_v<T, std::int64_t>)
			{
				std::get<I>(Data) = stoi64_t(Base::Input(get_angle_name(std::integral_constant<std::size_t, I>{}, Angle) + Assign));
			}
			else if constexpr (std::is_same_v<T, std::pair<std::int64_t, std::int64_t>>)
			{
				std::int64_t Min = stoi64_t(Base::Input(get_angle_name(std::integral_constant<std::size_t, I>{}, Angle) + L"Min" + Assign));
				std::int64_t Max = stoi64_t(Base::Input(get_angle_name(std::integral_constant<std::size_t, I>{}, Angle) + L"Max" + Assign));
				std::get<I>(Data) = std::make_pair<std::int64_t, std::int64_t>(std::move(Min), std::move(Max));
			}
			if constexpr (I < A)
			{
				power_get_impl<T, I + 1, A, S>(Data, Angle);
			}
		}
	};
	template <typename T, std::size_t A>
	void power_get(std::array<T, A>& Data)
	{
		std::array<const wchar_t*, 4> Angle{ L"Theta", L"Phi", L"Tau", L"Omega" };
		power_get_impl(Data, Angle);
	};
	template <typename F, typename N, std::size_t A, std::size_t... I>
	void power_result_impl(F Subroutine, const N& Union, const N& Value, const std::array<std::int64_t, A>& Data, std::integer_sequence<std::size_t, I...>)
	{
		Base::Output(to_wstring(std::invoke(Subroutine, Union, Value, std::get<I>(Data)...)));
	};
	template <typename F, typename N, std::size_t A, std::size_t... I>
	void power_result_impl(F Subroutine, const std::wstring& RightValue, const N& Union, const N& Value, const std::array<std::int64_t, A>& Temp, std::integer_sequence<std::size_t, I...>)
	{
		Base::Output(
			get_output_prepend(RightValue, std::get<I>(Temp)...),
			to_wstring(std::invoke(Subroutine, Union, Value, std::get<I>(Temp)...))
		);
	};
	template <typename F, typename N, std::size_t A, std::size_t I = 0>
	void power_result_impl(F Subroutine, const std::wstring& RightValue, const N& Union, const N& Value, const std::array<std::pair<std::int64_t, std::int64_t>, A>& Data, std::array<std::int64_t, A>& Temp)
	{
		if constexpr (I < A)
		{
			while (std::get<I>(Temp) <= std::get<I>(Data).second)
			{
				power_result_impl<F, N, A, I + 1>(Subroutine, RightValue, Union, Value, Data, Temp);
				std::get<I>(Temp) = std::get<I>(Temp) + 1;
			}
			std::get<I>(Temp) = std::get<I>(Data).first;
		}
		else if constexpr (I == A)
		{
			power_result_impl(Subroutine, RightValue, Union, Value, Temp, std::make_index_sequence<A>{});
		}
	};
	template <std::size_t A, std::size_t I = 0>
	void power_temp_init(const std::array<std::pair<std::int64_t, std::int64_t>, A>& Data, std::array<std::int64_t, A>& Temp)
	{
		if constexpr (I < A)
		{
			std::get<I>(Temp) = std::get<I>(Data).first;
			power_temp_init<A, I + 1>(Data, Temp);
		}
	};
	template <typename T, typename F, typename N, std::size_t A>
	void power_result(F Subroutine, const std::wstring& RightValue, const N& Union, const N& Value, const std::array<T, A>& Data)
	{
		if constexpr (std::is_same_v<T, std::int64_t>)
		{
			power_result_impl(Subroutine, Union, Value, Data, std::make_index_sequence<A>{});
		}
		else if constexpr (std::is_same_v<T, std::pair<std::int64_t, std::int64_t>>)
		{
			std::array<std::int64_t, A> Temp{};
			power_temp_init(Data, Temp);
			power_result_impl(Subroutine, RightValue, Union, Value, Data, Temp);
		}
	};
}
#endif
