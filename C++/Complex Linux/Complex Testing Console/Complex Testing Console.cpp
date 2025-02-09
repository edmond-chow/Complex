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
#include "Complex.h"
#pragma push_macro("Gbl")
#if defined(_MSVC_LANG)
#define Gbl __stdcall
#else
#define Gbl
#endif
using namespace ComplexTestingConsole;
using namespace Num;
namespace CmplxBasis
{
	template <typename T>
	void Mul(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Cmplx&, const Cmplx&))
	{
		if (L == R)
		{
			Cmplx U = Val<Cmplx>(Base::Input(L"U = "));
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			T Rst = std::invoke(F, U, V);
			std::wstring Str;
			if constexpr (std::is_same_v<T, Vec1D>) { Str = ToModStr(Cmplx{ 0, Rst }); }
			else { Str = ToModStr(Rst); }
			Base::Output(Str);
		}
	};
	template <typename T>
	void Op(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Cmplx&, const Cmplx&))
	{
		if (L == R)
		{
			Cmplx U = Val<Cmplx>(Base::Input(L"U = "));
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	inline void Pow(const std::wstring& L, const wchar_t* R, Cmplx(Gbl* F)(const Cmplx&, std::int64_t))
	{
		if (L == R)
		{
			Cmplx U = Val<Cmplx>(Base::Input(L"U = "));
			std::int64_t V = Int(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	template <typename... As>
	void Pow(const std::wstring& L, std::wstring&& R, Cmplx(Gbl* F)(const Cmplx&, const Cmplx&, std::int64_t, As...))
	{
		if (L == R)
		{
			Cmplx U = Val<Cmplx>(Base::Input(L"U = "));
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			std::array<std::int64_t, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, U, V, Dat);
		}
		else if (L == R + L"()")
		{
			Cmplx U = Val<Cmplx>(Base::Input(L"U = "));
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			std::array<std::pair<std::int64_t, std::int64_t>, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, R, U, V, Dat);
		}
	};
	template <typename T>
	void Bas(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Cmplx&))
	{
		if (L == R)
		{
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	template <typename T>
	void BasP(const std::wstring& L, std::wstring&& R, T(Gbl* F)(const Cmplx&, std::int64_t))
	{
		if (L == R)
		{
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, P)));
		}
		else if (L == R + L"()")
		{
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			std::int64_t PMin = Int(Base::Input(L"P(min) = "));
			std::int64_t PMax = Int(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(" + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, P)));
			}
		}
	};
	inline void Tri(const std::wstring& L, const wchar_t* R, Cmplx(Gbl* F)(const Cmplx&))
	{
		if (L == R)
		{
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	inline void Atri(const std::wstring& L, std::wstring&& R, Cmplx(Gbl* F)(const Cmplx&, bool, std::int64_t))
	{
		if (L == R)
		{
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
			bool S = false;
			std::wstring Ipt = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Ipt == L"+") { S = true; }
			else if (Ipt != L"-") { throw std::invalid_argument{ "A String interpretation of the sign cannot be converted as a bool value." }; }
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, S, P)));
		}
		else if (L == R + L"()")
		{
			Cmplx V = Val<Cmplx>(Base::Input(L"V = "));
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
	class CmplxConsole final
	{
	private:
		constexpr CmplxConsole() noexcept = delete;
		constexpr ~CmplxConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void CmplxConsole::Load() noexcept
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
				Pow(L, L"Power", Cmplx::Power);
				Pow(L, L"Root", Cmplx::Root);
				Pow(L, L"Log", Cmplx::Log);
				/****/
				Mul(L, L"Dot", Cmplx::Dot);
				Mul(L, L"Outer", Cmplx::Outer);
				Mul(L, L"Even", Cmplx::Even);
				Mul(L, L"Cross", Cmplx::Cross);
				/****/
				Bas(L, L"Abs", Cmplx::Abs);
				BasP(L, L"Arg", Cmplx::Arg);
				Bas(L, L"Conjg", Cmplx::Conjg);
				Bas(L, L"Sgn", Cmplx::Sgn);
				Bas(L, L"Inverse", Cmplx::Inverse);
				Bas(L, L"Exp", Cmplx::Exp);
				BasP(L, L"Ln", Cmplx::Ln);
				/****/
				Tri(L, L"Sin", Cmplx::Sin);
				Tri(L, L"Cos", Cmplx::Cos);
				Tri(L, L"Tan", Cmplx::Tan);
				Tri(L, L"Csc", Cmplx::Csc);
				Tri(L, L"Sec", Cmplx::Sec);
				Tri(L, L"Cot", Cmplx::Cot);
				Tri(L, L"Sinh", Cmplx::Sinh);
				Tri(L, L"Cosh", Cmplx::Cosh);
				Tri(L, L"Tanh", Cmplx::Tanh);
				Tri(L, L"Csch", Cmplx::Csch);
				Tri(L, L"Sech", Cmplx::Sech);
				Tri(L, L"Coth", Cmplx::Coth);
				Atri(L, L"Arcsin", Cmplx::Arcsin);
				Atri(L, L"Arccos", Cmplx::Arccos);
				Atri(L, L"Arctan", Cmplx::Arctan);
				Atri(L, L"Arccsc", Cmplx::Arccsc);
				Atri(L, L"Arcsec", Cmplx::Arcsec);
				Atri(L, L"Arccot", Cmplx::Arccot);
				Atri(L, L"Arcsinh", Cmplx::Arcsinh);
				Atri(L, L"Arccosh", Cmplx::Arccosh);
				Atri(L, L"Arctanh", Cmplx::Arctanh);
				Atri(L, L"Arccsch", Cmplx::Arccsch);
				Atri(L, L"Arcsech", Cmplx::Arcsech);
				Atri(L, L"Arccoth", Cmplx::Arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
#pragma pop_macro("Gbl")
