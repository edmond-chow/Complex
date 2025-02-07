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
#if (__cplusplus >= 201103L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201103L) && (_MSC_VER >= 1800))
#pragma once
#ifndef QUTER
#define QUTER
#include <cstddef>
#include <cstdint>
#include <string>
#include <NumString.h>
#pragma pack(push)
#pragma push_macro("I")
#pragma push_macro("Gbl")
#pragma push_macro("Ths")
#pragma pack(8)
#if defined(_MSVC_LANG)
#define I __declspec(dllimport)
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
	};
	///
	/// operators
	///
	bool I Gbl operator ==(const Vec7D& U, const Vec7D& V);
	bool I Gbl operator !=(const Vec7D& U, const Vec7D& V);
	Vec7D I Gbl operator +(const Vec7D& V);
	Vec7D I Gbl operator -(const Vec7D& V);
	Vec7D I Gbl operator +(const Vec7D& U, const Vec7D& V);
	Vec7D I Gbl operator -(const Vec7D& U, const Vec7D& V);
	Vec7D I Gbl operator *(const Vec7D& U, double V);
	Vec7D I Gbl operator *(double U, const Vec7D& V);
	Vec7D I Gbl operator /(const Vec7D& U, double V);
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
		Octon& Ths operator ++() &;
		Octon Ths operator ++(int) &;
		Octon& Ths operator --() &;
		Octon Ths operator --(int) &;
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
	};
	///
	/// operators
	///
	bool I Gbl operator ==(const Octon& U, const Octon& V);
	bool I Gbl operator !=(const Octon& U, const Octon& V);
	Octon I Gbl operator +(const Octon& V);
	Octon I Gbl operator -(const Octon& V);
	Octon I Gbl operator ~(const Octon& V);
	Octon I Gbl operator +(const Octon& U, const Octon& V);
	Octon I Gbl operator -(const Octon& U, const Octon& V);
	Octon I Gbl operator *(const Octon& U, const Octon& V);
	Octon I Gbl operator /(const Octon& U, const Octon& V);
	Octon I Gbl operator ^(const Octon& U, std::int64_t V);
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
#endif
#endif
