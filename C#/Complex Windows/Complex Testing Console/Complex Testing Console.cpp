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
	void Bas(const std::wstring& L, std::wstring&& R, T(Gbl* F)(const Cmplx&, std::int64_t))
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
				Pow(L, L"power", Cmplx::Power);
				Pow(L, L"root", Cmplx::Root);
				Pow(L, L"log", Cmplx::Log);
				/****/
				Mul(L, L"dot", Cmplx::Dot);
				Mul(L, L"outer", Cmplx::Outer);
				Mul(L, L"even", Cmplx::Even);
				Mul(L, L"cross", Cmplx::Cross);
				/****/
				Bas(L, L"abs", Cmplx::Abs);
				Bas(L, L"arg", Cmplx::Arg);
				Bas(L, L"conjg", Cmplx::Conjg);
				Bas(L, L"sgn", Cmplx::Sgn);
				Bas(L, L"inverse", Cmplx::Inverse);
				Bas(L, L"exp", Cmplx::Exp);
				Bas(L, L"ln", Cmplx::Ln);
				/****/
				Tri(L, L"sin", Cmplx::Sin);
				Tri(L, L"cos", Cmplx::Cos);
				Tri(L, L"tan", Cmplx::Tan);
				Tri(L, L"csc", Cmplx::Csc);
				Tri(L, L"sec", Cmplx::Sec);
				Tri(L, L"cot", Cmplx::Cot);
				Tri(L, L"sinh", Cmplx::Sinh);
				Tri(L, L"cosh", Cmplx::Cosh);
				Tri(L, L"tanh", Cmplx::Tanh);
				Tri(L, L"csch", Cmplx::Csch);
				Tri(L, L"sech", Cmplx::Sech);
				Tri(L, L"coth", Cmplx::Coth);
				Atri(L, L"arcsin", Cmplx::Arcsin);
				Atri(L, L"arccos", Cmplx::Arccos);
				Atri(L, L"arctan", Cmplx::Arctan);
				Atri(L, L"arccsc", Cmplx::Arccsc);
				Atri(L, L"arcsec", Cmplx::Arcsec);
				Atri(L, L"arccot", Cmplx::Arccot);
				Atri(L, L"arcsinh", Cmplx::Arcsinh);
				Atri(L, L"arccosh", Cmplx::Arccosh);
				Atri(L, L"arctanh", Cmplx::Arctanh);
				Atri(L, L"arccsch", Cmplx::Arccsch);
				Atri(L, L"arcsech", Cmplx::Arcsech);
				Atri(L, L"arccoth", Cmplx::Arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
#pragma pop_macro("Gbl")
