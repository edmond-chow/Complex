#include "Base.h"
#include "Complex 2.0.h"
using namespace SedenionTestingConsole;
using namespace Cmplx2;
using namespace Cmplx2::MainType;
namespace Mod2
{
	template <typename F = Quaternion(CMPLX2_FUNC_CALL*)(const Quaternion&, const Quaternion&)>
	void op(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Quaternion Union = Quaternion::GetInstance(Base::Input(L"Union = "));
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Union, Value)));
		}
	};
	template <typename F>
	void power(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Quaternion Base = Quaternion::GetInstance(Base::Input(L"Base = "));
			std::int64_t Exponent = stoi64_t(Base::Input(L"Exponent = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Base, Exponent)));
		}
	};
	template <typename... args>
	void power(const std::wstring& LeftValue, std::wstring&& RightValue, Quaternion(CMPLX2_FUNC_CALL* Subroutine)(const Quaternion&, const Quaternion&, std::int64_t, args...))
	{
		if (LeftValue == RightValue)
		{
			Quaternion Union = Quaternion::GetInstance(Base::Input(L"Union = "));
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			std::array<std::int64_t, 1 + sizeof...(args)> Data{};
			power_get(Data);
			power_result(Subroutine, RightValue, Union, Value, Data);
		}
		else if (LeftValue == RightValue + L"()")
		{
			Quaternion Union = Quaternion::GetInstance(Base::Input(L"Union = "));
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
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
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename R>
	void basic(const std::wstring& LeftValue, std::wstring&& RightValue, R(CMPLX2_FUNC_CALL* Subroutine)(const Quaternion&, std::int64_t))
	{
		if (LeftValue == RightValue)
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			std::int64_t Theta = stoi64_t(Base::Input(L"Theta = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Theta)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			std::int64_t ThetaMin = stoi64_t(Base::Input(L"ThetaMin = "));
			std::int64_t ThetaMax = stoi64_t(Base::Input(L"ThetaMax = "));
			for (std::int64_t Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
			{
				Base::Output(RightValue + L"(" + to_wstring(Theta) + L") = ", to_wstring(std::invoke(Subroutine, Value, Theta)));
			}
		}
	};
	template <typename F = Quaternion(CMPLX2_FUNC_CALL*)(const Quaternion&)>
	inline void tri(const std::wstring& LeftValue, const wchar_t* RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value)));
		}
	};
	template <typename F = Quaternion(CMPLX2_FUNC_CALL*)(const Quaternion&, bool, std::int64_t)>
	inline void arctri(const std::wstring& LeftValue, std::wstring&& RightValue, F Subroutine)
	{
		if (LeftValue == RightValue)
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
			bool Sign = false;
			std::wstring Input = std::regex_replace(Base::Input(L"Sign : "), std::wregex(L" "), L"");
			if (Input == L"+") { Sign = true; }
			else if (Input != L"-") { throw std::invalid_argument("A string interpretation of the sign cannot be converted as a bool value."); }
			std::int64_t Period = stoi64_t(Base::Input(L"Period = "));
			Base::Output(to_wstring(std::invoke(Subroutine, Value, Sign, Period)));
		}
		else if (LeftValue == RightValue + L"()")
		{
			Quaternion Value = Quaternion::GetInstance(Base::Input(L"Value = "));
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
				power(Line, L"power", Quaternion::power);
				power(Line, L"root", Quaternion::root);
				power(Line, L"log", Quaternion::log);
				/****/
				basic(Line, L"abs", Quaternion::abs);
				basic(Line, L"arg", Quaternion::arg);
				basic(Line, L"conjg", Quaternion::conjg);
				basic(Line, L"sgn", Quaternion::sgn);
				basic(Line, L"inverse", Quaternion::inverse);
				basic(Line, L"exp", Quaternion::exp);
				basic(Line, L"ln", Quaternion::ln);
				/****/
				tri(Line, L"sin", Quaternion::sin);
				tri(Line, L"cos", Quaternion::cos);
				tri(Line, L"tan", Quaternion::tan);
				tri(Line, L"csc", Quaternion::csc);
				tri(Line, L"sec", Quaternion::sec);
				tri(Line, L"cot", Quaternion::cot);
				tri(Line, L"sinh", Quaternion::sinh);
				tri(Line, L"cosh", Quaternion::cosh);
				tri(Line, L"tanh", Quaternion::tanh);
				tri(Line, L"csch", Quaternion::csch);
				tri(Line, L"sech", Quaternion::sech);
				tri(Line, L"coth", Quaternion::coth);
				arctri(Line, L"arcsin", Quaternion::arcsin);
				arctri(Line, L"arccos", Quaternion::arccos);
				arctri(Line, L"arctan", Quaternion::arctan);
				arctri(Line, L"arccsc", Quaternion::arccsc);
				arctri(Line, L"arcsec", Quaternion::arcsec);
				arctri(Line, L"arccot", Quaternion::arccot);
				arctri(Line, L"arcsinh", Quaternion::arcsinh);
				arctri(Line, L"arccosh", Quaternion::arccosh);
				arctri(Line, L"arctanh", Quaternion::arctanh);
				arctri(Line, L"arccsch", Quaternion::arccsch);
				arctri(Line, L"arcsech", Quaternion::arcsech);
				arctri(Line, L"arccoth", Quaternion::arccoth);
			}
			catch (const std::exception& ex) { Base::Exception(ex); }
		}
	};
}
