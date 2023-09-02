#include "Base.h"
#include "Sedenion.h"
using namespace SedenionTestingConsole;
using namespace Seden;
namespace SedenionMod
{
	inline double stod_t(const std::wstring& str)
	{
		std::wstring result = std::regex_replace(str, std::wregex(L" "), L"");
		return std::stod(str);
	};
	template <typename F = Sedenion(SEDEN_FUNC_CALL*)(const Sedenion&, const Sedenion&)>
	void op(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Sedenion Union = Sedenion::GetInstance(Base::Input(L"Union = "));
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Union, Value)));
		}
	};
	inline void op(const std::wstring& LeftValue, const wchar_t* RightValue, Sedenion(SEDEN_FUNC_CALL* Subroutine)(const Sedenion&, double))
	{
		if (LeftValue == RightValue)
		{
			Sedenion Union = Sedenion::GetInstance(Base::Input(L"Union = "));
			double Value = stod_t(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Sedenion Base = Sedenion::GetInstance(Base::Input(L"Base = "));
			std::int64_t Exponent = stoi64_t(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& LeftValue, std::wstring&& RightValue, Sedenion(SEDEN_FUNC_CALL* Subroutine)(const Sedenion&, const Sedenion&, std::int64_t, args...))
	{
		if (LeftValue == RightValue)
		{
			Sedenion Union = Sedenion::GetInstance(Base::Input(L"Union = "));
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(Subroutine, RightValue, Union, Value, Data);
		}
		else if (LeftValue == RightValue + L"()")
		{
			Sedenion Union = Sedenion::GetInstance(Base::Input(L"Union = "));
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
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
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& LeftValue, std::wstring&& RightValue, R(SEDEN_FUNC_CALL* Subroutine)(const Sedenion&, std::int64_t))
	{
		if (LeftValue == RightValue)
		{
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			std::int64_t Theta = stoi64_t(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Theta)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			std::int64_t ThetaMin = stoi64_t(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = stoi64_t(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(RightValue + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(Subroutine, Value, Theta)));
			}
		}
	};
	template <typename F = Sedenion(SEDEN_FUNC_CALL*)(const Sedenion&)>
	inline void tri(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename F = Sedenion(SEDEN_FUNC_CALL*)(const Sedenion&, bool, std::int64_t)>
	inline void arctri(const std::wstring& LeftValue, std::wstring&& RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = stoi64_t(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Sign, Period)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Sedenion Value = Sedenion::GetInstance(Base::Input(L"Value = "));
			std::int64_t PeriodMin = stoi64_t(Base::Input(L"PeriodMin = "));
			std::int64_t PeriodMax = stoi64_t(Base::Input(L"PeriodMax = "));
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
	class MySedenionTestor final
	{
	private:
		constexpr MySedenionTestor() noexcept = delete;
		constexpr ~MySedenionTestor() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void MySedenionTestor::Load() noexcept
	{
		Base::Startup(Base::GetTitle());
		Base::Selection(L"=   +   -   *   /   ^   power()   root()   log()");
		Base::Selection(L"abs   arg()   conjg   sgn   inverse   exp   ln()");
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
				power(Line, L"power", Sedenion::power);
				power(Line, L"root", Sedenion::root);
				power(Line, L"log", Sedenion::log);
				/****/
				basic(Line, L"abs", Sedenion::abs);
				basic(Line, L"arg", Sedenion::arg);
				basic(Line, L"conjg", Sedenion::conjg);
				basic(Line, L"sgn", Sedenion::sgn);
				basic(Line, L"inverse", Sedenion::inverse);
				basic(Line, L"exp", Sedenion::exp);
				basic(Line, L"ln", Sedenion::ln);
				/****/
				tri(Line, L"sin", Sedenion::sin);
				tri(Line, L"cos", Sedenion::cos);
				tri(Line, L"tan", Sedenion::tan);
				tri(Line, L"csc", Sedenion::csc);
				tri(Line, L"sec", Sedenion::sec);
				tri(Line, L"cot", Sedenion::cot);
				tri(Line, L"sinh", Sedenion::sinh);
				tri(Line, L"cosh", Sedenion::cosh);
				tri(Line, L"tanh", Sedenion::tanh);
				tri(Line, L"csch", Sedenion::csch);
				tri(Line, L"sech", Sedenion::sech);
				tri(Line, L"coth", Sedenion::coth);
				arctri(Line, L"arcsin", Sedenion::arcsin);
				arctri(Line, L"arccos", Sedenion::arccos);
				arctri(Line, L"arctan", Sedenion::arctan);
				arctri(Line, L"arccsc", Sedenion::arccsc);
				arctri(Line, L"arcsec", Sedenion::arcsec);
				arctri(Line, L"arccot", Sedenion::arccot);
				arctri(Line, L"arcsinh", Sedenion::arcsinh);
				arctri(Line, L"arccosh", Sedenion::arccosh);
				arctri(Line, L"arctanh", Sedenion::arctanh);
				arctri(Line, L"arccsch", Sedenion::arccsch);
				arctri(Line, L"arcsech", Sedenion::arcsech);
				arctri(Line, L"arccoth", Sedenion::arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
