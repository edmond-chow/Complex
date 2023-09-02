#if (__cplusplus >= 201103L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201103L) && (_MSC_VER >= 1800))
#pragma once
#ifndef CMPLX_3
#define CMPLX_3
#include <string>
#include <stdexcept>
#pragma pack(push)
#pragma push_macro("CALL")
#pragma push_macro("CMPLX3_INTERFACE")
#pragma push_macro("CMPLX3_FUNC_CALL")
#pragma push_macro("CMPLX3_FUNC_INSTANCE_CALL")
#if defined(X86) || defined(ARM)
#pragma pack(4)
#elif defined(X64) || defined(ARM64)
#pragma pack(8)
#endif
#define CALL(c)
#define CMPLX3_INTERFACE
#define CMPLX3_FUNC_CALL
#define CMPLX3_FUNC_INSTANCE_CALL
namespace Cmplx3
{
	namespace BaseType
	{
		enum struct index : std::int64_t
		{
			e1 = 1,
			e2 = 2,
			e3 = 3,
			e4 = 4,
			e5 = 5,
			e6 = 6,
			e7 = 7,
		};
		struct CMPLX3_INTERFACE Vector7D
		{
		public:
			static const double pi;
			static const double e;
			static const Vector7D e1;
			static const Vector7D e2;
			static const Vector7D e3;
			static const Vector7D e4;
			static const Vector7D e5;
			static const Vector7D e6;
			static const Vector7D e7;
		private:
			///
			/// Initializer
			///
			double x1;
			double x2;
			double x3;
			double x4;
			double x5;
			double x6;
			double x7;
		public:
			explicit CMPLX3_FUNC_INSTANCE_CALL Vector7D() noexcept;
			explicit CMPLX3_FUNC_INSTANCE_CALL Vector7D(double x1, double x2, double x3, double x4, double x5, double x6, double x7) noexcept;
			CMPLX3_FUNC_INSTANCE_CALL Vector7D(const Vector7D& Value) noexcept;
			///
			/// Operators
			///
			Vector7D CMPLX3_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& CMPLX3_FUNC_INSTANCE_CALL operator [](index i) &;
			double& CMPLX3_FUNC_INSTANCE_CALL operator [](std::int64_t i) &;
			const double& CMPLX3_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& CMPLX3_FUNC_INSTANCE_CALL operator [](std::int64_t i) const&;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator =(const Vector7D& Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator +=(const Vector7D& Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Vector7D>& Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator -=(const Vector7D& Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Vector7D>& Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator *=(double Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<double>& Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator /=(double Value) & noexcept;
			Vector7D& CMPLX3_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<double>& Value) & noexcept;
			///
			/// Basic functions for constructing vectors
			///
			static double CMPLX3_FUNC_CALL abs(const Vector7D& Value);
			static Vector7D CMPLX3_FUNC_CALL sgn(const Vector7D& Value);
			static double CMPLX3_FUNC_CALL dot(const Vector7D& Union, const Vector7D& Value) noexcept;
			static Vector7D CMPLX3_FUNC_CALL cross(const Vector7D& Union, const Vector7D& Value) noexcept;
			///
			/// Conversion of Types
			///
			static std::wstring CMPLX3_FUNC_CALL GetString(const Vector7D& Value);
			static Vector7D CMPLX3_FUNC_CALL GetInstance(const std::wstring& Value);
		};
		bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ==(const Vector7D& Union, const Vector7D& Value) noexcept;
		bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator !=(const Vector7D& Union, const Vector7D& Value) noexcept;
		Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Vector7D& Value) noexcept;
		Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Vector7D& Value) noexcept;
		Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Vector7D& Union, const Vector7D& Value) noexcept;
		Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Vector7D& Union, const Vector7D& Value) noexcept;
		Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator *(double Union, const Vector7D& Value) noexcept;
		Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator *(const Vector7D& Union, double Value) noexcept;
		Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator /(const Vector7D& Union, double Value) noexcept;
	}
	namespace MainType
	{
		enum struct index : std::int64_t
		{
			s = 0,
			i = 1,
			j = 2,
			k = 3,
			l = 4,
			il = 5,
			jl = 6,
			kl = 7,
		};
		struct CMPLX3_INTERFACE Octonion
		{
		public:
			static const double pi;
			static const double e;
			static const Octonion i;
			static const Octonion j;
			static const Octonion k;
			static const Octonion l;
			static const Octonion il;
			static const Octonion jl;
			static const Octonion kl;
		private:
			///
			/// Initializer
			///
			double real;
			BaseType::Vector7D imaginary;
		public:
			explicit CMPLX3_FUNC_INSTANCE_CALL Octonion() noexcept;
			explicit CMPLX3_FUNC_INSTANCE_CALL Octonion(double s, const BaseType::Vector7D& v) noexcept;
			explicit CMPLX3_FUNC_INSTANCE_CALL Octonion(double s, double i, double j, double k, double l, double il, double jl, double kl) noexcept;
			CMPLX3_FUNC_INSTANCE_CALL Octonion(double Value) noexcept;
			CMPLX3_FUNC_INSTANCE_CALL Octonion(const BaseType::Vector7D& Value) noexcept;
			CMPLX3_FUNC_INSTANCE_CALL Octonion(const Octonion& Value) noexcept;
			static double CMPLX3_FUNC_CALL Scalar(const Octonion& Value) noexcept;
			static BaseType::Vector7D CMPLX3_FUNC_CALL Vector(const Octonion& Value) noexcept;
			///
			/// Operators
			///
			Octonion CMPLX3_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& CMPLX3_FUNC_INSTANCE_CALL operator [](index i) &;
			double& CMPLX3_FUNC_INSTANCE_CALL operator [](std::int64_t i) &;
			const double& CMPLX3_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& CMPLX3_FUNC_INSTANCE_CALL operator [](std::int64_t i) const&;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator ++() & noexcept;
			Octonion CMPLX3_FUNC_INSTANCE_CALL operator ++(int) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator --() & noexcept;
			Octonion CMPLX3_FUNC_INSTANCE_CALL operator --(int) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator =(const Octonion& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator +=(const Octonion& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator -=(const Octonion& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator *=(const Octonion& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator /= (const Octonion& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator ^=(std::int64_t Exponent) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept;
			///
			/// Basic functions for constructing numbers
			///
			static double CMPLX3_FUNC_CALL abs(const Octonion& Value);
			static double CMPLX3_FUNC_CALL arg(const Octonion& Value);
			static double CMPLX3_FUNC_CALL arg(const Octonion& Value, std::int64_t Theta);
			static Octonion CMPLX3_FUNC_CALL conjg(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL sgn(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL inverse(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL exp(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL ln(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL ln(const Octonion& Value, std::int64_t Theta);
			///
			/// 1st rank tensor algorithms
			///
			static double CMPLX3_FUNC_CALL dot(const Octonion& Union, const Octonion& Value) noexcept;
			static Octonion CMPLX3_FUNC_CALL outer(const Octonion& Union, const Octonion& Value) noexcept;
			static Octonion CMPLX3_FUNC_CALL even(const Octonion& Union, const Octonion& Value) noexcept;
			static Octonion CMPLX3_FUNC_CALL cross(const Octonion& Union, const Octonion& Value) noexcept;
			///
			/// Operation 3 algorithms
			///
			static Octonion CMPLX3_FUNC_CALL power(const Octonion& Base, const Octonion& Exponent);
			static Octonion CMPLX3_FUNC_CALL power(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
			static Octonion CMPLX3_FUNC_CALL power(const Octonion& Base, double Exponent);
			static Octonion CMPLX3_FUNC_CALL power(const Octonion& Base, double Exponent, std::int64_t Theta);
			static Octonion CMPLX3_FUNC_CALL root(const Octonion& Base, const Octonion& Exponent);
			static Octonion CMPLX3_FUNC_CALL root(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
			static Octonion CMPLX3_FUNC_CALL root(const Octonion& Base, double Exponent);
			static Octonion CMPLX3_FUNC_CALL root(const Octonion& Base, double Exponent, std::int64_t Theta);
			static Octonion CMPLX3_FUNC_CALL log(const Octonion& Base, const Octonion& Number);
			static Octonion CMPLX3_FUNC_CALL log(const Octonion& Base, const Octonion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega);
			///
			/// Trigonometric functions
			///
			static Octonion CMPLX3_FUNC_CALL sin(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsin(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsin(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL sinh(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsinh(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsinh(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL cos(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccos(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccos(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL cosh(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccosh(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccosh(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL tan(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arctan(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arctan(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL tanh(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arctanh(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arctanh(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL csc(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccsc(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccsc(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL csch(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccsch(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccsch(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL sec(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsec(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsec(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL sech(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsech(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arcsech(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL cot(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccot(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccot(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion CMPLX3_FUNC_CALL coth(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccoth(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL arccoth(const Octonion& Value, bool Sign, std::int64_t Period);
			///
			/// Conversion of Types
			///
			static std::wstring CMPLX3_FUNC_CALL GetString(const Octonion& Value);
			static Octonion CMPLX3_FUNC_CALL GetInstance(const std::wstring& Value);
		};
		bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ==(const Octonion& Union, const Octonion& Value) noexcept;
		bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator !=(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ~(const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator *(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator /(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ^(const Octonion& Base, std::int64_t Exponent) noexcept;
		/* suffix operator */
		inline Octonion operator"" _o(long double Value) noexcept { return Octonion(static_cast<double>(Value)); };
		inline Octonion operator"" _o(unsigned long long int Value) noexcept { return operator"" _o(static_cast<long double>(Value)); };
	}
}
#pragma pack(pop)
#endif
#endif
