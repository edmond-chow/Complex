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
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <array>
#include <stdexcept>
#include <functional>
#include <NumString.h>
inline std::wstring Str(double Num)
{
	std::wstringstream Rst;
	Rst << std::defaultfloat << std::setprecision(17) << Num;
	return std::regex_replace(Rst.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
};
inline std::wstring Replace(const std::wstring& Ipt, const std::wstring& Sch, const std::wstring& Rpt)
{
	std::wstring Rst = Ipt;
	std::size_t Pos = Rst.find(Sch);
	while (Pos != std::wstring::npos)
	{
		Rst = Rst.replace(Pos, Sch.size(), Rpt);
		Pos = Rst.find(Sch, Pos + Rpt.size());
	}
	return Rst;
};
inline std::int64_t stoi64_t(const std::wstring& Str)
{
	std::size_t Idx{ 0 };
	long long Rst{ std::stoll(Str, &Idx) };
	if (Idx < Str.size() || Str[0] == L' ')
	{
		throw std::invalid_argument{ "The string cannot be converted as a integer type." };
	}
	return static_cast<std::int64_t>(Rst);
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
inline std::int64_t Int(const std::wstring& Val)
{
	return stoi64_t(Replace(Val, L" ", L""));
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
		static bool IsSwitchTo(const std::wstring& Opt);
		///
		/// Main Thread
		///
		static void Main();
		///
		/// Console Line Materials
		///
		static std::wstring Exception(const std::exception& Exc);
		static std::wstring Exception();
		static std::wstring Selection(const std::wstring& Con);
		static std::wstring Selection();
		static std::wstring Input(const std::wstring& Con);
		static std::wstring Input();
		static std::wstring Output(const std::wstring& Pre, const std::wstring& Con);
		static std::wstring Output(const std::wstring& Con);
		static std::wstring Output();
		static std::wstring Comment(const std::wstring& Pre, const std::wstring& Con);
		static std::wstring Comment(const std::wstring& Con);
		static std::wstring Comment();
		static void Startup(const std::wstring& Tle);
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
			std::get<I>(Dat) = Int(Base::Input(GetName<I>() + Assign));
			PowGet<A, I + 1>(Dat);
		}
	};
	template <std::size_t A, std::size_t I = 0>
	void PowGet(std::array<std::pair<std::int64_t, std::int64_t>, A>& Dat)
	{
		if constexpr (I < A)
		{
			std::int64_t Min = Int(Base::Input(GetName<I>() + L"(min)" + Assign));
			std::int64_t Max = Int(Base::Input(GetName<I>() + L"(max)" + Assign));
			std::pair<std::int64_t, std::int64_t> Par{ Min, Max };
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
