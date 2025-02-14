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
#include "Quaternion.h"
#pragma push_macro("Gbl")
#if defined(_MSVC_LANG)
#define Gbl __stdcall
#else
#define Gbl
#endif
using namespace ComplexTestingConsole;
using namespace Num;
namespace QuterBasis
{
	inline void Idt(const std::wstring& L, const wchar_t* R)
	{
		if (L == R)
		{
			Quter V = Val<Quter>(Base::Input(L"V = "));
			Base::Output(ToModStr(V));
		}
	};
	template <typename T>
	void Mul(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Quter&, const Quter&))
	{
		if (L == R)
		{
			Quter U = Val<Quter>(Base::Input(L"U = "));
			Quter V = Val<Quter>(Base::Input(L"V = "));
			T Rst = std::invoke(F, U, V);
			std::wstring Str;
			if constexpr (std::is_same_v<T, Vec3D>) { Str = ToModStr(Quter{ 0, Rst }); }
			else { Str = ToModStr(Rst); }
			Base::Output(Str);
		}
	};
	template <typename T>
	void Op(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Quter&, const Quter&))
	{
		if (L == R)
		{
			Quter U = Val<Quter>(Base::Input(L"U = "));
			Quter V = Val<Quter>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	inline void Pow(const std::wstring& L, const wchar_t* R, Quter(Gbl* F)(const Quter&, std::int64_t))
	{
		if (L == R)
		{
			Quter U = Val<Quter>(Base::Input(L"U = "));
			std::int64_t V = Int(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, U, V)));
		}
	};
	template <typename... As>
	void Pow(const std::wstring& L, std::wstring&& R, Quter(Gbl* F)(const Quter&, const Quter&, std::int64_t, As...))
	{
		if (L == R)
		{
			Quter U = Val<Quter>(Base::Input(L"U = "));
			Quter V = Val<Quter>(Base::Input(L"V = "));
			std::array<std::int64_t, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, U, V, Dat);
		}
		else if (L == R + L"()")
		{
			Quter U = Val<Quter>(Base::Input(L"U = "));
			Quter V = Val<Quter>(Base::Input(L"V = "));
			std::array<std::pair<std::int64_t, std::int64_t>, 1 + sizeof...(As)> Dat{};
			PowGet(Dat);
			PowRst(F, R, U, V, Dat);
		}
	};
	template <typename T>
	void Bas(const std::wstring& L, const wchar_t* R, T(Gbl* F)(const Quter&))
	{
		if (L == R)
		{
			Quter V = Val<Quter>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	template <typename T>
	void BasP(const std::wstring& L, std::wstring&& R, T(Gbl* F)(const Quter&, std::int64_t))
	{
		if (L == R)
		{
			Quter V = Val<Quter>(Base::Input(L"V = "));
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, P)));
		}
		else if (L == R + L"()")
		{
			Quter V = Val<Quter>(Base::Input(L"V = "));
			std::int64_t PMin = Int(Base::Input(L"P(min) = "));
			std::int64_t PMax = Int(Base::Input(L"P(max) = "));
			for (std::int64_t P = PMin; P <= PMax; ++P)
			{
				Base::Output(R + L"(" + ToModStr(P) + L") = ", ToModStr(std::invoke(F, V, P)));
			}
		}
	};
	inline void Tri(const std::wstring& L, const wchar_t* R, Quter(Gbl* F)(const Quter&))
	{
		if (L == R)
		{
			Quter V = Val<Quter>(Base::Input(L"V = "));
			Base::Output(ToModStr(std::invoke(F, V)));
		}
	};
	inline void Atri(const std::wstring& L, std::wstring&& R, Quter(Gbl* F)(const Quter&, bool, std::int64_t))
	{
		if (L == R)
		{
			Quter V = Val<Quter>(Base::Input(L"V = "));
			bool S = false;
			std::wstring Ipt = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Ipt == L"+") { S = true; }
			else if (Ipt != L"-") { throw std::invalid_argument{ "A String interpretation of the sign cannot be converted as a bool value." }; }
			std::int64_t P = Int(Base::Input(L"P = "));
			Base::Output(ToModStr(std::invoke(F, V, S, P)));
		}
		else if (L == R + L"()")
		{
			Quter V = Val<Quter>(Base::Input(L"V = "));
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
	class QuterConsole final
	{
	private:
		constexpr QuterConsole() noexcept = delete;
		constexpr ~QuterConsole() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void QuterConsole::Load() noexcept
	{
		Base::Startup(Base::GetTitle());
		Base::Selection(L"&   =   +   -   *   /   ^   Power()   Root()   Log()");
		Base::Selection(L"Abs   Arg()   Conjg   Sgn   Inverse   Exp   Ln()   Dot   Outer   Even   Cross");
		Base::Selection(L"Sin   Cos   Tan   Csc   Sec   Cot   Arcsin()   Arccos()   Arctan()   Arccsc()   Arcsec()   Arccot()");
		Base::Selection(L"Sinh   Cosh   Tanh   Csch   Sech   Coth   Arcsinh()   Arccosh()   Arctanh()   Arccsch()   Arcsech()   Arccoth()");
		Base::Selection(Base::GetStartupLine());
		for (std::wstring L; !Base::IsSwitchTo(L); L = Trim(Base::Input()))
		{
			if (L.empty()) { continue; }
			try
			{
				Idt(L, L"&");
				Op(L, L"=", operator ==);
				Op(L, L"+", operator +);
				Op(L, L"-", operator -);
				Op(L, L"*", operator *);
				Op(L, L"/", operator /);
				/****/
				Pow(L, L"^", operator ^);
				Pow(L, L"Power", Quter::Power);
				Pow(L, L"Root", Quter::Root);
				Pow(L, L"Log", Quter::Log);
				/****/
				Mul(L, L"Dot", Quter::Dot);
				Mul(L, L"Outer", Quter::Outer);
				Mul(L, L"Even", Quter::Even);
				Mul(L, L"Cross", Quter::Cross);
				/****/
				Bas(L, L"Abs", Quter::Abs);
				BasP(L, L"Arg", Quter::Arg);
				Bas(L, L"Conjg", Quter::Conjg);
				Bas(L, L"Sgn", Quter::Sgn);
				Bas(L, L"Inverse", Quter::Inverse);
				Bas(L, L"Exp", Quter::Exp);
				BasP(L, L"Ln", Quter::Ln);
				/****/
				Tri(L, L"Sin", Quter::Sin);
				Tri(L, L"Cos", Quter::Cos);
				Tri(L, L"Tan", Quter::Tan);
				Tri(L, L"Csc", Quter::Csc);
				Tri(L, L"Sec", Quter::Sec);
				Tri(L, L"Cot", Quter::Cot);
				Tri(L, L"Sinh", Quter::Sinh);
				Tri(L, L"Cosh", Quter::Cosh);
				Tri(L, L"Tanh", Quter::Tanh);
				Tri(L, L"Csch", Quter::Csch);
				Tri(L, L"Sech", Quter::Sech);
				Tri(L, L"Coth", Quter::Coth);
				Atri(L, L"Arcsin", Quter::Arcsin);
				Atri(L, L"Arccos", Quter::Arccos);
				Atri(L, L"Arctan", Quter::Arctan);
				Atri(L, L"Arccsc", Quter::Arccsc);
				Atri(L, L"Arcsec", Quter::Arcsec);
				Atri(L, L"Arccot", Quter::Arccot);
				Atri(L, L"Arcsinh", Quter::Arcsinh);
				Atri(L, L"Arccosh", Quter::Arccosh);
				Atri(L, L"Arctanh", Quter::Arctanh);
				Atri(L, L"Arccsch", Quter::Arccsch);
				Atri(L, L"Arcsech", Quter::Arcsech);
				Atri(L, L"Arccoth", Quter::Arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
#pragma pop_macro("Gbl")
