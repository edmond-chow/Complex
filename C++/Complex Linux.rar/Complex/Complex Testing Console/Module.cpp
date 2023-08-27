#include "Base.h"
#include "Complex.h"
using namespace ComplexTestingConsole;
using namespace Cmplx;
using namespace Cmplx::MainType;
namespace Mod
{
	template <typename F = Complex(CMPLX_UNIT_TEST_INTERFACE*)(const Complex&, const Complex&)>
	void op(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Complex Union = Complex::CType_Complex(Base::Input(L"Union = "));
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Complex Base = Complex::CType_Complex(Base::Input(L"Base = "));
			std::int64_t Exponent = stoi64_t(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(f, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& str, std::wstring&& ptr, Complex(CMPLX_UNIT_TEST_INTERFACE* f)(const Complex&, const Complex&, std::int64_t, args...))
	{
		if (str == ptr)
		{
			Complex Union = Complex::CType_Complex(Base::Input(L"Union = "));
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(f, ptr, Union, Value, Data);
		}
		else if (str == ptr + L"()")
		{
			Complex Union = Complex::CType_Complex(Base::Input(L"Union = "));
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			std::array<std::pair<std::int64_t, std::int64_t>, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(f, ptr, Union, Value, Data);
		}
	};
	template <typename F>
	void basic(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& str, std::wstring&& ptr, R(CMPLX_UNIT_TEST_INTERFACE* f)(const Complex&, std::int64_t))
	{
		if (str == ptr)
		{
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			std::int64_t Theta = stoi64_t(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(f, Value, Theta)));
		}
		else if (str == ptr + L"()")
		{
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			std::int64_t ThetaMin = stoi64_t(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = stoi64_t(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(ptr + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(f, Value, Theta)));
			}
		}
	};
	template <typename F = Complex(CMPLX_UNIT_TEST_INTERFACE*)(const Complex&)>
	inline void tri(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename F = Complex(CMPLX_UNIT_TEST_INTERFACE*)(const Complex&, bool, std::int64_t)>
	inline void arctri(const std::wstring& str, std::wstring&& ptr, F f)
	{
		if (str == ptr)
		{
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = stoi64_t(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(f, Value, Sign, Period)));
		}
		else if (str == ptr + L"()")
		{
			Complex Value = Complex::CType_Complex(Base::Input(L"Value = "));
			std::int64_t PeriodMin = stoi64_t(Base::Input(L"PeriodMin = "));
			std::int64_t PeriodMax = stoi64_t(Base::Input(L"PeriodMax = "));
			for (std::int64_t Period = PeriodMin; Period <= PeriodMax; ++Period)
			{
				Base::Output(ptr + L"(+, " + to_wstring(Period) + L") = ", to_wstring(std::invoke(f, Value, true, Period)));
			}
			for (std::int64_t Period = PeriodMin; Period <= PeriodMax; ++Period)
			{
				Base::Output(ptr + L"(-, " + to_wstring(Period) + L") = ", to_wstring(std::invoke(f, Value, false, Period)));
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
		Base::Selection(L"=   +   -   *   /   ^   Power()   Root()   Log()");
		Base::Selection(L"abs   arg()   conjg   sgn   inverse   exp   ln()");
		Base::Selection(L"sin   cos   tan   csc   sec   cot   arcsin()   arccos()   arctan()   arccsc()   arcsec()   arccot()");
		Base::Selection(L"sinh   cosh   tanh   csch   sech   coth   arcsinh()   arccosh()   arctanh()   arccsch()   arcsech()   arccoth()");
		Base::Selection(Base::GetStartupLine());
		for (std::wstring Str; !Base::IsSwitchTo(Str); Str = Base::Input())
		{
			if (Str.empty()) { continue; }
			try
			{
				op(Str, L"=", operator ==);
				op(Str, L"+", operator +);
				op(Str, L"-", operator -);
				op(Str, L"*", operator *);
				op(Str, L"/", operator /);
				/****/
				power(Str, L"^", operator ^);
				power(Str, L"Power", Complex::Power);
				power(Str, L"Root", Complex::Root);
				power(Str, L"Log", Complex::Log);
				/****/
				basic(Str, L"abs", Complex::abs);
				basic(Str, L"arg", Complex::arg);
				basic(Str, L"conjg", Complex::conjg);
				basic(Str, L"sgn", Complex::sgn);
				basic(Str, L"inverse", Complex::inverse);
				basic(Str, L"exp", Complex::exp);
				basic(Str, L"ln", Complex::ln);
				/****/
				tri(Str, L"sin", Complex::sin);
				tri(Str, L"cos", Complex::cos);
				tri(Str, L"tan", Complex::tan);
				tri(Str, L"csc", Complex::csc);
				tri(Str, L"sec", Complex::sec);
				tri(Str, L"cot", Complex::cot);
				tri(Str, L"sinh", Complex::sinh);
				tri(Str, L"cosh", Complex::cosh);
				tri(Str, L"tanh", Complex::tanh);
				tri(Str, L"csch", Complex::csch);
				tri(Str, L"sech", Complex::sech);
				tri(Str, L"coth", Complex::coth);
				arctri(Str, L"arcsin", Complex::arcsin);
				arctri(Str, L"arccos", Complex::arccos);
				arctri(Str, L"arctan", Complex::arctan);
				arctri(Str, L"arccsc", Complex::arccsc);
				arctri(Str, L"arcsec", Complex::arcsec);
				arctri(Str, L"arccot", Complex::arccot);
				arctri(Str, L"arcsinh", Complex::arcsinh);
				arctri(Str, L"arccosh", Complex::arccosh);
				arctri(Str, L"arctanh", Complex::arctanh);
				arctri(Str, L"arccsch", Complex::arccsch);
				arctri(Str, L"arcsech", Complex::arcsech);
				arctri(Str, L"arccoth", Complex::arccoth);
			}
			catch (const std::exception& ex) { Base::Exception(ex); }
		}
	};
}
