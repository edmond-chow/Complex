#include <cmath>
#include <numbers>
#include <stdexcept>
#include "Module.h"
#include "Cayley Dickson Algebra.h"
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
#define CMPLX_INTERFACE __attribute__((dllexport))
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
#define CMPLX_INTERFACE __declspec(dllexport)
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
			///
			/// constants
			///
			static const double pi;
			static const double e;
			static const Vector1D e1;
		private:
			///
			/// basis
			///
			double x1;
		public:
			explicit CMPLX_FUNC_INSTANCE_CALL Vector1D() noexcept;
			explicit CMPLX_FUNC_INSTANCE_CALL Vector1D(double x1) noexcept;
			CMPLX_FUNC_INSTANCE_CALL Vector1D(const Vector1D& Value) noexcept;
			///
			/// operators
			///
			Vector1D CMPLX_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) &;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) & noexcept;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) const& noexcept;
			friend bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator ==(const Vector1D& Union, const Vector1D& Value) noexcept;
			friend bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator !=(const Vector1D& Union, const Vector1D& Value) noexcept;
			friend Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Vector1D& Value) noexcept;
			friend Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Vector1D& Value) noexcept;
			friend Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Vector1D& Union, const Vector1D& Value) noexcept;
			friend Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Vector1D& Union, const Vector1D& Value) noexcept;
			friend Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(double Union, const Vector1D& Value) noexcept;
			friend Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(const Vector1D& Union, double Value) noexcept;
			friend Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator /(const Vector1D& Union, double Value) noexcept;
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
			/// fundamentals
			///
			static double CMPLX_FUNC_CALL abs(const Vector1D& Value);
			static Vector1D CMPLX_FUNC_CALL sgn(const Vector1D& Value);
			static double CMPLX_FUNC_CALL dot(const Vector1D& Union, const Vector1D& Value) noexcept;
			static Vector1D CMPLX_FUNC_CALL cross(const Vector1D& Union, const Vector1D& Value) noexcept;
			///
			/// conventions
			///
			static std::wstring CMPLX_FUNC_CALL GetString(const Vector1D& Value);
			static Vector1D CMPLX_FUNC_CALL GetInstance(const std::wstring& Value);
			///
			/// casing
			///
			inline auto to_number() const& noexcept
				-> decltype(forward_as_number(0, (*this)[index::e1]))
			{
				return forward_as_number(0, (*this)[index::e1]);
			};
			template <std::size_t N>
			inline auto from(const Number<N>& number) && noexcept -> decltype(*this)
			{
				double temp{};
				number.store(temp, (*this)[index::e1]);
				return *this;
			};
			///
			/// traits
			///
			static double dot_with_numbers(const Vector1D& Union, const Vector1D& Value);
			static Vector1D cross_with_numbers(const Vector1D& Union, const Vector1D& Value);
		};
		///
		/// operators
		///
		bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator ==(const Vector1D& Union, const Vector1D& Value) noexcept;
		bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator !=(const Vector1D& Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Vector1D& Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Vector1D& Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(double Union, const Vector1D& Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(const Vector1D& Union, double Value) noexcept;
		Vector1D CMPLX_INTERFACE CMPLX_FUNC_CALL operator /(const Vector1D& Union, double Value) noexcept;
		/* struct Vector1D */
		///
		/// constants
		///
		const double Vector1D::pi = std::numbers::pi;
		const double Vector1D::e = std::numbers::e;
		const Vector1D Vector1D::e1 = Vector1D(1);
		///
		/// basis
		///
		CMPLX_FUNC_INSTANCE_CALL Vector1D::Vector1D() noexcept : x1() {};
		CMPLX_FUNC_INSTANCE_CALL Vector1D::Vector1D(double x1) noexcept : x1(x1) {};
		CMPLX_FUNC_INSTANCE_CALL Vector1D::Vector1D(const Vector1D& Value) noexcept : x1(Value.x1) {};
		///
		/// operators
		///
		Vector1D CMPLX_FUNC_INSTANCE_CALL Vector1D::operator ()() const noexcept { return *this; };
		double& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator [](index i) &
		{
			switch (i)
			{
			case index::e1:
				return this->x1;
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		double& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator [](std::int64_t i) & noexcept
		{
			try { return this->operator[](static_cast<index>(PeriodShift(i, Period<Vector1D>))); }
			catch (...) { return this->operator[](i); }
		};
		const double& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator [](index i) const&
		{
			switch (i)
			{
			case index::e1:
				return this->x1;
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		const double& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator [](std::int64_t i) const& noexcept
		{
			try { return this->operator[](static_cast<index>(PeriodShift(i, Period<Vector1D>))); }
			catch (...) { return this->operator[](i); }
		};
		bool CMPLX_FUNC_CALL operator ==(const Vector1D& Union, const Vector1D& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool CMPLX_FUNC_CALL operator !=(const Vector1D& Union, const Vector1D& Value) noexcept { return !(Union == Value); };
		Vector1D CMPLX_FUNC_CALL operator +(const Vector1D& Value) noexcept { return Value; };
		Vector1D CMPLX_FUNC_CALL operator -(const Vector1D& Value) noexcept { return Vector1D{}.from(-Value.to_number()); };
		Vector1D CMPLX_FUNC_CALL operator +(const Vector1D& Union, const Vector1D& Value) noexcept { return Vector1D{}.from(Union.to_number() + Value.to_number()); };
		Vector1D CMPLX_FUNC_CALL operator -(const Vector1D& Union, const Vector1D& Value) noexcept { return Vector1D{}.from(Union.to_number() - Value.to_number()); };
		Vector1D CMPLX_FUNC_CALL operator *(double Union, const Vector1D& Value) noexcept { return Vector1D{}.from(Union * Value.to_number()); };
		Vector1D CMPLX_FUNC_CALL operator *(const Vector1D& Union, double Value) noexcept { return Vector1D{}.from(Union.to_number() * Value); };
		Vector1D CMPLX_FUNC_CALL operator /(const Vector1D& Union, double Value) noexcept { return Vector1D{}.from(Union.to_number() / Value); };
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator =(const Vector1D& Value) & noexcept
		{
			this->x1 = Value.x1;
			return *this;
		};
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator +=(const Vector1D& Value) & noexcept { return *this = *this + Value; };
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator +=(const std::initializer_list<Vector1D>& Value) & noexcept
		{
			for (std::initializer_list<Vector1D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator -=(const Vector1D& Value) & noexcept { return *this = *this - Value; };
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator -=(const std::initializer_list<Vector1D>& Value) & noexcept
		{
			for (std::initializer_list<Vector1D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator *=(double Value) & noexcept { return *this = *this * Value; };
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator *=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator /=(double Value) & noexcept { return *this = *this / Value; };
		Vector1D& CMPLX_FUNC_INSTANCE_CALL Vector1D::operator /=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		///
		/// fundamentals
		///
		double CMPLX_FUNC_CALL Vector1D::abs(const Vector1D& Value) { return std::sqrt(dot(Value, Value)); };
		Vector1D CMPLX_FUNC_CALL Vector1D::sgn(const Vector1D& Value) { return Value / abs(Value); };
		double CMPLX_FUNC_CALL Vector1D::dot(const Vector1D& Union, const Vector1D& Value) noexcept { return dot_with_numbers(Union, Value); };
		Vector1D CMPLX_FUNC_CALL Vector1D::cross(const Vector1D& Union, const Vector1D& Value) noexcept { return cross_with_numbers(Union, Value); };;
		///
		/// conventions
		///
		std::wstring CMPLX_FUNC_CALL Vector1D::GetString(const Vector1D& Value)
		{
			return ToString(Value[index::e1], L"e1");
		};
		Vector1D CMPLX_FUNC_CALL Vector1D::GetInstance(const std::wstring& Value)
		{
			Vector1D Object;
			ToNumbers(Value, Object[index::e1], L"e1");
			return Object;
		};
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
			///
			/// constants
			///
			static const double pi;
			static const double e;
			static const Complex i;
		private:
			///
			/// basis
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
			/// operators
			///
			Complex CMPLX_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) &;
			double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) & noexcept;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& CMPLX_FUNC_INSTANCE_CALL operator [](std::int64_t i) const& noexcept;
			friend bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator ==(const Complex& Union, const Complex& Value) noexcept;
			friend bool CMPLX_INTERFACE CMPLX_FUNC_CALL operator !=(const Complex& Union, const Complex& Value) noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Complex& Value) noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Complex& Value) noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator ~(const Complex& Value) noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator ++() & noexcept;
			Complex CMPLX_FUNC_INSTANCE_CALL operator ++(int) & noexcept;
			Complex& CMPLX_FUNC_INSTANCE_CALL operator --() & noexcept;
			Complex CMPLX_FUNC_INSTANCE_CALL operator --(int) & noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator +(const Complex& Union, const Complex& Value) noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator -(const Complex& Union, const Complex& Value) noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator *(const Complex& Union, const Complex& Value) noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator /(const Complex& Union, const Complex& Value) noexcept;
			friend Complex CMPLX_INTERFACE CMPLX_FUNC_CALL operator ^(const Complex& Base, std::int64_t Exponent) noexcept;
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
			/// fundamentals
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
			/// multiples
			///
			static double CMPLX_FUNC_CALL dot(const Complex& Union, const Complex& Value) noexcept;
			static Complex CMPLX_FUNC_CALL outer(const Complex& Union, const Complex& Value) noexcept;
			static Complex CMPLX_FUNC_CALL even(const Complex& Union, const Complex& Value) noexcept;
			static Complex CMPLX_FUNC_CALL cross(const Complex& Union, const Complex& Value) noexcept;
			///
			/// exponentials
			///
			static Complex CMPLX_FUNC_CALL power(const Complex& Base, const Complex& Exponent);
			static Complex CMPLX_FUNC_CALL power(const Complex& Base, const Complex& Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL power(const Complex& Base, double Exponent);
			static Complex CMPLX_FUNC_CALL power(const Complex& Base, double Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL root(const Complex& Base, const Complex& Exponent);
			static Complex CMPLX_FUNC_CALL root(const Complex& Base, const Complex& Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL root(const Complex& Base, double Exponent);
			static Complex CMPLX_FUNC_CALL root(const Complex& Base, double Exponent, std::int64_t Theta);
			static Complex CMPLX_FUNC_CALL log(const Complex& Base, const Complex& Number);
			static Complex CMPLX_FUNC_CALL log(const Complex& Base, const Complex& Number, std::int64_t Theta, std::int64_t Phi);
			///
			/// trigonometrics
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
			/// conventions
			///
			static std::wstring CMPLX_FUNC_CALL GetString(const Complex& Value);
			static Complex CMPLX_FUNC_CALL GetInstance(const std::wstring& Value);
			///
			/// casing
			///
			inline auto to_number() const& noexcept
				-> decltype(forward_as_number((*this)[index::s], (*this)[index::i]))
			{
				return forward_as_number((*this)[index::s], (*this)[index::i]);
			};
			template <std::size_t N>
			inline auto from(const Number<N>& number) && noexcept -> decltype(*this)
			{
				number.store((*this)[index::s], (*this)[index::i]);
				return *this;
			};
		};
		///
		/// operators
		///
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
		/* struct Complex */
		///
		/// constants
		///
		const double Complex::pi = std::numbers::pi;
		const double Complex::e = std::numbers::e;
		const Complex Complex::i = Complex(0, 1);
		///
		/// basis
		///
		CMPLX_FUNC_INSTANCE_CALL Complex::Complex() noexcept : real(), imaginary() {};
		CMPLX_FUNC_INSTANCE_CALL Complex::Complex(double s, const BaseType::Vector1D& v) noexcept : real(s), imaginary(v) {};
		CMPLX_FUNC_INSTANCE_CALL Complex::Complex(double s, double i) noexcept : real(s), imaginary(BaseType::Vector1D(i)) {};
		CMPLX_FUNC_INSTANCE_CALL Complex::Complex(double Value) noexcept : real(Value), imaginary() {};
		CMPLX_FUNC_INSTANCE_CALL Complex::Complex(const BaseType::Vector1D& Value) noexcept : real(), imaginary(Value) {};
		CMPLX_FUNC_INSTANCE_CALL Complex::Complex(const Complex& Value) noexcept : real(Value.real), imaginary(Value.imaginary) {};
		double CMPLX_FUNC_CALL Complex::Scalar(const Complex& Value) noexcept { return Value.real; };
		BaseType::Vector1D CMPLX_FUNC_CALL Complex::Vector(const Complex& Value) noexcept { return Value.imaginary; };
		double CMPLX_FUNC_CALL Complex::Re(const Complex& z) noexcept { return Scalar(z); };
		double CMPLX_FUNC_CALL Complex::Im(const Complex& z) noexcept { return BaseType::Vector1D::dot(Vector(z), BaseType::Vector1D::e1); };
		///
		/// operators
		///
		Complex CMPLX_FUNC_INSTANCE_CALL Complex::operator ()() const noexcept { return *this; };
		double& CMPLX_FUNC_INSTANCE_CALL Complex::operator [](index i) &
		{
			switch (i)
			{
			case index::s:
				return this->real;
			case index::i:
				return this->imaginary[BaseType::index::e1];
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		double& CMPLX_FUNC_INSTANCE_CALL Complex::operator [](std::int64_t i) & noexcept
		{
			try { return this->operator[](static_cast<index>(i % Period<Complex>)); }
			catch (...) { return this->operator[](i); }
		};
		const double& CMPLX_FUNC_INSTANCE_CALL Complex::operator [](index i) const&
		{
			switch (i)
			{
			case index::s:
				return this->real;
			case index::i:
				return this->imaginary[BaseType::index::e1];
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		const double& CMPLX_FUNC_INSTANCE_CALL Complex::operator [](std::int64_t i) const& noexcept
		{
			try { return this->operator[](static_cast<index>(i % Period<Complex>)); }
			catch (...) { return this->operator[](i); }
		};
		bool CMPLX_FUNC_CALL operator ==(const Complex& Union, const Complex& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool CMPLX_FUNC_CALL operator !=(const Complex& Union, const Complex& Value) noexcept { return !(Union == Value); };
		Complex CMPLX_FUNC_CALL operator +(const Complex& Value) noexcept { return Value; };
		Complex CMPLX_FUNC_CALL operator -(const Complex& Value) noexcept { return Complex{}.from(-Value.to_number()); };
		Complex CMPLX_FUNC_CALL operator ~(const Complex& Value) noexcept { return Complex{}.from(~Value.to_number()); };
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator ++() & noexcept
		{
			++this->real;
			return *this;
		};
		Complex CMPLX_FUNC_INSTANCE_CALL Complex::operator ++(int) & noexcept
		{
			Complex temp = *this;
			++this->real;
			return temp;
		};
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator --() & noexcept
		{
			--this->real;
			return *this;
		};
		Complex CMPLX_FUNC_INSTANCE_CALL Complex::operator --(int) & noexcept
		{
			Complex temp = *this;
			--this->real;
			return temp;
		};
		Complex CMPLX_FUNC_CALL operator +(const Complex& Union, const Complex& Value) noexcept { return Complex{}.from(Union.to_number() + Value.to_number()); };
		Complex CMPLX_FUNC_CALL operator -(const Complex& Union, const Complex& Value) noexcept { return Complex{}.from(Union.to_number() - Value.to_number()); };
		Complex CMPLX_FUNC_CALL operator *(const Complex& Union, const Complex& Value) noexcept { return Complex{}.from(Union.to_number() * Value.to_number()); };
		Complex CMPLX_FUNC_CALL operator /(const Complex& Union, const Complex& Value) noexcept
		{
			try
			{
				if (Complex::Vector(Value) == 0) { return Complex{}.from(Union.to_number() / Complex::Scalar(Value)); }
				return Union * Complex::inverse(Value);
			}
			catch (...) { return 0; }
		};
		Complex CMPLX_FUNC_CALL operator ^(const Complex& Base, std::int64_t Exponent) noexcept
		{
			try { return Complex::power(Base, static_cast<double>(Exponent)); }
			catch (...) { return 0; }
		};
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator =(const Complex& Value) & noexcept
		{
			this->real = Value.real;
			this->imaginary = Value.imaginary;
			return *this;
		};
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator +=(const Complex& Value) & noexcept { return *this = *this + Value; };
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator +=(const std::initializer_list<Complex>& Value) & noexcept
		{
			for (std::initializer_list<Complex>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator -=(const Complex& Value) & noexcept { return *this = *this - Value; };
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator -=(const std::initializer_list<Complex>& Value) & noexcept
		{
			for (std::initializer_list<Complex>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator *=(const Complex& Value) & noexcept { return *this = *this * Value; };
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator *=(const std::initializer_list<Complex>& Value) & noexcept
		{
			for (std::initializer_list<Complex>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator /=(const Complex& Value) & noexcept { return *this = *this / Value; };
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator /=(const std::initializer_list<Complex>& Value) & noexcept
		{
			for (std::initializer_list<Complex>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator ^=(std::int64_t Exponent) & noexcept { return *this = *this ^ Exponent; };
		Complex& CMPLX_FUNC_INSTANCE_CALL Complex::operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept
		{
			for (std::initializer_list<std::int64_t>::const_iterator ite = Exponent.begin(); ite != Exponent.end(); ++ite) { *this ^= *ite; }
			return *this;
		};
		///
		/// fundamentals
		///
		double CMPLX_FUNC_CALL Complex::abs(const Complex& Value) { return std::sqrt(dot(Value, Value)); };
		double CMPLX_FUNC_CALL Complex::arg(const Complex& Value) { return arg(Value, 0); };
		double CMPLX_FUNC_CALL Complex::arg(const Complex& Value, std::int64_t Theta) { return std::acos(Scalar(Value) / abs(Value)) + 2 * pi * static_cast<double>(Theta); };
		Complex CMPLX_FUNC_CALL Complex::conjg(const Complex& Value) { return ~Value; };
		Complex CMPLX_FUNC_CALL Complex::sgn(const Complex& Value) { return Value / abs(Value); };
		Complex CMPLX_FUNC_CALL Complex::inverse(const Complex& Value) { return conjg(Value) / dot(Value, Value); };
		Complex CMPLX_FUNC_CALL Complex::exp(const Complex& Value) { return std::exp(Scalar(Value)) * (std::cos(abs(Vector(Value))) + sgn(Vector(Value)) * std::sin(abs(Vector(Value)))); };
		Complex CMPLX_FUNC_CALL Complex::ln(const Complex& Value) { return ln(Value, 0); };
		Complex CMPLX_FUNC_CALL Complex::ln(const Complex& Value, std::int64_t Theta) { return std::log(abs(Value)) + (Vector(Value) == 0 ? 0 : sgn(Vector(Value)) * arg(Value, Theta)); };
		///
		/// multiples
		///
		double CMPLX_FUNC_CALL Complex::dot(const Complex& Union, const Complex& Value) noexcept { return Scalar(conjg(Union) * Value + conjg(Value) * Union) / 2; };
		Complex CMPLX_FUNC_CALL Complex::outer(const Complex& Union, const Complex& Value) noexcept { return (conjg(Union) * Value - conjg(Value) * Union) / 2; };
		Complex CMPLX_FUNC_CALL Complex::even(const Complex& Union, const Complex& Value) noexcept { return (Union * Value + Value * Union) / 2; };
		Complex CMPLX_FUNC_CALL Complex::cross(const Complex& Union, const Complex& Value) noexcept { return (Union * Value - Value * Union) / 2; };
		///
		/// exponentials
		///
		Complex CMPLX_FUNC_CALL Complex::power(const Complex& Base, const Complex& Exponent) { return power(Base, Exponent, 0); };
		Complex CMPLX_FUNC_CALL Complex::power(const Complex& Base, const Complex& Exponent, std::int64_t Theta)
		{
			return exp(Exponent * ln(Base, Theta));
		};
		Complex CMPLX_FUNC_CALL Complex::power(const Complex& Base, double Exponent) { return power(Base, Exponent, 0); };
		Complex CMPLX_FUNC_CALL Complex::power(const Complex& Base, double Exponent, std::int64_t Theta)
		{
			if (Base == 0) { return Exponent == 0 ? 1 : 0; }
			return std::pow(abs(Base), Exponent) *
				(std::cos(Exponent * arg(Base, Theta)) + sgn(Vector(Base)) * std::sin(Exponent * arg(Base, Theta)));
		};
		Complex CMPLX_FUNC_CALL Complex::root(const Complex& Base, const Complex& Exponent) { return root(Base, Exponent, 0); };
		Complex CMPLX_FUNC_CALL Complex::root(const Complex& Base, const Complex& Exponent, std::int64_t Theta) { return power(Base, inverse(Exponent), Theta); };
		Complex CMPLX_FUNC_CALL Complex::root(const Complex& Base, double Exponent) { return root(Base, Exponent, 0); };
		Complex CMPLX_FUNC_CALL Complex::root(const Complex& Base, double Exponent, std::int64_t Theta) { return power(Base, 1 / Exponent, Theta); };
		Complex CMPLX_FUNC_CALL Complex::log(const Complex& Base, const Complex& Number) { return log(Base, Number, 0, 0); };
		Complex CMPLX_FUNC_CALL Complex::log(const Complex& Base, const Complex& Number, std::int64_t Theta, std::int64_t Phi)
		{
			return ln(Number, Theta) / ln(Base, Phi);
		};
		///
		/// trigonometrics
		///
		Complex CMPLX_FUNC_CALL Complex::sin(const Complex& Value)
		{
			return std::sin(Scalar(Value)) * std::cosh(abs(Vector(Value)))
				+ std::cos(Scalar(Value)) * sgn(Vector(Value)) * std::sinh(abs(Vector(Value)));
		};
		Complex CMPLX_FUNC_CALL Complex::arcsin(const Complex& Value) { return arcsin(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arcsin(const Complex& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return -sgn(Vector(Value)) * arcsinh(Value * sgn(Vector(Value))); }
			else { return pi - arcsin(Value, true, Period); }
		};
		Complex CMPLX_FUNC_CALL Complex::sinh(const Complex& Value)
		{
			return std::sinh(Scalar(Value)) * std::cos(abs(Vector(Value)))
				+ std::cosh(Scalar(Value)) * sgn(Vector(Value)) * std::sin(abs(Vector(Value)));
		};
		Complex CMPLX_FUNC_CALL Complex::arcsinh(const Complex& Value) { return arcsinh(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arcsinh(const Complex& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(power(Value, 2) + 1, 2), Period); }
			else { return pi * sgn(Vector(Value)) - arcsinh(Value, true, Period); }
		};
		Complex CMPLX_FUNC_CALL Complex::cos(const Complex& Value)
		{
			return std::cos(Scalar(Value)) * std::cosh(abs(Vector(Value)))
				- std::sin(Scalar(Value)) * sgn(Vector(Value)) * std::sinh(abs(Vector(Value)));
		};
		Complex CMPLX_FUNC_CALL Complex::arccos(const Complex& Value) { return arccos(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arccos(const Complex& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return -sgn(Vector(Value)) * arccosh(Value); }
			else { return 2 * pi - arccos(Value, true, Period); }
		};
		Complex CMPLX_FUNC_CALL Complex::cosh(const Complex& Value)
		{
			return std::cosh(Scalar(Value)) * std::cos(abs(Vector(Value)))
				+ std::sinh(Scalar(Value)) * sgn(Vector(Value)) * std::sin(abs(Vector(Value)));
		};
		Complex CMPLX_FUNC_CALL Complex::arccosh(const Complex& Value) { return arccosh(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arccosh(const Complex& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(power(Value, 2) - 1, 2), Period); }
			else { return 2 * pi * sgn(Vector(Value)) - arccosh(Value, true, Period); }
		};
		Complex CMPLX_FUNC_CALL Complex::tan(const Complex& Value)
		{
			return root(power(sec(Value), 2) - 1, 2);
		};
		Complex CMPLX_FUNC_CALL Complex::arctan(const Complex& Value) { return arctan(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arctan(const Complex& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return -sgn(Vector(Value)) * arctanh(Value * sgn(Vector(Value))); }
			else { return pi + arctan(Value, true, Period); }
		};
		Complex CMPLX_FUNC_CALL Complex::tanh(const Complex& Value)
		{
			return 1 - 2 * inverse(exp(2 * Value) + 1);
		};
		Complex CMPLX_FUNC_CALL Complex::arctanh(const Complex& Value) { return arctanh(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arctanh(const Complex& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return (ln(1 + Value, Period) - ln(1 - Value)) / 2; }
			else { return pi * sgn(Vector(Value)) + arctanh(Value, true, Period); }
		};
		Complex CMPLX_FUNC_CALL Complex::csc(const Complex& Value) { return inverse(sin(Value)); };
		Complex CMPLX_FUNC_CALL Complex::arccsc(const Complex& Value) { return arccsc(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arccsc(const Complex& Value, bool Sign, std::int64_t Period) { return arcsin(inverse(Value), Sign, Period); };
		Complex CMPLX_FUNC_CALL Complex::csch(const Complex& Value) { return inverse(sinh(Value)); };
		Complex CMPLX_FUNC_CALL Complex::arccsch(const Complex& Value) { return arccsch(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arccsch(const Complex& Value, bool Sign, std::int64_t Period) { return arcsinh(inverse(Value), Sign, Period); };
		Complex CMPLX_FUNC_CALL Complex::sec(const Complex& Value) { return inverse(cos(Value)); };
		Complex CMPLX_FUNC_CALL Complex::arcsec(const Complex& Value) { return arcsec(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arcsec(const Complex& Value, bool Sign, std::int64_t Period) { return arccos(inverse(Value), Sign, Period); };
		Complex CMPLX_FUNC_CALL Complex::sech(const Complex& Value) { return inverse(cosh(Value)); };
		Complex CMPLX_FUNC_CALL Complex::arcsech(const Complex& Value) { return arcsech(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arcsech(const Complex& Value, bool Sign, std::int64_t Period) { return arccosh(inverse(Value), Sign, Period); };
		Complex CMPLX_FUNC_CALL Complex::cot(const Complex& Value) { return inverse(tan(Value)); };
		Complex CMPLX_FUNC_CALL Complex::arccot(const Complex& Value) { return arccot(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arccot(const Complex& Value, bool Sign, std::int64_t Period) { return arctan(inverse(Value), Sign, Period); };
		Complex CMPLX_FUNC_CALL Complex::coth(const Complex& Value) { return inverse(tanh(Value)); };
		Complex CMPLX_FUNC_CALL Complex::arccoth(const Complex& Value) { return arccoth(Value, true, 0); };
		Complex CMPLX_FUNC_CALL Complex::arccoth(const Complex& Value, bool Sign, std::int64_t Period) { return arctanh(inverse(Value), Sign, Period); };
		///
		/// conventions
		///
		std::wstring CMPLX_FUNC_CALL Complex::GetString(const Complex& Value)
		{
			return ToString(Value[index::s], L"", Value[index::i], L"i");
		};
		Complex CMPLX_FUNC_CALL Complex::GetInstance(const std::wstring& Value)
		{
			Complex Object;
			ToNumbers(Value, Object[index::s], L"", Object[index::i], L"i");
			return Object;
		};
	}
	///
	/// traits
	///
	double BaseType::Vector1D::dot_with_numbers(const BaseType::Vector1D& Union, const BaseType::Vector1D& Value)
	{
		return MainType::Complex::dot(MainType::Complex{ Union }, MainType::Complex{ Value });
	};
	BaseType::Vector1D BaseType::Vector1D::cross_with_numbers(const BaseType::Vector1D& Union, const BaseType::Vector1D& Value)
	{
		return Vector1D{}.from(MainType::Complex::cross(MainType::Complex{ Union }, MainType::Complex{ Value }).to_number());
	};
}
#pragma pop_macro("CMPLX_FUNC_INSTANCE_CALL")
#pragma pop_macro("CMPLX_FUNC_CALL")
#pragma pop_macro("CMPLX_INTERFACE")
#pragma pop_macro("CALL")
#pragma pack(pop)
