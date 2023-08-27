#if (__cplusplus >= 201103L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201103L) && (_MSC_VER >= 1800))
#pragma once
#ifndef SEDEN
#define SEDEN
#include <string>
#include <stdexcept>
#pragma pack(push)
#pragma push_macro("CALL")
#pragma push_macro("SEDEN_INTERFACE")
#pragma push_macro("SEDEN_FUNC_CALL")
#pragma push_macro("SEDEN_FUNC_INSTANCE_CALL")
#if defined(X86) || defined(ARM)
#pragma pack(4)
#elif defined(X64) || defined(ARM64)
#pragma pack(8)
#endif
#if defined(__GNUG__)
#define CALL(c) __attribute__((c))
#define SEDEN_INTERFACE __attribute__((dllimport))
#if defined(DEBUG) || defined(X86) || defined(X64)
#define SEDEN_FUNC_CALL CALL(__stdcall__)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define SEDEN_FUNC_CALL CALL(__fastcall__)
#else
#define SEDEN_FUNC_CALL
#endif
#define SEDEN_FUNC_INSTANCE_CALL CALL(__thiscall__)
#elif defined(_MSVC_LANG)
#define CALL(c) c
#define SEDEN_INTERFACE __declspec(dllimport)
#if defined(DEBUG) || defined(X86) || defined(X64)
#define SEDEN_FUNC_CALL CALL(__stdcall)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define SEDEN_FUNC_CALL CALL(__fastcall)
#else
#define SEDEN_FUNC_CALL
#endif
#define SEDEN_FUNC_INSTANCE_CALL CALL(__thiscall)
#else
#define CALL(c)
#define SEDEN_INTERFACE
#define SEDEN_FUNC_CALL
#define SEDEN_FUNC_INSTANCE_CALL
#endif
namespace Seden
{
	class SEDEN_INTERFACE Sedenion
	{
	public:
		static const double pi;
		static const double e;
	private:
		///
		/// Initializer
		///
		double* data;
		std::size_t size;
	public:
		explicit SEDEN_FUNC_INSTANCE_CALL Sedenion();
		explicit SEDEN_FUNC_INSTANCE_CALL Sedenion(const std::initializer_list<double>& numbers);
		SEDEN_FUNC_INSTANCE_CALL Sedenion(double Value);
		SEDEN_FUNC_INSTANCE_CALL Sedenion(const Sedenion& Value);
		SEDEN_FUNC_INSTANCE_CALL Sedenion(Sedenion&& Value) noexcept;
		SEDEN_FUNC_INSTANCE_CALL ~Sedenion() noexcept;
		static double SEDEN_FUNC_CALL Scalar(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL Vector(const Sedenion& Value);
		///
		/// Operators
		///
		Sedenion SEDEN_FUNC_INSTANCE_CALL operator ()() const;
		double& SEDEN_FUNC_INSTANCE_CALL operator [](std::int64_t i)&;
		const double& SEDEN_FUNC_INSTANCE_CALL operator [](std::int64_t i) const&;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator ++()&;
		Sedenion SEDEN_FUNC_INSTANCE_CALL operator ++(int)&;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator --()&;
		Sedenion SEDEN_FUNC_INSTANCE_CALL operator --(int)&;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator =(const Sedenion& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator =(Sedenion&& Value) & noexcept;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator +=(const Sedenion& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Sedenion>& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator -=(const Sedenion& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Sedenion>& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator *=(const Sedenion& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<Sedenion>& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator /=(double Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<double>& Value) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator ^=(std::int64_t Exponent)&;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator ^=(const std::initializer_list<std::int64_t>& Exponent)&;
		///
		/// Basic functions for constructing numbers
		///
		static double SEDEN_FUNC_CALL abs(const Sedenion& Value);
		static double SEDEN_FUNC_CALL arg(const Sedenion& Value);
		static double SEDEN_FUNC_CALL arg(const Sedenion& Value, std::int64_t Theta);
		static Sedenion SEDEN_FUNC_CALL conjg(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL sgn(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL inverse(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL exp(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL ln(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL ln(const Sedenion& Value, std::int64_t Theta);
		///
		/// 1st rank tensor algorithms
		///
		static double SEDEN_FUNC_CALL dot(const Sedenion& Union, const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL outer(const Sedenion& Union, const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL even(const Sedenion& Union, const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL cross(const Sedenion& Union, const Sedenion& Value);
		///
		/// Operation 3 algorithms
		///
		static Sedenion SEDEN_FUNC_CALL Power(const Sedenion& Base, const Sedenion& Exponent);
		static Sedenion SEDEN_FUNC_CALL Power(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
		static Sedenion SEDEN_FUNC_CALL Power(const Sedenion& Base, double Exponent);
		static Sedenion SEDEN_FUNC_CALL Power(const Sedenion& Base, double Exponent, std::int64_t Theta);
		static Sedenion SEDEN_FUNC_CALL Root(const Sedenion& Base, const Sedenion& Exponent);
		static Sedenion SEDEN_FUNC_CALL Root(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
		static Sedenion SEDEN_FUNC_CALL Root(const Sedenion& Base, double Exponent);
		static Sedenion SEDEN_FUNC_CALL Root(const Sedenion& Base, double Exponent, std::int64_t Theta);
		static Sedenion SEDEN_FUNC_CALL Log(const Sedenion& Base, const Sedenion& Number);
		static Sedenion SEDEN_FUNC_CALL Log(const Sedenion& Base, const Sedenion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega);
		///
		/// Trigonometric functions
		///
		static Sedenion SEDEN_FUNC_CALL sin(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsin(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsin(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL sinh(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsinh(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsinh(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL cos(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccos(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccos(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL cosh(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccosh(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccosh(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL tan(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arctan(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arctan(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL tanh(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arctanh(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arctanh(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL csc(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccsc(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccsc(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL csch(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccsch(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccsch(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL sec(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsec(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsec(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL sech(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsech(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arcsech(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL cot(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccot(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccot(const Sedenion& Value, bool Sign, std::int64_t Period);
		static Sedenion SEDEN_FUNC_CALL coth(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccoth(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL arccoth(const Sedenion& Value, bool Sign, std::int64_t Period);
		///
		/// Conversion of Types
		///
		static std::wstring SEDEN_FUNC_CALL CType_String(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL CType_Sedenion(const std::wstring& Value);
	};
	bool SEDEN_INTERFACE SEDEN_FUNC_CALL operator ==(const Sedenion& Union, const Sedenion& Value);
	bool SEDEN_INTERFACE SEDEN_FUNC_CALL operator !=(const Sedenion& Union, const Sedenion& Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator +(const Sedenion& Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator -(const Sedenion& Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator ~(const Sedenion& Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator +(const Sedenion& Union, const Sedenion& Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator -(const Sedenion& Union, const Sedenion& Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator *(const Sedenion& Union, const Sedenion& Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator /(const Sedenion& Union, double Value);
	Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator ^(const Sedenion& Base, std::int64_t Exponent);
	/* suffix operator */
	inline Sedenion operator"" _s(long double Value) { return Sedenion(static_cast<double>(Value)); };
	inline Sedenion operator"" _s(unsigned long long int Value) { return operator"" _s(static_cast<long double>(Value)); };
}
#pragma pop_macro("SEDEN_FUNC_INSTANCE_CALL")
#pragma pop_macro("SEDEN_FUNC_CALL")
#pragma pop_macro("SEDEN_INTERFACE")
#pragma pop_macro("CALL")
#pragma pack(pop)
#endif
#endif
