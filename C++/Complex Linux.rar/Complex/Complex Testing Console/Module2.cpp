#include "Base.h"
#include "Complex 2.0.h"
using namespace ComplexTestingConsole;
using namespace Cmplx2;
using namespace Cmplx2::MainType;
namespace Mod2
{
	template <typename F = Quaternion(CMPLX2_FUNC_CALL*)(const Quaternion&, const Quaternion&)>
	void op(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Quaternion Union = Quaternion::GetInstance(Base::Input(L"Union = "));
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Quaternion Base = Quaternion::GetInstance(Base::Input(L"Base = "));
			std::int64_t Exponent = stoi64_t(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(f, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& str, std::wstring&& ptr, Quaternion(CMPLX2_FUNC_CALL* f)(const Quaternion&, const Quaternion&, std::int64_t, args...))
	{
		if (str == ptr)
		{
			Quaternion Union = Quaternion::GetInstance(Base::Input(L"Union = "));
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(f, ptr, Union, Value, Data);
		}
		else if (str == ptr + L"()")
		{
			Quaternion Union = Quaternion::GetInstance(Base::Input(L"Union = "));
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
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
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& str, std::wstring&& ptr, R(CMPLX2_FUNC_CALL* f)(const Quaternion&, std::int64_t))
	{
		if (str == ptr)
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			std::int64_t Theta = stoi64_t(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(f, Value, Theta)));
		}
		else if (str == ptr + L"()")
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			std::int64_t ThetaMin = stoi64_t(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = stoi64_t(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(ptr + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(f, Value, Theta)));
			}
		}
	};
	template <typename F = Quaternion(CMPLX2_FUNC_CALL*)(const Quaternion&)>
	inline void tri(const std::wstring& str, const wchar_t* ptr, F f)
	{
		if (str == ptr)
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(f, Value)));
		}
	};
	template <typename F = Quaternion(CMPLX2_FUNC_CALL*)(const Quaternion&, bool, std::int64_t)>
	inline void arctri(const std::wstring& str, std::wstring&& ptr, F f)
	{
		if (str == ptr)
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = stoi64_t(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(f, Value, Sign, Period)));
		}
		else if (str == ptr + L"()")
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
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
	class MyModule2 final
	{
	private:
		constexpr MyModule2() noexcept = delete;
		constexpr ~MyModule2() noexcept = delete;
	public:
		static void Load() noexcept;
	};
	void MyModule2::Load() noexcept
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
				power(Str, L"Power", Quaternion::Power);
				power(Str, L"Root", Quaternion::Root);
				power(Str, L"Log", Quaternion::Log);
				/****/
				basic(Str, L"abs", Quaternion::abs);
				basic(Str, L"arg", Quaternion::arg);
				basic(Str, L"conjg", Quaternion::conjg);
				basic(Str, L"sgn", Quaternion::sgn);
				basic(Str, L"inverse", Quaternion::inverse);
				basic(Str, L"exp", Quaternion::exp);
				basic(Str, L"ln", Quaternion::ln);
				/****/
				tri(Str, L"sin", Quaternion::sin);
				tri(Str, L"cos", Quaternion::cos);
				tri(Str, L"tan", Quaternion::tan);
				tri(Str, L"csc", Quaternion::csc);
				tri(Str, L"sec", Quaternion::sec);
				tri(Str, L"cot", Quaternion::cot);
				tri(Str, L"sinh", Quaternion::sinh);
				tri(Str, L"cosh", Quaternion::cosh);
				tri(Str, L"tanh", Quaternion::tanh);
				tri(Str, L"csch", Quaternion::csch);
				tri(Str, L"sech", Quaternion::sech);
				tri(Str, L"coth", Quaternion::coth);
				arctri(Str, L"arcsin", Quaternion::arcsin);
				arctri(Str, L"arccos", Quaternion::arccos);
				arctri(Str, L"arctan", Quaternion::arctan);
				arctri(Str, L"arccsc", Quaternion::arccsc);
				arctri(Str, L"arcsec", Quaternion::arcsec);
				arctri(Str, L"arccot", Quaternion::arccot);
				arctri(Str, L"arcsinh", Quaternion::arcsinh);
				arctri(Str, L"arccosh", Quaternion::arccosh);
				arctri(Str, L"arctanh", Quaternion::arctanh);
				arctri(Str, L"arccsch", Quaternion::arccsch);
				arctri(Str, L"arcsech", Quaternion::arcsech);
				arctri(Str, L"arccoth", Quaternion::arccoth);
			}
			catch (const std::exception& ex) { Base::Exception(ex); }
		}
	};
}
