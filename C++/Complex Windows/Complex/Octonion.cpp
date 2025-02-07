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
#include <cstddef>
#include <cstdint>
#include <string>
#include "Module.h"
#include "Cayley Dickson Algebra.h"
#pragma pack(push)
#pragma push_macro("I")
#pragma push_macro("Gbl")
#pragma push_macro("Ths")
#pragma pack(8)
#if defined(_MSVC_LANG)
#define I __declspec(dllexport)
#define Gbl __stdcall
#define Ths __thiscall
#else
#define I
#define Gbl
#define Ths
#endif
namespace Num
{
	struct I Vec7D
	{
		///
		/// constants
		///
	public:
		static const Vec7D Zero;
		static const Vec7D e1;
		static const Vec7D e2;
		static const Vec7D e3;
		static const Vec7D e4;
		static const Vec7D e5;
		static const Vec7D e6;
		static const Vec7D e7;
		///
		/// basis
		///
	private:
		double x1;
		double x2;
		double x3;
		double x4;
		double x5;
		double x6;
		double x7;
	public:
		explicit Ths Vec7D();
		explicit Ths Vec7D(double e1, double e2, double e3, double e4, double e5, double e6, double e7);
		///
		/// operators
		///
	public:
		Vec7D Ths operator ()() const;
		double& Ths operator [](std::size_t i) &;
		const double& Ths operator [](std::size_t i) const&;
		friend bool I Gbl operator ==(const Vec7D& U, const Vec7D& V);
		friend bool I Gbl operator !=(const Vec7D& U, const Vec7D& V);
		friend Vec7D I Gbl operator +(const Vec7D& V);
		friend Vec7D I Gbl operator -(const Vec7D& V);
		friend Vec7D I Gbl operator +(const Vec7D& U, const Vec7D& V);
		friend Vec7D I Gbl operator -(const Vec7D& U, const Vec7D& V);
		friend Vec7D I Gbl operator *(const Vec7D& U, double V);
		friend Vec7D I Gbl operator *(double U, const Vec7D& V);
		friend Vec7D I Gbl operator /(const Vec7D& U, double V);
		Vec7D& Ths operator +=(const Vec7D& O) &;
		Vec7D& Ths operator +=(const std::initializer_list<Vec7D>& O) &;
		Vec7D& Ths operator -=(const Vec7D& O) &;
		Vec7D& Ths operator -=(const std::initializer_list<Vec7D>& O) &;
		Vec7D& Ths operator *=(double O) &;
		Vec7D& Ths operator *=(const std::initializer_list<double>& O) &;
		Vec7D& Ths operator /=(double O) &;
		Vec7D& Ths operator /=(const std::initializer_list<double>& O) &;
		///
		/// multiples
		///
	public:
		static double Gbl Dot(const Vec7D& U, const Vec7D& V);
		static Vec7D Gbl Cross(const Vec7D& U, const Vec7D& V);
		///
		/// fundamentals
		///
	public:
		static double Gbl Abs(const Vec7D& V);
		static Vec7D Gbl Sgn(const Vec7D& V);
		///
		/// conventions
		///
	public:
		static String Gbl Str(const Vec7D& V);
		static Vec7D Gbl Val(const String& V);
		///
		/// casing
		///
	public:
		Number Num() const&
		{
			return Number{ 0, x1, x2, x3, x4, x5, x6, x7 };
		};
		static Vec7D Val(const Number& N)
		{
			return Vec7D{ N[1], N[2], N[3], N[4], N[5], N[6], N[7] };
		};
	};
	/* struct Vec7D */
	///
	/// constants
	///
	const Vec7D Vec7D::Zero = Vec7D{ 0, 0, 0, 0, 0, 0, 0 };
	const Vec7D Vec7D::e1 = Vec7D{ 1, 0, 0, 0, 0, 0, 0 };
	const Vec7D Vec7D::e2 = Vec7D{ 0, 1, 0, 0, 0, 0, 0 };
	const Vec7D Vec7D::e3 = Vec7D{ 0, 0, 1, 0, 0, 0, 0 };
	const Vec7D Vec7D::e4 = Vec7D{ 0, 0, 0, 1, 0, 0, 0 };
	const Vec7D Vec7D::e5 = Vec7D{ 0, 0, 0, 0, 1, 0, 0 };
	const Vec7D Vec7D::e6 = Vec7D{ 0, 0, 0, 0, 0, 1, 0 };
	const Vec7D Vec7D::e7 = Vec7D{ 0, 0, 0, 0, 0, 0, 1 };
	///
	/// basis
	///
	Ths Vec7D::Vec7D()
		: x1{ 0 }, x2{ 0 }, x3{ 0 }, x4{ 0 }, x5{ 0 }, x6{ 0 }, x7{ 0 }
	{};
	Ths Vec7D::Vec7D(double e1, double e2, double e3, double e4, double e5, double e6, double e7)
		: x1{ e1 }, x2{ e2 }, x3{ e3 }, x4{ e4 }, x5{ e5 }, x6{ e6 }, x7{ e7 }
	{};
	///
	/// operators
	///
	Vec7D Ths Vec7D::operator ()() const
	{
		return *this;
	};
	double& Ths Vec7D::operator [](std::size_t i) &
	{
		switch (i)
		{
		case 1:
			return this->x1;
		case 2:
			return this->x2;
		case 3:
			return this->x3;
		case 4:
			return this->x4;
		case 5:
			return this->x5;
		case 6:
			return this->x6;
		case 7:
			return this->x7;
		default:
			throw std::out_of_range{ "The index is out of range." };
		}
	};
	const double& Ths Vec7D::operator [](std::size_t i) const&
	{
		switch (i)
		{
		case 1:
			return this->x1;
		case 2:
			return this->x2;
		case 3:
			return this->x3;
		case 4:
			return this->x4;
		case 5:
			return this->x5;
		case 6:
			return this->x6;
		case 7:
			return this->x7;
		default:
			throw std::out_of_range{ "The index is out of range." };
		}
	};
	inline bool I Gbl operator ==(const Vec7D& U, const Vec7D& V)
	{
		return U.Num() == V.Num();
	};
	inline bool I Gbl operator !=(const Vec7D& U, const Vec7D& V)
	{
		return !(U == V);
	};
	inline Vec7D I Gbl operator +(const Vec7D& V)
	{
		return V;
	};
	inline Vec7D I Gbl operator -(const Vec7D& V)
	{
		return Vec7D::Val(-V.Num());
	};
	inline Vec7D I Gbl operator +(const Vec7D& U, const Vec7D& V)
	{
		return Vec7D::Val(U.Num() + V.Num());
	};
	inline Vec7D I Gbl operator -(const Vec7D& U, const Vec7D& V)
	{
		return Vec7D::Val(U.Num() - V.Num());
	};
	inline Vec7D I Gbl operator *(const Vec7D& U, double V)
	{
		return Vec7D::Val(U.Num() * V);
	};
	inline Vec7D I Gbl operator *(double U, const Vec7D& V)
	{
		return Vec7D::Val(U * V.Num());
	};
	inline Vec7D I Gbl operator /(const Vec7D& U, double V)
	{
		return Vec7D::Val(U.Num() / V);
	};
	Vec7D& Ths Vec7D::operator +=(const Vec7D& O) &
	{
		return *this = *this + O;
	};
	Vec7D& Ths Vec7D::operator +=(const std::initializer_list<Vec7D>& O) &
	{
		for (std::initializer_list<Vec7D>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this += *ite; }
		return *this;
	};
	Vec7D& Ths Vec7D::operator -=(const Vec7D& O) &
	{
		return *this = *this - O;
	};
	Vec7D& Ths Vec7D::operator -=(const std::initializer_list<Vec7D>& O) &
	{
		for (std::initializer_list<Vec7D>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this -= *ite; }
		return *this;
	};
	Vec7D& Ths Vec7D::operator *=(double O) &
	{
		return *this = *this * O;
	};
	Vec7D& Ths Vec7D::operator *=(const std::initializer_list<double>& O) &
	{
		for (std::initializer_list<double>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this *= *ite; }
		return *this;
	};
	Vec7D& Ths Vec7D::operator /=(double O) &
	{
		return *this = *this / O;
	};
	Vec7D& Ths Vec7D::operator /=(const std::initializer_list<double>& O) &
	{
		for (std::initializer_list<double>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this /= *ite; }
		return *this;
	};
	///
	/// multiples
	///
	double Gbl Vec7D::Dot(const Vec7D& U, const Vec7D& V)
	{
		return Number::Dot(U.Num(), V.Num());
	};
	Vec7D Gbl Vec7D::Cross(const Vec7D& U, const Vec7D& V)
	{
		return Val(Number::Cross(U.Num(), V.Num()));
	};
	///
	/// fundamentals
	///
	double Gbl Vec7D::Abs(const Vec7D& V)
	{
		return Ev::Sqrt(Dot(V, V));
	};
	Vec7D Gbl Vec7D::Sgn(const Vec7D& V)
	{
		return V / Abs(V);
	};
	///
	/// conventions
	///
	String Gbl Vec7D::Str(const Vec7D& V)
	{
		std::wstring Rst = ToString(V, true, L"e1", L"e2", L"e3", L"e4", L"e5", L"e6", L"e7");
		return String{ Rst.data() };
	};
	Vec7D Gbl Vec7D::Val(const String& V)
	{
		std::wstring Str = Replace(V.Ptr(), L" ", L"");
		Vec7D Rst{};
		ToNumbers(Str, Rst, true, L"e1", L"e2", L"e3", L"e4", L"e5", L"e6", L"e7");
		return Rst;
	};
	struct I Octon
	{
		///
		/// constants
		///
	public:
		static const Octon Zero;
		static const Octon i;
		static const Octon j;
		static const Octon k;
		static const Octon l;
		static const Octon il;
		static const Octon jl;
		static const Octon kl;
		///
		/// basis
		///
	private:
		double Re;
		Vec7D Im;
	public:
		explicit Ths Octon();
		explicit Ths Octon(double s, const Vec7D& v);
		explicit Ths Octon(double s, double i, double j, double k, double l, double il, double jl, double kl);
		Ths Octon(double V);
		Ths Octon(const Vec7D& V);
		static double Gbl Scalar(const Octon& V);
		static Vec7D Gbl Vector(const Octon& V);
		///
		/// operators
		///
	public:
		Octon Ths operator ()() const;
		double& Ths operator [](std::size_t i) &;
		const double& Ths operator [](std::size_t i) const&;
		friend bool I Gbl operator ==(const Octon& U, const Octon& V);
		friend bool I Gbl operator !=(const Octon& U, const Octon& V);
		friend Octon I Gbl operator +(const Octon& V);
		friend Octon I Gbl operator -(const Octon& V);
		friend Octon I Gbl operator ~(const Octon& V);
		Octon& Ths operator ++() &;
		Octon Ths operator ++(int) &;
		Octon& Ths operator --() &;
		Octon Ths operator --(int) &;
		friend Octon I Gbl operator +(const Octon& U, const Octon& V);
		friend Octon I Gbl operator -(const Octon& U, const Octon& V);
		friend Octon I Gbl operator *(const Octon& U, const Octon& V);
		friend Octon I Gbl operator /(const Octon& U, const Octon& V);
		friend Octon I Gbl operator ^(const Octon& U, std::int64_t V);
		Octon& Ths operator +=(const Octon& O) &;
		Octon& Ths operator +=(const std::initializer_list<Octon>& O) &;
		Octon& Ths operator -=(const Octon& O) &;
		Octon& Ths operator -=(const std::initializer_list<Octon>& O) &;
		Octon& Ths operator *=(const Octon& O) &;
		Octon& Ths operator *=(const std::initializer_list<Octon>& O) &;
		Octon& Ths operator /=(const Octon& O) &;
		Octon& Ths operator /=(const std::initializer_list<Octon>& O) &;
		Octon& Ths operator ^=(std::int64_t O) &;
		Octon& Ths operator ^=(const std::initializer_list<std::int64_t>& O) &;
		///
		/// multiples
		///
	public:
		static double Gbl Dot(const Octon& U, const Octon& V);
		static Vec7D Gbl Outer(const Octon& U, const Octon& V);
		static Octon Gbl Even(const Octon& U, const Octon& V);
		static Vec7D Gbl Cross(const Octon& U, const Octon& V);
		///
		/// fundamentals
		///
	public:
		static double Gbl Abs(const Octon& V);
		static double Gbl Arg(const Octon& V, std::int64_t P);
		static double Gbl Arg(const Octon& V);
		static Octon Gbl Conjg(const Octon& V);
		static Octon Gbl Sgn(const Octon& V);
		static Octon Gbl Inverse(const Octon& V);
		static Octon Gbl Exp(const Octon& V);
		static Octon Gbl Ln(const Octon& V, std::int64_t P);
		static Octon Gbl Ln(const Octon& V);
		///
		/// exponentials
		///
	public:
		static Octon Gbl Power(const Octon& U, const Octon& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Octon Gbl Power(const Octon& U, const Octon& V);
		static Octon Gbl Power(const Octon& U, double V, std::int64_t P);
		static Octon Gbl Power(const Octon& U, double V);
		static Octon Gbl Root(const Octon& U, const Octon& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Octon Gbl Root(const Octon& U, const Octon& V);
		static Octon Gbl Root(const Octon& U, double V, std::int64_t P);
		static Octon Gbl Root(const Octon& U, double V);
		static Octon Gbl Log(const Octon& U, const Octon& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4);
		static Octon Gbl Log(const Octon& U, const Octon& V);
		///
		/// trigonometrics
		///
	public:
		static Octon Gbl Sin(const Octon& V);
		static Octon Gbl Cos(const Octon& V);
		static Octon Gbl Tan(const Octon& V);
		static Octon Gbl Csc(const Octon& V);
		static Octon Gbl Sec(const Octon& V);
		static Octon Gbl Cot(const Octon& V);
		static Octon Gbl Sinh(const Octon& V);
		static Octon Gbl Cosh(const Octon& V);
		static Octon Gbl Tanh(const Octon& V);
		static Octon Gbl Csch(const Octon& V);
		static Octon Gbl Sech(const Octon& V);
		static Octon Gbl Coth(const Octon& V);
		static Octon Gbl Arcsin(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arcsin(const Octon& V);
		static Octon Gbl Arccos(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arccos(const Octon& V);
		static Octon Gbl Arctan(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arctan(const Octon& V);
		static Octon Gbl Arccsc(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arccsc(const Octon& V);
		static Octon Gbl Arcsec(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arcsec(const Octon& V);
		static Octon Gbl Arccot(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arccot(const Octon& V);
		static Octon Gbl Arcsinh(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arcsinh(const Octon& V);
		static Octon Gbl Arccosh(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arccosh(const Octon& V);
		static Octon Gbl Arctanh(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arctanh(const Octon& V);
		static Octon Gbl Arccsch(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arccsch(const Octon& V);
		static Octon Gbl Arcsech(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arcsech(const Octon& V);
		static Octon Gbl Arccoth(const Octon& V, bool S, std::int64_t P);
		static Octon Gbl Arccoth(const Octon& V);
		///
		/// conventions
		///
	public:
		static String Gbl Str(const Octon& V);
		static Octon Gbl Val(const String& V);
		///
		/// casing
		///
	public:
		Number Num() const&
		{
			return Number{ Re, Im[1], Im[2], Im[3], Im[4], Im[5], Im[6], Im[7] };
		};
		static Octon Val(const Number& N)
		{
			return Octon{ N[0], N[1], N[2], N[3], N[4], N[5], N[6], N[7] };
		};
	};
	/* struct Octon */
	///
	/// constants
	///
	const Octon Octon::Zero = Octon{ 0, Vec7D::Zero };
	const Octon Octon::i = Octon{ 0, Vec7D::e1 };
	const Octon Octon::j = Octon{ 0, Vec7D::e2 };
	const Octon Octon::k = Octon{ 0, Vec7D::e3 };
	const Octon Octon::l = Octon{ 0, Vec7D::e4 };
	const Octon Octon::il = Octon{ 0, Vec7D::e5 };
	const Octon Octon::jl = Octon{ 0, Vec7D::e6 };
	const Octon Octon::kl = Octon{ 0, Vec7D::e7 };
	///
	/// basis
	///
	Ths Octon::Octon()
		: Re{ 0 }, Im{ Vec7D::Zero }
	{};
	Ths Octon::Octon(double s, const Vec7D& v)
		: Re{ s }, Im{ v }
	{};
	Ths Octon::Octon(double s, double i, double j, double k, double l, double il, double jl, double kl)
		: Re{ s }, Im{ i, j, k, l, il, jl, kl }
	{};
	Ths Octon::Octon(double V)
		: Re{ V }, Im{ Vec7D::Zero }
	{};
	Ths Octon::Octon(const Vec7D& V)
		: Re{ 0 }, Im{ V }
	{};
	double Gbl Octon::Scalar(const Octon& V)
	{
		return V.Re;
	};
	Vec7D Gbl Octon::Vector(const Octon& V)
	{
		return V.Im;
	};
	///
	/// operators
	///
	Octon Ths Octon::operator ()() const
	{
		return *this;
	};
	double& Ths Octon::operator [](std::size_t i) &
	{
		switch (i)
		{
		case 0: return Re;
		default: return Im[i];
		}
	};
	const double& Ths Octon::operator [](std::size_t i) const&
	{
		switch (i)
		{
		case 0: return Re;
		default: return Im[i];
		}
	};
	inline bool I Gbl operator ==(const Octon& U, const Octon& V)
	{
		return U.Num() == V.Num();
	};
	inline bool I Gbl operator !=(const Octon& U, const Octon& V)
	{
		return !(U == V);
	};
	inline Octon I Gbl operator +(const Octon& V)
	{
		return V;
	};
	inline Octon I Gbl operator -(const Octon& V)
	{
		return Octon::Val(-V.Num());
	};
	inline Octon I Gbl operator ~(const Octon& V)
	{
		return Octon::Val(~V.Num());
	};
	Octon& Ths Octon::operator ++() &
	{
		++(*this)[0];
		return *this;
	};
	Octon Ths Octon::operator ++(int) &
	{
		Octon Rst = *this;
		++(*this)[0];
		return Rst;
	};
	Octon& Ths Octon::operator --() &
	{
		--(*this)[0];
		return *this;
	};
	Octon Ths Octon::operator --(int) &
	{
		Octon Rst = *this;
		--(*this)[0];
		return Rst;
	};
	inline Octon I Gbl operator +(const Octon& U, const Octon& V)
	{
		return Octon::Val(U.Num() + V.Num());
	};
	inline Octon I Gbl operator -(const Octon& U, const Octon& V)
	{
		return Octon::Val(U.Num() - V.Num());
	};
	inline Octon I Gbl operator *(const Octon& U, const Octon& V)
	{
		return Octon::Val(U.Num() * V.Num());
	};
	inline Octon I Gbl operator /(const Octon& U, const Octon& V)
	{
		if (Octon::Vector(V) == Octon::Zero) { return Octon::Val(U.Num() / Octon::Scalar(V)); }
		return U * Octon::Inverse(V);
	};
	inline Octon I Gbl operator ^(const Octon& U, std::int64_t V)
	{
		return Octon::Power(U, static_cast<double>(V));
	};
	Octon& Ths Octon::operator +=(const Octon& O) &
	{
		return *this = *this + O;
	};
	Octon& Ths Octon::operator +=(const std::initializer_list<Octon>& O) &
	{
		for (std::initializer_list<Octon>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this += *ite; }
		return *this;
	};
	Octon& Ths Octon::operator -=(const Octon& O) &
	{
		return *this = *this - O;
	};
	Octon& Ths Octon::operator -=(const std::initializer_list<Octon>& O) &
	{
		for (std::initializer_list<Octon>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this -= *ite; }
		return *this;
	};
	Octon& Ths Octon::operator *=(const Octon& O) &
	{
		return *this = *this * O;
	};
	Octon& Ths Octon::operator *=(const std::initializer_list<Octon>& O) &
	{
		for (std::initializer_list<Octon>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this *= *ite; }
		return *this;
	};
	Octon& Ths Octon::operator /=(const Octon& O) &
	{
		return *this = *this / O;
	};
	Octon& Ths Octon::operator /=(const std::initializer_list<Octon>& O) &
	{
		for (std::initializer_list<Octon>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this /= *ite; }
		return *this;
	};
	Octon& Ths Octon::operator ^=(std::int64_t O) &
	{
		return *this = *this ^ O;
	};
	Octon& Ths Octon::operator ^=(const std::initializer_list<std::int64_t>& O) &
	{
		for (std::initializer_list<std::int64_t>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this ^= *ite; }
		return *this;
	};
	///
	/// multiples
	///
	double Gbl Octon::Dot(const Octon& U, const Octon& V)
	{
		return Number::Dot(U.Num(), V.Num());
	};
	Vec7D Gbl Octon::Outer(const Octon& U, const Octon& V)
	{
		return Vec7D::Val(Number::Outer(U.Num(), V.Num()));
	};
	Octon Gbl Octon::Even(const Octon& U, const Octon& V)
	{
		return Val(Number::Even(U.Num(), V.Num()));
	};
	Vec7D Gbl Octon::Cross(const Octon& U, const Octon& V)
	{
		return Vec7D::Val(Number::Cross(U.Num(), V.Num()));
	};
	///
	/// fundamentals
	///
	double Gbl Octon::Abs(const Octon& V)
	{
		return Ev::Sqrt(Dot(V, V));
	};
	double Gbl Octon::Arg(const Octon& V, std::int64_t P)
	{
		return Ev::Arccos(Scalar(V) / Abs(V)) + 2 * Ev::PI * static_cast<double>(P);
	};
	double Gbl Octon::Arg(const Octon& V)
	{
		return Arg(V, 0);
	};
	Octon Gbl Octon::Conjg(const Octon& V)
	{
		return ~V;
	};
	Octon Gbl Octon::Sgn(const Octon& V)
	{
		return V / Abs(V);
	};
	Octon Gbl Octon::Inverse(const Octon& V)
	{
		return Conjg(V) / Dot(V, V);
	};
	Octon Gbl Octon::Exp(const Octon& V)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return Ev::Exp(Re); }
		double Sz = Abs(Im);
		Octon Or = Sgn(Im);
		return Ev::Exp(Re) * (Ev::Cos(Sz) + Or * Ev::Sin(Sz));
	};
	Octon Gbl Octon::Ln(const Octon& V, std::int64_t P)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero)
		{
			if (Re >= 0) { return Ev::Ln(Re) + 2 * static_cast<double>(P) * Ev::PI * i; }
			else { return Ev::Ln(-Re) + (2 * static_cast<double>(P) + 1) * Ev::PI * i; }
		}
		Octon Or = Sgn(Im);
		return Ev::Ln(Abs(V)) + Or * Arg(V, P);
	};
	Octon Gbl Octon::Ln(const Octon& V)
	{
		return Ln(V, 0);
	};
	///
	/// exponentials
	///
	Octon Gbl Octon::Power(const Octon& U, const Octon& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
	{
		return Exp(Exp(Ln(V, z3) + Ln(Ln(U, z1), z2)));
	};
	Octon Gbl Octon::Power(const Octon& U, const Octon& V)
	{
		return Power(U, V, 0, 0, 0);
	};
	Octon Gbl Octon::Power(const Octon& U, double V, std::int64_t P)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero)
		{
			if (Re >= 0)
			{
				double Ai = 2 * static_cast<double>(P) * Ev::PI * V;
				return Ev::Power(Re, V) * (Ev::Cos(Ai) + i * Ev::Sin(Ai));
			}
			else
			{
				double Ai = (2 * static_cast<double>(P) + 1) * Ev::PI * V;
				return Ev::Power(-Re, V) * (Ev::Cos(Ai) + i * Ev::Sin(Ai));
			}
		}
		Octon Or = Sgn(Im);
		double A = Arg(U, P) * V;
		return Ev::Power(Abs(U), V) * (Ev::Cos(A) + Or * Ev::Sin(A));
	};
	Octon Gbl Octon::Power(const Octon& U, double V)
	{
		return Power(U, V, 0);
	};
	Octon Gbl Octon::Root(const Octon& U, const Octon& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
	{
		return Power(U, Inverse(V), z1, z2, z3);
	};
	Octon Gbl Octon::Root(const Octon& U, const Octon& V)
	{
		return Root(U, V, 0, 0, 0);
	};
	Octon Gbl Octon::Root(const Octon& U, double V, std::int64_t P)
	{
		return Power(U, 1 / V, P);
	};
	Octon Gbl Octon::Root(const Octon& U, double V)
	{
		return Root(U, V, 0);
	};
	Octon Gbl Octon::Log(const Octon& U, const Octon& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4)
	{
		return Exp(Ln(Ln(V, z1), z3) - Ln(Ln(U, z2), z4));
	};
	Octon Gbl Octon::Log(const Octon& U, const Octon& V)
	{
		return Log(U, V, 0, 0, 0, 0);
	};
	///
	/// trigonometrics
	///
	Octon Gbl Octon::Sin(const Octon& V)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return Ev::Sin(Re); }
		double Sz = Abs(Im);
		Octon Or = Sgn(Im);
		return Ev::Sin(Re) * Ev::Cosh(Sz) + Ev::Cos(Re) * Ev::Sinh(Sz) * Or;
	};
	Octon Gbl Octon::Cos(const Octon& V)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return Ev::Cos(Re); }
		double Sz = Abs(Im);
		Octon Or = Sgn(Im);
		return Ev::Cos(Re) * Ev::Cosh(Sz) - Ev::Sin(Re) * Ev::Sinh(Sz) * Or;
	};
	Octon Gbl Octon::Tan(const Octon& V)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		double T = Ev::Tan(Re);
		if (Im == Vec7D::Zero) { return T; }
		double Sz = Abs(Im);
		Octon Or = Sgn(Im);
		double Th = Ev::Tanh(Sz);
		double T2 = T * T;
		double Th2 = Th * Th;
		return (T * (1 - Th2) + Th * (1 + T2) * Or) / (1 + T2 * Th2);
	};
	Octon Gbl Octon::Csc(const Octon& V)
	{
		return Inverse(Sin(V));
	};
	Octon Gbl Octon::Sec(const Octon& V)
	{
		return Inverse(Cos(V));
	};
	Octon Gbl Octon::Cot(const Octon& V)
	{
		return Inverse(Tan(V));
	};
	Octon Gbl Octon::Sinh(const Octon& V)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return Ev::Sinh(Re); }
		double Sz = Abs(Im);
		Octon Or = Sgn(Im);
		return Ev::Sinh(Re) * Ev::Cos(Sz) + Ev::Cosh(Re) * Ev::Sin(Sz) * Or;
	};
	Octon Gbl Octon::Cosh(const Octon& V)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return Ev::Cosh(Re); }
		double Sz = Abs(Im);
		Octon Or = Sgn(Im);
		return Ev::Cosh(Re) * Ev::Cos(Sz) + Ev::Sinh(Re) * Ev::Sin(Sz) * Or;
	};
	Octon Gbl Octon::Tanh(const Octon& V)
	{
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		double Th = Ev::Tanh(Re);
		if (Im == Vec7D::Zero) { return Th; }
		double Sz = Abs(Im);
		Octon Or = Sgn(Im);
		double T = Ev::Tan(Sz);
		double Th2 = Th * Th;
		double T2 = T * T;
		return (Th * (1 - T2) + T * (1 + Th2) * Or) / (1 + Th2 * T2);
	};
	Octon Gbl Octon::Csch(const Octon& V)
	{
		return Inverse(Sinh(V));
	};
	Octon Gbl Octon::Sech(const Octon& V)
	{
		return Inverse(Cosh(V));
	};
	Octon Gbl Octon::Coth(const Octon& V)
	{
		return Inverse(Tanh(V));
	};
	Octon Gbl Octon::Arcsin(const Octon& V, bool S, std::int64_t P)
	{
		if (!S) { return Ev::PI - Arcsin(V, true, P); }
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
		Octon Or = Sgn(Im);
		return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
	};
	Octon Gbl Octon::Arcsin(const Octon& V)
	{
		return Arcsin(V, true, 0);
	};
	Octon Gbl Octon::Arccos(const Octon& V, bool S, std::int64_t P)
	{
		if (!S) { return 2 * Ev::PI - Arccos(V, true, P); }
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
		Octon Or = Sgn(Im);
		return -Or * Ln(V + Root(V * V - 1, 2), P);
	};
	Octon Gbl Octon::Arccos(const Octon& V)
	{
		return Arccos(V, true, 0);
	};
	Octon Gbl Octon::Arctan(const Octon& V, bool S, std::int64_t P)
	{
		if (!S) { return Ev::PI + Arctan(V, true, P); }
		double Re = Scalar(V);
		Vec7D Im = Vector(V);
		if (Im == Vec7D::Zero) { return 2 * Ev::PI * static_cast<double>(P) + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
		Octon Or = Sgn(Im);
		return 2 * Ev::PI * static_cast<double>(P) + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
	};
	Octon Gbl Octon::Arctan(const Octon& V)
	{
		return Arctan(V, true, 0);
	};
	Octon Gbl Octon::Arccsc(const Octon& V, bool S, std::int64_t P)
	{
		return Arcsin(Inverse(V), S, P);
	};
	Octon Gbl Octon::Arccsc(const Octon& V)
	{
		return Arccsc(V, true, 0);
	};
	Octon Gbl Octon::Arcsec(const Octon& V, bool S, std::int64_t P)
	{
		return Arccos(Inverse(V), S, P);
	};
	Octon Gbl Octon::Arcsec(const Octon& V)
	{
		return Arcsec(V, true, 0);
	};
	Octon Gbl Octon::Arccot(const Octon& V, bool S, std::int64_t P)
	{
		return Arctan(Inverse(V), S, P);
	};
	Octon Gbl Octon::Arccot(const Octon& V)
	{
		return Arccot(V, true, 0);
	};
	Octon Gbl Octon::Arcsinh(const Octon& V, bool S, std::int64_t P)
	{
		Vec7D Im = Vector(V);
		Octon Or = Sgn(Im);
		if (!S) { return Ev::PI * Or - Arcsinh(V, true, P); }
		return Ln(V + Root(V * V + 1, 2), P);
	};
	Octon Gbl Octon::Arcsinh(const Octon& V)
	{
		return Arcsinh(V, true, 0);
	};
	Octon Gbl Octon::Arccosh(const Octon& V, bool S, std::int64_t P)
	{
		Vec7D Im = Vector(V);
		Octon Or = Sgn(Im);
		if (!S) { return 2 * Ev::PI * Or - Arccosh(V, true, P); }
		return Ln(V + Root(V * V - 1, 2), P);
	};
	Octon Gbl Octon::Arccosh(const Octon& V)
	{
		return Arccosh(V, true, 0);
	};
	Octon Gbl Octon::Arctanh(const Octon& V, bool S, std::int64_t P)
	{
		Vec7D Im = Vector(V);
		Octon Or = Sgn(Im);
		if (!S) { return Ev::PI * Or + Arctan(V, true, P); }
		return 2 * Ev::PI * static_cast<double>(P) * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
	};
	Octon Gbl Octon::Arctanh(const Octon& V)
	{
		return Arctanh(V, true, 0);
	};
	Octon Gbl Octon::Arccsch(const Octon& V, bool S, std::int64_t P)
	{
		return Arcsinh(Inverse(V), S, P);
	};
	Octon Gbl Octon::Arccsch(const Octon& V)
	{
		return Arccsch(V, true, 0);
	};
	Octon Gbl Octon::Arcsech(const Octon& V, bool S, std::int64_t P)
	{
		return Arccosh(Inverse(V), S, P);
	};
	Octon Gbl Octon::Arcsech(const Octon& V)
	{
		return Arcsech(V, true, 0);
	};
	Octon Gbl Octon::Arccoth(const Octon& V, bool S, std::int64_t P)
	{
		return Arctanh(Inverse(V), S, P);
	};
	Octon Gbl Octon::Arccoth(const Octon& V)
	{
		return Arccoth(V, true, 0);
	};
	///
	/// conventions
	///
	String Gbl Octon::Str(const Octon& V)
	{
		std::wstring Rst = ToString(V, false, L"", L"i", L"j", L"k", L"l", L"il", L"jl", L"kl");
		return String{ Rst.data() };
	};
	Octon Gbl Octon::Val(const String& V)
	{
		std::wstring Str = Replace(V.Ptr(), L" ", L"");
		Octon Rst{};
		ToNumbers(Str, Rst, false, L"", L"i", L"j", L"k", L"l", L"il", L"jl", L"kl");
		return Rst;
	};
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
