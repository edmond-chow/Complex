/*
 *   Copyright 2022 Edmond Chow
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#include "Module.h"
#include "Cayley Dickson Algebra.h"
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
#if defined(__GNUG__)
#define CALL(c) __attribute__((c))
#define QUTER_INTERFACE __attribute__((dllexport))
#if defined(DEBUG) || defined(X86) || defined(X64)
#define QUTER_FUNC_CALL CALL(__stdcall__)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define QUTER_FUNC_CALL CALL(__fastcall__)
#else
#define QUTER_FUNC_CALL
#endif
#define QUTER_FUNC_INSTANCE_CALL CALL(__thiscall__)
#elif defined(_MSVC_LANG)
#define CALL(c) c
#define QUTER_INTERFACE __declspec(dllexport)
#if defined(DEBUG) || defined(X86) || defined(X64)
#define QUTER_FUNC_CALL CALL(__stdcall)
#elif defined(RELEASE) || defined(X86) || defined(X64)
#define QUTER_FUNC_CALL CALL(__fastcall)
#else
#define QUTER_FUNC_CALL
#endif
#define QUTER_FUNC_INSTANCE_CALL CALL(__thiscall)
#else
#define CALL(c)
#define QUTER_INTERFACE
#define QUTER_FUNC_CALL
#define QUTER_FUNC_INSTANCE_CALL
#endif
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
			Vector3D QUTER_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& QUTER_FUNC_INSTANCE_CALL operator [](index i) &;
			double& QUTER_FUNC_INSTANCE_CALL operator [](std::size_t i) & noexcept;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](std::size_t i) const& noexcept;
			friend bool QUTER_INTERFACE QUTER_FUNC_CALL operator ==(const Vector3D& Union, const Vector3D& Value) noexcept;
			friend bool QUTER_INTERFACE QUTER_FUNC_CALL operator !=(const Vector3D& Union, const Vector3D& Value) noexcept;
			friend Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Vector3D& Value) noexcept;
			friend Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Vector3D& Value) noexcept;
			friend Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Vector3D& Union, const Vector3D& Value) noexcept;
			friend Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Vector3D& Union, const Vector3D& Value) noexcept;
			friend Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator *(double Union, const Vector3D& Value) noexcept;
			friend Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator *(const Vector3D& Union, double Value) noexcept;
			friend Vector3D QUTER_INTERFACE QUTER_FUNC_CALL operator /(const Vector3D& Union, double Value) noexcept;
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
			///
			/// casing
			///
			inline auto to_number() const& noexcept
				-> decltype(forward_as_number((*this)[index::e1], (*this)[index::e2], (*this)[index::e3]))
			{
				return forward_as_number((*this)[index::e1], (*this)[index::e2], (*this)[index::e3]);
			};
			template <std::size_t N>
			inline auto from(const Number<N>& number) && noexcept -> decltype(*this)
			{
				number.store((*this)[index::e1], (*this)[index::e2], (*this)[index::e3]);
				return *this;
			};
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
		/* struct Vector3D */
		///
		/// constants
		///
		const double Vector3D::pi = std::numbers::pi;
		const double Vector3D::e = std::numbers::e;
		const Vector3D Vector3D::e1 = Vector3D(1, 0, 0);
		const Vector3D Vector3D::e2 = Vector3D(0, 1, 0);
		const Vector3D Vector3D::e3 = Vector3D(0, 0, 1);
		///
		/// basis
		///
		QUTER_FUNC_INSTANCE_CALL Vector3D::Vector3D() noexcept : x1(), x2(), x3() {};
		QUTER_FUNC_INSTANCE_CALL Vector3D::Vector3D(double x1, double x2, double x3) noexcept : x1(x1), x2(x2), x3(x3) {};
		QUTER_FUNC_INSTANCE_CALL Vector3D::Vector3D(const Vector3D& Value) noexcept : x1(Value.x1), x2(Value.x2), x3(Value.x3) {};
		///
		/// operators
		///
		Vector3D QUTER_FUNC_INSTANCE_CALL Vector3D::operator ()() const noexcept { return *this; };
		double& QUTER_FUNC_INSTANCE_CALL Vector3D::operator [](index i) &
		{
			switch (i)
			{
			case index::e1:
				return this->x1;
			case index::e2:
				return this->x2;
			case index::e3:
				return this->x3;
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		double& QUTER_FUNC_INSTANCE_CALL Vector3D::operator [](std::size_t i) & noexcept
		{
			try
			{
				Adjust<Period<Vector3D>, true>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		const double& QUTER_FUNC_INSTANCE_CALL Vector3D::operator [](index i) const&
		{
			switch (i)
			{
			case index::e1:
				return this->x1;
			case index::e2:
				return this->x2;
			case index::e3:
				return this->x3;
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		const double& QUTER_FUNC_INSTANCE_CALL Vector3D::operator [](std::size_t i) const& noexcept
		{
			try
			{
				Adjust<Period<Vector3D>, true>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		bool QUTER_FUNC_CALL operator ==(const Vector3D& Union, const Vector3D& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool QUTER_FUNC_CALL operator !=(const Vector3D& Union, const Vector3D& Value) noexcept { return !(Union == Value); };
		Vector3D QUTER_FUNC_CALL operator +(const Vector3D& Value) noexcept { return Value; };
		Vector3D QUTER_FUNC_CALL operator -(const Vector3D& Value) noexcept { return Vector3D{}.from(-Value.to_number()); };
		Vector3D QUTER_FUNC_CALL operator +(const Vector3D& Union, const Vector3D& Value) noexcept { return Vector3D{}.from(Union.to_number() + Value.to_number()); };
		Vector3D QUTER_FUNC_CALL operator -(const Vector3D& Union, const Vector3D& Value) noexcept { return Vector3D{}.from(Union.to_number() - Value.to_number()); };
		Vector3D QUTER_FUNC_CALL operator *(double Union, const Vector3D& Value) noexcept { return Vector3D{}.from(Union * Value.to_number()); };
		Vector3D QUTER_FUNC_CALL operator *(const Vector3D& Union, double Value) noexcept { return Vector3D{}.from(Union.to_number() * Value); };
		Vector3D QUTER_FUNC_CALL operator /(const Vector3D& Union, double Value) noexcept { return Vector3D{}.from(Union.to_number() / Value); };
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator =(const Vector3D& Value) & noexcept
		{
			this->x1 = Value.x1;
			this->x2 = Value.x2;
			this->x3 = Value.x3;
			return *this;
		};
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator +=(const Vector3D& Value) & noexcept { return *this = *this + Value; };
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator +=(const std::initializer_list<Vector3D>& Value) & noexcept
		{
			for (std::initializer_list<Vector3D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator -=(const Vector3D& Value) & noexcept { return *this = *this - Value; };
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator -=(const std::initializer_list<Vector3D>& Value) & noexcept
		{
			for (std::initializer_list<Vector3D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator *=(double Value) & noexcept { return *this = *this * Value; };
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator *=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator /=(double Value) & noexcept { return *this = *this / Value; };
		Vector3D& QUTER_FUNC_INSTANCE_CALL Vector3D::operator /=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		///
		/// fundamentals
		///
		double QUTER_FUNC_CALL Vector3D::abs(const Vector3D& Value) { return std::sqrt(dot(Value, Value)); };
		Vector3D QUTER_FUNC_CALL Vector3D::sgn(const Vector3D& Value) { return Value / abs(Value); };
		double QUTER_FUNC_CALL Vector3D::dot(const Vector3D& Union, const Vector3D& Value) noexcept
		{
			return vector_dot(Union.to_number(), Value.to_number());
		};
		Vector3D QUTER_FUNC_CALL Vector3D::cross(const Vector3D& Union, const Vector3D& Value) noexcept
		{
			return Vector3D{}.from(vector_cross(Union.to_number(), Value.to_number()));
		};
		///
		/// conventions
		///
		std::wstring QUTER_FUNC_CALL Vector3D::GetString(const Vector3D& Value)
		{
			return ToString(Value[index::e1], L"e1", Value[index::e2], L"e2", Value[index::e3], L"e3");
		};
		Vector3D QUTER_FUNC_CALL Vector3D::GetInstance(const std::wstring& Value)
		{
			std::wstring Replaced = Replace(Value, L" ", L"");
			Vector3D Object;
			ToNumbers(Replaced, Object[index::e1], L"e1", Object[index::e2], L"e2", Object[index::e3], L"e3");
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
			Quaternion QUTER_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& QUTER_FUNC_INSTANCE_CALL operator [](index i) &;
			double& QUTER_FUNC_INSTANCE_CALL operator [](std::size_t i) & noexcept;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& QUTER_FUNC_INSTANCE_CALL operator [](std::size_t i) const& noexcept;
			friend bool QUTER_INTERFACE QUTER_FUNC_CALL operator ==(const Quaternion& Union, const Quaternion& Value) noexcept;
			friend bool QUTER_INTERFACE QUTER_FUNC_CALL operator !=(const Quaternion& Union, const Quaternion& Value) noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Quaternion& Value) noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Quaternion& Value) noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator ~(const Quaternion& Value) noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator ++() & noexcept;
			Quaternion QUTER_FUNC_INSTANCE_CALL operator ++(int) & noexcept;
			Quaternion& QUTER_FUNC_INSTANCE_CALL operator --() & noexcept;
			Quaternion QUTER_FUNC_INSTANCE_CALL operator --(int) & noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator +(const Quaternion& Union, const Quaternion& Value) noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator -(const Quaternion& Union, const Quaternion& Value) noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator *(const Quaternion& Union, const Quaternion& Value) noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator /(const Quaternion& Union, const Quaternion& Value) noexcept;
			friend Quaternion QUTER_INTERFACE QUTER_FUNC_CALL operator ^(const Quaternion& Base, std::int64_t Exponent) noexcept;
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
			///
			/// casing
			///
			inline auto to_number() const& noexcept
				-> decltype(forward_as_number((*this)[index::s], (*this)[index::i], (*this)[index::j], (*this)[index::k]))
			{
				return forward_as_number((*this)[index::s], (*this)[index::i], (*this)[index::j], (*this)[index::k]);
			};
			template <std::size_t N>
			inline auto from(const Number<N>& number) && noexcept -> decltype(*this)
			{
				number.store((*this)[index::s], (*this)[index::i], (*this)[index::j], (*this)[index::k]);
				return *this;
			};
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
		/* struct Quaternion */
		///
		/// constants
		///
		const double Quaternion::pi = std::numbers::pi;
		const double Quaternion::e = std::numbers::e;
		const Quaternion Quaternion::i = Quaternion(0, 1, 0, 0);
		const Quaternion Quaternion::j = Quaternion(0, 0, 1, 0);
		const Quaternion Quaternion::k = Quaternion(0, 0, 0, 1);
		///
		/// basis
		///
		QUTER_FUNC_INSTANCE_CALL Quaternion::Quaternion() noexcept : real(), imaginary() {};
		QUTER_FUNC_INSTANCE_CALL Quaternion::Quaternion(double s, const BaseType::Vector3D& v) noexcept : real(s), imaginary(v) {};
		QUTER_FUNC_INSTANCE_CALL Quaternion::Quaternion(double s, double i, double j, double k) noexcept : real(s), imaginary(BaseType::Vector3D(i, j, k)) {};
		QUTER_FUNC_INSTANCE_CALL Quaternion::Quaternion(double Value) noexcept : real(Value), imaginary() {};
		QUTER_FUNC_INSTANCE_CALL Quaternion::Quaternion(const BaseType::Vector3D& Value) noexcept : real(), imaginary(Value) {};
		QUTER_FUNC_INSTANCE_CALL Quaternion::Quaternion(const Quaternion& Value) noexcept : real(Value.real), imaginary(Value.imaginary) {};
		double QUTER_FUNC_CALL Quaternion::Scalar(const Quaternion& Value) noexcept { return Value.real; };
		BaseType::Vector3D QUTER_FUNC_CALL Quaternion::Vector(const Quaternion& Value) noexcept { return Value.imaginary; };
		///
		/// operators
		///
		Quaternion QUTER_FUNC_INSTANCE_CALL Quaternion::operator ()() const noexcept { return *this; };
		double& QUTER_FUNC_INSTANCE_CALL Quaternion::operator [](index i) &
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
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		double& QUTER_FUNC_INSTANCE_CALL Quaternion::operator [](std::size_t i) & noexcept
		{
			try
			{
				Adjust<Period<Quaternion>, false>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		const double& QUTER_FUNC_INSTANCE_CALL Quaternion::operator [](index i) const&
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
			default:
				throw std::out_of_range("The index is out of range.");
			}
		};
		const double& QUTER_FUNC_INSTANCE_CALL Quaternion::operator [](std::size_t i) const& noexcept
		{
			try
			{
				Adjust<Period<Quaternion>, false>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		bool QUTER_FUNC_CALL operator ==(const Quaternion& Union, const Quaternion& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool QUTER_FUNC_CALL operator !=(const Quaternion& Union, const Quaternion& Value) noexcept { return !(Union == Value); };
		Quaternion QUTER_FUNC_CALL operator +(const Quaternion& Value) noexcept { return Value; };
		Quaternion QUTER_FUNC_CALL operator -(const Quaternion& Value) noexcept { return Quaternion{}.from(-Value.to_number()); };
		Quaternion QUTER_FUNC_CALL operator ~(const Quaternion& Value) noexcept { return Quaternion{}.from(~Value.to_number()); };
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator ++() & noexcept
		{
			++this->real;
			return *this;
		};
		Quaternion QUTER_FUNC_INSTANCE_CALL Quaternion::operator ++(int) & noexcept
		{
			Quaternion temp = *this;
			++this->real;
			return temp;
		};
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator --() & noexcept
		{
			--this->real;
			return *this;
		};
		Quaternion QUTER_FUNC_INSTANCE_CALL Quaternion::operator --(int) & noexcept
		{
			Quaternion temp = *this;
			--this->real;
			return temp;
		};
		Quaternion QUTER_FUNC_CALL operator +(const Quaternion& Union, const Quaternion& Value) noexcept { return Quaternion{}.from(Union.to_number() + Value.to_number()); };
		Quaternion QUTER_FUNC_CALL operator -(const Quaternion& Union, const Quaternion& Value) noexcept { return Quaternion{}.from(Union.to_number() - Value.to_number()); };
		Quaternion QUTER_FUNC_CALL operator *(const Quaternion& Union, const Quaternion& Value) noexcept { return Quaternion{}.from(Union.to_number() * Value.to_number()); };
		Quaternion QUTER_FUNC_CALL operator /(const Quaternion& Union, const Quaternion& Value) noexcept
		{
			try
			{
				if (Quaternion::Vector(Value) == 0) { return Quaternion{}.from(Union.to_number() / Quaternion::Scalar(Value)); }
				return Union * Quaternion::inverse(Value);
			}
			catch (...) { return 0; }
		};
		Quaternion QUTER_FUNC_CALL operator ^(const Quaternion& Base, std::int64_t Exponent) noexcept
		{
			try { return Quaternion::power(Base, static_cast<double>(Exponent)); }
			catch (...) { return 0; }
		};
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator =(const Quaternion& Value) & noexcept
		{
			this->real = Value.real;
			this->imaginary = Value.imaginary;
			return *this;
		};
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator +=(const Quaternion& Value) & noexcept { return *this = *this + Value; };
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator +=(const std::initializer_list<Quaternion>& Value) & noexcept
		{
			for (std::initializer_list<Quaternion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator -=(const Quaternion& Value) & noexcept { return *this = *this - Value; };
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator -=(const std::initializer_list<Quaternion>& Value) & noexcept
		{
			for (std::initializer_list<Quaternion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator *=(const Quaternion& Value) & noexcept { return *this = *this * Value; };
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator *=(const std::initializer_list<Quaternion>& Value) & noexcept
		{
			for (std::initializer_list<Quaternion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator /=(const Quaternion& Value) & noexcept { return *this = *this / Value; };
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator /=(const std::initializer_list<Quaternion>& Value) & noexcept
		{
			for (std::initializer_list<Quaternion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator ^=(std::int64_t Exponent) & noexcept { return *this = *this ^ Exponent; };
		Quaternion& QUTER_FUNC_INSTANCE_CALL Quaternion::operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept
		{
			for (std::initializer_list<std::int64_t>::const_iterator ite = Exponent.begin(); ite != Exponent.end(); ++ite) { *this ^= *ite; }
			return *this;
		};
		///
		/// fundamentals
		///
		double QUTER_FUNC_CALL Quaternion::abs(const Quaternion& Value) { return std::sqrt(dot(Value, Value)); };
		double QUTER_FUNC_CALL Quaternion::arg(const Quaternion& Value) { return arg(Value, 0); };
		double QUTER_FUNC_CALL Quaternion::arg(const Quaternion& Value, std::int64_t Theta) { return std::acos(Scalar(Value) / abs(Value)) + 2 * pi * static_cast<double>(Theta); };
		Quaternion QUTER_FUNC_CALL Quaternion::conjg(const Quaternion& Value) { return ~Value; };
		Quaternion QUTER_FUNC_CALL Quaternion::sgn(const Quaternion& Value) { return Value / abs(Value); };
		Quaternion QUTER_FUNC_CALL Quaternion::inverse(const Quaternion& Value) { return conjg(Value) / dot(Value, Value); };
		Quaternion QUTER_FUNC_CALL Quaternion::exp(const Quaternion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::exp(S); }
			return std::exp(S) * (std::cos(abs(V)) + sgn(V) * std::sin(abs(V)));
		};
		Quaternion QUTER_FUNC_CALL Quaternion::ln(const Quaternion& Value) { return ln(Value, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::ln(const Quaternion& Value, std::int64_t Theta)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0)
			{
				if (S < 0) { return std::log(-S) + static_cast<double>(2 * Theta + 1) * i * pi; }
				return std::log(S);
			}
			return std::log(abs(Value)) + sgn(V) * arg(Value, Theta);
		};
		///
		/// multiples
		///
		double QUTER_FUNC_CALL Quaternion::dot(const Quaternion& Union, const Quaternion& Value) noexcept
		{
			return Scalar(Union) * Scalar(Value) + BaseType::Vector3D::dot(Vector(Union), Vector(Value));
		};
		BaseType::Vector3D QUTER_FUNC_CALL Quaternion::outer(const Quaternion& Union, const Quaternion& Value) noexcept
		{
			return BaseType::Vector3D::cross(Vector(Union), Vector(Value)) + Scalar(Union) * Vector(Value) - Scalar(Value) * Vector(Union);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::even(const Quaternion& Union, const Quaternion& Value) noexcept
		{
			return Scalar(Union) * Scalar(Value) - BaseType::Vector3D::dot(Vector(Union), Vector(Value)) + Scalar(Union) * Vector(Value) + Scalar(Value) * Vector(Union);
		};
		BaseType::Vector3D QUTER_FUNC_CALL Quaternion::cross(const Quaternion& Union, const Quaternion& Value) noexcept
		{
			return BaseType::Vector3D::cross(Vector(Union), Vector(Value));
		};
		///
		/// exponentials
		///
		Quaternion QUTER_FUNC_CALL Quaternion::power(const Quaternion& Base, const Quaternion& Exponent) { return power(Base, Exponent, 0, 0, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::power(const Quaternion& Base, const Quaternion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau)
		{
			return exp(exp(ln(ln(Base, Theta), Phi) + ln(Exponent, Tau)));
		};
		Quaternion QUTER_FUNC_CALL Quaternion::power(const Quaternion& Base, double Exponent) { return power(Base, Exponent, 0); }
		Quaternion QUTER_FUNC_CALL Quaternion::power(const Quaternion& Base, double Exponent, std::int64_t Theta)
		{
			if (Base == 0) { return Exponent == 0 ? 1 : 0; }
			return std::pow(abs(Base), Exponent) *
				(std::cos(Exponent * arg(Base, Theta)) + sgn(Vector(Base)) * std::sin(Exponent * arg(Base, Theta)));
		};
		Quaternion QUTER_FUNC_CALL Quaternion::root(const Quaternion& Base, const Quaternion& Exponent) { return root(Base, Exponent, 0, 0, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::root(const Quaternion& Base, const Quaternion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau) { return power(Base, inverse(Exponent), Theta, Phi, Tau); };
		Quaternion QUTER_FUNC_CALL Quaternion::root(const Quaternion& Base, double Exponent) { return root(Base, Exponent, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::root(const Quaternion& Base, double Exponent, std::int64_t Theta) { return power(Base, 1 / Exponent, Theta); };
		Quaternion QUTER_FUNC_CALL Quaternion::log(const Quaternion& Base, const Quaternion& Number) { return log(Base, Number, 0, 0, 0, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::log(const Quaternion& Base, const Quaternion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega)
		{
			return exp(ln(ln(Number, Theta), Phi) - ln(ln(Base, Tau), Omega));
		};
		///
		/// trigonometrics
		///
		Quaternion QUTER_FUNC_CALL Quaternion::sin(const Quaternion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::sin(S); }
			return std::sin(S) * std::cosh(abs(V)) + sgn(V) * (std::cos(S) * std::sinh(abs(V)));
		};
		Quaternion QUTER_FUNC_CALL Quaternion::arcsin(const Quaternion& Value) { return arcsin(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arcsin(const Quaternion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true)
			{
				auto S = Scalar(Value);
				auto V = Vector(Value);
				if (V == 0) { return -i * ln(i * S + root(1 - S * S, 2), Period); }
				return -sgn(V) * ln(sgn(V) * Value + root(1 - Value * Value, 2), Period);
			}
			return pi - arcsin(Value, true, Period);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::sinh(const Quaternion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::sinh(S); }
			return std::sinh(S) * std::cos(abs(V)) + sgn(V) * (std::cosh(S) * std::sin(abs(V)));
		};
		Quaternion QUTER_FUNC_CALL Quaternion::arcsinh(const Quaternion& Value) { return arcsinh(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arcsinh(const Quaternion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(Value * Value + 1, 2), Period); }
			auto V = Vector(Value);
			if (V == 0) { return pi * i - arcsinh(Value, true, Period); }
			return pi * sgn(V) - arcsinh(Value, true, Period);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::cos(const Quaternion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::cos(S); }
			return std::cos(S) * std::cosh(abs(V)) - sgn(V) * (std::sin(S) * std::sinh(abs(V)));
		};
		Quaternion QUTER_FUNC_CALL Quaternion::arccos(const Quaternion& Value) { return arccos(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccos(const Quaternion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true)
			{
				auto S = Scalar(Value);
				auto V = Vector(Value);
				if (V == 0) { return -i * ln(S + root(S * S - 1, 2), Period); }
				return -sgn(V) * ln(Value + root(Value * Value - 1, 2), Period);
			}
			return 2 * pi - arccos(Value, true, Period);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::cosh(const Quaternion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::cosh(S); }
			return std::cosh(S) * std::cos(abs(V)) + sgn(V) * (std::sinh(S) * std::sin(abs(V)));
		};
		Quaternion QUTER_FUNC_CALL Quaternion::arccosh(const Quaternion& Value) { return arccosh(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccosh(const Quaternion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(Value * Value - 1, 2), Period); }
			auto V = Vector(Value);
			if (V == 0) { return 2 * pi * i - arccosh(Value, true, Period); }
			return 2 * pi * sgn(V) - arccosh(Value, true, Period);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::tan(const Quaternion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			auto TanS = std::tan(S);
			if (V == 0) { return TanS; }
			auto TanS2 = TanS * TanS;
			auto TanhV = std::tanh(abs(V));
			auto TanhV2 = TanhV * TanhV;
			return (TanS * (1 - TanhV2) + sgn(V) * (TanhV * (1 + TanS2))) / (1 + TanS2 * TanhV2);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::arctan(const Quaternion& Value) { return arctan(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arctan(const Quaternion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true)
			{
				auto S = Scalar(Value);
				auto V = Vector(Value);
				if (V == 0) { return i / 2 * (ln(1 - i * S, Period) - ln(1 + i * S)); }
				return sgn(V) / 2 * (ln(1 - sgn(V) * Value, Period) - ln(1 + sgn(V) * Value));
			}
			return pi + arctan(Value, true, Period);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::tanh(const Quaternion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			auto TanhS = std::tanh(S);
			if (V == 0) { return TanhS; }
			auto TanhS2 = TanhS * TanhS;
			auto TanV = std::tan(abs(V));
			auto TanV2 = TanV * TanV;
			return (TanhS * (1 - TanV2) + sgn(V) * (TanV * (1 + TanhS2))) / (1 + TanhS2 * TanV2);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::arctanh(const Quaternion& Value) { return arctanh(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arctanh(const Quaternion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return 1 / 2 * (ln(1 + Value, Period) - ln(1 - Value)); }
			auto V = Vector(Value);
			if (V == 0) { return pi * i + arctanh(Value, true, Period); }
			return pi * sgn(V) + arctanh(Value, true, Period);
		};
		Quaternion QUTER_FUNC_CALL Quaternion::csc(const Quaternion& Value) { return inverse(sin(Value)); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccsc(const Quaternion& Value) { return arccsc(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccsc(const Quaternion& Value, bool Sign, std::int64_t Period) { return arcsin(inverse(Value), Sign, Period); };
		Quaternion QUTER_FUNC_CALL Quaternion::csch(const Quaternion& Value) { return inverse(sinh(Value)); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccsch(const Quaternion& Value) { return arccsch(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccsch(const Quaternion& Value, bool Sign, std::int64_t Period) { return arcsinh(inverse(Value), Sign, Period); };
		Quaternion QUTER_FUNC_CALL Quaternion::sec(const Quaternion& Value) { return inverse(cos(Value)); };
		Quaternion QUTER_FUNC_CALL Quaternion::arcsec(const Quaternion& Value) { return arcsec(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arcsec(const Quaternion& Value, bool Sign, std::int64_t Period) { return arccos(inverse(Value), Sign, Period); };
		Quaternion QUTER_FUNC_CALL Quaternion::sech(const Quaternion& Value) { return inverse(cosh(Value)); };
		Quaternion QUTER_FUNC_CALL Quaternion::arcsech(const Quaternion& Value) { return arcsech(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arcsech(const Quaternion& Value, bool Sign, std::int64_t Period) { return arccosh(inverse(Value), Sign, Period); };
		Quaternion QUTER_FUNC_CALL Quaternion::cot(const Quaternion& Value) { return inverse(tan(Value)); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccot(const Quaternion& Value) { return arccot(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccot(const Quaternion& Value, bool Sign, std::int64_t Period) { return arctan(inverse(Value), Sign, Period); };
		Quaternion QUTER_FUNC_CALL Quaternion::coth(const Quaternion& Value) { return inverse(tanh(Value)); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccoth(const Quaternion& Value) { return arccoth(Value, true, 0); };
		Quaternion QUTER_FUNC_CALL Quaternion::arccoth(const Quaternion& Value, bool Sign, std::int64_t Period) { return arctanh(inverse(Value), Sign, Period); };
		///
		/// conventions
		///
		std::wstring QUTER_FUNC_CALL Quaternion::GetString(const Quaternion& Value)
		{
			return ToString(Value[index::s], L"", Value[index::i], L"i", Value[index::j], L"j", Value[index::k], L"k");
		};
		Quaternion QUTER_FUNC_CALL Quaternion::GetInstance(const std::wstring& Value)
		{
			std::wstring Replaced = Replace(Value, L" ", L"");
			Quaternion Object;
			ToNumbers(Replaced, Object[index::s], L"", Object[index::i], L"i", Object[index::j], L"j", Object[index::k], L"k");
			return Object;
		};
	}
}
#pragma pop_macro("QUTER_FUNC_INSTANCE_CALL")
#pragma pop_macro("QUTER_FUNC_CALL")
#pragma pop_macro("QUTER_INTERFACE")
#pragma pop_macro("CALL")
#pragma pack(pop)
