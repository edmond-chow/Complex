#include <cmath>
#include <numbers>
#include <stdexcept>
#include "Module.h"
#include "Cayley Dickson Algebra.h"
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
#if defined(__GNUG__)
#define CALL(c) __attribute__((c))
#define CMPLX3_INTERFACE __attribute__((dllexport))
#if defined(DEBUG) || defined(X86) || defined(X64)
#define CMPLX3_FUNC_CALL CALL(__stdcall__)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define CMPLX3_FUNC_CALL CALL(__fastcall__)
#else
#define CMPLX3_FUNC_CALL
#endif
#define CMPLX3_FUNC_INSTANCE_CALL CALL(__thiscall__)
#elif defined(_MSVC_LANG)
#define CALL(c) c
#define CMPLX3_INTERFACE __declspec(dllexport)
#if defined(DEBUG) || defined(X86) || defined(X64)
#define CMPLX3_FUNC_CALL CALL(__stdcall)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define CMPLX3_FUNC_CALL CALL(__fastcall)
#else
#define CMPLX3_FUNC_CALL
#endif
#define CMPLX3_FUNC_INSTANCE_CALL CALL(__thiscall)
#else
#define CALL(c)
#define CMPLX3_INTERFACE
#define CMPLX3_FUNC_CALL
#define CMPLX3_FUNC_INSTANCE_CALL
#endif
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
			friend bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ==(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator !=(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Vector7D& Value) noexcept;
			friend Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Vector7D& Value) noexcept;
			friend Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator *(double Union, const Vector7D& Value) noexcept;
			friend Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator *(const Vector7D& Union, double Value) noexcept;
			friend Vector7D CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator /(const Vector7D& Union, double Value) noexcept;
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
			/* Casting */
			inline auto to_number() const& noexcept
				-> decltype(forward_as_number(0, (*this)[index::e1], (*this)[index::e2], (*this)[index::e3], (*this)[index::e4], (*this)[index::e5], (*this)[index::e6], (*this)[index::e7]))
			{
				return forward_as_number(0, (*this)[index::e1], (*this)[index::e2], (*this)[index::e3], (*this)[index::e4], (*this)[index::e5], (*this)[index::e6], (*this)[index::e7]);
			};
			template <std::size_t N>
			inline auto from(const Number<N>& number) && noexcept -> decltype(*this)
			{
				double temp{};
				number.store(temp, (*this)[index::e1], (*this)[index::e2], (*this)[index::e3], (*this)[index::e4], (*this)[index::e5], (*this)[index::e6], (*this)[index::e7]);
				return *this;
			};
			static double build_in_dot(const Vector7D& Union, const Vector7D& Value);
			static Vector7D build_in_cross(const Vector7D& Union, const Vector7D& Value);
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
		/* struct Vector7D */
		const double Vector7D::pi = std::numbers::pi;
		const double Vector7D::e = std::numbers::e;
		const Vector7D Vector7D::e1 = Vector7D(1, 0, 0, 0, 0, 0, 0);
		const Vector7D Vector7D::e2 = Vector7D(0, 1, 0, 0, 0, 0, 0);
		const Vector7D Vector7D::e3 = Vector7D(0, 0, 1, 0, 0, 0, 0);
		const Vector7D Vector7D::e4 = Vector7D(0, 0, 0, 1, 0, 0, 0);
		const Vector7D Vector7D::e5 = Vector7D(0, 0, 0, 0, 1, 0, 0);
		const Vector7D Vector7D::e6 = Vector7D(0, 0, 0, 0, 0, 1, 0);
		const Vector7D Vector7D::e7 = Vector7D(0, 0, 0, 0, 0, 0, 1);
		///
		/// Initializer
		///
		CMPLX3_FUNC_INSTANCE_CALL Vector7D::Vector7D() noexcept : x1(), x2(), x3(), x4(), x5(), x6(), x7() {};
		CMPLX3_FUNC_INSTANCE_CALL Vector7D::Vector7D(double x1, double x2, double x3, double x4, double x5, double x6, double x7) noexcept : x1(x1), x2(x2), x3(x3), x4(x4), x5(x5), x6(x6), x7(x7) {};
		CMPLX3_FUNC_INSTANCE_CALL Vector7D::Vector7D(const Vector7D& Value) noexcept : x1(Value.x1), x2(Value.x2), x3(Value.x3), x4(Value.x4), x5(Value.x5), x6(Value.x6), x7(Value.x7) {};
		///
		/// Operators
		///
		Vector7D CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator ()() const noexcept { return *this; };
		double& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator [](index i) &
		{
			switch (i)
			{
			case index::e1:
				return this->x1;
			case index::e2:
				return this->x2;
			case index::e3:
				return this->x3;
			case index::e4:
				return this->x4;
			case index::e5:
				return this->x5;
			case index::e6:
				return this->x6;
			case index::e7:
				return this->x7;
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		double& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator [](std::int64_t i) &
		{
			try { return this->operator[](static_cast<index>(PeriodShift(i, Period<Vector7D>))); }
			catch (...) { return this->operator[](i); }
		};
		const double& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator [](index i) const&
		{
			switch (i)
			{
			case index::e1:
				return this->x1;
			case index::e2:
				return this->x2;
			case index::e3:
				return this->x3;
			case index::e4:
				return this->x4;
			case index::e5:
				return this->x5;
			case index::e6:
				return this->x6;
			case index::e7:
				return this->x7;
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		const double& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator [](std::int64_t i) const&
		{
			try { return this->operator[](static_cast<index>(PeriodShift(i, Period<Vector7D>))); }
			catch (...) { return this->operator[](i); }
		};
		bool CMPLX3_FUNC_CALL operator ==(const Vector7D& Union, const Vector7D& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool CMPLX3_FUNC_CALL operator !=(const Vector7D& Union, const Vector7D& Value) noexcept { return !(Union == Value); };
		Vector7D CMPLX3_FUNC_CALL operator +(const Vector7D& Value) noexcept { return Value; };
		Vector7D CMPLX3_FUNC_CALL operator -(const Vector7D& Value) noexcept { return Vector7D{}.from(-Value.to_number()); };
		Vector7D CMPLX3_FUNC_CALL operator +(const Vector7D& Union, const Vector7D& Value) noexcept { return Vector7D{}.from(Union.to_number() + Value.to_number()); };
		Vector7D CMPLX3_FUNC_CALL operator -(const Vector7D& Union, const Vector7D& Value) noexcept { return Vector7D{}.from(Union.to_number() - Value.to_number()); };
		Vector7D CMPLX3_FUNC_CALL operator *(double Union, const Vector7D& Value) noexcept { return Vector7D{}.from(Union * Value.to_number()); };
		Vector7D CMPLX3_FUNC_CALL operator *(const Vector7D& Union, double Value) noexcept { return Vector7D{}.from(Union.to_number() * Value); };
		Vector7D CMPLX3_FUNC_CALL operator /(const Vector7D& Union, double Value) noexcept { return Vector7D{}.from(Union.to_number() / Value); };
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator =(const Vector7D& Value) & noexcept
		{
			this->x1 = Value.x1;
			this->x2 = Value.x2;
			this->x3 = Value.x3;
			this->x4 = Value.x4;
			this->x5 = Value.x5;
			this->x6 = Value.x6;
			this->x7 = Value.x7;
			return *this;
		};
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator +=(const Vector7D& Value) & noexcept { return *this = *this + Value; };
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator +=(const std::initializer_list<Vector7D>& Value) & noexcept
		{
			for (std::initializer_list<Vector7D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator -=(const Vector7D& Value) & noexcept { return *this = *this - Value; };
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator -=(const std::initializer_list<Vector7D>& Value) & noexcept
		{
			for (std::initializer_list<Vector7D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator *=(double Value) & noexcept { return *this = *this * Value; };
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator *=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator /=(double Value) & noexcept { return *this = *this / Value; };
		Vector7D& CMPLX3_FUNC_INSTANCE_CALL Vector7D::operator /=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		///
		/// Basic functions for constructing vectors
		///
		double CMPLX3_FUNC_CALL Vector7D::abs(const Vector7D& Value) { return std::sqrt(dot(Value, Value)); };
		Vector7D CMPLX3_FUNC_CALL Vector7D::sgn(const Vector7D& Value) { return Value / abs(Value); };
		double CMPLX3_FUNC_CALL Vector7D::dot(const Vector7D& Union, const Vector7D& Value) noexcept { return build_in_dot(Union, Value); };
		Vector7D CMPLX3_FUNC_CALL Vector7D::cross(const Vector7D& Union, const Vector7D& Value) noexcept { return build_in_cross(Union, Value); };
		///
		/// Conversion of Types
		///
		std::wstring CMPLX3_FUNC_CALL Vector7D::GetString(const Vector7D& Value)
		{
			return ToString(Value[index::e1], L"e1", Value[index::e2], L"e2", Value[index::e3], L"e3", Value[index::e4], L"e4", Value[index::e5], L"e5", Value[index::e6], L"e6", Value[index::e7], L"e7");
		};
		Vector7D CMPLX3_FUNC_CALL Vector7D::GetInstance(const std::wstring& Value)
		{
			Vector7D Object;
			ToNumbers(Value, Object[index::e1], L"e1", Object[index::e2], L"e2", Object[index::e3], L"e3", Object[index::e4], L"e4", Object[index::e5], L"e5", Object[index::e6], L"e6", Object[index::e7], L"e7");
			return Object;
		};
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
			friend bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ==(const Octonion& Union, const Octonion& Value) noexcept;
			friend bool CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator !=(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Octonion& Value) noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Octonion& Value) noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ~(const Octonion& Value) noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator ++() & noexcept;
			Octonion CMPLX3_FUNC_INSTANCE_CALL operator ++(int) & noexcept;
			Octonion& CMPLX3_FUNC_INSTANCE_CALL operator --() & noexcept;
			Octonion CMPLX3_FUNC_INSTANCE_CALL operator --(int) & noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator +(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator -(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator *(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator /(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion CMPLX3_INTERFACE CMPLX3_FUNC_CALL operator ^(const Octonion& Base, std::int64_t Exponent) noexcept;
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
			/* Casting */
			inline auto to_number() const& noexcept
				-> decltype(forward_as_number((*this)[index::s], (*this)[index::i], (*this)[index::j], (*this)[index::k], (*this)[index::l], (*this)[index::il], (*this)[index::jl], (*this)[index::kl]))
			{
				return forward_as_number((*this)[index::s], (*this)[index::i], (*this)[index::j], (*this)[index::k], (*this)[index::l], (*this)[index::il], (*this)[index::jl], (*this)[index::kl]);
			};
			template <std::size_t N>
			inline auto from(const Number<N>& number) && noexcept -> decltype(*this)
			{
				number.store((*this)[index::s], (*this)[index::i], (*this)[index::j], (*this)[index::k], (*this)[index::l], (*this)[index::il], (*this)[index::jl], (*this)[index::kl]);
				return *this;
			};
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
		/* struct Octonion */
		const double Octonion::pi = std::numbers::pi;
		const double Octonion::e = std::numbers::e;
		const Octonion Octonion::i = Octonion(0, 1, 0, 0, 0, 0, 0, 0);
		const Octonion Octonion::j = Octonion(0, 0, 1, 0, 0, 0, 0, 0);
		const Octonion Octonion::k = Octonion(0, 0, 0, 1, 0, 0, 0, 0);
		const Octonion Octonion::l = Octonion(0, 0, 0, 0, 1, 0, 0, 0);
		const Octonion Octonion::il = Octonion(0, 0, 0, 0, 0, 1, 0, 0);
		const Octonion Octonion::jl = Octonion(0, 0, 0, 0, 0, 0, 1, 0);
		const Octonion Octonion::kl = Octonion(0, 0, 0, 0, 0, 0, 0, 1);
		///
		/// Initializer
		///
		CMPLX3_FUNC_INSTANCE_CALL Octonion::Octonion() noexcept : real(), imaginary() {};
		CMPLX3_FUNC_INSTANCE_CALL Octonion::Octonion(double s, const BaseType::Vector7D& v) noexcept : real(s), imaginary(v) {};
		CMPLX3_FUNC_INSTANCE_CALL Octonion::Octonion(double s, double i, double j, double k, double l, double il, double jl, double kl) noexcept : real(s), imaginary(BaseType::Vector7D(i, j, k, l, il, jl, kl)) {};
		CMPLX3_FUNC_INSTANCE_CALL Octonion::Octonion(double Value) noexcept : real(Value), imaginary() {};
		CMPLX3_FUNC_INSTANCE_CALL Octonion::Octonion(const BaseType::Vector7D& Value) noexcept : real(), imaginary(Value) {};
		CMPLX3_FUNC_INSTANCE_CALL Octonion::Octonion(const Octonion& Value) noexcept : real(Value.real), imaginary(Value.imaginary) {};
		double CMPLX3_FUNC_CALL Octonion::Scalar(const Octonion& Value) noexcept { return Value.real; };
		BaseType::Vector7D CMPLX3_FUNC_CALL Octonion::Vector(const Octonion& Value) noexcept { return Value.imaginary; };
		///
		/// Operators
		///
		Octonion CMPLX3_FUNC_INSTANCE_CALL Octonion::operator ()() const noexcept { return *this; };
		double& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator [](index i) &
		{
			switch (i)
			{
			case index::s:
				return this->real;
			case index::i:
				return this->imaginary[BaseType::index::e1];
			case index::j:
				return this->imaginary[BaseType::index::e2];
			case index::k:
				return this->imaginary[BaseType::index::e3];
			case index::l:
				return this->imaginary[BaseType::index::e4];
			case index::il:
				return this->imaginary[BaseType::index::e5];
			case index::jl:
				return this->imaginary[BaseType::index::e6];
			case index::kl:
				return this->imaginary[BaseType::index::e7];
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		double& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator [](std::int64_t i) &
		{
			try { return this->operator[](static_cast<index>(i % Period<Octonion>)); }
			catch (...) { return this->operator[](i); }
		};
		const double& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator [](index i) const&
		{
			switch (i)
			{
			case index::s:
				return this->real;
			case index::i:
				return this->imaginary[BaseType::index::e1];
			case index::j:
				return this->imaginary[BaseType::index::e2];
			case index::k:
				return this->imaginary[BaseType::index::e3];
			case index::l:
				return this->imaginary[BaseType::index::e4];
			case index::il:
				return this->imaginary[BaseType::index::e5];
			case index::jl:
				return this->imaginary[BaseType::index::e6];
			case index::kl:
				return this->imaginary[BaseType::index::e7];
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		const double& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator [](std::int64_t i) const&
		{
			try { return this->operator[](static_cast<index>(i % Period<Octonion>)); }
			catch (...) { return this->operator[](i); }
		};
		bool CMPLX3_FUNC_CALL operator ==(const Octonion& Union, const Octonion& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool CMPLX3_FUNC_CALL operator !=(const Octonion& Union, const Octonion& Value) noexcept { return !(Union == Value); };
		Octonion CMPLX3_FUNC_CALL operator +(const Octonion& Value) noexcept { return Value; };
		Octonion CMPLX3_FUNC_CALL operator -(const Octonion& Value) noexcept { return Octonion{}.from(-Value.to_number()); };
		Octonion CMPLX3_FUNC_CALL operator ~(const Octonion& Value) noexcept { return Octonion{}.from(~Value.to_number()); };
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator ++() & noexcept
		{
			++this->real;
			return *this;
		};
		Octonion CMPLX3_FUNC_INSTANCE_CALL Octonion::operator ++(int) & noexcept
		{
			Octonion temp = *this;
			++this->real;
			return temp;
		};
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator --() & noexcept
		{
			--this->real;
			return *this;
		};
		Octonion CMPLX3_FUNC_INSTANCE_CALL Octonion::operator --(int) & noexcept
		{
			Octonion temp = *this;
			--this->real;
			return temp;
		};
		Octonion CMPLX3_FUNC_CALL operator +(const Octonion& Union, const Octonion& Value) noexcept { return Octonion{}.from(Union.to_number() + Value.to_number()); };
		Octonion CMPLX3_FUNC_CALL operator -(const Octonion& Union, const Octonion& Value) noexcept { return Octonion{}.from(Union.to_number() - Value.to_number()); };
		Octonion CMPLX3_FUNC_CALL operator *(const Octonion& Union, const Octonion& Value) noexcept { return Octonion{}.from(Union.to_number() * Value.to_number()); };
		Octonion CMPLX3_FUNC_CALL operator /(const Octonion& Union, const Octonion& Value) noexcept
		{
			try
			{
				if (Octonion::Vector(Value) == 0) { return Octonion{}.from(Union.to_number() / Octonion::Scalar(Value)); }
				return Union * Octonion::inverse(Value);
			}
			catch (...) { return 0; }
		};
		Octonion CMPLX3_FUNC_CALL operator ^(const Octonion& Base, std::int64_t Exponent) noexcept
		{
			try { return Octonion::power(Base, static_cast<double>(Exponent)); }
			catch (...) { return 0; }
		};
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator =(const Octonion& Value) & noexcept
		{
			this->real = Value.real;
			this->imaginary = Value.imaginary;
			return *this;
		};
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator +=(const Octonion& Value) & noexcept { return *this = *this + Value; };
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator +=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator -=(const Octonion& Value) & noexcept { return *this = *this - Value; };
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator -=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator *=(const Octonion& Value) & noexcept { return *this = *this * Value; };
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator *=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator /=(const Octonion& Value) & noexcept { return *this = *this / Value; };
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator /=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator ^=(std::int64_t Exponent) & noexcept { return *this = *this ^ Exponent; };
		Octonion& CMPLX3_FUNC_INSTANCE_CALL Octonion::operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept
		{
			for (std::initializer_list<std::int64_t>::const_iterator ite = Exponent.begin(); ite != Exponent.end(); ++ite) { *this ^= *ite; }
			return *this;
		};
		///
		/// Basic functions for constructing numbers
		///
		double CMPLX3_FUNC_CALL Octonion::abs(const Octonion& Value) { return std::sqrt(dot(Value, Value)); };
		double CMPLX3_FUNC_CALL Octonion::arg(const Octonion& Value) { return arg(Value, 0); };
		double CMPLX3_FUNC_CALL Octonion::arg(const Octonion& Value, std::int64_t Theta) { return std::acos(Scalar(Value) / abs(Value)) + 2 * pi * static_cast<double>(Theta); };
		Octonion CMPLX3_FUNC_CALL Octonion::conjg(const Octonion& Value) { return ~Value; };
		Octonion CMPLX3_FUNC_CALL Octonion::sgn(const Octonion& Value) { return Value / abs(Value); };
		Octonion CMPLX3_FUNC_CALL Octonion::inverse(const Octonion& Value) { return conjg(Value) / dot(Value, Value); };
		Octonion CMPLX3_FUNC_CALL Octonion::exp(const Octonion& Value) { return std::exp(Scalar(Value)) * (std::cos(abs(Vector(Value))) + sgn(Vector(Value)) * std::sin(abs(Vector(Value)))); };
		Octonion CMPLX3_FUNC_CALL Octonion::ln(const Octonion& Value) { return ln(Value, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::ln(const Octonion& Value, std::int64_t Theta) { return std::log(abs(Value)) + sgn(Vector(Value)) * arg(Value, Theta); };
		///
		/// 1st rank tensor algorithms
		///
		double CMPLX3_FUNC_CALL Octonion::dot(const Octonion& Union, const Octonion& Value) noexcept { return Scalar(conjg(Union) * Value + conjg(Value) * Union) / 2; };
		Octonion CMPLX3_FUNC_CALL Octonion::outer(const Octonion& Union, const Octonion& Value) noexcept { return (conjg(Union) * Value - conjg(Value) * Union) / 2; };
		Octonion CMPLX3_FUNC_CALL Octonion::even(const Octonion& Union, const Octonion& Value) noexcept { return (Union * Value + Value * Union) / 2; };
		Octonion CMPLX3_FUNC_CALL Octonion::cross(const Octonion& Union, const Octonion& Value) noexcept { return (Union * Value - Value * Union) / 2; };
		///
		/// Operation 3 algorithms
		///
		Octonion CMPLX3_FUNC_CALL Octonion::power(const Octonion& Base, const Octonion& Exponent) { return power(Base, Exponent, 0, 0, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::power(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau)
		{
			return exp(exp(ln(ln(Base, Theta), Phi) + ln(Exponent, Tau)));
		};
		Octonion CMPLX3_FUNC_CALL Octonion::power(const Octonion& Base, double Exponent) { return power(Base, Exponent, 0); }
		Octonion CMPLX3_FUNC_CALL Octonion::power(const Octonion& Base, double Exponent, std::int64_t Theta)
		{
			if (Base == 0) { return Exponent == 0 ? 1 : 0; }
			return std::pow(abs(Base), Exponent) *
				(std::cos(Exponent * arg(Base, Theta)) + sgn(Vector(Base)) * std::sin(Exponent * arg(Base, Theta)));
		};
		Octonion CMPLX3_FUNC_CALL Octonion::root(const Octonion& Base, const Octonion& Exponent) { return root(Base, Exponent, 0, 0, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::root(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau) { return power(Base, inverse(Exponent), Theta, Phi, Tau); };
		Octonion CMPLX3_FUNC_CALL Octonion::root(const Octonion& Base, double Exponent) { return power(Base, 1 / Exponent); };
		Octonion CMPLX3_FUNC_CALL Octonion::root(const Octonion& Base, double Exponent, std::int64_t Theta) { return power(Base, 1 / Exponent, Theta); };
		Octonion CMPLX3_FUNC_CALL Octonion::log(const Octonion& Base, const Octonion& Number) { return log(Base, Number, 0, 0, 0, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::log(const Octonion& Base, const Octonion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega)
		{
			return exp(ln(ln(Number, Theta), Phi) - ln(ln(Base, Tau), Omega));
		};
		///
		/// Trigonometric functions
		///
		Octonion CMPLX3_FUNC_CALL Octonion::sin(const Octonion& Value)
		{
			return std::sin(Scalar(Value)) * std::cosh(abs(Vector(Value)))
				+ std::cos(Scalar(Value)) * sgn(Vector(Value)) * std::sinh(abs(Vector(Value)));
		};
		Octonion CMPLX3_FUNC_CALL Octonion::arcsin(const Octonion& Value) { return arcsin(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arcsin(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return -sgn(Vector(Value)) * arcsinh(Value * sgn(Vector(Value))); }
			else { return pi - arcsin(Value, true, Period); }
		};
		Octonion CMPLX3_FUNC_CALL Octonion::sinh(const Octonion& Value)
		{
			return std::sinh(Scalar(Value)) * std::cos(abs(Vector(Value)))
				+ std::cosh(Scalar(Value)) * sgn(Vector(Value)) * std::sin(abs(Vector(Value)));
		};
		Octonion CMPLX3_FUNC_CALL Octonion::arcsinh(const Octonion& Value) { return arcsinh(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arcsinh(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(power(Value, 2) + 1, 2), Period); }
			else { return pi * sgn(Vector(Value)) - arcsinh(Value, true, Period); }
		};
		Octonion CMPLX3_FUNC_CALL Octonion::cos(const Octonion& Value)
		{
			return std::cos(Scalar(Value)) * std::cosh(abs(Vector(Value)))
				- std::sin(Scalar(Value)) * sgn(Vector(Value)) * std::sinh(abs(Vector(Value)));
		};
		Octonion CMPLX3_FUNC_CALL Octonion::arccos(const Octonion& Value) { return arccos(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccos(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return -sgn(Vector(Value)) * arccosh(Value); }
			else { return 2 * pi - arccos(Value, true, Period); }
		};
		Octonion CMPLX3_FUNC_CALL Octonion::cosh(const Octonion& Value)
		{
			return std::cosh(Scalar(Value)) * std::cos(abs(Vector(Value)))
				+ std::sinh(Scalar(Value)) * sgn(Vector(Value)) * std::sin(abs(Vector(Value)));
		};
		Octonion CMPLX3_FUNC_CALL Octonion::arccosh(const Octonion& Value) { return arccosh(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccosh(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(power(Value, 2) - 1, 2), Period); }
			else { return 2 * pi * sgn(Vector(Value)) - arccosh(Value, true, Period); }
		};
		Octonion CMPLX3_FUNC_CALL Octonion::tan(const Octonion& Value)
		{
			return root(power(sec(Value), 2) - 1, 2);
		};
		Octonion CMPLX3_FUNC_CALL Octonion::arctan(const Octonion& Value) { return arctan(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arctan(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return -sgn(Vector(Value)) * arctanh(Value * sgn(Vector(Value))); }
			else { return pi + arctan(Value, true, Period); }
		};
		Octonion CMPLX3_FUNC_CALL Octonion::tanh(const Octonion& Value)
		{
			return 1 - 2 * inverse(exp(2 * Value) + 1);
		};
		Octonion CMPLX3_FUNC_CALL Octonion::arctanh(const Octonion& Value) { return arctanh(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arctanh(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return (ln(1 + Value, Period) - ln(1 - Value)) / 2; }
			else { return pi * sgn(Vector(Value)) + arctanh(Value, true, Period); }
		};
		Octonion CMPLX3_FUNC_CALL Octonion::csc(const Octonion& Value) { return inverse(sin(Value)); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccsc(const Octonion& Value) { return arccsc(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccsc(const Octonion& Value, bool Sign, std::int64_t Period) { return arcsin(inverse(Value), Sign, Period); };
		Octonion CMPLX3_FUNC_CALL Octonion::csch(const Octonion& Value) { return inverse(sinh(Value)); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccsch(const Octonion& Value) { return arccsch(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccsch(const Octonion& Value, bool Sign, std::int64_t Period) { return arcsinh(inverse(Value), Sign, Period); };
		Octonion CMPLX3_FUNC_CALL Octonion::sec(const Octonion& Value) { return inverse(cos(Value)); };
		Octonion CMPLX3_FUNC_CALL Octonion::arcsec(const Octonion& Value) { return arcsec(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arcsec(const Octonion& Value, bool Sign, std::int64_t Period) { return arccos(inverse(Value), Sign, Period); };
		Octonion CMPLX3_FUNC_CALL Octonion::sech(const Octonion& Value) { return inverse(cosh(Value)); };
		Octonion CMPLX3_FUNC_CALL Octonion::arcsech(const Octonion& Value) { return arcsech(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arcsech(const Octonion& Value, bool Sign, std::int64_t Period) { return arccosh(inverse(Value), Sign, Period); };
		Octonion CMPLX3_FUNC_CALL Octonion::cot(const Octonion& Value) { return inverse(tan(Value)); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccot(const Octonion& Value) { return arccot(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccot(const Octonion& Value, bool Sign, std::int64_t Period) { return arctan(inverse(Value), Sign, Period); };
		Octonion CMPLX3_FUNC_CALL Octonion::coth(const Octonion& Value) { return inverse(tanh(Value)); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccoth(const Octonion& Value) { return arccoth(Value, true, 0); };
		Octonion CMPLX3_FUNC_CALL Octonion::arccoth(const Octonion& Value, bool Sign, std::int64_t Period) { return arctanh(inverse(Value), Sign, Period); };
		///
		/// Conversion of Types
		///
		std::wstring CMPLX3_FUNC_CALL Octonion::GetString(const Octonion& Value)
		{
			return ToString(Value[index::s], L"", Value[index::i], L"i", Value[index::j], L"j", Value[index::k], L"k", Value[index::l], L"l", Value[index::il], L"il", Value[index::jl], L"jl", Value[index::kl], L"kl");
		};
		Octonion CMPLX3_FUNC_CALL Octonion::GetInstance(const std::wstring& Value)
		{
			Octonion Object;
			ToNumbers(Value, Object[index::s], L"", Object[index::i], L"i", Object[index::j], L"j", Object[index::k], L"k", Object[index::l], L"l", Object[index::il], L"il", Object[index::jl], L"jl", Object[index::kl], L"kl");
			return Object;
		};
	}
	double BaseType::Vector7D::build_in_dot(const BaseType::Vector7D& Union, const BaseType::Vector7D& Value)
	{
		return MainType::Octonion::dot(MainType::Octonion{ Union }, MainType::Octonion{ Value });
	};
	BaseType::Vector7D BaseType::Vector7D::build_in_cross(const BaseType::Vector7D& Union, const BaseType::Vector7D& Value)
	{
		return Vector7D{}.from(MainType::Octonion::cross(MainType::Octonion{ Union }, MainType::Octonion{ Value }).to_number());
	};
}
#pragma pop_macro("CMPLX3_FUNC_INSTANCE_CALL")
#pragma pop_macro("CMPLX3_FUNC_CALL")
#pragma pop_macro("CMPLX3_INTERFACE")
#pragma pop_macro("CALL")
#pragma pack(pop)
