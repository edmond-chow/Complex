#include "Base.h"
#include "Sedenion.h"
using namespace ComplexTestingConsole;
using namespace Seden;
namespace SedenionMod
{
	inline double stod_t(const std::wstring& str)
	{
		std::wstring result = std::regex_replace(str, std::wregex(L" "), L"");
		return std::stod(str);
	};
	template <typename F = Sedenion(CMPLX_UNIT_TEST_INTERFACE*)(const Sedenion&, const Sedenion&)>
	void op(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Sedenion Union = Sedenion::CType_Sedenion(Base::Input(L"Union = "));
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Union, Value)));
		}
	};
	inline void op(const std::wstring& str, const wchar_t* ptr, Sedenion(CMPLX_UNIT_TEST_INTERFACE* f)(const Sedenion&, double))
	{
		if (str == ptr)
		{
			Sedenion Union = Sedenion::CType_Sedenion(Base::Input(L"Union = "));
			double Value = stod_t(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Sedenion Base = Sedenion::CType_Sedenion(Base::Input(L"Base = "));
			std::int64_t Exponent = stoi64_t(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(f, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& str, std::wstring&& ptr, Sedenion(CMPLX_UNIT_TEST_INTERFACE* f)(const Sedenion&, const Sedenion&, std::int64_t, args...))
	{
		if (str == ptr)
		{
			Sedenion Union = Sedenion::CType_Sedenion(Base::Input(L"Union = "));
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(f, ptr, Union, Value, Data);
		}
		else if (str == ptr + L"()")
		{
			Sedenion Union = Sedenion::CType_Sedenion(Base::Input(L"Union = "));
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
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
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& str, std::wstring&& ptr, R(CMPLX_UNIT_TEST_INTERFACE* f)(const Sedenion&, std::int64_t))
	{
		if (str == ptr)
		{
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
			std::int64_t Theta = stoi64_t(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(f, Value, Theta)));
		}
		else if (str == ptr + L"()")
		{
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
			std::int64_t ThetaMin = stoi64_t(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = stoi64_t(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(ptr + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(f, Value, Theta)));
			}
		}
	};
	template <typename F = Sedenion(CMPLX_UNIT_TEST_INTERFACE*)(const Sedenion&)>
	inline void tri(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename F = Sedenion(CMPLX_UNIT_TEST_INTERFACE*)(const Sedenion&, bool, std::int64_t)>
	inline void arctri(const std::wstring& str, std::wstring&& ptr, F f)
	{
		if (str == ptr)
		{
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = stoi64_t(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(f, Value, Sign, Period)));
		}
		else if (str == ptr + L"()")
		{
			Sedenion Value = Sedenion::CType_Sedenion(Base::Input(L"Value = "));
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
		Base::Startup(Base::GetTitle() + L" (" + Base::GetSedenTitle() + L")");
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
				power(Str, L"Power", Sedenion::Power);
				power(Str, L"Root", Sedenion::Root);
				power(Str, L"Log", Sedenion::Log);
				/****/
				basic(Str, L"abs", Sedenion::abs);
				basic(Str, L"arg", Sedenion::arg);
				basic(Str, L"conjg", Sedenion::conjg);
				basic(Str, L"sgn", Sedenion::sgn);
				basic(Str, L"inverse", Sedenion::inverse);
				basic(Str, L"exp", Sedenion::exp);
				basic(Str, L"ln", Sedenion::ln);
				/****/
				tri(Str, L"sin", Sedenion::sin);
				tri(Str, L"cos", Sedenion::cos);
				tri(Str, L"tan", Sedenion::tan);
				tri(Str, L"csc", Sedenion::csc);
				tri(Str, L"sec", Sedenion::sec);
				tri(Str, L"cot", Sedenion::cot);
				tri(Str, L"sinh", Sedenion::sinh);
				tri(Str, L"cosh", Sedenion::cosh);
				tri(Str, L"tanh", Sedenion::tanh);
				tri(Str, L"csch", Sedenion::csch);
				tri(Str, L"sech", Sedenion::sech);
				tri(Str, L"coth", Sedenion::coth);
				arctri(Str, L"arcsin", Sedenion::arcsin);
				arctri(Str, L"arccos", Sedenion::arccos);
				arctri(Str, L"arctan", Sedenion::arctan);
				arctri(Str, L"arccsc", Sedenion::arccsc);
				arctri(Str, L"arcsec", Sedenion::arcsec);
				arctri(Str, L"arccot", Sedenion::arccot);
				arctri(Str, L"arcsinh", Sedenion::arcsinh);
				arctri(Str, L"arccosh", Sedenion::arccosh);
				arctri(Str, L"arctanh", Sedenion::arctanh);
				arctri(Str, L"arccsch", Sedenion::arccsch);
				arctri(Str, L"arcsech", Sedenion::arcsech);
				arctri(Str, L"arccoth", Sedenion::arccoth);
			}
			catch (const std::exception& Ex) { Base::Exception(Ex); }
		}
	};
}
