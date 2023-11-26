#if (__cplusplus >= 201103L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201103L) && (_MSC_VER >= 1800))
#pragma once
#ifndef QUTER
#define QUTER
#include <string>
#include <stdexcept>
#pragma pack(push)
#pragma push_macro("CALL")
#pragma push_macro("QUTER_INTERFACE")
#pragma push_macro("QUTER_FUNC_CALL")
#pragma push_macro("QUTER_FUNC_INSTANCE_CALL")
#if defined(X86) || defined(ARM)
#pragma pack(4)
#elif defined(X64) || defined(ARM64)
#pragma pack(8)
#endif
#define CALL(c)
#define QUTER_INTERFACE
#define QUTER_FUNC_CALL
#define QUTER_FUNC_INSTANCE_CALL
namespace Quter
{
	namespace BaseType
	{
		enum struct index : std::int64_t
		{
			e1 = 1,
			e2 = 2,
			e3 = 3,
		};
		struct QUTER_INTERFACE Vector3D
		{
		public:
			///
			/// constants
			///
			static const double pi;
			static const double e;
			static const Vector3D e1;
			static const Vector3D e2;
			static const Vector3D e3;
		private:
			///
			/// basis
			///
			double x1;
			double x2;
			double x3;
		public:
			explicit QUTER_FUNC_INSTANCE_CALL Vector3D() noexcept;
			explicit QUTER_FUNC_INSTANCE_CALL Vector3D(double x1, double x2, double x3) noexcept;
			QUTER_FUNC_INSTANCE_CALL Vector3D(const Vector3D& Value) noexcept;
			///
			/// operators
			///
			const Vector3D QUTER_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& QUTER_FUNC_INSTANCE_CALL operator [](index i) &;
			double& QUTER_FUNC_INSTANCE_CALL operator [](std::int64_t i) & noexcept;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](std::int64_t i) const& noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator =(const Vector3D& Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator +=(const Vector3D& Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Vector3D>& Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator -=(const Vector3D& Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Vector3D>& Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator *=(double Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<double>& Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator /=(double Value) & noexcept;
			Vector3D& QUTER_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<double>& Value) & noexcept;
			///
			/// fundamentals
			///
			static double QUTER_FUNC_CALL abs(const Vector3D& Value);
			static Vector3D QUTER_FUNC_CALL sgn(const Vector3D& Value);
			static double QUTER_FUNC_CALL dot(const Vector3D& Union, const Vector3D& Value) noexcept;
			static Vector3D QUTER_FUNC_CALL cross(const Vector3D& Union, const Vector3D& Value) noexcept;
			///
			/// conventions
			///
			static std::wstring QUTER_FUNC_CALL GetString(const Vector3D& Value);
			static Vector3D QUTER_FUNC_CALL GetInstance(const std::wstring& Value);
		};
		///
		/// operators
		///
		bool QUTER_INTERFACE QUTER_FUNC_CALL operator ==(const Vector3D& Union, const Vector3D& Value) noexcept;
		bool QUTER_INTERFACE QUTER_FUNC_CALL operator !=(const Vector3D& Union, const Vector3D& Value) noexcept;
		Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Vector3D& Value) noexcept;
		Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Vector3D& Value) noexcept;
		Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Vector3D& Union, const Vector3D& Value) noexcept;
		Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Vector3D& Union, const Vector3D& Value) noexcept;
		Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator *(double Union, const Vector3D& Value) noexcept;
		Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator *(const Vector3D& Union, double Value) noexcept;
		Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator /(const Vector3D& Union, double Value) noexcept;
	}
	namespace MainType
	{
		enum struct index : std::int64_t
		{
			s = 0,
			i = 1,
			j = 2,
			k = 3,
		};
		struct QUTER_INTERFACE Quaternion
		{
		public:
			///
			/// constants
			///
			static const double pi;
			static const double e;
			static const Quaternion i;
			static const Quaternion j;
			static const Quaternion k;
		private:
			///
			/// basis
			///
			double real;
			BaseType::Vector3D imaginary;
		public:
			explicit QUTER_FUNC_INSTANCE_CALL Quaternion() noexcept;
			explicit QUTER_FUNC_INSTANCE_CALL Quaternion(double s, const BaseType::Vector3D& v) noexcept;
			explicit QUTER_FUNC_INSTANCE_CALL Quaternion(double s, double i, double j, double k) noexcept;
			QUTER_FUNC_INSTANCE_CALL Quaternion(double Value) noexcept;
			QUTER_FUNC_INSTANCE_CALL Quaternion(const BaseType::Vector3D& Value) noexcept;
			QUTER_FUNC_INSTANCE_CALL Quaternion(const Quaternion& Value) noexcept;
			static double QUTER_FUNC_CALL Scalar(const Quaternion& Value) noexcept;
			static BaseType::Vector3D QUTER_FUNC_CALL Vector(const Quaternion& Value) noexcept;
            ///
			/// operators
			///
			const Quaternion QUTER_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& QUTER_FUNC_INSTANCE_CALL operator [](index i) &;
			double& QUTER_FUNC_INSTANCE_CALL operator [](std::int64_t i) & noexcept;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](std::int64_t i) const& noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator ++() & noexcept;
			const Quaternion QUTER_FUNC_INSTANCE_CALL operator ++(int) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator --() & noexcept;
			const Quaternion QUTER_FUNC_INSTANCE_CALL operator --(int) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator =(const Quaternion& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator +=(const Quaternion& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Quaternion>& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator -=(const Quaternion& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Quaternion>& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator *=(const Quaternion& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<Quaternion>& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator /=(const Quaternion& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<Quaternion>& Value) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator ^=(std::int64_t Exponent) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept;
			///
			/// fundamentals
			///
			static double QUTER_FUNC_CALL abs(const Quaternion& Value);
			static double QUTER_FUNC_CALL arg(const Quaternion& Value);
			static double QUTER_FUNC_CALL arg(const Quaternion& Value, std::int64_t Theta);
			static Quaternion QUTER_FUNC_CALL conjg(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL sgn(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL inverse(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL exp(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL ln(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL ln(const Quaternion& Value, std::int64_t Theta);
			///
			/// multiples
			///
			static double QUTER_FUNC_CALL dot(const Quaternion& Union, const Quaternion& Value) noexcept;
			static BaseType::Vector3D QUTER_FUNC_CALL outer(const Quaternion& Union, const Quaternion& Value) noexcept;
			static Quaternion QUTER_FUNC_CALL even(const Quaternion& Union, const Quaternion& Value) noexcept;
			static BaseType::Vector3D QUTER_FUNC_CALL cross(const Quaternion& Union, const Quaternion& Value) noexcept;
			///
			/// exponentials
			///
			static Quaternion QUTER_FUNC_CALL power(const Quaternion& Base, const Quaternion& Exponent);
			static Quaternion QUTER_FUNC_CALL power(const Quaternion& Base, const Quaternion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
			static Quaternion QUTER_FUNC_CALL power(const Quaternion& Base, double Exponent);
			static Quaternion QUTER_FUNC_CALL power(const Quaternion& Base, double Exponent, std::int64_t Theta);
			static Quaternion QUTER_FUNC_CALL root(const Quaternion& Base, const Quaternion& Exponent);
			static Quaternion QUTER_FUNC_CALL root(const Quaternion& Base, const Quaternion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
			static Quaternion QUTER_FUNC_CALL root(const Quaternion& Base, double Exponent);
			static Quaternion QUTER_FUNC_CALL root(const Quaternion& Base, double Exponent, std::int64_t Theta);
			static Quaternion QUTER_FUNC_CALL log(const Quaternion& Base, const Quaternion& Number);
			static Quaternion QUTER_FUNC_CALL log(const Quaternion& Base, const Quaternion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega);
			///
			/// trigonometrics
			///
			static Quaternion QUTER_FUNC_CALL sin(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsin(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsin(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL sinh(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsinh(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsinh(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL cos(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccos(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccos(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL cosh(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccosh(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccosh(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL tan(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arctan(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arctan(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL tanh(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arctanh(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arctanh(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL csc(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccsc(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccsc(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL csch(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccsch(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccsch(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL sec(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsec(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsec(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL sech(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsech(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arcsech(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL cot(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccot(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccot(const Quaternion& Value, bool Sign, std::int64_t Period);
			static Quaternion QUTER_FUNC_CALL coth(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccoth(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL arccoth(const Quaternion& Value, bool Sign, std::int64_t Period);
			///
			/// conventions
			///
			static std::wstring QUTER_FUNC_CALL GetString(const Quaternion& Value);
			static Quaternion QUTER_FUNC_CALL GetInstance(const std::wstring& Value);
		};
		///
		/// operators
		///
		bool QUTER_INTERFACE QUTER_FUNC_CALL operator ==(const Quaternion& Union, const Quaternion& Value) noexcept;
		bool QUTER_INTERFACE QUTER_FUNC_CALL operator !=(const Quaternion& Union, const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator ~(const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Quaternion& Union, const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Quaternion& Union, const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator *(const Quaternion& Union, const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator /(const Quaternion& Union, const Quaternion& Value) noexcept;
		Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator ^(const Quaternion& Base, std::int64_t Exponent) noexcept;
	}
}
#pragma pack(pop)
#endif
#endif
