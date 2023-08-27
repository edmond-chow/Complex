#if (__cplusplus >= 201103L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201103L) && (_MSC_VER >= 1800))
#pragma once
#ifndef CMPLX
#define CMPLX
#include <string>
#include <stdexcept>
#pragma pack(push)
#pragma push_macro("CALL")
#pragma push_macro("CMPLX_INTERFACE")
#pragma push_macro("CMPLX_FUNC_CALL")
#pragma push_macro("CMPLX_FUNC_INSTANCE_CALL")
#if defined(X86) || defined(ARM)
#pragma pack(4)
#elif defined(X64) || defined(ARM64)
#pragma pack(8)
#endif
#if defined(__GNUG__)
#define CALL(c) __attribute__((c))
#define CMPLX_INTERFACE __attribute__((dllimport))
#if defined(DEBUG) || defined(X86) || defined(X64)
#define CMPLX_FUNC_CALL CALL(__stdcall__)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define CMPLX_FUNC_CALL CALL(__fastcall__)
#else
#define CMPLX_FUNC_CALL
#endif
#define CMPLX_FUNC_INSTANCE_CALL CALL(__thiscall__)
#elif defined(_MSVC_LANG)
#define CALL(c) c
#define CMPLX_INTERFACE __declspec(dllimport)
#if defined(DEBUG) || defined(X86) || defined(X64)
#define CMPLX_FUNC_CALL CALL(__stdcall)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define CMPLX_FUNC_CALL CALL(__fastcall)
#else
#define CMPLX_FUNC_CALL
#endif
#define CMPLX_FUNC_INSTANCE_CALL CALL(__thiscall)
#else
#define CALL(c)
#define CMPLX_INTERFACE
#define CMPLX_FUNC_CALL
#define CMPLX_FUNC_INSTANCE_CALL
#endif
namespace Cmplx
{
	namespace BaseType
	{
		enum struct index : std::int64_t
		{
			e1 = 1,
		};
		struct CMPLX_INTERFACE Vector1D
		{
		public:
			static const double pi;
			static const double e;
			static const Vector1D e1;
		private:
			///
			/// Initializer
			///
			double x1;
		public:
			explicit CMPLX_FUNC_INSTANCE_CALL Vector1D() noexcept;
			explicit CMPLX_FUNC_INSTANCE_CALL Vector1D(double x1) noexcept;
			CMPLX_FUNC_INSTANCE_CALL Vector1D(const Vector1D& Value) noexcept;
			///
			/// Operators
			///
			Vector1D CMPLX_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) &;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) & noexcept;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) const& noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator =(const Vector1D& Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator +=(const Vector1D& Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Vector1D>& Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator -=(const Vector1D& Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Vector1D>& Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator *=(double Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<double>& Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator /=(double Value) & noexcept;
			Vector1D& CMPLX_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<double>& Value) & noexcept;
			///
			/// Basic functions for constructing vectors
			///
			static double CMPLX_FUNC_CALL abs(const Vector1D& Value);
			static Vector1D CMPLX_FUNC_CALL sgn(const Vector1D& Value);
			static double CMPLX_FUNC_CALL dot(const Vector1D& Union, const Vector1D& Value) noexcept;
			static Vector1D CMPLX_FUNC_CALL cross(const Vector1D& Union, const Vector1D& Value) noexcept;
			///
			/// Conversion of Types
			///
			static std::wstring CMPLX_FUNC_CALL GetString(const Vector1D& Value);
			static Vector1D CMPLX_FUNC_CALL GetInstance(const std::wstring& Value);
		};
		bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator ==(const Vector1D& Union, const Vector1D& Value) noexcept;
		bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator !=(const Vector1D& Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Vector1D& Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Vector1D& Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(double Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(const Vector1D& Union, double Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator /(const Vector1D& Union, double Value) noexcept;
	}
	namespace MainType
	{
		enum struct index : std::int64_t
		{
			s = 0,
			i = 1,
		};
		struct CMPLX_INTERFACE Complex
		{
		public:
			static const double pi;
			static const double e;
			static const Complex i;
		private:
			///
			/// Initializer
			///
			double real;
			BaseType::Vector1D imaginary;
		public:
			explicit CMPLX_FUNC_INSTANCE_CALL Complex() noexcept;
			explicit CMPLX_FUNC_INSTANCE_CALL Complex(double s, const BaseType::Vector1D& v) noexcept;
			explicit CMPLX_FUNC_INSTANCE_CALL Complex(double s, double i) noexcept;
			CMPLX_FUNC_INSTANCE_CALL Complex(double Value) noexcept;
			CMPLX_FUNC_INSTANCE_CALL Complex(const BaseType::Vector1D& Value) noexcept;
			CMPLX_FUNC_INSTANCE_CALL Complex(const Complex& Value) noexcept;
			static double CMPLX_FUNC_CALL Scalar(const Complex& Value) noexcept;
			static BaseType::Vector1D CMPLX_FUNC_CALL Vector(const Complex& Value) noexcept;
			static double CMPLX_FUNC_CALL Re(const Complex& z) noexcept;
			static double CMPLX_FUNC_CALL Im(const Complex& z) noexcept;
			///
			/// Operators
			///
			Complex CMPLX_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) &;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) & noexcept;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) const& noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator ++() & noexcept;
			Complex CMPLX_FUNC_INSTANCE_CALL operator ++(int) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator --() & noexcept;
			Complex CMPLX_FUNC_INSTANCE_CALL operator --(int) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator =(const Complex& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator +=(const Complex& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Complex>& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator -=(const Complex& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Complex>& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator *=(const Complex& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<Complex>& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator /=(const Complex& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<Complex>& Value) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator ^=(std::int64_t Exponent) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept;
			///
			/// Basic functions for constructing numbers
			///
			static double CMPLX_FUNC_CALL abs(const Complex& Value);
			static double CMPLX_FUNC_CALL arg(const Complex& Value);
			static double CMPLX_FUNC_CALL arg(const Complex& Value, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL conjg(const Complex& Value);
			static Complex CMPLX_FUNC_CALL sgn(const Complex& Value);
			static Complex CMPLX_FUNC_CALL inverse(const Complex& Value);
			static Complex CMPLX_FUNC_CALL exp(const Complex& Value);
			static Complex CMPLX_FUNC_CALL ln(const Complex& Value);
			static Complex CMPLX_FUNC_CALL ln(const Complex& Value, std::int64_t Theta);
			///
			/// 1st rank tensor algorithms
			///
			static double CMPLX_FUNC_CALL dot(const Complex& Union, const Complex& Value) noexcept;
			static Complex CMPLX_FUNC_CALL outer(const Complex& Union, const Complex& Value) noexcept;
			static Complex CMPLX_FUNC_CALL even(const Complex& Union, const Complex& Value) noexcept;
			static Complex CMPLX_FUNC_CALL cross(const Complex& Union, const Complex& Value) noexcept;
			///
			/// Operation 3 algorithms
			///
			static Complex CMPLX_FUNC_CALL Power(const Complex& Base, const Complex& Exponent);
			static Complex CMPLX_FUNC_CALL Power(const Complex& Base, const Complex& Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL Power(const Complex& Base, double Exponent);
			static Complex CMPLX_FUNC_CALL Power(const Complex& Base, double Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL Root(const Complex& Base, const Complex& Exponent);
			static Complex CMPLX_FUNC_CALL Root(const Complex& Base, const Complex& Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL Root(const Complex& Base, double Exponent);
			static Complex CMPLX_FUNC_CALL Root(const Complex& Base, double Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL Log(const Complex& Base, const Complex& Number);
			static Complex CMPLX_FUNC_CALL Log(const Complex& Base, const Complex& Number, std::int64_t Theta, std::int64_t Phi);
			///
			/// Trigonometric functions
			///
			static Complex CMPLX_FUNC_CALL sin(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsin(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsin(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL sinh(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsinh(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsinh(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL cos(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccos(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccos(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL cosh(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccosh(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccosh(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL tan(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arctan(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arctan(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL tanh(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arctanh(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arctanh(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL csc(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccsc(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccsc(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL csch(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccsch(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccsch(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL sec(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsec(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsec(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL sech(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsech(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arcsech(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL cot(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccot(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccot(const Complex& Value, bool Sign, std::int64_t Period);
			static Complex CMPLX_FUNC_CALL coth(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccoth(const Complex& Value);
			static Complex CMPLX_FUNC_CALL arccoth(const Complex& Value, bool Sign, std::int64_t Period);
			///
			/// Conversion of Types
			///
			static std::wstring CMPLX_FUNC_CALL GetString(const Complex& Value);
			static Complex CMPLX_FUNC_CALL GetInstance(const std::wstring& Value);
		};
		bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator ==(const Complex& Union, const Complex& Value) noexcept;
		bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator !=(const Complex& Union, const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator ~(const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Complex& Union, const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Complex& Union, const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(const Complex& Union, const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator /(const Complex& Union, const Complex& Value) noexcept;
		Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator ^(const Complex& Base, std::int64_t Exponent) noexcept;
		/* suffix operator */
		inline Complex operator"" _c(long double Value) noexcept { return Complex(static_cast<double>(Value)); };
		inline Complex operator"" _c(unsigned long long int Value) noexcept { return operator"" _c(static_cast<long double>(Value)); };
	}
}
#pragma pack(pop)
#endif
#endif
