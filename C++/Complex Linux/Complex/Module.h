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
#include <cmath>
#include <limits>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <stdexcept>
inline constexpr const wchar_t* Ws = L" \t\n\v\f\r";
inline std::wstring Str(double Num)
{
	if (std::isnan(Num)) { return L"-nan"; }
	else if (std::isinf(Num)) { return std::signbit(Num) ? L"-inf" : L"inf"; }
	std::wstringstream Rst;
	Rst << std::defaultfloat << std::setprecision(17) << Num;
	return std::regex_replace(Rst.str(), std::wregex(L"e-0(?=[1-9])"), L"e-");
};
inline std::size_t stos_t(const std::wstring& Str)
{
	if (Str.find_first_not_of(Ws) > 0)
	{
		throw std::invalid_argument{ "The string cannot be converted as a size type." };
	}
	std::size_t Idx{ 0 };
	unsigned long long Rst{ std::stoull(Str, &Idx) };
	if (Idx < Str.size())
	{
		throw std::invalid_argument{ "The string cannot be converted as a size type." };
	}
	return static_cast<std::size_t>(Rst);
};
inline double stod_t(const std::wstring& Str)
{
	if (Str.find_first_not_of(Ws) > 0)
	{
		throw std::invalid_argument{ "The string cannot be converted as a double type." };
	}
	std::size_t Idx{ 0 };
	double Rst{ std::stod(Str, &Idx) };
	if (Idx < Str.size())
	{
		throw std::invalid_argument{ "The string cannot be converted as a double type." };
	}
	return Rst;
};
struct Terms
{
private:
	const std::vector<std::wstring>* Rf;
	std::size_t Sz;
public:
	explicit Terms(const std::vector<std::wstring>& Trm)
		: Rf{ &Trm }, Sz{ 0 }
	{};
	explicit Terms(std::size_t Dim)
		: Rf{ nullptr }, Sz{ Dim }
	{};
	bool Null() const&
	{
		return Rf == nullptr;
	};
	std::size_t Size() const&
	{
		return Rf == nullptr ? Sz : Rf->size();
	};
	std::wstring operator [](std::size_t i) const&
	{
		return Rf == nullptr ? L"e" + std::to_wstring(i) : (*Rf)[i];
	};
};
inline constexpr const wchar_t Beg[] = LR"((-|\+|^))";
inline constexpr const wchar_t Sig[] = LR"(((\d+)(\.\d+|)([Ee](-|\+|)(\d+)|)|nan|inf|))";
inline constexpr const wchar_t End[] = LR"((?=(-|\+|$)))";
inline constexpr const std::size_t BegI = 1;
inline constexpr const std::size_t SigI = 2;
inline constexpr const std::size_t TrmI = 8;
inline std::wstring Group(const Terms& Trm)
{
	if (Trm.Null()) { return L"(e\\d+)"; }
	std::wstringstream Rst;
	Rst << L"(";
	for (std::size_t i = 0; i < Trm.Size(); ++i)
	{
		Rst << (i == 0 ? L"" : L"|") << Trm[i];
	}
	Rst << L")";
	return Rst.str();
};
inline std::wstring Pat(const Terms& Trm)
{
	std::wstringstream Rst;
	Rst << Beg << Sig << Group(Trm) << End;
	return Rst.str();
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
inline std::wstring ToString(const std::vector<double>& Num, const Terms& Trm)
{
	if (Num.size() != Trm.Size()) { throw std::runtime_error{ "The branch should unreachable." }; }
	std::wstringstream Rst;
	bool Fst = true;
	for (std::size_t i = 0; i < Num.size(); ++i)
	{
		if (Num[i] == 0) { continue; }
		if (Num[i] > 0 && !Fst) { Rst << L"+"; }
		else if (Num[i] == -1) { Rst << L"-"; }
		if (Num[i] != 1 && Num[i] != -1) { Rst << Str(Num[i]); }
		else if (Trm[i].empty()) { Rst << L"1"; }
		if (!Trm[i].empty()) { Rst << Trm[i]; }
		Fst = false;
	}
	if (Fst) { Rst << L"0"; }
	return Rst.str();
};
template <typename N, typename... Ts>
std::wstring ToString(N& Rst, bool Vec, Ts... As)
{
	std::vector<std::wstring> Trm{ As... };
	std::size_t Siz = Trm.size();
	std::vector<double> Num(Siz);
	for (std::size_t i = 0, o = Vec ? 1 : 0; i < Siz; ++i) { Num[i] = Rst[i + o]; }
	return ToString(Num, Terms{ Trm });
};
inline std::vector<double> ToNumbers(const std::wstring& Val, const Terms& Trm)
{
	std::size_t Siz = Trm.Size();
	std::vector<double> Num(Siz);
	std::wstring::const_iterator Suf{ Val.begin() };
	std::wstring::const_iterator End{ Val.end() };
	std::wsmatch Mat;
	std::wregex Reg{ Pat(Trm) };
	std::regex_constants::match_flag_type Flg{ std::regex_constants::match_default };
	while (std::regex_search(Suf, End, Mat, Reg, Flg))
	{
		if (Mat.prefix().matched) { throw std::invalid_argument{ "The string is invalid." }; }
		std::wstring BegV = Mat.str(BegI);
		std::wstring SigV = Mat.str(SigI);
		std::wstring TrmV = Mat.str(TrmI);
		std::wstring Cap{ BegV + SigV };
		std::size_t i{ 0 };
		if (Trm.Null()) { i = stos_t(TrmV.substr(1)); }
		else
		{
			while (Trm[i] != TrmV && i < Siz) { ++i; }
			if (i == Siz) { throw std::runtime_error{ "The branch should unreachable." }; }
		}
		if (SigV.empty() && TrmV.empty()) { throw std::invalid_argument{"The string is invalid."}; }
		else if (SigV == L"nan") { Num[i] += std::numeric_limits<double>::quiet_NaN(); }
		else if (SigV == L"inf")
		{
			double Inf = std::numeric_limits<double>::infinity();
			if (BegV == L"-") { Inf = -Inf; }
			Num[i] += Inf;
		}
		else if (Cap.empty() || Cap == L"+") { ++Num[i]; }
		else if (Cap == L"-") { --Num[i]; }
		else { Num[i] += stod_t(Cap); }
		Suf = Mat.suffix().first;
		Flg |= std::regex_constants::match_not_bol;
	}
	if (Suf != End) { throw std::invalid_argument{ "The string is invalid." }; }
	return Num;
};
template <typename N, typename... Ts>
void ToNumbers(const std::wstring& Val, N& Rst, bool Vec, Ts... As)
{
	std::vector<std::wstring> Trm{ As... };
	std::vector<double> Num = ToNumbers(Val, Terms{ Trm });
	for (std::size_t i = 0, o = Vec ? 1 : 0; i < Trm.size(); ++i) { Rst[i + o] = Num[i]; }
};
#pragma pack(push)
#pragma push_macro("Ths")
#if defined(X86) || defined(ARM)
#pragma pack(4)
#elif defined(X64) || defined(ARM64)
#pragma pack(8)
#endif
#if defined(_MSVC_LANG)
#define Ths __thiscall
#else
#define Ths
#endif
namespace Num
{
	class String
	{
	private:
		wchar_t* Pointer;
	public:
		Ths String();
		Ths String(const wchar_t* Pt);
		String(const String& Self) = delete;
		Ths String(String&& Self) noexcept;
		String& operator =(const String& O) & = delete;
		String& Ths operator =(String&& O) & noexcept;
		Ths ~String() noexcept;
		const wchar_t* Ths Ptr() const&;
	};
}
#pragma pop_macro("Ths")
#pragma pack(pop)
