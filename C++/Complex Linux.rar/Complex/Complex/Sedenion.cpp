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
inline std::size_t wtos_t(const wchar_t* str)
{
	static const std::wstring limit = std::to_wstring(std::numeric_limits<std::size_t>::max());
	if (str[0] == L'\0' || str[0] == L'-') { throw std::invalid_argument("The string cannot be converted as an integer."); }
	const wchar_t* number = str;
	if (str[0] == L'+')
	{
		if (str[1] == L'\0') { throw std::invalid_argument("The string cannot be converted as an integer."); }
		++number;
	}
	std::size_t number_size = std::wcslen(str);
	const wchar_t* number_end = number;
	while (*number_end != L'\0')
	{
		if (static_cast<std::uint16_t>(*number_end) < 48 || static_cast<std::uint16_t>(*number_end) > 57) { throw std::invalid_argument("The string cannot be converted as an integer."); }
		++number_end;
	}
	const wchar_t* wchars = limit.c_str();
	std::size_t wchars_size = limit.size();
	wchar_t* digitsCheck = new wchar_t[wchars_size] { L'\0' };
	if (number_size > wchars_size)
	{
		throw std::out_of_range("An integer is exceeded the limit.");
	}
	std::size_t accumulate = 1;
	std::size_t output = 0;
	for (std::size_t i = 0; i < number_size; ++i)
	{
		wchar_t wchar = number[number_size - i - 1];
		digitsCheck[number_size - i - 1] = wchar;
		std::uint16_t digit = static_cast<std::uint16_t>(wchar) - 48;
		output += digit * accumulate;
		accumulate = accumulate * 10;
	}
	if (number_size == wchars_size)
	{
		for (std::size_t i = 0; i < wchars_size; ++i)
		{
			if (digitsCheck[i] < wchars[i]) { break; }
			else if (digitsCheck[i] > wchars[i]) { throw std::out_of_range("An integer is exceeded the limit."); }
		}
	}
	delete[] digitsCheck;
	return output;
};
inline std::size_t stos_t(const std::wstring& str)
{
	return wtos_t(str.c_str());
};
namespace Seden
{
	class SEDEN_INTERFACE Sedenion
	{
	private:
		///
		/// helpers
		///
		static std::size_t GetDimension(std::size_t Value)
		{
			std::size_t Result = 1;
			while (Value > 0)
			{
				Value >>= 1;
				Result <<= 1;
			}
			return Result;
		};
	public:
		///
		/// constants
		///
		static const double pi;
		static const double e;
		static const Sedenion i;
	private:
		///
		/// basis
		///
		static constexpr const std::size_t basic_size = 16;
		static constexpr const std::size_t null = 0;
		double* data;
		std::size_t size;
		explicit Sedenion(const double* data, std::size_t size)
			: data{ nullptr }, size{ size > basic_size ? size : basic_size }
		{
			this->data = new double[this->size] {};
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
		/// operators
		///
		Sedenion SEDEN_FUNC_INSTANCE_CALL operator ()() const;
		double& SEDEN_FUNC_INSTANCE_CALL operator [](std::size_t i) & noexcept;
		const double& SEDEN_FUNC_INSTANCE_CALL operator [](std::size_t i) const& noexcept;
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
		/// fundamentals
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
		/// multiples
		///
		static double SEDEN_FUNC_CALL dot(const Sedenion& Union, const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL outer(const Sedenion& Union, const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL even(const Sedenion& Union, const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL cross(const Sedenion& Union, const Sedenion& Value);
		///
		/// exponentials
		///
		static Sedenion SEDEN_FUNC_CALL power(const Sedenion& Base, const Sedenion& Exponent);
		static Sedenion SEDEN_FUNC_CALL power(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
		static Sedenion SEDEN_FUNC_CALL power(const Sedenion& Base, double Exponent);
		static Sedenion SEDEN_FUNC_CALL power(const Sedenion& Base, double Exponent, std::int64_t Theta);
		static Sedenion SEDEN_FUNC_CALL root(const Sedenion& Base, const Sedenion& Exponent);
		static Sedenion SEDEN_FUNC_CALL root(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau);
		static Sedenion SEDEN_FUNC_CALL root(const Sedenion& Base, double Exponent);
		static Sedenion SEDEN_FUNC_CALL root(const Sedenion& Base, double Exponent, std::int64_t Theta);
		static Sedenion SEDEN_FUNC_CALL log(const Sedenion& Base, const Sedenion& Number);
		static Sedenion SEDEN_FUNC_CALL log(const Sedenion& Base, const Sedenion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega);
		///
		/// trigonometrics
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
		/// conventions
		///
		static std::wstring SEDEN_FUNC_CALL GetString(const Sedenion& Value);
		static Sedenion SEDEN_FUNC_CALL GetInstance(const std::wstring& Value);
		///
		/// casing
		///
	private:
		Factor to_factor() const& noexcept { return Factor{ data, size }; };
		static Sedenion from(const Factor& number) { return Sedenion{ number.get_data(), number.get_size() }; };
	};
	///
	/// operators
	///
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
	/* class Sedenion */
	///
	/// constants
	///
	const double Sedenion::pi = std::numbers::pi;
	const double Sedenion::e = std::numbers::e;
	const Sedenion Sedenion::i{ 0, 1 };
	///
	/// basis
	///
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion()
		: data{ nullptr }, size{ basic_size }
	{
		this->data = new double[this->size] {};
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(const std::initializer_list<double>& numbers)
		: data{ nullptr }, size{ numbers.size() > basic_size ? numbers.size() : basic_size }
	{
		this->data = new double[this->size] {};
		std::copy(numbers.begin(), numbers.end(), this->data);
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(double Value)
		: data{ nullptr }, size{ basic_size }
	{
		this->data = new double[this->size] { Value };
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(const Sedenion& Value)
		: data{ nullptr }, size{ Value.size }
	{
		this->data = new double[this->size] {};
		std::copy(Value.data, Value.data + Value.size, this->data);
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::Sedenion(Sedenion&& Value) noexcept
		: data{ Value.data }, size{ Value.size }
	{
		Value.data = nullptr;
		Value.size = 0;
	};
	SEDEN_FUNC_INSTANCE_CALL Sedenion::~Sedenion() noexcept
	{
		delete[] this->data;
		this->data = nullptr;
		this->size = 0;
	};
	double SEDEN_FUNC_CALL Sedenion::Scalar(const Sedenion& Value) { return Value[0]; };
	Sedenion SEDEN_FUNC_CALL Sedenion::Vector(const Sedenion& Value)
	{
		Sedenion Result = Value;
		Result[0] = 0;
		return Result;
	};
	///
	/// operators
	///
	Sedenion SEDEN_FUNC_INSTANCE_CALL Sedenion::operator ()() const { return *this; };
	double& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator [](std::size_t i) & noexcept
	{
		if (this->size == 0) { return this->data[null]; }
		return this->data[i % this->size];
	};
	const double& SEDEN_FUNC_INSTANCE_CALL Sedenion::operator [](std::size_t i) const& noexcept
	{
		if (this->size == 0) { return this->data[null]; }
		return this->data[i % this->size];
	};
	bool SEDEN_FUNC_CALL operator ==(const Sedenion& Union, const Sedenion& Value) { return Union.to_factor() == Value.to_factor(); };
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
		try { return Sedenion::power(Base, static_cast<double>(Exponent)); }
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
	/// fundamentals
	///
	double SEDEN_FUNC_CALL Sedenion::abs(const Sedenion& Value) { return std::sqrt(dot(Value, Value)); };
	double SEDEN_FUNC_CALL Sedenion::arg(const Sedenion& Value) { return arg(Value, 0); };
	double SEDEN_FUNC_CALL Sedenion::arg(const Sedenion& Value, std::int64_t Theta) { return std::acos(Scalar(Value) / abs(Value)) + 2 * pi * static_cast<double>(Theta); };
	Sedenion SEDEN_FUNC_CALL Sedenion::conjg(const Sedenion& Value) { return ~Value; };
	Sedenion SEDEN_FUNC_CALL Sedenion::sgn(const Sedenion& Value) { return Value / abs(Value); };
	Sedenion SEDEN_FUNC_CALL Sedenion::inverse(const Sedenion& Value) { return conjg(Value) / dot(Value, Value); };
	Sedenion SEDEN_FUNC_CALL Sedenion::exp(const Sedenion& Value)
	{
		auto S = Scalar(Value);
		auto V = Vector(Value);
		if (V == 0) { return std::exp(S); }
		return std::exp(S) * (std::cos(abs(V)) + sgn(V) * std::sin(abs(V)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::ln(const Sedenion& Value) { return ln(Value, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::ln(const Sedenion& Value, std::int64_t Theta)
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
	double SEDEN_FUNC_CALL Sedenion::dot(const Sedenion& Union, const Sedenion& Value)
	{
		return number_dot(Union.to_factor(), Value.to_factor());
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::outer(const Sedenion& Union, const Sedenion& Value)
	{
		return Sedenion::from(number_outer(Union.to_factor(), Value.to_factor()));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::even(const Sedenion& Union, const Sedenion& Value)
	{
		return Sedenion::from(number_even(Union.to_factor(), Value.to_factor()));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::cross(const Sedenion& Union, const Sedenion& Value)
	{
		return Sedenion::from(number_cross(Union.to_factor(), Value.to_factor()));
	};
	///
	/// exponentials
	///
	Sedenion SEDEN_FUNC_CALL Sedenion::power(const Sedenion& Base, const Sedenion& Exponent) { return power(Base, Exponent, 0, 0, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::power(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau)
	{
		return exp(exp(ln(ln(Base, Theta), Phi) + ln(Exponent, Tau)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::power(const Sedenion& Base, double Exponent) { return power(Base, Exponent, 0); }
	Sedenion SEDEN_FUNC_CALL Sedenion::power(const Sedenion& Base, double Exponent, std::int64_t Theta)
	{
		if (Base == 0) { return Exponent == 0 ? 1 : 0; }
		return std::pow(abs(Base), Exponent) *
			(std::cos(Exponent * arg(Base, Theta)) + sgn(Vector(Base)) * std::sin(Exponent * arg(Base, Theta)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::root(const Sedenion& Base, const Sedenion& Exponent) { return root(Base, Exponent, 0, 0, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::root(const Sedenion& Base, const Sedenion& Exponent, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau) { return power(Base, inverse(Exponent), Theta, Phi, Tau); };
	Sedenion SEDEN_FUNC_CALL Sedenion::root(const Sedenion& Base, double Exponent) { return power(Base, 1 / Exponent); };
	Sedenion SEDEN_FUNC_CALL Sedenion::root(const Sedenion& Base, double Exponent, std::int64_t Theta) { return power(Base, 1 / Exponent, Theta); };
	Sedenion SEDEN_FUNC_CALL Sedenion::log(const Sedenion& Base, const Sedenion& Number) { return log(Base, Number, 0, 0, 0, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::log(const Sedenion& Base, const Sedenion& Number, std::int64_t Theta, std::int64_t Phi, std::int64_t Tau, std::int64_t Omega)
	{
		return exp(ln(ln(Number, Theta), Phi) - ln(ln(Base, Tau), Omega));
	};
	///
	/// trigonometrics
	///
	Sedenion SEDEN_FUNC_CALL Sedenion::sin(const Sedenion& Value)
	{
		auto S = Scalar(Value);
		auto V = Vector(Value);
		if (V == 0) { return std::sin(S); }
		return std::sin(S) * std::cosh(abs(V)) + sgn(V) * (std::cos(S) * std::sinh(abs(V)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsin(const Sedenion& Value) { return arcsin(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsin(const Sedenion& Value, bool Sign, std::int64_t Period)
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
	Sedenion SEDEN_FUNC_CALL Sedenion::sinh(const Sedenion& Value)
	{
		auto S = Scalar(Value);
		auto V = Vector(Value);
		if (V == 0) { return std::sinh(S); }
		return std::sinh(S) * std::cos(abs(V)) + sgn(V) * (std::cosh(S) * std::sin(abs(V)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsinh(const Sedenion& Value) { return arcsinh(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arcsinh(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return ln(Value + root(Value * Value + 1, 2), Period); }
		auto V = Vector(Value);
		if (V == 0) { return pi * i - arcsinh(Value, true, Period); }
		return pi * sgn(V) - arcsinh(Value, true, Period);
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::cos(const Sedenion& Value)
	{
		auto S = Scalar(Value);
		auto V = Vector(Value);
		if (V == 0) { return std::cos(S); }
		return std::cos(S) * std::cosh(abs(V)) - sgn(V) * (std::sin(S) * std::sinh(abs(V)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arccos(const Sedenion& Value) { return arccos(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccos(const Sedenion& Value, bool Sign, std::int64_t Period)
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
	Sedenion SEDEN_FUNC_CALL Sedenion::cosh(const Sedenion& Value)
	{
		auto S = Scalar(Value);
		auto V = Vector(Value);
		if (V == 0) { return std::cosh(S); }
		return std::cosh(S) * std::cos(abs(V)) + sgn(V) * (std::sinh(S) * std::sin(abs(V)));
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::arccosh(const Sedenion& Value) { return arccosh(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arccosh(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return ln(Value + root(Value * Value - 1, 2), Period); }
		auto V = Vector(Value);
		if (V == 0) { return 2 * pi * i - arccosh(Value, true, Period); }
		return 2 * pi * sgn(V) - arccosh(Value, true, Period);
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::tan(const Sedenion& Value)
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
	Sedenion SEDEN_FUNC_CALL Sedenion::arctan(const Sedenion& Value) { return arctan(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arctan(const Sedenion& Value, bool Sign, std::int64_t Period)
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
	Sedenion SEDEN_FUNC_CALL Sedenion::tanh(const Sedenion& Value)
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
	Sedenion SEDEN_FUNC_CALL Sedenion::arctanh(const Sedenion& Value) { return arctanh(Value, true, 0); };
	Sedenion SEDEN_FUNC_CALL Sedenion::arctanh(const Sedenion& Value, bool Sign, std::int64_t Period)
	{
		if (Sign == true) { return 1 / 2 * (ln(1 + Value, Period) - ln(1 - Value)); }
		auto V = Vector(Value);
		if (V == 0) { return pi * i + arctanh(Value, true, Period); }
		return pi * sgn(V) + arctanh(Value, true, Period);
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
	/// conventions
	///
	std::wstring SEDEN_FUNC_CALL Sedenion::GetString(const Sedenion& Value)
	{
		std::vector<std::wstring> Terms(Value.size);
		for (std::size_t i = 0; i < Value.size; ++i) { Terms[i] = L"e" + std::to_wstring(i); }
		return ToString(Value.size, Value.data, Terms.data());
	};
	Sedenion SEDEN_FUNC_CALL Sedenion::GetInstance(const std::wstring& Value)
	{
		std::wstring Replaced = Replace(Value, L" ", L"");
		if (Replaced == L"0") { return Sedenion{}; };
		std::size_t Dimension = 0;
		std::wstring Rest = Replaced;
		std::wsmatch Match;
		while (std::regex_search(Rest, Match, std::wregex(LR"(e(\d+)(?=-|\+|$))")))
		{
			Dimension = std::max(Dimension, stos_t(Match.str(1)));
			Rest = Match.suffix().str();
		}
		std::size_t Size = GetDimension(Dimension);
		std::vector<double> Numbers(Size);
		std::vector<std::wstring> Terms(Size);
		for (std::size_t i = 0; i < Size; ++i) { Terms[i] = L"e" + std::to_wstring(i); }
		ToNumbers(Replaced, Size, Numbers.data(), Terms.data());
		return Sedenion{ Numbers.data(), Size };
	};
}
#pragma pop_macro("SEDEN_FUNC_INSTANCE_CALL")
#pragma pop_macro("SEDEN_FUNC_CALL")
#pragma pop_macro("SEDEN_INTERFACE")
#pragma pop_macro("CALL")
#pragma pack(pop)
