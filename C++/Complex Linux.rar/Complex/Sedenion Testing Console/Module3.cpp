#include "Base.h"
#include "Complex 3.0.h"
using namespace SedenionTestingConsole;
using namespace Cmplx3;
using namespace Cmplx3::MainType;
namespace Mod3
{
	template <typename F = Octonion(CMPLX_UNIT_TEST_INTERFACE*)(const Octonion&, const Octonion&)>
	void op(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Octonion Union = Octonion::CType_Octonion(Base::Input(L"Union = "));
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Octonion Base = Octonion::CType_Octonion(Base::Input(L"Base = "));
			std::int64_t Exponent = stoi64_t(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(f, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& str, std::wstring&& ptr, Octonion(CMPLX_UNIT_TEST_INTERFACE* f)(const Octonion&, const Octonion&, std::int64_t, args...))
	{
		if (str == ptr)
		{
			Octonion Union = Octonion::CType_Octonion(Base::Input(L"Union = "));
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(f, ptr, Union, Value, Data);
		}
		else if (str == ptr + L"()")
		{
			Octonion Union = Octonion::CType_Octonion(Base::Input(L"Union = "));
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
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
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& str, std::wstring&& ptr, R(CMPLX_UNIT_TEST_INTERFACE* f)(const Octonion&, std::int64_t))
	{
		if (str == ptr)
		{
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
			std::int64_t Theta = stoi64_t(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(f, Value, Theta)));
		}
		else if (str == ptr + L"()")
		{
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
			std::int64_t ThetaMin = stoi64_t(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = stoi64_t(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(ptr + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(f, Value, Theta)));
			}
		}
	};
	template <typename F = Octonion(CMPLX_UNIT_TEST_INTERFACE*)(const Octonion&)>
	inline void tri(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename F = Octonion(CMPLX_UNIT_TEST_INTERFACE*)(const Octonion&, bool, std::int64_t)>
	inline void arctri(const std::wstring& str, std::wstring&& ptr, F f)
	{
		if (str == ptr)
		{
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = stoi64_t(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(f, Value, Sign, Period)));
		}
		else if (str == ptr + L"()")
		{
			Octonion Value = Octonion::CType_Octonion(Base::Input(L"Value = "));
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
	class MyModule3 final
	{
	private:
		constexpr MyModule3() noexcept = delete;
		constexpr ~MyModule3() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void MyModule3::Load() noexcept
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
				power(Str, L"Power", Octonion::Power);
				power(Str, L"Root", Octonion::Root);
				power(Str, L"Log", Octonion::Log);
				/****/
				basic(Str, L"abs", Octonion::abs);
				basic(Str, L"arg", Octonion::arg);
				basic(Str, L"conjg", Octonion::conjg);
				basic(Str, L"sgn", Octonion::sgn);
				basic(Str, L"inverse", Octonion::inverse);
				basic(Str, L"exp", Octonion::exp);
				basic(Str, L"ln", Octonion::ln);
				/****/
				tri(Str, L"sin", Octonion::sin);
				tri(Str, L"cos", Octonion::cos);
				tri(Str, L"tan", Octonion::tan);
				tri(Str, L"csc", Octonion::csc);
				tri(Str, L"sec", Octonion::sec);
				tri(Str, L"cot", Octonion::cot);
				tri(Str, L"sinh", Octonion::sinh);
				tri(Str, L"cosh", Octonion::cosh);
				tri(Str, L"tanh", Octonion::tanh);
				tri(Str, L"csch", Octonion::csch);
				tri(Str, L"sech", Octonion::sech);
				tri(Str, L"coth", Octonion::coth);
				arctri(Str, L"arcsin", Octonion::arcsin);
				arctri(Str, L"arccos", Octonion::arccos);
				arctri(Str, L"arctan", Octonion::arctan);
				arctri(Str, L"arccsc", Octonion::arccsc);
				arctri(Str, L"arcsec", Octonion::arcsec);
				arctri(Str, L"arccot", Octonion::arccot);
				arctri(Str, L"arcsinh", Octonion::arcsinh);
				arctri(Str, L"arccosh", Octonion::arccosh);
				arctri(Str, L"arctanh", Octonion::arctanh);
				arctri(Str, L"arccsch", Octonion::arccsch);
				arctri(Str, L"arcsech", Octonion::arcsech);
				arctri(Str, L"arccoth", Octonion::arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
