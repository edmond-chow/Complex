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
 *   disTributed under the License is disTributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#include "Base.h"
#include "Octonion.h"
#pragma push_macro("Gbl")
#if defined(_MSVC_LANG)
#define Gbl __stdcall
#else
#define Gbl
#endif
using namespace ComplexTestingConsole;
using namespace Num;
namespace OctonBasis
{
	template <typename T>
	void Mul(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Octon&, const Octon&))
	{
		if (L == R)
		{
			Octon U = Val<Octon>(Base::Input(L"U = "));
			Octon V = Val<Octon>(Base::Input(L"V = "));
			T Rst = std::invoke(F, U, V);
			std::wstring Str;
			if constexpr (std::is_same_v<T, Vec7D>) { Str = ToModStr(Octon{ 0, Rst }); }
			else { Str = ToModStr(Rst); }
			Base::Output(Str);
		}
	};
	template <typename T>
	void Op(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Octon&, const Octon&))
	{
		if (L == R)
		{
			Octon U = Val<Octon>(Base::Input(L"U = "));
			Octon V = Val<Octon>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	inline void Pow(const std::wstring& L, const wchar_t* R, Octon(Gbl* F)(const Octon&, std::int64_t))
	{
		if (L == R)
		{
			Octon U = Val<Octon>(Base::Input(L"U = "));
			std::int64_t V = Int(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	template <typename... As>
	void Pow(const std::wstring& L, std::wstring&& R, Octon(Gbl* F)(const Octon&, const Octon&, std::int64_t, As...))
	{
		if (L == R)
		{
			Octon U = Val<Octon>(Base::Input(L"U = "));
			Octon V = Val<Octon>(Base::Input(L"V = "));
			std::array<std::int64_t, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, U, V, Dat);
		}
		else if (L == R + L"()")
		{
			Octon U = Val<Octon>(Base::Input(L"U = "));
			Octon V = Val<Octon>(Base::Input(L"V = "));
			std::array<std::pair<std::int64_t, std::int64_t>, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, R, U, V, Dat);
		}
	};
	template <typename T>
	void Bas(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Octon&))
	{
		if (L == R)
		{
			Octon V = Val<Octon>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	template <typename T>
	void BasP(const std::wstring& L, std::wstring&& R, T(Gbl* F)(const Octon&, std::int64_t))
	{
		if (L == R)
		{
			Octon V = Val<Octon>(Base::Input(L"V = "));
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, P)));
		}
		else if (L == R + L"()")
		{
			Octon V = Val<Octon>(Base::Input(L"V = "));
			std::int64_t PMin = Int(Base::Input(L"P(min) = "));
			std::int64_t PMax = Int(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(" + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, P)));
			}
		}
	};
	inline void Tri(const std::wstring& L, const wchar_t* R, Octon(Gbl* F)(const Octon&))
	{
		if (L == R)
		{
			Octon V = Val<Octon>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	inline void Atri(const std::wstring& L, std::wstring&& R, Octon(Gbl* F)(const Octon&, bool, std::int64_t))
	{
		if (L == R)
		{
			Octon V = Val<Octon>(Base::Input(L"V = "));
			bool S = false;
			std::wstring Ipt = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Ipt == L"+") { S = true; }
			else if (Ipt != L"-") { throw std::invalid_argument{ "A String interpretation of the sign cannot be converted as a bool value." }; }
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, S, P)));
		}
		else if (L == R + L"()")
		{
			Octon V = Val<Octon>(Base::Input(L"V = "));
			std::int64_t PMin = Int(Base::Input(L"P(min) = "));
			std::int64_t PMax = Int(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(+, " + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, true, P)));
			}
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(-, " + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, false, P)));
			}
		}
	};
	class OctonConsole final
	{
	private:
		constexpr OctonConsole() noexcept = delete;
		constexpr ~OctonConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void OctonConsole::Load() noexcept
	{
		Base::Startup(Base::GetTitle());
		Base::Selection(L"=   +   -   *   /   ^   Power()   Root()   Log()");
		Base::Selection(L"Abs   Arg()   Conjg   Sgn   Inverse   Exp   Ln()   Dot   Outer   Even   Cross");
		Base::Selection(L"Sin   Cos   Tan   Csc   Sec   Cot   Arcsin()   Arccos()   Arctan()   Arccsc()   Arcsec()   Arccot()");
		Base::Selection(L"Sinh   Cosh   Tanh   Csch   Sech   Coth   Arcsinh()   Arccosh()   Arctanh()   Arccsch()   Arcsech()   Arccoth()");
		Base::Selection(Base::GetStartupLine());
		for (std::wstring L; !Base::IsSwitchTo(L); L = Trim(Base::Input()))
		{
			if (L.empty()) { continue; }
			try
			{
				Op(L, L"=", operator ==);
				Op(L, L"+", operator +);
				Op(L, L"-", operator -);
				Op(L, L"*", operator *);
				Op(L, L"/", operator /);
				/****/
				Pow(L, L"^", operator ^);
				Pow(L, L"Power", Octon::Power);
				Pow(L, L"Root", Octon::Root);
				Pow(L, L"Log", Octon::Log);
				/****/
				Mul(L, L"Dot", Octon::Dot);
				Mul(L, L"Outer", Octon::Outer);
				Mul(L, L"Even", Octon::Even);
				Mul(L, L"Cross", Octon::Cross);
				/****/
				Bas(L, L"Abs", Octon::Abs);
				BasP(L, L"Arg", Octon::Arg);
				Bas(L, L"Conjg", Octon::Conjg);
				Bas(L, L"Sgn", Octon::Sgn);
				Bas(L, L"Inverse", Octon::Inverse);
				Bas(L, L"Exp", Octon::Exp);
				BasP(L, L"Ln", Octon::Ln);
				/****/
				Tri(L, L"Sin", Octon::Sin);
				Tri(L, L"Cos", Octon::Cos);
				Tri(L, L"Tan", Octon::Tan);
				Tri(L, L"Csc", Octon::Csc);
				Tri(L, L"Sec", Octon::Sec);
				Tri(L, L"Cot", Octon::Cot);
				Tri(L, L"Sinh", Octon::Sinh);
				Tri(L, L"Cosh", Octon::Cosh);
				Tri(L, L"Tanh", Octon::Tanh);
				Tri(L, L"Csch", Octon::Csch);
				Tri(L, L"Sech", Octon::Sech);
				Tri(L, L"Coth", Octon::Coth);
				Atri(L, L"Arcsin", Octon::Arcsin);
				Atri(L, L"Arccos", Octon::Arccos);
				Atri(L, L"Arctan", Octon::Arctan);
				Atri(L, L"Arccsc", Octon::Arccsc);
				Atri(L, L"Arcsec", Octon::Arcsec);
				Atri(L, L"Arccot", Octon::Arccot);
				Atri(L, L"Arcsinh", Octon::Arcsinh);
				Atri(L, L"Arccosh", Octon::Arccosh);
				Atri(L, L"Arctanh", Octon::Arctanh);
				Atri(L, L"Arccsch", Octon::Arccsch);
				Atri(L, L"Arcsech", Octon::Arcsech);
				Atri(L, L"Arccoth", Octon::Arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
#pragma pop_macro("Gbl")
