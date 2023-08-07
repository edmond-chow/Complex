#include <cmath>
#include <numbers>
#include "Module.h"
#include "Cayley Dickson Algebra.h"
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
#define CALL(c)
#define SEDEN_INTERFACE
#define SEDEN_FUNC_CALL
#define SEDEN_FUNC_INSTANCE_CALL
std::size_t stos_t(const std::wstring& s)
{
	if constexpr (sizeof(decltype(std::stoul(s))) == sizeof(std::size_t)) { return static_cast<std::size_t>(std::stoul(s)); }
	return static_cast<std::size_t>(std::stoull(s));
};
namespace Seden
{
	class SEDEN_INTERFACE Sedenion
	{
	private:
		static std::size_t GetDimension(std::size_t Value)
		{
			std::size_t n = 0;
			while (Value > 0)
			{
				Value >>= static_cast<size_t>(1);
				++n;
			}
			return static_cast<size_t>(1) << n;
		};
	public:
		static const double pi;
		static const double e;
	private:
		///
		/// Initializer
		///
		double* data;
		std::size_t size;
		explicit Sedenion(const double* data, std::size_t size) : data{ new double[size] {} }, size{ size }
		{
			std::copy(data, data + size, this->data);
		};
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
		double& SEDEN_FUNC_INSTANCE_CALL operator [](std::int64_t i) &;
		const double& SEDEN_FUNC_INSTANCE_CALL operator [](std::int64_t i) const&;
		friend bool SEDEN_INTERFACE SEDEN_FUNC_CALL operator ==(const Sedenion& Union, const Sedenion& Value);
		friend bool SEDEN_INTERFACE SEDEN_FUNC_CALL operator !=(const Sedenion& Union, const Sedenion& Value);
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator +(const Sedenion& Value);
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator -(const Sedenion& Value);
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator ~(const Sedenion& Value);
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator ++() &;
		Sedenion SEDEN_FUNC_INSTANCE_CALL operator ++(int) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator --() &;
		Sedenion SEDEN_FUNC_INSTANCE_CALL operator --(int) &;
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator +(const Sedenion& Union, const Sedenion& Value);
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator -(const Sedenion& Union, const Sedenion& Value);
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator *(const Sedenion& Union, const Sedenion& Value);
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator /(const Sedenion& Union, double Value);
		friend Sedenion SEDEN_INTERFACE SEDEN_FUNC_CALL operator ^(const Sedenion& Base, std::int64_t Exponent);
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
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator ^=(std::int64_t Exponent) &;
		Sedenion& SEDEN_FUNC_INSTANCE_CALL operator ^=(const std::initializer_list<std::int64_t>& Exponent) &;
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
		/* Casting */
	private:
		Factor to_factor() const& noexcept { return Factor{ data, size }; };
		static Sedenion from(const Factor& number)
		{
			std::size_t Size = number.get_size();
			double* Temp = new double[Size] {};
			std::copy(number.get_data(), number.get_data() + Size, Temp);
			Sedenion Output{ Temp, Size };
			delete[] Temp;
			return Output;
		};
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
	/* class Sedenion */
	const double Sedenion::pi = std::numbers::pi;
	const double Sedenion::e = std::numbers::e;
	///
	/// Initializer
	///
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion()
		: data(new double[16] {}), size(16) {};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(const std::initializer_list<double>& numbers)
		: data(new double[numbers.size()] {}), size(numbers.size())
	{
		std::copy(numbers.begin(), numbers.end(), this->data);
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(double Value)
		: data(new double[1] { Value }), size(1) {};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(const Sedenion& Value)
		: data(new double[Value.size] {}), size(Value.size)
	{
		std::copy(Value.data, Value.data + Value.size, this->data);
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(Sedenion&& Value) noexcept
		: data(Value.data), size(Value.size)
	{
		Value.data = nullptr;
		Value.size = 0;
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::~Sedenion() noexcept { delete[] this->data; };
	double SEDEN_FUNC_CALL Sedenion::Scalar(const Sedenion& Value) { return Value[0]; };
	Sedenion SEDEN_FUNC_CALL Sedenion::Vector(const Sedenion& Value)
	{
		Sedenion ret = Value;
		ret[0] = 0;
		return ret;
	};
	///
	/// Operators
	///
	Sedenion SEDEN_FUNC_INSTANCE_CALL Sedenion::operator ()() const { return *this; };
	double& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator [](std::int64_t i) &
	{
		return this->data[i % this->size];
	};
	const double& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator [](std::int64_t i) const&
	{
		return this->data[i % this->size];
	};
	bool SEDEN_FUNC_CALL operator ==(const Sedenion& Union, const Sedenion& Value) { return std::equal(Union.data, Union.data + Union.size, Value.data); };
	bool SEDEN_FUNC_CALL operator !=(const Sedenion& Union, const Sedenion& Value) { return !(Union == Value); };
	Sedenion SEDEN_FUNC_CALL operator +(const Sedenion& Value) { return Value; };
	Sedenion SEDEN_FUNC_CALL operator -(const Sedenion& Value) { return Sedenion::from(-Value.to_factor()); };
	Sedenion SEDEN_FUNC_CALL operator ~(const Sedenion& Value) { return Sedenion::from(~Value.to_factor()); };
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator ++() &
	{
		++this->operator[](0);
		return *this;
	};
	Sedenion SEDEN_FUNC_INSTANCE_CALL Sedenion::operator ++(int) &
	{
		Sedenion temp = *this;
		++this->operator[](0);
		return temp;
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator --() &
	{
		--this->operator[](0);
		return *this;
	};
	Sedenion SEDEN_FUNC_INSTANCE_CALL Sedenion::operator --(int) &
	{
		Sedenion temp = *this;
		--this->operator[](0);
		return temp;
	};
	Sedenion SEDEN_FUNC_CALL operator +(const Sedenion& Union, const Sedenion& Value)
	{
		return Sedenion::from(Union.to_factor() + Value.to_factor());
	};
	Sedenion SEDEN_FUNC_CALL operator -(const Sedenion& Union, const Sedenion& Value)
	{
		return Sedenion::from(Union.to_factor() - Value.to_factor());
	};
	Sedenion SEDEN_FUNC_CALL operator *(const Sedenion& Union, const Sedenion& Value)
	{
		return Sedenion::from(Union.to_factor() * Value.to_factor());
	};
	Sedenion SEDEN_FUNC_CALL operator /(const Sedenion& Union, double Value)
	{
		return Sedenion::from(Union.to_factor() / Value);
	};
	Sedenion SEDEN_FUNC_CALL operator ^(const Sedenion& Base, std::int64_t Exponent)
	{
		try { return Sedenion::Power(Base, static_cast<double>(Exponent)); }
		catch (...) { return 0; }
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator =(const Sedenion& Value) &
	{
		if (this == &Value) { return *this; }
		delete[] this->data;
		this->data = new double[Value.size] {};
		std::copy(Value.data, Value.data + Value.size, this->data);
		this->size = Value.size;
		return *this;
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator =(Sedenion&& Value) & noexcept
	{
		this->data = Value.data;
		this->size = Value.size;
		Value.data = nullptr;
		Value.size = 0;
		return *this;
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator +=(const Sedenion& Value) & { return *this = *this + Value; };
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator +=(const std::initializer_list<Sedenion>& Value) &
	{
		for (std::initializer_list<Sedenion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this += *ite; }
		return *this;
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator -=(const Sedenion& Value) & { return *this = *this - Value; };
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator -=(const std::initializer_list<Sedenion>& Value) &
	{
		for (std::initializer_list<Sedenion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this -= *ite; }
		return *this;
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator *=(const Sedenion& Value) & { return *this = *this * Value; };
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator *=(const std::initializer_list<Sedenion>& Value) &
	{
		for (std::initializer_list<Sedenion>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this *= *ite; }
		return *this;
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator /=(double Value) & { return *this = *this / Value; };
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator /=(const std::initializer_list<double>& Value) &
	{
		for (std::initializer_list<double>::const_iterator ite = Value.begin(); ite != Value.end(); ++ite) { *this /= *ite; }
		return *this;
	};
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator ^=(std::int64_t Exponent) & { return *this = *this ^ Exponent; };
	Sedenion& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator ^=(const std::initializer_list<std::int64_t>& Exponent) &
	{
		for (std::initializer_list<std::int64_t>::const_iterator ite = Exponent.begin(); ite != Exponent.end(); ++ite) { *this ^= *ite; }
		return *this;
	};
	///
	/// Basic functions for constructing numbers
	///
	double SEDEN_FUNC_CALL Sedenion::abs(const Sedenion& Value) { return std::sqrt(dot(Value, Value)); };
	double SEDEN_FUNC_CALL Sedenion::arg(const Sedenion& Value) { return arg(Value, 0); };
	double SEDEN_FUNC_CALL Sedenion::arg(const Sedenion& Value, std::int64_t Theta) { return std::acos(Scalar(Value) / abs(Value)) + 2 * pi * static_cast<double>(Theta); };
	Sedenion SEDEN_FUNC_CALL Sedenion::conjg(const Sedenion& Value) { return ~Value; };
	Sedenion SEDEN_FUNC_CALL Sedenion::sgn(const Sedenion& Value) { return Value / abs(Value); };
	Sedenion SEDEN_FUNC_CALL Sedenion::inverse(const Sedenion& Value) { return conjg(Value) / dot(Value, Value); };
	Sedenion SEDEN_FUNC_CALL Sedenion::exp(const Sedenion& Value) { return std::exp(Scalar(Value)) * (std::cos(abs(Vector(Value))) + sgn(Vector(Value)) * std::sin(abs(Vector(Value)))); };
	Sedenion SEDEN_FUNC_CALL Sedenion::ln(const Sedenion& Value) { return ln(Value, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::ln(const Sedenion& Value, std::int64_t Theta) { return std::log(abs(Value)) + sgn(Vector(Value)) * arg(Value, Theta); };
	///
	/// 1st rank tensor algorithms
	///
	double SEDEN_FUNC_CALL Sedenion::dot(const Sedenion& Union, const Sedenion& Value) { return Scalar(conjg(Union) * Value + conjg(Value) * Union) / 2; };
	Sedenion SEDEN_FUNC_CALL Sedenion::outer(const Sedenion& Union, const Sedenion& Value) { return (conjg(Union) * Value - conjg(Value) * Union) / 2; };
	Sedenion SEDEN_FUNC_CALL Sedenion::even(const Sedenion& Union, const Sedenion& Value) { return (Union * Value + Value * Union) / 2; };
	Sedenion SEDEN_FUNC_CALL Sedenion::cross(const Sedenion& Union, const Sedenion& Value) { return (Union * Value - Value * Union) / 2; };
	///
	/// Operation 3 algorithms
	///
	Sedenion SEDEN_FUNC_CALL Sedenion::Power(const Sedenion& Base, const Sedenion& Exponent) { return Power(Base, Exponent, 0, 0, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::Power(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau)
	{
		return exp(exp(ln(ln(Base, Theta), Phi) + ln(Exponent, Tau)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::Power(const Sedenion& Base, double Exponent) { return Power(Base, Exponent, 0); }
	Sedenion SEDEN_FUNC_CALL Sedenion::Power(const Sedenion& Base, double Exponent, std::int64_t Theta)
	{
		if (Base == 0) { return Exponent == 0 ? 1 : 0; }
		return std::pow(abs(Base), Exponent) *
			(std::cos(Exponent * arg(Base, Theta)) + sgn(Vector(Base)) * std::sin(Exponent * arg(Base, Theta)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::Root(const Sedenion& Base, const Sedenion& Exponent) { return Root(Base, Exponent, 0, 0, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::Root(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau) { return Power(Base, inverse(Exponent), Theta, Phi, Tau); };
	Sedenion SEDEN_FUNC_CALL Sedenion::Root(const Sedenion& Base, double Exponent) { return Power(Base, 1 / Exponent); };
	Sedenion SEDEN_FUNC_CALL Sedenion::Root(const Sedenion& Base, double Exponent, std::int64_t Theta) { return Power(Base, 1 / Exponent, Theta); };
	Sedenion SEDEN_FUNC_CALL Sedenion::Log(const Sedenion& Base, const Sedenion& Number) { return Log(Base, Number, 0, 0, 0, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::Log(const Sedenion& Base, const Sedenion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega)
	{
		return exp(ln(ln(Number, Theta), Phi) - ln(ln(Base, Tau), Omega));
	};
	///
	/// Trigonometric functions
	///
	Sedenion SEDEN_FUNC_CALL Sedenion::sin(const Sedenion& Value)
	{
		return std::sin(Scalar(Value)) * std::cosh(abs(Vector(Value)))
			+ std::cos(Scalar(Value)) * sgn(Vector(Value)) * std::sinh(abs(Vector(Value)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsin(const Sedenion& Value) { return arcsin(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsin(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return -sgn(Vector(Value)) * arcsinh(Value * sgn(Vector(Value))); }
		else { return pi - arcsin(Value, true, Period); }
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::sinh(const Sedenion& Value)
	{
		return std::sinh(Scalar(Value)) * std::cos(abs(Vector(Value)))
			+ std::cosh(Scalar(Value)) * sgn(abs(Vector(Value))) * std::sin(abs(Vector(Value)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsinh(const Sedenion& Value) { return arcsinh(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsinh(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return ln(Value + Root(Power(Value, 2) + 1, 2), Period); }
		else { return pi * sgn(Vector(Value)) - arcsinh(Value, true, Period); }
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::cos(const Sedenion& Value)
	{
		return std::cos(Scalar(Value)) * std::cosh(abs(Vector(Value)))
			- std::sin(Scalar(Value)) * sgn(Vector(Value)) * std::sinh(abs(Vector(Value)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arccos(const Sedenion& Value) { return arccos(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccos(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return -sgn(Vector(Value)) * arccosh(Value); }
		else { return 2 * pi - arccos(Value, true, Period); }
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::cosh(const Sedenion& Value)
	{
		return std::cosh(Scalar(Value)) * std::cos(abs(Vector(Value)))
			+ std::sinh(Scalar(Value)) * sgn(abs(Vector(Value))) * std::sin(abs(Vector(Value)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arccosh(const Sedenion& Value) { return arccosh(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccosh(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return ln(Value + Root(Power(Value, 2) - 1, 2), Period); }
		else { return 2 * pi * sgn(Vector(Value)) - arccosh(Value, true, Period); }
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::tan(const Sedenion& Value)
	{
		return Root(Power(sec(Value), 2) - 1, 2);
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arctan(const Sedenion& Value) { return arctan(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arctan(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return -sgn(Vector(Value)) * arctanh(Value * sgn(Vector(Value))); }
		else { return pi + arctan(Value, true, Period); }
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::tanh(const Sedenion& Value)
	{
		return 1 - 2 * inverse(exp(2 * Value) + 1);
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arctanh(const Sedenion& Value) { return arctanh(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arctanh(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return (ln(1 + Value, Period) - ln(1 - Value)) / 2; }
		else { return pi * sgn(Vector(Value)) + arctanh(Value, true, Period); }
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::csc(const Sedenion& Value) { return inverse(sin(Value)); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccsc(const Sedenion& Value) { return arccsc(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccsc(const Sedenion& Value, bool Sign, std::int64_t Period) { return arcsin(inverse(Value), Sign, Period); };
	Sedenion SEDEN_FUNC_CALL Sedenion::csch(const Sedenion& Value) { return inverse(sinh(Value)); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccsch(const Sedenion& Value) { return arccsch(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccsch(const Sedenion& Value, bool Sign, std::int64_t Period) { return arcsinh(inverse(Value), Sign, Period); };
	Sedenion SEDEN_FUNC_CALL Sedenion::sec(const Sedenion& Value) { return inverse(cos(Value)); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsec(const Sedenion& Value) { return arcsec(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsec(const Sedenion& Value, bool Sign, std::int64_t Period) { return arccos(inverse(Value), Sign, Period); };
	Sedenion SEDEN_FUNC_CALL Sedenion::sech(const Sedenion& Value) { return inverse(cosh(Value)); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsech(const Sedenion& Value) { return arcsech(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsech(const Sedenion& Value, bool Sign, std::int64_t Period) { return arccosh(inverse(Value), Sign, Period); };
	Sedenion SEDEN_FUNC_CALL Sedenion::cot(const Sedenion& Value) { return inverse(tan(Value)); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccot(const Sedenion& Value) { return arccot(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccot(const Sedenion& Value, bool Sign, std::int64_t Period) { return arctan(inverse(Value), Sign, Period); };
	Sedenion SEDEN_FUNC_CALL Sedenion::coth(const Sedenion& Value) { return inverse(tanh(Value)); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccoth(const Sedenion& Value) { return arccoth(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccoth(const Sedenion& Value, bool Sign, std::int64_t Period) { return arctanh(inverse(Value), Sign, Period); };
	///
	/// Conversion of Types
	///
	std::wstring SEDEN_FUNC_CALL Sedenion::CType_String(const Sedenion& Value)
	{
		const double* Numbers = Value.data;
		std::wstring* Strings = new std::wstring[Value.size] {};
		for (std::size_t i = 0; i < Value.size; ++i) { Strings[i] = L"e" + std::to_wstring(i); }
		std::wstring Output = ToString(Value.size, Numbers, Strings);
		delete[] Strings;
		return Output;
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::CType_Sedenion(const std::wstring& Value)
	{
		std::size_t Dimension = 0;
		std::wregex Regex(L"e\\d+(?=-|\\+|$)");
		std::wstring TheString = Value;
		std::wsmatch Match;
		while (std::regex_search(TheString, Match, Regex))
		{
			Dimension = std::max(Dimension, stos_t(Match.str().substr(1)));
			TheString = Match.suffix().str();
		}
		std::size_t Size = GetDimension(Dimension);
		double* Numbers = new double[Size] {};
		std::wstring* Strings = new std::wstring[Size] {};
		for (std::size_t i = 0; i < Size; ++i) { Strings[i] = L"e" + std::to_wstring(i); }
		ToNumbers(Value, Size, Numbers, Strings);
		delete[] Strings;
		return Sedenion{ Numbers, Size };
	};
}
#pragma pop_macro("SEDEN_FUNC_INSTANCE_CALL")
#pragma pop_macro("SEDEN_FUNC_CALL")
#pragma pop_macro("SEDEN_INTERFACE")
#pragma pop_macro("CALL")
#pragma pack(pop)
