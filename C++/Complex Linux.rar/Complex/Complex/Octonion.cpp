#include "Module.h"
#pragma pack(push)
#pragma push_macro("CALL")
#pragma push_macro("OCTON_INTERFACE")
#pragma push_macro("OCTON_FUNC_CALL")
#pragma push_macro("OCTON_FUNC_INSTANCE_CALL")
#if defined(X86) || defined(ARM)
#pragma pack(4)
#elif defined(X64) || defined(ARM64)
#pragma pack(8)
#endif
#define CALL(c)
#define OCTON_INTERFACE
#define OCTON_FUNC_CALL
#define OCTON_FUNC_INSTANCE_CALL
namespace Octon
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
		struct OCTON_INTERFACE Vector7D
		{
		public:
			///
			/// constants
			///
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
			/// basis
			///
			double x1;
			double x2;
			double x3;
			double x4;
			double x5;
			double x6;
			double x7;
		public:
			explicit OCTON_FUNC_INSTANCE_CALL Vector7D() noexcept;
			explicit OCTON_FUNC_INSTANCE_CALL Vector7D(double x1, double x2, double x3, double x4, double x5, double x6, double x7) noexcept;
			OCTON_FUNC_INSTANCE_CALL Vector7D(const Vector7D& Value) noexcept;
			///
			/// operators
			///
			Vector7D OCTON_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& OCTON_FUNC_INSTANCE_CALL operator [](index i) &;
			double& OCTON_FUNC_INSTANCE_CALL operator [](std::size_t i) & noexcept;
			const double& OCTON_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& OCTON_FUNC_INSTANCE_CALL operator [](std::size_t i) const& noexcept;
			friend bool OCTON_INTERFACE OCTON_FUNC_CALL operator ==(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend bool OCTON_INTERFACE OCTON_FUNC_CALL operator !=(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Vector7D& Value) noexcept;
			friend Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Vector7D& Value) noexcept;
			friend Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Vector7D& Union, const Vector7D& Value) noexcept;
			friend Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator *(double Union, const Vector7D& Value) noexcept;
			friend Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator *(const Vector7D& Union, double Value) noexcept;
			friend Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator /(const Vector7D& Union, double Value) noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator =(const Vector7D& Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator +=(const Vector7D& Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Vector7D>& Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator -=(const Vector7D& Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Vector7D>& Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator *=(double Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<double>& Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator /=(double Value) & noexcept;
			Vector7D& OCTON_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<double>& Value) & noexcept;
			///
			/// fundamentals
			///
			static double OCTON_FUNC_CALL abs(const Vector7D& Value);
			static Vector7D OCTON_FUNC_CALL sgn(const Vector7D& Value);
			static double OCTON_FUNC_CALL dot(const Vector7D& Union, const Vector7D& Value) noexcept;
			static Vector7D OCTON_FUNC_CALL cross(const Vector7D& Union, const Vector7D& Value) noexcept;
			///
			/// conventions
			///
			static std::wstring OCTON_FUNC_CALL GetString(const Vector7D& Value);
			static Vector7D OCTON_FUNC_CALL GetInstance(const std::wstring& Value);
			///
			/// casing
			///
			inline auto to_number() const& noexcept
				-> decltype(forward_as_number((*this)[index::e1], (*this)[index::e2], (*this)[index::e3], (*this)[index::e4], (*this)[index::e5], (*this)[index::e6], (*this)[index::e7]))
			{
				return forward_as_number((*this)[index::e1], (*this)[index::e2], (*this)[index::e3], (*this)[index::e4], (*this)[index::e5], (*this)[index::e6], (*this)[index::e7]);
			};
			template <std::size_t N>
			inline auto from(const Number<N>& number) && noexcept -> decltype(*this)
			{
				number.store((*this)[index::e1], (*this)[index::e2], (*this)[index::e3], (*this)[index::e4], (*this)[index::e5], (*this)[index::e6], (*this)[index::e7]);
				return *this;
			};
		};
		///
		/// operators
		///
		bool OCTON_INTERFACE OCTON_FUNC_CALL operator ==(const Vector7D& Union, const Vector7D& Value) noexcept;
		bool OCTON_INTERFACE OCTON_FUNC_CALL operator !=(const Vector7D& Union, const Vector7D& Value) noexcept;
		Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Vector7D& Value) noexcept;
		Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Vector7D& Value) noexcept;
		Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Vector7D& Union, const Vector7D& Value) noexcept;
		Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Vector7D& Union, const Vector7D& Value) noexcept;
		Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator *(double Union, const Vector7D& Value) noexcept;
		Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator *(const Vector7D& Union, double Value) noexcept;
		Vector7D OCTON_INTERFACE OCTON_FUNC_CALL operator /(const Vector7D& Union, double Value) noexcept;
		/* struct Vector7D */
		///
		/// constants
		///
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
		/// basis
		///
		OCTON_FUNC_INSTANCE_CALL Vector7D::Vector7D() noexcept : x1(), x2(), x3(), x4(), x5(), x6(), x7() {};
		OCTON_FUNC_INSTANCE_CALL Vector7D::Vector7D(double x1, double x2, double x3, double x4, double x5, double x6, double x7) noexcept : x1(x1), x2(x2), x3(x3), x4(x4), x5(x5), x6(x6), x7(x7) {};
		OCTON_FUNC_INSTANCE_CALL Vector7D::Vector7D(const Vector7D& Value) noexcept : x1(Value.x1), x2(Value.x2), x3(Value.x3), x4(Value.x4), x5(Value.x5), x6(Value.x6), x7(Value.x7) {};
		///
		/// operators
		///
		Vector7D OCTON_FUNC_INSTANCE_CALL Vector7D::operator ()() const noexcept { return *this; };
		double& OCTON_FUNC_INSTANCE_CALL Vector7D::operator [](index i) &
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
		double& OCTON_FUNC_INSTANCE_CALL Vector7D::operator [](std::size_t i) & noexcept
		{
			try
			{
				Adjust<Period<Vector7D>, true>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		const double& OCTON_FUNC_INSTANCE_CALL Vector7D::operator [](index i) const&
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
		const double& OCTON_FUNC_INSTANCE_CALL Vector7D::operator [](std::size_t i) const& noexcept
		{
			try
			{
				Adjust<Period<Vector7D>, true>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		bool OCTON_FUNC_CALL operator ==(const Vector7D& Union, const Vector7D& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool OCTON_FUNC_CALL operator !=(const Vector7D& Union, const Vector7D& Value) noexcept { return !(Union == Value); };
		Vector7D OCTON_FUNC_CALL operator +(const Vector7D& Value) noexcept { return Value; };
		Vector7D OCTON_FUNC_CALL operator -(const Vector7D& Value) noexcept { return Vector7D{}.from(-Value.to_number()); };
		Vector7D OCTON_FUNC_CALL operator +(const Vector7D& Union, const Vector7D& Value) noexcept { return Vector7D{}.from(Union.to_number() + Value.to_number()); };
		Vector7D OCTON_FUNC_CALL operator -(const Vector7D& Union, const Vector7D& Value) noexcept { return Vector7D{}.from(Union.to_number() - Value.to_number()); };
		Vector7D OCTON_FUNC_CALL operator *(double Union, const Vector7D& Value) noexcept { return Vector7D{}.from(Union * Value.to_number()); };
		Vector7D OCTON_FUNC_CALL operator *(const Vector7D& Union, double Value) noexcept { return Vector7D{}.from(Union.to_number() * Value); };
		Vector7D OCTON_FUNC_CALL operator /(const Vector7D& Union, double Value) noexcept { return Vector7D{}.from(Union.to_number() / Value); };
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator =(const Vector7D& Value) & noexcept
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
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator +=(const Vector7D& Value) & noexcept { return *this = *this + Value; };
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator +=(const std::initializer_list<Vector7D>& Value) & noexcept
		{
			for (std::initializer_list<Vector7D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator -=(const Vector7D& Value) & noexcept { return *this = *this - Value; };
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator -=(const std::initializer_list<Vector7D>& Value) & noexcept
		{
			for (std::initializer_list<Vector7D>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator *=(double Value) & noexcept { return *this = *this * Value; };
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator *=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator /=(double Value) & noexcept { return *this = *this / Value; };
		Vector7D& OCTON_FUNC_INSTANCE_CALL Vector7D::operator /=(const std::initializer_list<double>& Value) & noexcept
		{
			for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		///
		/// fundamentals
		///
		double OCTON_FUNC_CALL Vector7D::abs(const Vector7D& Value) { return std::sqrt(dot(Value, Value)); };
		Vector7D OCTON_FUNC_CALL Vector7D::sgn(const Vector7D& Value) { return Value / abs(Value); };
		double OCTON_FUNC_CALL Vector7D::dot(const Vector7D& Union, const Vector7D& Value) noexcept
		{
			return vector_dot(Union.to_number(), Value.to_number());
		};
		Vector7D OCTON_FUNC_CALL Vector7D::cross(const Vector7D& Union, const Vector7D& Value) noexcept
		{
			return Vector7D{}.from(vector_cross(Union.to_number(), Value.to_number()));
		};
		///
		/// conventions
		///
		std::wstring OCTON_FUNC_CALL Vector7D::GetString(const Vector7D& Value)
		{
			return ToString(Value[index::e1], L"e1", Value[index::e2], L"e2", Value[index::e3], L"e3", Value[index::e4], L"e4", Value[index::e5], L"e5", Value[index::e6], L"e6", Value[index::e7], L"e7");
		};
		Vector7D OCTON_FUNC_CALL Vector7D::GetInstance(const std::wstring& Value)
		{
			std::wstring Replaced = Replace(Value, L" ", L"");
			Vector7D Object;
			ToNumbers(Replaced, Object[index::e1], L"e1", Object[index::e2], L"e2", Object[index::e3], L"e3", Object[index::e4], L"e4", Object[index::e5], L"e5", Object[index::e6], L"e6", Object[index::e7], L"e7");
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
		struct OCTON_INTERFACE Octonion
		{
		public:
			///
			/// constants
			///
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
			/// basis
			///
			double real;
			BaseType::Vector7D imaginary;
		public:
			explicit OCTON_FUNC_INSTANCE_CALL Octonion() noexcept;
			explicit OCTON_FUNC_INSTANCE_CALL Octonion(double s, const BaseType::Vector7D& v) noexcept;
			explicit OCTON_FUNC_INSTANCE_CALL Octonion(double s, double i, double j, double k, double l, double il, double jl, double kl) noexcept;
			OCTON_FUNC_INSTANCE_CALL Octonion(double Value) noexcept;
			OCTON_FUNC_INSTANCE_CALL Octonion(const BaseType::Vector7D& Value) noexcept;
			OCTON_FUNC_INSTANCE_CALL Octonion(const Octonion& Value) noexcept;
			static double OCTON_FUNC_CALL Scalar(const Octonion& Value) noexcept;
			static BaseType::Vector7D OCTON_FUNC_CALL Vector(const Octonion& Value) noexcept;
			///
			/// operators
			///
			Octonion OCTON_FUNC_INSTANCE_CALL operator ()() const noexcept;
			double& OCTON_FUNC_INSTANCE_CALL operator [](index i) &;
			double& OCTON_FUNC_INSTANCE_CALL operator [](std::size_t i) & noexcept;
			const double& OCTON_FUNC_INSTANCE_CALL operator [](index i) const&;
			const double& OCTON_FUNC_INSTANCE_CALL operator [](std::size_t i) const& noexcept;
			friend bool OCTON_INTERFACE OCTON_FUNC_CALL operator ==(const Octonion& Union, const Octonion& Value) noexcept;
			friend bool OCTON_INTERFACE OCTON_FUNC_CALL operator !=(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Octonion& Value) noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Octonion& Value) noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator ~(const Octonion& Value) noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator ++() & noexcept;
			Octonion OCTON_FUNC_INSTANCE_CALL operator ++(int) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator --() & noexcept;
			Octonion OCTON_FUNC_INSTANCE_CALL operator --(int) & noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator *(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator /(const Octonion& Union, const Octonion& Value) noexcept;
			friend Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator ^(const Octonion& Base, std::int64_t Exponent) noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator =(const Octonion& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator +=(const Octonion& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator +=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator -=(const Octonion& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator -=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator *=(const Octonion& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator *=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator /= (const Octonion& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator /=(const std::initializer_list<Octonion>& Value) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator ^=(std::int64_t Exponent) & noexcept;
			Octonion& OCTON_FUNC_INSTANCE_CALL operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept;
			///
			/// fundamentals
			///
			static double OCTON_FUNC_CALL abs(const Octonion& Value);
			static double OCTON_FUNC_CALL arg(const Octonion& Value);
			static double OCTON_FUNC_CALL arg(const Octonion& Value, std::int64_t Theta);
			static Octonion OCTON_FUNC_CALL conjg(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL sgn(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL inverse(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL exp(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL ln(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL ln(const Octonion& Value, std::int64_t Theta);
			///
			/// multiples
			///
			static double OCTON_FUNC_CALL dot(const Octonion& Union, const Octonion& Value) noexcept;
			static BaseType::Vector7D OCTON_FUNC_CALL outer(const Octonion& Union, const Octonion& Value) noexcept;
			static Octonion OCTON_FUNC_CALL even(const Octonion& Union, const Octonion& Value) noexcept;
			static BaseType::Vector7D OCTON_FUNC_CALL cross(const Octonion& Union, const Octonion& Value) noexcept;
			///
			/// exponentials
			///
			static Octonion OCTON_FUNC_CALL power(const Octonion& Base, const Octonion& Exponent);
			static Octonion OCTON_FUNC_CALL power(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
			static Octonion OCTON_FUNC_CALL power(const Octonion& Base, double Exponent);
			static Octonion OCTON_FUNC_CALL power(const Octonion& Base, double Exponent, std::int64_t Theta);
			static Octonion OCTON_FUNC_CALL root(const Octonion& Base, const Octonion& Exponent);
			static Octonion OCTON_FUNC_CALL root(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
			static Octonion OCTON_FUNC_CALL root(const Octonion& Base, double Exponent);
			static Octonion OCTON_FUNC_CALL root(const Octonion& Base, double Exponent, std::int64_t Theta);
			static Octonion OCTON_FUNC_CALL log(const Octonion& Base, const Octonion& Number);
			static Octonion OCTON_FUNC_CALL log(const Octonion& Base, const Octonion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega);
			///
			/// trigonometrics
			///
			static Octonion OCTON_FUNC_CALL sin(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsin(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsin(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL sinh(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsinh(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsinh(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL cos(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccos(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccos(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL cosh(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccosh(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccosh(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL tan(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arctan(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arctan(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL tanh(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arctanh(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arctanh(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL csc(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccsc(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccsc(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL csch(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccsch(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccsch(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL sec(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsec(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsec(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL sech(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsech(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arcsech(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL cot(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccot(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccot(const Octonion& Value, bool Sign, std::int64_t Period);
			static Octonion OCTON_FUNC_CALL coth(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccoth(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL arccoth(const Octonion& Value, bool Sign, std::int64_t Period);
			///
			/// conventions
			///
			static std::wstring OCTON_FUNC_CALL GetString(const Octonion& Value);
			static Octonion OCTON_FUNC_CALL GetInstance(const std::wstring& Value);
			///
			/// casing
			///
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
		///
		/// operators
		///
		bool OCTON_INTERFACE OCTON_FUNC_CALL operator ==(const Octonion& Union, const Octonion& Value) noexcept;
		bool OCTON_INTERFACE OCTON_FUNC_CALL operator !=(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator ~(const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator +(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator -(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator *(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator /(const Octonion& Union, const Octonion& Value) noexcept;
		Octonion OCTON_INTERFACE OCTON_FUNC_CALL operator ^(const Octonion& Base, std::int64_t Exponent) noexcept;
		/* struct Octonion */
		///
		/// constants
		///
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
		/// basis
		///
		OCTON_FUNC_INSTANCE_CALL Octonion::Octonion() noexcept : real(), imaginary() {};
		OCTON_FUNC_INSTANCE_CALL Octonion::Octonion(double s, const BaseType::Vector7D& v) noexcept : real(s), imaginary(v) {};
		OCTON_FUNC_INSTANCE_CALL Octonion::Octonion(double s, double i, double j, double k, double l, double il, double jl, double kl) noexcept : real(s), imaginary(BaseType::Vector7D(i, j, k, l, il, jl, kl)) {};
		OCTON_FUNC_INSTANCE_CALL Octonion::Octonion(double Value) noexcept : real(Value), imaginary() {};
		OCTON_FUNC_INSTANCE_CALL Octonion::Octonion(const BaseType::Vector7D& Value) noexcept : real(), imaginary(Value) {};
		OCTON_FUNC_INSTANCE_CALL Octonion::Octonion(const Octonion& Value) noexcept : real(Value.real), imaginary(Value.imaginary) {};
		double OCTON_FUNC_CALL Octonion::Scalar(const Octonion& Value) noexcept { return Value.real; };
		BaseType::Vector7D OCTON_FUNC_CALL Octonion::Vector(const Octonion& Value) noexcept { return Value.imaginary; };
		///
		/// operators
		///
		Octonion OCTON_FUNC_INSTANCE_CALL Octonion::operator ()() const noexcept { return *this; };
		double& OCTON_FUNC_INSTANCE_CALL Octonion::operator [](index i) &
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
		double& OCTON_FUNC_INSTANCE_CALL Octonion::operator [](std::size_t i) & noexcept
		{
			try
			{
				Adjust<Period<Octonion>, false>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		const double& OCTON_FUNC_INSTANCE_CALL Octonion::operator [](index i) const&
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
		const double& OCTON_FUNC_INSTANCE_CALL Octonion::operator [](std::size_t i) const& noexcept
		{
			try
			{
				Adjust<Period<Octonion>, false>(i);
				return this->operator[](static_cast<index>(i));
			}
			catch (...) { return this->operator[](i); }
		};
		bool OCTON_FUNC_CALL operator ==(const Octonion& Union, const Octonion& Value) noexcept { return Union.to_number() == Value.to_number(); };
		bool OCTON_FUNC_CALL operator !=(const Octonion& Union, const Octonion& Value) noexcept { return !(Union == Value); };
		Octonion OCTON_FUNC_CALL operator +(const Octonion& Value) noexcept { return Value; };
		Octonion OCTON_FUNC_CALL operator -(const Octonion& Value) noexcept { return Octonion{}.from(-Value.to_number()); };
		Octonion OCTON_FUNC_CALL operator ~(const Octonion& Value) noexcept { return Octonion{}.from(~Value.to_number()); };
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator ++() & noexcept
		{
			++this->real;
			return *this;
		};
		Octonion OCTON_FUNC_INSTANCE_CALL Octonion::operator ++(int) & noexcept
		{
			Octonion temp = *this;
			++this->real;
			return temp;
		};
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator --() & noexcept
		{
			--this->real;
			return *this;
		};
		Octonion OCTON_FUNC_INSTANCE_CALL Octonion::operator --(int) & noexcept
		{
			Octonion temp = *this;
			--this->real;
			return temp;
		};
		Octonion OCTON_FUNC_CALL operator +(const Octonion& Union, const Octonion& Value) noexcept { return Octonion{}.from(Union.to_number() + Value.to_number()); };
		Octonion OCTON_FUNC_CALL operator -(const Octonion& Union, const Octonion& Value) noexcept { return Octonion{}.from(Union.to_number() - Value.to_number()); };
		Octonion OCTON_FUNC_CALL operator *(const Octonion& Union, const Octonion& Value) noexcept { return Octonion{}.from(Union.to_number() * Value.to_number()); };
		Octonion OCTON_FUNC_CALL operator /(const Octonion& Union, const Octonion& Value) noexcept
		{
			try
			{
				if (Octonion::Vector(Value) == 0) { return Octonion{}.from(Union.to_number() / Octonion::Scalar(Value)); }
				return Union * Octonion::inverse(Value);
			}
			catch (...) { return 0; }
		};
		Octonion OCTON_FUNC_CALL operator ^(const Octonion& Base, std::int64_t Exponent) noexcept
		{
			try { return Octonion::power(Base, static_cast<double>(Exponent)); }
			catch (...) { return 0; }
		};
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator =(const Octonion& Value) & noexcept
		{
			this->real = Value.real;
			this->imaginary = Value.imaginary;
			return *this;
		};
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator +=(const Octonion& Value) & noexcept { return *this = *this + Value; };
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator +=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
			return *this;
		};
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator -=(const Octonion& Value) & noexcept { return *this = *this - Value; };
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator -=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator *=(const Octonion& Value) & noexcept { return *this = *this * Value; };
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator *=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator /=(const Octonion& Value) & noexcept { return *this = *this / Value; };
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator /=(const std::initializer_list<Octonion>& Value) & noexcept
		{
			for (std::initializer_list<Octonion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator ^=(std::int64_t Exponent) & noexcept { return *this = *this ^ Exponent; };
		Octonion& OCTON_FUNC_INSTANCE_CALL Octonion::operator ^=(const std::initializer_list<std::int64_t>& Exponent) & noexcept
		{
			for (std::initializer_list<std::int64_t>::const_iterator ite = Exponent.begin(); ite != Exponent.end(); ++ite) { *this ^= *ite; }
			return *this;
		};
		///
		/// fundamentals
		///
		double OCTON_FUNC_CALL Octonion::abs(const Octonion& Value) { return std::sqrt(dot(Value, Value)); };
		double OCTON_FUNC_CALL Octonion::arg(const Octonion& Value) { return arg(Value, 0); };
		double OCTON_FUNC_CALL Octonion::arg(const Octonion& Value, std::int64_t Theta) { return std::acos(Scalar(Value) / abs(Value)) + 2 * pi * static_cast<double>(Theta); };
		Octonion OCTON_FUNC_CALL Octonion::conjg(const Octonion& Value) { return ~Value; };
		Octonion OCTON_FUNC_CALL Octonion::sgn(const Octonion& Value) { return Value / abs(Value); };
		Octonion OCTON_FUNC_CALL Octonion::inverse(const Octonion& Value) { return conjg(Value) / dot(Value, Value); };
		Octonion OCTON_FUNC_CALL Octonion::exp(const Octonion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::exp(S); }
			return std::exp(S) * (std::cos(abs(V)) + sgn(V) * std::sin(abs(V)));
		};
		Octonion OCTON_FUNC_CALL Octonion::ln(const Octonion& Value) { return ln(Value, 0); };
		Octonion OCTON_FUNC_CALL Octonion::ln(const Octonion& Value, std::int64_t Theta)
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
		double OCTON_FUNC_CALL Octonion::dot(const Octonion& Union, const Octonion& Value) noexcept
		{
			return Scalar(Union) * Scalar(Value) + BaseType::Vector7D::dot(Vector(Union), Vector(Value));
		};
		BaseType::Vector7D OCTON_FUNC_CALL Octonion::outer(const Octonion& Union, const Octonion& Value) noexcept
		{
			return BaseType::Vector7D::cross(Vector(Union), Vector(Value)) + Scalar(Union) * Vector(Value) - Scalar(Value) * Vector(Union);
		};
		Octonion OCTON_FUNC_CALL Octonion::even(const Octonion& Union, const Octonion& Value) noexcept
		{
			return Scalar(Union) * Scalar(Value) - BaseType::Vector7D::dot(Vector(Union), Vector(Value)) + Scalar(Union) * Vector(Value) + Scalar(Value) * Vector(Union);
		};
		BaseType::Vector7D OCTON_FUNC_CALL Octonion::cross(const Octonion& Union, const Octonion& Value) noexcept
		{
			return BaseType::Vector7D::cross(Vector(Union), Vector(Value));
		};
		///
		/// exponentials
		///
		Octonion OCTON_FUNC_CALL Octonion::power(const Octonion& Base, const Octonion& Exponent) { return power(Base, Exponent, 0, 0, 0); };
		Octonion OCTON_FUNC_CALL Octonion::power(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau)
		{
			return exp(exp(ln(ln(Base, Theta), Phi) + ln(Exponent, Tau)));
		};
		Octonion OCTON_FUNC_CALL Octonion::power(const Octonion& Base, double Exponent) { return power(Base, Exponent, 0); }
		Octonion OCTON_FUNC_CALL Octonion::power(const Octonion& Base, double Exponent, std::int64_t Theta)
		{
			if (Base == 0) { return Exponent == 0 ? 1 : 0; }
			return std::pow(abs(Base), Exponent) *
				(std::cos(Exponent * arg(Base, Theta)) + sgn(Vector(Base)) * std::sin(Exponent * arg(Base, Theta)));
		};
		Octonion OCTON_FUNC_CALL Octonion::root(const Octonion& Base, const Octonion& Exponent) { return root(Base, Exponent, 0, 0, 0); };
		Octonion OCTON_FUNC_CALL Octonion::root(const Octonion& Base, const Octonion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau) { return power(Base, inverse(Exponent), Theta, Phi, Tau); };
		Octonion OCTON_FUNC_CALL Octonion::root(const Octonion& Base, double Exponent) { return power(Base, 1 / Exponent); };
		Octonion OCTON_FUNC_CALL Octonion::root(const Octonion& Base, double Exponent, std::int64_t Theta) { return power(Base, 1 / Exponent, Theta); };
		Octonion OCTON_FUNC_CALL Octonion::log(const Octonion& Base, const Octonion& Number) { return log(Base, Number, 0, 0, 0, 0); };
		Octonion OCTON_FUNC_CALL Octonion::log(const Octonion& Base, const Octonion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega)
		{
			return exp(ln(ln(Number, Theta), Phi) - ln(ln(Base, Tau), Omega));
		};
		///
		/// trigonometrics
		///
		Octonion OCTON_FUNC_CALL Octonion::sin(const Octonion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::sin(S); }
			return std::sin(S) * std::cosh(abs(V)) + sgn(V) * (std::cos(S) * std::sinh(abs(V)));
		};
		Octonion OCTON_FUNC_CALL Octonion::arcsin(const Octonion& Value) { return arcsin(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arcsin(const Octonion& Value, bool Sign, std::int64_t Period)
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
		Octonion OCTON_FUNC_CALL Octonion::sinh(const Octonion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::sinh(S); }
			return std::sinh(S) * std::cos(abs(V)) + sgn(V) * (std::cosh(S) * std::sin(abs(V)));
		};
		Octonion OCTON_FUNC_CALL Octonion::arcsinh(const Octonion& Value) { return arcsinh(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arcsinh(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(Value * Value + 1, 2), Period); }
			auto V = Vector(Value);
			if (V == 0) { return pi * i - arcsinh(Value, true, Period); }
			return pi * sgn(V) - arcsinh(Value, true, Period);
		};
		Octonion OCTON_FUNC_CALL Octonion::cos(const Octonion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::cos(S); }
			return std::cos(S) * std::cosh(abs(V)) - sgn(V) * (std::sin(S) * std::sinh(abs(V)));
		};
		Octonion OCTON_FUNC_CALL Octonion::arccos(const Octonion& Value) { return arccos(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arccos(const Octonion& Value, bool Sign, std::int64_t Period)
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
		Octonion OCTON_FUNC_CALL Octonion::cosh(const Octonion& Value)
		{
			auto S = Scalar(Value);
			auto V = Vector(Value);
			if (V == 0) { return std::cosh(S); }
			return std::cosh(S) * std::cos(abs(V)) + sgn(V) * (std::sinh(S) * std::sin(abs(V)));
		};
		Octonion OCTON_FUNC_CALL Octonion::arccosh(const Octonion& Value) { return arccosh(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arccosh(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return ln(Value + root(Value * Value - 1, 2), Period); }
			auto V = Vector(Value);
			if (V == 0) { return 2 * pi * i - arccosh(Value, true, Period); }
			return 2 * pi * sgn(V) - arccosh(Value, true, Period);
		};
		Octonion OCTON_FUNC_CALL Octonion::tan(const Octonion& Value)
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
		Octonion OCTON_FUNC_CALL Octonion::arctan(const Octonion& Value) { return arctan(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arctan(const Octonion& Value, bool Sign, std::int64_t Period)
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
		Octonion OCTON_FUNC_CALL Octonion::tanh(const Octonion& Value)
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
		Octonion OCTON_FUNC_CALL Octonion::arctanh(const Octonion& Value) { return arctanh(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arctanh(const Octonion& Value, bool Sign, std::int64_t Period)
		{
			if (Sign == true) { return 1 / 2 * (ln(1 + Value, Period) - ln(1 - Value)); }
			auto V = Vector(Value);
			if (V == 0) { return pi * i + arctanh(Value, true, Period); }
			return pi * sgn(V) + arctanh(Value, true, Period);
		};
		Octonion OCTON_FUNC_CALL Octonion::csc(const Octonion& Value) { return inverse(sin(Value)); };
		Octonion OCTON_FUNC_CALL Octonion::arccsc(const Octonion& Value) { return arccsc(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arccsc(const Octonion& Value, bool Sign, std::int64_t Period) { return arcsin(inverse(Value), Sign, Period); };
		Octonion OCTON_FUNC_CALL Octonion::csch(const Octonion& Value) { return inverse(sinh(Value)); };
		Octonion OCTON_FUNC_CALL Octonion::arccsch(const Octonion& Value) { return arccsch(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arccsch(const Octonion& Value, bool Sign, std::int64_t Period) { return arcsinh(inverse(Value), Sign, Period); };
		Octonion OCTON_FUNC_CALL Octonion::sec(const Octonion& Value) { return inverse(cos(Value)); };
		Octonion OCTON_FUNC_CALL Octonion::arcsec(const Octonion& Value) { return arcsec(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arcsec(const Octonion& Value, bool Sign, std::int64_t Period) { return arccos(inverse(Value), Sign, Period); };
		Octonion OCTON_FUNC_CALL Octonion::sech(const Octonion& Value) { return inverse(cosh(Value)); };
		Octonion OCTON_FUNC_CALL Octonion::arcsech(const Octonion& Value) { return arcsech(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arcsech(const Octonion& Value, bool Sign, std::int64_t Period) { return arccosh(inverse(Value), Sign, Period); };
		Octonion OCTON_FUNC_CALL Octonion::cot(const Octonion& Value) { return inverse(tan(Value)); };
		Octonion OCTON_FUNC_CALL Octonion::arccot(const Octonion& Value) { return arccot(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arccot(const Octonion& Value, bool Sign, std::int64_t Period) { return arctan(inverse(Value), Sign, Period); };
		Octonion OCTON_FUNC_CALL Octonion::coth(const Octonion& Value) { return inverse(tanh(Value)); };
		Octonion OCTON_FUNC_CALL Octonion::arccoth(const Octonion& Value) { return arccoth(Value, true, 0); };
		Octonion OCTON_FUNC_CALL Octonion::arccoth(const Octonion& Value, bool Sign, std::int64_t Period) { return arctanh(inverse(Value), Sign, Period); };
		///
		/// conventions
		///
		std::wstring OCTON_FUNC_CALL Octonion::GetString(const Octonion& Value)
		{
			return ToString(Value[index::s], L"", Value[index::i], L"i", Value[index::j], L"j", Value[index::k], L"k", Value[index::l], L"l", Value[index::il], L"il", Value[index::jl], L"jl", Value[index::kl], L"kl");
		};
		Octonion OCTON_FUNC_CALL Octonion::GetInstance(const std::wstring& Value)
		{
			std::wstring Replaced = Replace(Value, L" ", L"");
			Octonion Object;
			ToNumbers(Replaced, Object[index::s], L"", Object[index::i], L"i", Object[index::j], L"j", Object[index::k], L"k", Object[index::l], L"l", Object[index::il], L"il", Object[index::jl], L"jl", Object[index::kl], L"kl");
			return Object;
		};
	}
}
#pragma pop_macro("OCTON_FUNC_INSTANCE_CALL")
#pragma pop_macro("OCTON_FUNC_CALL")
#pragma pop_macro("OCTON_INTERFACE")
#pragma pop_macro("CALL")
#pragma pack(pop)
