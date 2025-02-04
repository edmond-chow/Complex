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
#define Gbl __stdcall
using namespace ComplexTestingConsole;
using namespace Num;
namespace OctonBasis
{
	template <typename F = Octon(Gbl*)(const Octon&, const Octon&)>
	void Mul(const std::wstring& L, const wchar_t* R, F S)
	{
		if (L == R)
		{
			Octon U = Octon::Val(Base::Input(L"U = "));
			Octon V = Octon::Val(Base::Input(L"V = "));
			Base::Output(ToModStr<Octon>(std::invoke(S, U, V)));
		}
	};
	template <typename T>
	void Op(const std::wstring& L, const wchar_t* R, T(Gbl* S)(const Octon&, const Octon&))
	{
		if (L == R)
		{
			Octon U = Octon::Val(Base::Input(L"U = "));
			Octon V = Octon::Val(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(S, U, V)));
		}
	};
	template <typename F>
	void Pow(const std::wstring& L, const wchar_t* R, F S)
	{
		if (L == R)
		{
			Octon U = Octon::Val(Base::Input(L"U = "));
			std::int64_t V = AsInt(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(S, U, V)));
		}
	};
	template <typename... As>
	void Pow(const std::wstring& L, std::wstring&& R, Octon(Gbl* S)(const Octon&, const Octon&, std::int64_t, As...))
	{
		if (L == R)
		{
			Octon U = Octon::Val(Base::Input(L"U = "));
			Octon V = Octon::Val(Base::Input(L"V = "));
			std::array<std::int64_t, 1 + sizeof...(As)> Data{};
			PowGet(Data);
			PowRst(S, R, U, V, Data);
		}
		else if (L == R + L"()")
		{
			Octon U = Octon::Val(Base::Input(L"U = "));
			Octon V = Octon::Val(Base::Input(L"V = "));
			std::array<std::pair<std::int64_t, std::int64_t>, 1 + sizeof...(As)> Data{};
			PowGet(Data);
			PowRst(S, R, U, V, Data);
		}
	};
	template <typename F>
	void Bas(const std::wstring& L, const wchar_t* R, F S)
	{
		if (L == R)
		{
			Octon V = Octon::Val(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(S, V)));
		}
	};
	template <typename T>
	void Bas(const std::wstring& L, std::wstring&& R, T(Gbl* S)(const Octon&, std::int64_t))
	{
		if (L == R)
		{
			Octon V = Octon::Val(Base::Input(L"V = "));
			std::int64_t P = AsInt(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(S, V, P)));
		}
		else if (L == R + L"()")
		{
			Octon V = Octon::Val(Base::Input(L"V = "));
			std::int64_t PMin = AsInt(Base::Input(L"P(min) = "));
			std::int64_t PMax = AsInt(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(" + ToModStr(P) + L") = ", ToModStr(std::invoke(S, V, P)));
			}
		}
	};
	template <typename F = Octon(Gbl*)(const Octon&)>
	inline void Tri(const std::wstring& L, const wchar_t* R, F S)
	{
		if (L == R)
		{
			Octon V = Octon::Val(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(S, V)));
		}
	};
	template <typename F = Octon(Gbl*)(const Octon&, bool, std::int64_t)>
	inline void Atri(const std::wstring& L, std::wstring&& R, F S)
	{
		if (L == R)
		{
			Octon V = Octon::Val(Base::Input(L"V = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A String interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t P = AsInt(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(S, V, Sign, P)));
		}
		else if (L == R + L"()")
		{
			Octon V = Octon::Val(Base::Input(L"V = "));
			std::int64_t PMin = AsInt(Base::Input(L"P(min) = "));
			std::int64_t PMax = AsInt(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(+, " + ToModStr(P) + L") = ", ToModStr(std::invoke(S, V, true, P)));
			}
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(-, " + ToModStr(P) + L") = ", ToModStr(std::invoke(S, V, false, P)));
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
		Base::Selection(L"=   +   -   *   /   ^   power()   root()   log()");
		Base::Selection(L"abs   arg()   conjg   sgn   inverse   exp   ln()   dot   outer   even   cross");
		Base::Selection(L"sin   cos   tan   csc   sec   cot   arcsin()   arccos()   arctan()   arccsc()   arcsec()   arccot()");
		Base::Selection(L"sinh   cosh   tanh   csch   sech   coth   arcsinh()   arccosh()   arctanh()   arccsch()   arcsech()   arccoth()");
		Base::Selection(Base::GetStartupLine());
		for (std::wstring L; !Base::IsSwitchTo(L); L = Base::Input())
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
				Pow(L, L"power", Octon::Power);
				Pow(L, L"root", Octon::Root);
				Pow(L, L"log", Octon::Log);
				/****/
				Mul(L, L"dot", Octon::Dot);
				Mul(L, L"outer", Octon::Outer);
				Mul(L, L"even", Octon::Even);
				Mul(L, L"cross", Octon::Cross);
				/****/
				Bas(L, L"abs", Octon::Abs);
				Bas(L, L"arg", Octon::Arg);
				Bas(L, L"conjg", Octon::Conjg);
				Bas(L, L"sgn", Octon::Sgn);
				Bas(L, L"inverse", Octon::Inverse);
				Bas(L, L"exp", Octon::Exp);
				Bas(L, L"ln", Octon::Ln);
				/****/
				Tri(L, L"sin", Octon::Sin);
				Tri(L, L"cos", Octon::Cos);
				Tri(L, L"tan", Octon::Tan);
				Tri(L, L"csc", Octon::Csc);
				Tri(L, L"sec", Octon::Sec);
				Tri(L, L"cot", Octon::Cot);
				Tri(L, L"sinh", Octon::Sinh);
				Tri(L, L"cosh", Octon::Cosh);
				Tri(L, L"tanh", Octon::Tanh);
				Tri(L, L"csch", Octon::Csch);
				Tri(L, L"sech", Octon::Sech);
				Tri(L, L"coth", Octon::Coth);
				Atri(L, L"arcsin", Octon::Arcsin);
				Atri(L, L"arccos", Octon::Arccos);
				Atri(L, L"arctan", Octon::Arctan);
				Atri(L, L"arccsc", Octon::Arccsc);
				Atri(L, L"arcsec", Octon::Arcsec);
				Atri(L, L"arccot", Octon::Arccot);
				Atri(L, L"arcsinh", Octon::Arcsinh);
				Atri(L, L"arccosh", Octon::Arccosh);
				Atri(L, L"arctanh", Octon::Arctanh);
				Atri(L, L"arccsch", Octon::Arccsch);
				Atri(L, L"arcsech", Octon::Arcsech);
				Atri(L, L"arccoth", Octon::Arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
