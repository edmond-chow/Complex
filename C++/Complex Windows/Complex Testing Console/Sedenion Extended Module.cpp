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
#include "Sedenion.h"
#pragma push_macro("Gbl")
#if defined(_MSVC_LANG)
#define Gbl __stdcall
#else
#define Gbl
#endif
using namespace ComplexTestingConsole;
using namespace Num;
namespace SedenBasis
{
	template <typename T>
	void Mul(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Seden&, const Seden&))
	{
		if (L == R)
		{
			Seden U = Val<Seden>(Base::Input(L"U = "));
			Seden V = Val<Seden>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	template <typename T>
	void Op(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Seden&, const Seden&))
	{
		if (L == R)
		{
			Seden U = Val<Seden>(Base::Input(L"U = "));
			Seden V = Val<Seden>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	inline void Pow(const std::wstring& L, const wchar_t* R, Seden(Gbl* F)(const Seden&, std::int64_t))
	{
		if (L == R)
		{
			Seden U = Val<Seden>(Base::Input(L"U = "));
			std::int64_t V = Int(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	template <typename... As>
	void Pow(const std::wstring& L, std::wstring&& R, Seden(Gbl* F)(const Seden&, const Seden&, std::int64_t, As...))
	{
		if (L == R)
		{
			Seden U = Val<Seden>(Base::Input(L"U = "));
			Seden V = Val<Seden>(Base::Input(L"V = "));
			std::array<std::int64_t, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, U, V, Dat);
		}
		else if (L == R + L"()")
		{
			Seden U = Val<Seden>(Base::Input(L"U = "));
			Seden V = Val<Seden>(Base::Input(L"V = "));
			std::array<std::pair<std::int64_t, std::int64_t>, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, R, U, V, Dat);
		}
	};
	template <typename T>
	void Bas(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Seden&))
	{
		if (L == R)
		{
			Seden V = Val<Seden>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	template <typename T>
	void BasP(const std::wstring& L, std::wstring&& R, T(Gbl* F)(const Seden&, std::int64_t))
	{
		if (L == R)
		{
			Seden V = Val<Seden>(Base::Input(L"V = "));
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, P)));
		}
		else if (L == R + L"()")
		{
			Seden V = Val<Seden>(Base::Input(L"V = "));
			std::int64_t PMin = Int(Base::Input(L"P(min) = "));
			std::int64_t PMax = Int(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(" + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, P)));
			}
		}
	};
	inline void Tri(const std::wstring& L, const wchar_t* R, Seden(Gbl* F)(const Seden&))
	{
		if (L == R)
		{
			Seden V = Val<Seden>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	inline void Atri(const std::wstring& L, std::wstring&& R, Seden(Gbl* F)(const Seden&, bool, std::int64_t))
	{
		if (L == R)
		{
			Seden V = Val<Seden>(Base::Input(L"V = "));
			bool S = false;
			std::wstring Ipt = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Ipt == L"+") { S = true; }
			else if (Ipt != L"-") { throw std::invalid_argument{ "A String interpretation of the sign cannot be converted as a bool value." }; }
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, S, P)));
		}
		else if (L == R + L"()")
		{
			Seden V = Val<Seden>(Base::Input(L"V = "));
			std::int64_t PMin = Int(Base::Input(L"P(min) = "));
			std::int64_t PMax = Int(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(+, L" + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, true, P)));
			}
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(-, L" + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, false, P)));
			}
		}
	};
	class SedenConsole final
	{
	private:
		constexpr SedenConsole() noexcept = delete;
		constexpr ~SedenConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void SedenConsole::Load() noexcept
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
				Pow(L, L"Power", Seden::Power);
				Pow(L, L"Root", Seden::Root);
				Pow(L, L"Log", Seden::Log);
				/****/
				Mul(L, L"Dot", Seden::Dot);
				Mul(L, L"Outer", Seden::Outer);
				Mul(L, L"Even", Seden::Even);
				Mul(L, L"Cross", Seden::Cross);
				/****/
				Bas(L, L"Abs", Seden::Abs);
				BasP(L, L"Arg", Seden::Arg);
				Bas(L, L"Conjg", Seden::Conjg);
				Bas(L, L"Sgn", Seden::Sgn);
				Bas(L, L"Inverse", Seden::Inverse);
				Bas(L, L"Exp", Seden::Exp);
				BasP(L, L"Ln", Seden::Ln);
				/****/
				Tri(L, L"Sin", Seden::Sin);
				Tri(L, L"Cos", Seden::Cos);
				Tri(L, L"Tan", Seden::Tan);
				Tri(L, L"Csc", Seden::Csc);
				Tri(L, L"Sec", Seden::Sec);
				Tri(L, L"Cot", Seden::Cot);
				Tri(L, L"Sinh", Seden::Sinh);
				Tri(L, L"Cosh", Seden::Cosh);
				Tri(L, L"Tanh", Seden::Tanh);
				Tri(L, L"Csch", Seden::Csch);
				Tri(L, L"Sech", Seden::Sech);
				Tri(L, L"Coth", Seden::Coth);
				Atri(L, L"Arcsin", Seden::Arcsin);
				Atri(L, L"Arccos", Seden::Arccos);
				Atri(L, L"Arctan", Seden::Arctan);
				Atri(L, L"Arccsc", Seden::Arccsc);
				Atri(L, L"Arcsec", Seden::Arcsec);
				Atri(L, L"Arccot", Seden::Arccot);
				Atri(L, L"Arcsinh", Seden::Arcsinh);
				Atri(L, L"Arccosh", Seden::Arccosh);
				Atri(L, L"Arctanh", Seden::Arctanh);
				Atri(L, L"Arccsch", Seden::Arccsch);
				Atri(L, L"Arcsech", Seden::Arcsech);
				Atri(L, L"Arccoth", Seden::Arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
#pragma pop_macro("Gbl")
