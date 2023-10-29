#include "Base.h"
#include "Complex.h"
using namespace ComplexTestingConsole;
using namespace Cmplx;
using namespace Cmplx::MainType;
namespace Mod
{
	template <typename F = Complex(CMPLX_FUNC_CALL*)(const Complex&, const Complex&)>
	void multiple(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Complex Union = Complex::GetInstance(Base::Input(L"Union = "));
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring<Complex>(std::invoke(Subroutine, Union, Value)));
		}
	};
	template <typename F = Complex(CMPLX_FUNC_CALL*)(const Complex&, const Complex&)>
	void op(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Complex Union = Complex::GetInstance(Base::Input(L"Union = "));
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Complex Base = Complex::GetInstance(Base::Input(L"Base = "));
			std::int64_t Exponent = stoi64_t(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& LeftValue, std::wstring&& RightValue, Complex(CMPLX_FUNC_CALL* Subroutine)(const Complex&, const Complex&, std::int64_t, args...))
	{
		if (LeftValue == RightValue)
		{
			Complex Union = Complex::GetInstance(Base::Input(L"Union = "));
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(Subroutine, RightValue, Union, Value, Data);
		}
		else if (LeftValue == RightValue + L"()")
		{
			Complex Union = Complex::GetInstance(Base::Input(L"Union = "));
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
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
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& LeftValue, std::wstring&& RightValue, R(CMPLX_FUNC_CALL* Subroutine)(const Complex&, std::int64_t))
	{
		if (LeftValue == RightValue)
		{
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			std::int64_t Theta = stoi64_t(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Theta)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			std::int64_t ThetaMin = stoi64_t(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = stoi64_t(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(RightValue + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(Subroutine, Value, Theta)));
			}
		}
	};
	template <typename F = Complex(CMPLX_FUNC_CALL*)(const Complex&)>
	inline void tri(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename F = Complex(CMPLX_FUNC_CALL*)(const Complex&, bool, std::int64_t)>
	inline void arctri(const std::wstring& LeftValue, std::wstring&& RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = stoi64_t(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Sign, Period)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Complex Value = Complex::GetInstance(Base::Input(L"Value = "));
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
	class MyModule final
	{
	private:
		constexpr MyModule() noexcept = delete;
		constexpr ~MyModule() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void MyModule::Load() noexcept
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
				power(Line, L"power", Complex::power);
				power(Line, L"root", Complex::root);
				power(Line, L"log", Complex::log);
				/****/
				basic(Line, L"abs", Complex::abs);
				basic(Line, L"arg", Complex::arg);
				basic(Line, L"conjg", Complex::conjg);
				basic(Line, L"sgn", Complex::sgn);
				basic(Line, L"inverse", Complex::inverse);
				basic(Line, L"exp", Complex::exp);
				basic(Line, L"ln", Complex::ln);
				multiple(Line, L"dot", Complex::dot);
				multiple(Line, L"outer", Complex::outer);
				multiple(Line, L"even", Complex::even);
				multiple(Line, L"cross", Complex::cross);
				/****/
				tri(Line, L"sin", Complex::sin);
				tri(Line, L"cos", Complex::cos);
				tri(Line, L"tan", Complex::tan);
				tri(Line, L"csc", Complex::csc);
				tri(Line, L"sec", Complex::sec);
				tri(Line, L"cot", Complex::cot);
				tri(Line, L"sinh", Complex::sinh);
				tri(Line, L"cosh", Complex::cosh);
				tri(Line, L"tanh", Complex::tanh);
				tri(Line, L"csch", Complex::csch);
				tri(Line, L"sech", Complex::sech);
				tri(Line, L"coth", Complex::coth);
				arctri(Line, L"arcsin", Complex::arcsin);
				arctri(Line, L"arccos", Complex::arccos);
				arctri(Line, L"arctan", Complex::arctan);
				arctri(Line, L"arccsc", Complex::arccsc);
				arctri(Line, L"arcsec", Complex::arcsec);
				arctri(Line, L"arccot", Complex::arccot);
				arctri(Line, L"arcsinh", Complex::arcsinh);
				arctri(Line, L"arccosh", Complex::arccosh);
				arctri(Line, L"arctanh", Complex::arctanh);
				arctri(Line, L"arccsch", Complex::arccsch);
				arctri(Line, L"arcsech", Complex::arcsech);
				arctri(Line, L"arccoth", Complex::arccoth);
			}
			catch (const std::exception& ex) { Base::Exception(ex); }
		}
	};
}
