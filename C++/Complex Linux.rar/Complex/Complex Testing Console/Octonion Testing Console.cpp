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
#include "Base.h"
#include "Octonion.h"
using namespace ComplexTestingConsole;
using namespace Octon;
using namespace Octon::MainType;
namespace OctonBasis
{
	template <typename F = Octonion(OCTON_FUNC_CALL*)(const Octonion&, const Octonion&)>
	void multiple(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Octonion Union = Octonion::GetInstance(Base::Input(L"Union = "));
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring<Octonion>(std::invoke(Subroutine, Union, Value)));
		}
	};
	template <typename F = Octonion(OCTON_FUNC_CALL*)(const Octonion&, const Octonion&)>
	void op(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Octonion Union = Octonion::GetInstance(Base::Input(L"Union = "));
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Octonion Base = Octonion::GetInstance(Base::Input(L"Base = "));
			std::int64_t Exponent = PraseAsInteger(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& LeftValue, std::wstring&& RightValue, Octonion(OCTON_FUNC_CALL* Subroutine)(const Octonion&, const Octonion&, std::int64_t, args...))
	{
		if (LeftValue == RightValue)
		{
			Octonion Union = Octonion::GetInstance(Base::Input(L"Union = "));
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(Subroutine, RightValue, Union, Value, Data);
		}
		else if (LeftValue == RightValue + L"()")
		{
			Octonion Union = Octonion::GetInstance(Base::Input(L"Union = "));
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			std::array<std::pair<std::int64_t, std::int64_t>, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(Subroutine, RightValue, Union, Value, Data);
		}
	};
	template <typename F>
	void basic(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& LeftValue, std::wstring&& RightValue, R(OCTON_FUNC_CALL* Subroutine)(const Octonion&, std::int64_t))
	{
		if (LeftValue == RightValue)
		{
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			std::int64_t Theta = PraseAsInteger(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Theta)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			std::int64_t ThetaMin = PraseAsInteger(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = PraseAsInteger(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(RightValue + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(Subroutine, Value, Theta)));
			}
		}
	};
	template <typename F = Octonion(OCTON_FUNC_CALL*)(const Octonion&)>
	inline void tri(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename F = Octonion(OCTON_FUNC_CALL*)(const Octonion&, bool, std::int64_t)>
	inline void arctri(const std::wstring& LeftValue, std::wstring&& RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = PraseAsInteger(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Sign, Period)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Octonion Value = Octonion::GetInstance(Base::Input(L"Value = "));
			std::int64_t PeriodMin = PraseAsInteger(Base::Input(L"PeriodMin = "));
			std::int64_t PeriodMax = PraseAsInteger(Base::Input(L"PeriodMax = "));
			for (std::int64_t Period = PeriodMin; Period <= PeriodMax; ++Period)
			{
				Base::Output(RightValue + L"(+, " + to_wstring(Period) + L") = ", to_wstring(std::invoke(Subroutine, Value, true, Period)));
			}
			for (std::int64_t Period = PeriodMin; Period <= PeriodMax; ++Period)
			{
				Base::Output(RightValue + L"(-, " + to_wstring(Period) + L") = ", to_wstring(std::invoke(Subroutine, Value, false, Period)));
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
		for (std::wstring Line; !Base::IsSwitchTo(Line); Line = Base::Input())
		{
			if (Line.empty()) { continue; }
			try
			{
				op(Line, L"=", operator ==);
				op(Line, L"+", operator +);
				op(Line, L"-", operator -);
				op(Line, L"*", operator *);
				op(Line, L"/", operator /);
				/****/
				power(Line, L"^", operator ^);
				power(Line, L"power", Octonion::power);
				power(Line, L"root", Octonion::root);
				power(Line, L"log", Octonion::log);
				/****/
				basic(Line, L"abs", Octonion::abs);
				basic(Line, L"arg", Octonion::arg);
				basic(Line, L"conjg", Octonion::conjg);
				basic(Line, L"sgn", Octonion::sgn);
				basic(Line, L"inverse", Octonion::inverse);
				basic(Line, L"exp", Octonion::exp);
				basic(Line, L"ln", Octonion::ln);
				multiple(Line, L"dot", Octonion::dot);
				multiple(Line, L"outer", Octonion::outer);
				multiple(Line, L"even", Octonion::even);
				multiple(Line, L"cross", Octonion::cross);
				/****/
				tri(Line, L"sin", Octonion::sin);
				tri(Line, L"cos", Octonion::cos);
				tri(Line, L"tan", Octonion::tan);
				tri(Line, L"csc", Octonion::csc);
				tri(Line, L"sec", Octonion::sec);
				tri(Line, L"cot", Octonion::cot);
				tri(Line, L"sinh", Octonion::sinh);
				tri(Line, L"cosh", Octonion::cosh);
				tri(Line, L"tanh", Octonion::tanh);
				tri(Line, L"csch", Octonion::csch);
				tri(Line, L"sech", Octonion::sech);
				tri(Line, L"coth", Octonion::coth);
				arctri(Line, L"arcsin", Octonion::arcsin);
				arctri(Line, L"arccos", Octonion::arccos);
				arctri(Line, L"arctan", Octonion::arctan);
				arctri(Line, L"arccsc", Octonion::arccsc);
				arctri(Line, L"arcsec", Octonion::arcsec);
				arctri(Line, L"arccot", Octonion::arccot);
				arctri(Line, L"arcsinh", Octonion::arcsinh);
				arctri(Line, L"arccosh", Octonion::arccosh);
				arctri(Line, L"arctanh", Octonion::arctanh);
				arctri(Line, L"arccsch", Octonion::arccsch);
				arctri(Line, L"arcsech", Octonion::arcsech);
				arctri(Line, L"arccoth", Octonion::arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
