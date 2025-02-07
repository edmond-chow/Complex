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
	struct I Vec3D
	{
		///
		/// constants
		///
	public:
		static const Vec3D Zero;
		static const Vec3D e1;
		static const Vec3D e2;
		static const Vec3D e3;
		///
		/// basis
		///
	private:
		double x1;
		double x2;
		double x3;
	public:
		explicit Ths Vec3D();
		explicit Ths Vec3D(double e1, double e2, double e3);
		///
		/// operators
		///
	public:
		Vec3D Ths operator ()() const;
		double& Ths operator [](std::size_t i) &;
		const double& Ths operator [](std::size_t i) const&;
		friend bool I Gbl operator ==(const Vec3D& U, const Vec3D& V);
		friend bool I Gbl operator !=(const Vec3D& U, const Vec3D& V);
		friend Vec3D I Gbl operator +(const Vec3D& V);
		friend Vec3D I Gbl operator -(const Vec3D& V);
		friend Vec3D I Gbl operator +(const Vec3D& U, const Vec3D& V);
		friend Vec3D I Gbl operator -(const Vec3D& U, const Vec3D& V);
		friend Vec3D I Gbl operator *(const Vec3D& U, double V);
		friend Vec3D I Gbl operator *(double U, const Vec3D& V);
		friend Vec3D I Gbl operator /(const Vec3D& U, double V);
		Vec3D& Ths operator +=(const Vec3D& O) &;
		Vec3D& Ths operator +=(const std::initializer_list<Vec3D>& O) &;
		Vec3D& Ths operator -=(const Vec3D& O) &;
		Vec3D& Ths operator -=(const std::initializer_list<Vec3D>& O) &;
		Vec3D& Ths operator *=(double O) &;
		Vec3D& Ths operator *=(const std::initializer_list<double>& O) &;
		Vec3D& Ths operator /=(double O) &;
		Vec3D& Ths operator /=(const std::initializer_list<double>& O) &;
		///
		/// multiples
		///
	public:
		static double Gbl Dot(const Vec3D& U, const Vec3D& V);
		static Vec3D Gbl Cross(const Vec3D& U, const Vec3D& V);
		///
		/// fundamentals
		///
	public:
		static double Gbl Abs(const Vec3D& V);
		static Vec3D Gbl Sgn(const Vec3D& V);
		///
		/// conventions
		///
	public:
		static String Gbl Str(const Vec3D& V);
		static Vec3D Gbl Val(const String& V);
		///
		/// casing
		///
	public:
		Number Num() const&
		{
			return Number{ 0, x1, x2, x3 };
		};
		static Vec3D Val(const Number& N)
		{
			return Vec3D{ N[1], N[2], N[3] };
		};
	};
	/* struct Vec3D */
	///
	/// constants
	///
	const Vec3D Vec3D::Zero = Vec3D{ 0, 0, 0 };
	const Vec3D Vec3D::e1 = Vec3D{ 1, 0, 0 };
	const Vec3D Vec3D::e2 = Vec3D{ 0, 1, 0 };
	const Vec3D Vec3D::e3 = Vec3D{ 0, 0, 1 };
	///
	/// basis
	///
	Ths Vec3D::Vec3D()
		: x1{ 0 }, x2{ 0 }, x3{ 0 }
	{};
	Ths Vec3D::Vec3D(double e1, double e2, double e3)
		: x1{ e1 }, x2{ e2 }, x3{ e3 }
	{};
	///
	/// operators
	///
	Vec3D Ths Vec3D::operator ()() const
	{
		return *this;
	};
	double& Ths Vec3D::operator [](std::size_t i) &
	{
		switch (i)
		{
		case 1:
			return this->x1;
		case 2:
			return this->x2;
		case 3:
			return this->x3;
		default:
			throw std::out_of_range{ "The index is out of range." };
		}
	};
	const double& Ths Vec3D::operator [](std::size_t i) const&
	{
		switch (i)
		{
		case 1:
			return this->x1;
		case 2:
			return this->x2;
		case 3:
			return this->x3;
		default:
			throw std::out_of_range{ "The index is out of range." };
		}
	};
	inline bool I Gbl operator ==(const Vec3D& U, const Vec3D& V)
	{
		return U.Num() == V.Num();
	};
	inline bool I Gbl operator !=(const Vec3D& U, const Vec3D& V)
	{
		return !(U == V);
	};
	inline Vec3D I Gbl operator +(const Vec3D& V)
	{
		return V;
	};
	inline Vec3D I Gbl operator -(const Vec3D& V)
	{
		return Vec3D::Val(-V.Num());
	};
	inline Vec3D I Gbl operator +(const Vec3D& U, const Vec3D& V)
	{
		return Vec3D::Val(U.Num() + V.Num());
	};
	inline Vec3D I Gbl operator -(const Vec3D& U, const Vec3D& V)
	{
		return Vec3D::Val(U.Num() - V.Num());
	};
	inline Vec3D I Gbl operator *(const Vec3D& U, double V)
	{
		return Vec3D::Val(U.Num() * V);
	};
	inline Vec3D I Gbl operator *(double U, const Vec3D& V)
	{
		return Vec3D::Val(U * V.Num());
	};
	inline Vec3D I Gbl operator /(const Vec3D& U, double V)
	{
		return Vec3D::Val(U.Num() / V);
	};
	Vec3D& Ths Vec3D::operator +=(const Vec3D& O) &
	{
		return *this = *this + O;
	};
	Vec3D& Ths Vec3D::operator +=(const std::initializer_list<Vec3D>& O) &
	{
		for (std::initializer_list<Vec3D>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this += *ite; }
		return *this;
	};
	Vec3D& Ths Vec3D::operator -=(const Vec3D& O) &
	{
		return *this = *this - O;
	};
	Vec3D& Ths Vec3D::operator -=(const std::initializer_list<Vec3D>& O) &
	{
		for (std::initializer_list<Vec3D>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this -= *ite; }
		return *this;
	};
	Vec3D& Ths Vec3D::operator *=(double O) &
	{
		return *this = *this * O;
	};
	Vec3D& Ths Vec3D::operator *=(const std::initializer_list<double>& O) &
	{
		for (std::initializer_list<double>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this *= *ite; }
		return *this;
	};
	Vec3D& Ths Vec3D::operator /=(double O) &
	{
		return *this = *this / O;
	};
	Vec3D& Ths Vec3D::operator /=(const std::initializer_list<double>& O) &
	{
		for (std::initializer_list<double>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this /= *ite; }
		return *this;
	};
	///
	/// multiples
	///
	double Gbl Vec3D::Dot(const Vec3D& U, const Vec3D& V)
	{
		return Number::Dot(U.Num(), V.Num());
	};
	Vec3D Gbl Vec3D::Cross(const Vec3D& U, const Vec3D& V)
	{
		return Val(Number::Cross(U.Num(), V.Num()));
	};
	///
	/// fundamentals
	///
	double Gbl Vec3D::Abs(const Vec3D& V)
	{
		return Ev::Sqrt(Dot(V, V));
	};
	Vec3D Gbl Vec3D::Sgn(const Vec3D& V)
	{
		return V / Abs(V);
	};
	///
	/// conventions
	///
	String Gbl Vec3D::Str(const Vec3D& V)
	{
		std::wstring Rst = ToString(V, true, L"e1", L"e2", L"e3");
		return String{ Rst.data() };
	};
	Vec3D Gbl Vec3D::Val(const String& V)
	{
		std::wstring Str = Replace(V.Ptr(), L" ", L"");
		Vec3D Rst{};
		ToNumbers(Str, Rst, true, L"e1", L"e2", L"e3");
		return Rst;
	};
	struct I Quter
	{
		///
		/// constants
		///
	public:
		static const Quter Zero;
		static const Quter i;
		static const Quter j;
		static const Quter k;
		///
		/// basis
		///
	private:
		double Re;
		Vec3D Im;
	public:
		explicit Ths Quter();
		explicit Ths Quter(double s, const Vec3D& v);
		explicit Ths Quter(double s, double i, double j, double k);
		Ths Quter(double V);
		Ths Quter(const Vec3D& V);
		static double Gbl Scalar(const Quter& V);
		static Vec3D Gbl Vector(const Quter& V);
		///
		/// operators
		///
	public:
		Quter Ths operator ()() const;
		double& Ths operator [](std::size_t i) &;
		const double& Ths operator [](std::size_t i) const&;
		friend bool I Gbl operator ==(const Quter& U, const Quter& V);
		friend bool I Gbl operator !=(const Quter& U, const Quter& V);
		friend Quter I Gbl operator +(const Quter& V);
		friend Quter I Gbl operator -(const Quter& V);
		friend Quter I Gbl operator ~(const Quter& V);
		Quter& Ths operator ++() &;
		Quter Ths operator ++(int) &;
		Quter& Ths operator --() &;
		Quter Ths operator --(int) &;
		friend Quter I Gbl operator +(const Quter& U, const Quter& V);
		friend Quter I Gbl operator -(const Quter& U, const Quter& V);
		friend Quter I Gbl operator *(const Quter& U, const Quter& V);
		friend Quter I Gbl operator /(const Quter& U, const Quter& V);
		friend Quter I Gbl operator ^(const Quter& U, std::int64_t V);
		Quter& Ths operator +=(const Quter& O) &;
		Quter& Ths operator +=(const std::initializer_list<Quter>& O) &;
		Quter& Ths operator -=(const Quter& O) &;
		Quter& Ths operator -=(const std::initializer_list<Quter>& O) &;
		Quter& Ths operator *=(const Quter& O) &;
		Quter& Ths operator *=(const std::initializer_list<Quter>& O) &;
		Quter& Ths operator /=(const Quter& O) &;
		Quter& Ths operator /=(const std::initializer_list<Quter>& O) &;
		Quter& Ths operator ^=(std::int64_t O) &;
		Quter& Ths operator ^=(const std::initializer_list<std::int64_t>& O) &;
		///
		/// multiples
		///
	public:
		static double Gbl Dot(const Quter& U, const Quter& V);
		static Vec3D Gbl Outer(const Quter& U, const Quter& V);
		static Quter Gbl Even(const Quter& U, const Quter& V);
		static Vec3D Gbl Cross(const Quter& U, const Quter& V);
		///
		/// fundamentals
		///
	public:
		static double Gbl Abs(const Quter& V);
		static double Gbl Arg(const Quter& V, std::int64_t P);
		static double Gbl Arg(const Quter& V);
		static Quter Gbl Conjg(const Quter& V);
		static Quter Gbl Sgn(const Quter& V);
		static Quter Gbl Inverse(const Quter& V);
		static Quter Gbl Exp(const Quter& V);
		static Quter Gbl Ln(const Quter& V, std::int64_t P);
		static Quter Gbl Ln(const Quter& V);
		///
		/// exponentials
		///
	public:
		static Quter Gbl Power(const Quter& U, const Quter& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Quter Gbl Power(const Quter& U, const Quter& V);
		static Quter Gbl Power(const Quter& U, double V, std::int64_t P);
		static Quter Gbl Power(const Quter& U, double V);
		static Quter Gbl Root(const Quter& U, const Quter& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Quter Gbl Root(const Quter& U, const Quter& V);
		static Quter Gbl Root(const Quter& U, double V, std::int64_t P);
		static Quter Gbl Root(const Quter& U, double V);
		static Quter Gbl Log(const Quter& U, const Quter& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4);
		static Quter Gbl Log(const Quter& U, const Quter& V);
		///
		/// trigonometrics
		///
	public:
		static Quter Gbl Sin(const Quter& V);
		static Quter Gbl Cos(const Quter& V);
		static Quter Gbl Tan(const Quter& V);
		static Quter Gbl Csc(const Quter& V);
		static Quter Gbl Sec(const Quter& V);
		static Quter Gbl Cot(const Quter& V);
		static Quter Gbl Sinh(const Quter& V);
		static Quter Gbl Cosh(const Quter& V);
		static Quter Gbl Tanh(const Quter& V);
		static Quter Gbl Csch(const Quter& V);
		static Quter Gbl Sech(const Quter& V);
		static Quter Gbl Coth(const Quter& V);
		static Quter Gbl Arcsin(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arcsin(const Quter& V);
		static Quter Gbl Arccos(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arccos(const Quter& V);
		static Quter Gbl Arctan(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arctan(const Quter& V);
		static Quter Gbl Arccsc(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arccsc(const Quter& V);
		static Quter Gbl Arcsec(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arcsec(const Quter& V);
		static Quter Gbl Arccot(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arccot(const Quter& V);
		static Quter Gbl Arcsinh(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arcsinh(const Quter& V);
		static Quter Gbl Arccosh(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arccosh(const Quter& V);
		static Quter Gbl Arctanh(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arctanh(const Quter& V);
		static Quter Gbl Arccsch(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arccsch(const Quter& V);
		static Quter Gbl Arcsech(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arcsech(const Quter& V);
		static Quter Gbl Arccoth(const Quter& V, bool S, std::int64_t P);
		static Quter Gbl Arccoth(const Quter& V);
		///
		/// conventions
		///
	public:
		static String Gbl Str(const Quter& V);
		static Quter Gbl Val(const String& V);
		///
		/// casing
		///
	public:
		Number Num() const&
		{
			return Number{ Re, Im[1], Im[2], Im[3] };
		};
		static Quter Val(const Number& N)
		{
			return Quter{ N[0], N[1], N[2], N[3] };
		};
	};
	/* struct Quter */
	///
	/// constants
	///
	const Quter Quter::Zero = Quter{ 0, Vec3D::Zero };
	const Quter Quter::i = Quter{ 0, Vec3D::e1 };
	const Quter Quter::j = Quter{ 0, Vec3D::e2 };
	const Quter Quter::k = Quter{ 0, Vec3D::e3 };
	///
	/// basis
	///
	Ths Quter::Quter()
		: Re{ 0 }, Im{ Vec3D::Zero }
	{};
	Ths Quter::Quter(double s, const Vec3D& v)
		: Re{ s }, Im{ v }
	{};
	Ths Quter::Quter(double s, double i, double j, double k)
		: Re{ s }, Im{ i, j, k }
	{};
	Ths Quter::Quter(double V)
		: Re{ V }, Im{ Vec3D::Zero }
	{};
	Ths Quter::Quter(const Vec3D& V)
		: Re{ 0 }, Im{ V }
	{};
	double Gbl Quter::Scalar(const Quter& V)
	{
		return V.Re;
	};
	Vec3D Gbl Quter::Vector(const Quter& V)
	{
		return V.Im;
	};
	///
	/// operators
	///
	Quter Ths Quter::operator ()() const
	{
		return *this;
	};
	double& Ths Quter::operator [](std::size_t i) &
	{
		switch (i)
		{
		case 0: return Re;
		default: return Im[i];
		}
	};
	const double& Ths Quter::operator [](std::size_t i) const&
	{
		switch (i)
		{
		case 0: return Re;
		default: return Im[i];
		}
	};
	inline bool I Gbl operator ==(const Quter& U, const Quter& V)
	{
		return U.Num() == V.Num();
	};
	inline bool I Gbl operator !=(const Quter& U, const Quter& V)
	{
		return !(U == V);
	};
	inline Quter I Gbl operator +(const Quter& V)
	{
		return V;
	};
	inline Quter I Gbl operator -(const Quter& V)
	{
		return Quter::Val(-V.Num());
	};
	inline Quter I Gbl operator ~(const Quter& V)
	{
		return Quter::Val(~V.Num());
	};
	Quter& Ths Quter::operator ++() &
	{
		++(*this)[0];
		return *this;
	};
	Quter Ths Quter::operator ++(int) &
	{
		Quter Rst = *this;
		++(*this)[0];
		return Rst;
	};
	Quter& Ths Quter::operator --() &
	{
		--(*this)[0];
		return *this;
	};
	Quter Ths Quter::operator --(int) &
	{
		Quter Rst = *this;
		--(*this)[0];
		return Rst;
	};
	inline Quter I Gbl operator +(const Quter& U, const Quter& V)
	{
		return Quter::Val(U.Num() + V.Num());
	};
	inline Quter I Gbl operator -(const Quter& U, const Quter& V)
	{
		return Quter::Val(U.Num() - V.Num());
	};
	inline Quter I Gbl operator *(const Quter& U, const Quter& V)
	{
		return Quter::Val(U.Num() * V.Num());
	};
	inline Quter I Gbl operator /(const Quter& U, const Quter& V)
	{
		if (Quter::Vector(V) == Quter::Zero) { return Quter::Val(U.Num() / Quter::Scalar(V)); }
		return U * Quter::Inverse(V);
	};
	inline Quter I Gbl operator ^(const Quter& U, std::int64_t V)
	{
		return Quter::Power(U, static_cast<double>(V));
	};
	Quter& Ths Quter::operator +=(const Quter& O) &
	{
		return *this = *this + O;
	};
	Quter& Ths Quter::operator +=(const std::initializer_list<Quter>& O) &
	{
		for (std::initializer_list<Quter>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this += *ite; }
		return *this;
	};
	Quter& Ths Quter::operator -=(const Quter& O) &
	{
		return *this = *this - O;
	};
	Quter& Ths Quter::operator -=(const std::initializer_list<Quter>& O) &
	{
		for (std::initializer_list<Quter>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this -= *ite; }
		return *this;
	};
	Quter& Ths Quter::operator *=(const Quter& O) &
	{
		return *this = *this * O;
	};
	Quter& Ths Quter::operator *=(const std::initializer_list<Quter>& O) &
	{
		for (std::initializer_list<Quter>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this *= *ite; }
		return *this;
	};
	Quter& Ths Quter::operator /=(const Quter& O) &
	{
		return *this = *this / O;
	};
	Quter& Ths Quter::operator /=(const std::initializer_list<Quter>& O) &
	{
		for (std::initializer_list<Quter>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this /= *ite; }
		return *this;
	};
	Quter& Ths Quter::operator ^=(std::int64_t O) &
	{
		return *this = *this ^ O;
	};
	Quter& Ths Quter::operator ^=(const std::initializer_list<std::int64_t>& O) &
	{
		for (std::initializer_list<std::int64_t>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this ^= *ite; }
		return *this;
	};
	///
	/// multiples
	///
	double Gbl Quter::Dot(const Quter& U, const Quter& V)
	{
		return Number::Dot(U.Num(), V.Num());
	};
	Vec3D Gbl Quter::Outer(const Quter& U, const Quter& V)
	{
		return Vec3D::Val(Number::Outer(U.Num(), V.Num()));
	};
	Quter Gbl Quter::Even(const Quter& U, const Quter& V)
	{
		return Val(Number::Even(U.Num(), V.Num()));
	};
	Vec3D Gbl Quter::Cross(const Quter& U, const Quter& V)
	{
		return Vec3D::Val(Number::Cross(U.Num(), V.Num()));
	};
	///
	/// fundamentals
	///
	double Gbl Quter::Abs(const Quter& V)
	{
		return Ev::Sqrt(Dot(V, V));
	};
	double Gbl Quter::Arg(const Quter& V, std::int64_t P)
	{
		return Ev::Arccos(Scalar(V) / Abs(V)) + 2 * Ev::PI * static_cast<double>(P);
	};
	double Gbl Quter::Arg(const Quter& V)
	{
		return Arg(V, 0);
	};
	Quter Gbl Quter::Conjg(const Quter& V)
	{
		return ~V;
	};
	Quter Gbl Quter::Sgn(const Quter& V)
	{
		return V / Abs(V);
	};
	Quter Gbl Quter::Inverse(const Quter& V)
	{
		return Conjg(V) / Dot(V, V);
	};
	Quter Gbl Quter::Exp(const Quter& V)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return Ev::Exp(Re); }
		double Sz = Abs(Im);
		Quter Or = Sgn(Im);
		return Ev::Exp(Re) * (Ev::Cos(Sz) + Or * Ev::Sin(Sz));
	};
	Quter Gbl Quter::Ln(const Quter& V, std::int64_t P)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero)
		{
			if (Re >= 0) { return Ev::Ln(Re) + 2 * static_cast<double>(P) * Ev::PI * i; }
			else { return Ev::Ln(-Re) + (2 * static_cast<double>(P) + 1) * Ev::PI * i; }
		}
		Quter Or = Sgn(Im);
		return Ev::Ln(Abs(V)) + Or * Arg(V, P);
	};
	Quter Gbl Quter::Ln(const Quter& V)
	{
		return Ln(V, 0);
	};
	///
	/// exponentials
	///
	Quter Gbl Quter::Power(const Quter& U, const Quter& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
	{
		return Exp(Exp(Ln(V, z3) + Ln(Ln(U, z1), z2)));
	};
	Quter Gbl Quter::Power(const Quter& U, const Quter& V)
	{
		return Power(U, V, 0, 0, 0);
	};
	Quter Gbl Quter::Power(const Quter& U, double V, std::int64_t P)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero)
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
		Quter Or = Sgn(Im);
		double A = Arg(U, P) * V;
		return Ev::Power(Abs(U), V) * (Ev::Cos(A) + Or * Ev::Sin(A));
	};
	Quter Gbl Quter::Power(const Quter& U, double V)
	{
		return Power(U, V, 0);
	};
	Quter Gbl Quter::Root(const Quter& U, const Quter& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
	{
		return Power(U, Inverse(V), z1, z2, z3);
	};
	Quter Gbl Quter::Root(const Quter& U, const Quter& V)
	{
		return Root(U, V, 0, 0, 0);
	};
	Quter Gbl Quter::Root(const Quter& U, double V, std::int64_t P)
	{
		return Power(U, 1 / V, P);
	};
	Quter Gbl Quter::Root(const Quter& U, double V)
	{
		return Root(U, V, 0);
	};
	Quter Gbl Quter::Log(const Quter& U, const Quter& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4)
	{
		return Exp(Ln(Ln(V, z1), z3) - Ln(Ln(U, z2), z4));
	};
	Quter Gbl Quter::Log(const Quter& U, const Quter& V)
	{
		return Log(U, V, 0, 0, 0, 0);
	};
	///
	/// trigonometrics
	///
	Quter Gbl Quter::Sin(const Quter& V)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return Ev::Sin(Re); }
		double Sz = Abs(Im);
		Quter Or = Sgn(Im);
		return Ev::Sin(Re) * Ev::Cosh(Sz) + Ev::Cos(Re) * Ev::Sinh(Sz) * Or;
	};
	Quter Gbl Quter::Cos(const Quter& V)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return Ev::Cos(Re); }
		double Sz = Abs(Im);
		Quter Or = Sgn(Im);
		return Ev::Cos(Re) * Ev::Cosh(Sz) - Ev::Sin(Re) * Ev::Sinh(Sz) * Or;
	};
	Quter Gbl Quter::Tan(const Quter& V)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		double T = Ev::Tan(Re);
		if (Im == Vec3D::Zero) { return T; }
		double Sz = Abs(Im);
		Quter Or = Sgn(Im);
		double Th = Ev::Tanh(Sz);
		double T2 = T * T;
		double Th2 = Th * Th;
		return (T * (1 - Th2) + Th * (1 + T2) * Or) / (1 + T2 * Th2);
	};
	Quter Gbl Quter::Csc(const Quter& V)
	{
		return Inverse(Sin(V));
	};
	Quter Gbl Quter::Sec(const Quter& V)
	{
		return Inverse(Cos(V));
	};
	Quter Gbl Quter::Cot(const Quter& V)
	{
		return Inverse(Tan(V));
	};
	Quter Gbl Quter::Sinh(const Quter& V)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return Ev::Sinh(Re); }
		double Sz = Abs(Im);
		Quter Or = Sgn(Im);
		return Ev::Sinh(Re) * Ev::Cos(Sz) + Ev::Cosh(Re) * Ev::Sin(Sz) * Or;
	};
	Quter Gbl Quter::Cosh(const Quter& V)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return Ev::Cosh(Re); }
		double Sz = Abs(Im);
		Quter Or = Sgn(Im);
		return Ev::Cosh(Re) * Ev::Cos(Sz) + Ev::Sinh(Re) * Ev::Sin(Sz) * Or;
	};
	Quter Gbl Quter::Tanh(const Quter& V)
	{
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		double Th = Ev::Tanh(Re);
		if (Im == Vec3D::Zero) { return Th; }
		double Sz = Abs(Im);
		Quter Or = Sgn(Im);
		double T = Ev::Tan(Sz);
		double Th2 = Th * Th;
		double T2 = T * T;
		return (Th * (1 - T2) + T * (1 + Th2) * Or) / (1 + Th2 * T2);
	};
	Quter Gbl Quter::Csch(const Quter& V)
	{
		return Inverse(Sinh(V));
	};
	Quter Gbl Quter::Sech(const Quter& V)
	{
		return Inverse(Cosh(V));
	};
	Quter Gbl Quter::Coth(const Quter& V)
	{
		return Inverse(Tanh(V));
	};
	Quter Gbl Quter::Arcsin(const Quter& V, bool S, std::int64_t P)
	{
		if (!S) { return Ev::PI - Arcsin(V, true, P); }
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
		Quter Or = Sgn(Im);
		return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
	};
	Quter Gbl Quter::Arcsin(const Quter& V)
	{
		return Arcsin(V, true, 0);
	};
	Quter Gbl Quter::Arccos(const Quter& V, bool S, std::int64_t P)
	{
		if (!S) { return 2 * Ev::PI - Arccos(V, true, P); }
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
		Quter Or = Sgn(Im);
		return -Or * Ln(V + Root(V * V - 1, 2), P);
	};
	Quter Gbl Quter::Arccos(const Quter& V)
	{
		return Arccos(V, true, 0);
	};
	Quter Gbl Quter::Arctan(const Quter& V, bool S, std::int64_t P)
	{
		if (!S) { return Ev::PI + Arctan(V, true, P); }
		double Re = Scalar(V);
		Vec3D Im = Vector(V);
		if (Im == Vec3D::Zero) { return 2 * Ev::PI * static_cast<double>(P) + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
		Quter Or = Sgn(Im);
		return 2 * Ev::PI * static_cast<double>(P) + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
	};
	Quter Gbl Quter::Arctan(const Quter& V)
	{
		return Arctan(V, true, 0);
	};
	Quter Gbl Quter::Arccsc(const Quter& V, bool S, std::int64_t P)
	{
		return Arcsin(Inverse(V), S, P);
	};
	Quter Gbl Quter::Arccsc(const Quter& V)
	{
		return Arccsc(V, true, 0);
	};
	Quter Gbl Quter::Arcsec(const Quter& V, bool S, std::int64_t P)
	{
		return Arccos(Inverse(V), S, P);
	};
	Quter Gbl Quter::Arcsec(const Quter& V)
	{
		return Arcsec(V, true, 0);
	};
	Quter Gbl Quter::Arccot(const Quter& V, bool S, std::int64_t P)
	{
		return Arctan(Inverse(V), S, P);
	};
	Quter Gbl Quter::Arccot(const Quter& V)
	{
		return Arccot(V, true, 0);
	};
	Quter Gbl Quter::Arcsinh(const Quter& V, bool S, std::int64_t P)
	{
		Vec3D Im = Vector(V);
		Quter Or = Sgn(Im);
		if (!S) { return Ev::PI * Or - Arcsinh(V, true, P); }
		return Ln(V + Root(V * V + 1, 2), P);
	};
	Quter Gbl Quter::Arcsinh(const Quter& V)
	{
		return Arcsinh(V, true, 0);
	};
	Quter Gbl Quter::Arccosh(const Quter& V, bool S, std::int64_t P)
	{
		Vec3D Im = Vector(V);
		Quter Or = Sgn(Im);
		if (!S) { return 2 * Ev::PI * Or - Arccosh(V, true, P); }
		return Ln(V + Root(V * V - 1, 2), P);
	};
	Quter Gbl Quter::Arccosh(const Quter& V)
	{
		return Arccosh(V, true, 0);
	};
	Quter Gbl Quter::Arctanh(const Quter& V, bool S, std::int64_t P)
	{
		Vec3D Im = Vector(V);
		Quter Or = Sgn(Im);
		if (!S) { return Ev::PI * Or + Arctan(V, true, P); }
		return 2 * Ev::PI * static_cast<double>(P) * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
	};
	Quter Gbl Quter::Arctanh(const Quter& V)
	{
		return Arctanh(V, true, 0);
	};
	Quter Gbl Quter::Arccsch(const Quter& V, bool S, std::int64_t P)
	{
		return Arcsinh(Inverse(V), S, P);
	};
	Quter Gbl Quter::Arccsch(const Quter& V)
	{
		return Arccsch(V, true, 0);
	};
	Quter Gbl Quter::Arcsech(const Quter& V, bool S, std::int64_t P)
	{
		return Arccosh(Inverse(V), S, P);
	};
	Quter Gbl Quter::Arcsech(const Quter& V)
	{
		return Arcsech(V, true, 0);
	};
	Quter Gbl Quter::Arccoth(const Quter& V, bool S, std::int64_t P)
	{
		return Arctanh(Inverse(V), S, P);
	};
	Quter Gbl Quter::Arccoth(const Quter& V)
	{
		return Arccoth(V, true, 0);
	};
	///
	/// conventions
	///
	String Gbl Quter::Str(const Quter& V)
	{
		std::wstring Rst = ToString(V, false, L"", L"i", L"j", L"k");
		return String{ Rst.data() };
	};
	Quter Gbl Quter::Val(const String& V)
	{
		std::wstring Str = Replace(V.Ptr(), L" ", L"");
		Quter Rst{};
		ToNumbers(Str, Rst, false, L"", L"i", L"j", L"k");
		return Rst;
	};
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
