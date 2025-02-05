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
#include <functional>
#include <NumString.h>
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
inline std::wstring Str(double Num)
{
	std::wstringstream Rst;
	Rst << std::defaultfloat << std::setprecision(17) << Num;
	return std::regex_replace(Rst.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
};
inline std::wstring Replace(const std::wstring& Input, const std::wstring& Search, const std::wstring& Replacement)
{
	std::wstring Rst = Input;
	std::size_t Position = Rst.find(Search);
	while (Position != std::wstring::npos)
	{
		Rst = Rst.replace(Position, Search.size(), Replacement);
		Position = Rst.find(Search, Position + Replacement.size());
	}
	return Rst;
};
inline std::int64_t stoi64_t(const std::wstring& str)
{
	return wtoi64_t(str.c_str());
};
template <typename T>
T Val(const std::wstring& Str)
{
	Num::String V{ Str.data() };
	return T::Val(V);
};
template <typename T>
std::wstring ToModStr(const T& Obj)
{
	Num::String Rst{ T::Str(Obj) };
	return Rst.Ptr();
};
inline std::wstring ToModStr(double Obj)
{
	return Str(Obj);
};
inline std::wstring ToModStr(std::size_t Obj)
{
	return std::to_wstring(Obj);
};
inline std::wstring ToModStr(std::int64_t Obj)
{
	return std::to_wstring(Obj);
};
inline std::wstring ToModStr(bool Obj)
{
	return Obj ? L"true" : L"false";
};
inline std::int64_t AsInt(const std::wstring& Val)
{
	return stoi64_t(Replace(Val, L" ", L""));
};
inline double AsReal(const std::wstring& Val)
{
	std::wstring Replaced = Replace(Val, L" ", L"");
	std::size_t Processed = 0;
	double Rst = 0;
	try { Rst = std::stod(Replaced, &Processed); }
	catch (...) { Processed = std::wstring::npos; }
	if (Processed == Replaced.size()) { return Rst; }
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
	std::wstring GetName()
	{
		return L"z" + ToModStr(I);
	};
	template <typename... Args>
	std::wstring PowBegHit(const std::wstring& Beg, const std::wstring& Mid, const std::wstring& End, std::int64_t I)
	{
		return Beg + ToModStr(I) + End;
	};
	template <typename... Args>
	std::wstring PowBegHit(const std::wstring& Beg, const std::wstring& Mid, const std::wstring& End, std::int64_t I, Args... Is)
	{
		return PowBegHit(Beg + ToModStr(I) + Mid, Mid, End, Is...);
	};
	template <typename... Args>
	std::wstring PowBeg(const std::wstring& R, Args... Tmp)
	{
		return PowBegHit(R + L"(", L", ", L") = ", Tmp...);
	};
	inline static const wchar_t* Assign = L" = ";
	template <std::size_t A, std::size_t I = 0>
	void PowGet(std::array<std::int64_t, A>& Dat)
	{
		if constexpr (I < A)
		{
			std::get<I>(Dat) = AsInt(Base::Input(GetName<I>() + Assign));
			PowGet<A, I + 1>(Dat);
		}
	};
	template <std::size_t A, std::size_t I = 0>
	void PowGet(std::array<std::pair<std::int64_t, std::int64_t>, A>& Dat)
	{
		if constexpr (I < A)
		{
			std::int64_t Min = AsInt(Base::Input(GetName<I>() + L"(min)" + Assign));
			std::int64_t Max = AsInt(Base::Input(GetName<I>() + L"(max)" + Assign));
			std::pair<std::int64_t, std::int64_t> Par{ Min, Max };
			if (Min > Max) { std::swap(Par.first, Par.second); }
			std::get<I>(Dat) = Par;
			PowGet<A, I + 1>(Dat);
		}
	};
	template <typename F, typename N, std::size_t A, std::size_t... I>
	void PowRstPut(F S, const N& U, const N& V, const std::array<std::int64_t, A>& Dat, std::integer_sequence<std::size_t, I...>)
	{
		Base::Output(ToModStr(std::invoke(S, U, V, std::get<I>(Dat)...)));
	};
	template <typename F, typename N, std::size_t A, std::size_t... I>
	void PowRstPut(F S, const std::wstring& R, const N& U, const N& V, const std::array<std::int64_t, A>& Tmp, std::integer_sequence<std::size_t, I...>)
	{
		Base::Output(PowBeg(R, std::get<I>(Tmp)...), ToModStr(std::invoke(S, U, V, std::get<I>(Tmp)...)));
	};
	template <typename F, typename N, std::size_t A, std::size_t I = 0>
	void PowRstLoop(F S, const std::wstring& R, const N& U, const N& V, const std::array<std::pair<std::int64_t, std::int64_t>, A>& Dat, std::array<std::int64_t, A>& Tmp)
	{
		if constexpr (I < A)
		{
			while (std::get<I>(Tmp) <= std::get<I>(Dat).second)
			{
				PowRstLoop<F, N, A, I + 1>(S, R, U, V, Dat, Tmp);
				++std::get<I>(Tmp);
			}
			std::get<I>(Tmp) = std::get<I>(Dat).first;
		}
		else if constexpr (I == A)
		{
			PowRstPut(S, R, U, V, Tmp, std::make_index_sequence<A>{});
		}
	};
	template <std::size_t A, std::size_t I = 0>
	void PowTmpInit(const std::array<std::pair<std::int64_t, std::int64_t>, A>& Dat, std::array<std::int64_t, A>& Tmp)
	{
		if constexpr (I < A)
		{
			std::get<I>(Tmp) = std::get<I>(Dat).first;
			PowTmpInit<A, I + 1>(Dat, Tmp);
		}
	};
	template <typename F, typename N, std::size_t A>
	void PowRst(F S, const N& U, const N& V, const std::array<std::int64_t, A>& Dat)
	{
		PowRstPut(S, U, V, Dat, std::make_index_sequence<A>{});
	};
	template <typename F, typename N, std::size_t A>
	void PowRst(F S, const std::wstring& R, const N& U, const N& V, const std::array<std::pair<std::int64_t, std::int64_t>, A>& Dat)
	{
		std::array<std::int64_t, A> Tmp{};
		PowTmpInit(Dat, Tmp);
		PowRstLoop(S, R, U, V, Dat, Tmp);
	};
}
