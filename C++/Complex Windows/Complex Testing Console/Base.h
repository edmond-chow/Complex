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
#pragma once
#include <cstdint>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <array>
#include <stdexcept>
inline std::int64_t wtoi64_t(const wchar_t* str)
{
	if (str[0] == L'\0') { throw std::invalid_argument("The string cannot be converted as an integer."); }
	const wchar_t* number = str;
	if (str[0] == L'-' || str[0] == L'+')
	{
		if (str[1] == L'\0') { throw std::invalid_argument("The string cannot be converted as an integer."); }
		++number;
	}
	std::size_t number_size = 0;
	const wchar_t* number_end = number;
	while (*number_end != L'\0')
	{
		if (static_cast<std::uint16_t>(*number_end) < 48 || static_cast<std::uint16_t>(*number_end) > 57) { throw std::invalid_argument("The string cannot be converted as an integer."); }
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
inline std::int64_t stoi64_t(const std::wstring& str)
{
	return wtoi64_t(str.c_str());
};
template <typename T>
inline std::wstring ToModStr(T o) { return T::Str(o); };
template <>
inline std::wstring ToModStr<double>(double o) { return DoubleToString(o); };
template <>
inline std::wstring ToModStr<std::size_t>(std::size_t o) { return std::to_wstring(o); };
template <>
inline std::wstring ToModStr<std::int64_t>(std::int64_t o) { return std::to_wstring(o); };
template <>
inline std::wstring ToModStr<bool>(bool o) { return o ? L"true" : L"false"; };
inline std::int64_t AsInt(const std::wstring& V)
{
	return stoi64_t(Replace(V, L" ", L""));
};
inline double AsReal(const std::wstring& V)
{
	std::wstring Replaced = Replace(V, L" ", L"");
	std::size_t Processed = 0;
	double Result = 0;
	try { Result = std::stod(Replaced, &Processed); }
	catch (...) { Processed = std::wstring::npos; }
	if (Processed == Replaced.size()) { return Result; }
	throw std::invalid_argument("The string cannot be converted as a real.");
};
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
	template <std::size_t I>
	std::wstring GetName(std::integral_constant<std::size_t, I>)
	{
		return L"z" + ToModStr(I);
	};
	template <typename... Args>
	std::wstring PowPrependImpl(const std::wstring& Beg, const std::wstring& Mid, const std::wstring& End, std::int64_t I)
	{
		return Beg + ToModStr(I) + End;
	};
	template <typename... Args>
	std::wstring PowPrependImpl(const std::wstring& Beg, const std::wstring& Mid, const std::wstring& End, std::int64_t I, Args... Is)
	{
		return PowPrependImpl(Beg + ToModStr(I) + Mid, Mid, End, Is...);
	};
	template <typename... Args>
	std::wstring PowPrepend(const std::wstring& R, Args... Tmp)
	{
		return PowPrependImpl(R + L"(", L", ", L") = ", Tmp...);
	};
	template <typename T, std::size_t I = 0, std::size_t A>
	void PowGet(std::array<T, A>& Dat)
	{
		if constexpr (I < A)
		{
			const wchar_t* Assign = L" = ";
			if constexpr (std::is_same_v<T, std::int64_t>)
			{
				std::get<I>(Dat) = AsInt(Base::Input(GetName(std::integral_constant<std::size_t, I>{}) + Assign));
			}
			else if constexpr (std::is_same_v<T, std::pair<std::int64_t, std::int64_t>>)
			{
				std::int64_t Min = AsInt(Base::Input(GetName(std::integral_constant<std::size_t, I>{}) + L"(min)" + Assign));
				std::int64_t Max = AsInt(Base::Input(GetName(std::integral_constant<std::size_t, I>{}) + L"(max)" + Assign));
				std::get<I>(Dat) = std::make_pair<std::int64_t, std::int64_t>(std::move(Min), std::move(Max));
			}
			if constexpr (I < A)
			{
				PowGet<T, I + 1, A>(Dat);
			}
		}
	};
	template <typename F, typename N, std::size_t A, std::size_t... I>
	void PowRstImpl(F S, const N& Union, const N& Value, const std::array<std::int64_t, A>& Dat, std::integer_sequence<std::size_t, I...>)
	{
		Base::Output(ToModStr(std::invoke(S, Union, Value, std::get<I>(Dat)...)));
	};
	template <typename F, typename N, std::size_t A, std::size_t... I>
	void PowRstImpl(F S, const std::wstring& R, const N& Union, const N& Value, const std::array<std::int64_t, A>& Tmp, std::integer_sequence<std::size_t, I...>)
	{
		Base::Output(
			PowPrepend(R, std::get<I>(Tmp)...),
			ToModStr(std::invoke(S, Union, Value, std::get<I>(Tmp)...))
		);
	};
	template <typename F, typename N, std::size_t A, std::size_t I = 0>
	void PowRstImpl(F S, const std::wstring& R, const N& Union, const N& Value, const std::array<std::pair<std::int64_t, std::int64_t>, A>& Dat, std::array<std::int64_t, A>& Tmp)
	{
		if constexpr (I < A)
		{
			while (std::get<I>(Tmp) <= std::get<I>(Dat).second)
			{
				PowRstImpl<F, N, A, I + 1>(S, R, Union, Value, Dat, Tmp);
				std::get<I>(Tmp) = std::get<I>(Tmp) + 1;
			}
			std::get<I>(Tmp) = std::get<I>(Dat).first;
		}
		else if constexpr (I == A)
		{
			PowRstImpl(S, R, Union, Value, Tmp, std::make_index_sequence<A>{});
		}
	};
	template <std::size_t A, std::size_t I = 0>
	void PowTmp(const std::array<std::pair<std::int64_t, std::int64_t>, A>& Dat, std::array<std::int64_t, A>& Tmp)
	{
		if constexpr (I < A)
		{
			std::get<I>(Tmp) = std::get<I>(Dat).first;
			PowTmp<A, I + 1>(Dat, Tmp);
		}
	};
	template <typename T, typename F, typename N, std::size_t A>
	void PowRst(F S, const std::wstring& R, const N& Union, const N& Value, const std::array<T, A>& Dat)
	{
		if constexpr (std::is_same_v<T, std::int64_t>)
		{
			PowRstImpl(S, Union, Value, Dat, std::make_index_sequence<A>{});
		}
		else if constexpr (std::is_same_v<T, std::pair<std::int64_t, std::int64_t>>)
		{
			std::array<std::int64_t, A> Tmp{};
			PowTmp(Dat, Tmp);
			PowRstImpl(S, R, Union, Value, Dat, Tmp);
		}
	};
}
