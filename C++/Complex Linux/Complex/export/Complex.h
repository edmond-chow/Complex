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
#ifndef CMPLX
#define CMPLX
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
	struct I Vec1D
	{
		///
		/// constants
		///
	public:
		static const Vec1D Zero;
		static const Vec1D e1;
		///
		/// basis
		///
	private:
		double x1;
	public:
		explicit Ths Vec1D();
		explicit Ths Vec1D(double e1);
		///
		/// operators
		///
	public:
		Vec1D Ths operator ()() const;
		double& Ths operator [](std::size_t i) &;
		const double& Ths operator [](std::size_t i) const&;
		Vec1D& Ths operator +=(const Vec1D& O) &;
		Vec1D& Ths operator +=(const std::initializer_list<Vec1D>& O) &;
		Vec1D& Ths operator -=(const Vec1D& O) &;
		Vec1D& Ths operator -=(const std::initializer_list<Vec1D>& O) &;
		Vec1D& Ths operator *=(double O) &;
		Vec1D& Ths operator *=(const std::initializer_list<double>& O) &;
		Vec1D& Ths operator /=(double O) &;
		Vec1D& Ths operator /=(const std::initializer_list<double>& O) &;
		///
		/// multiples
		///
	public:
		static double Gbl Dot(const Vec1D& U, const Vec1D& V);
		static Vec1D Gbl Cross(const Vec1D& U, const Vec1D& V);
		///
		/// fundamentals
		///
	public:
		static double Gbl Abs(const Vec1D& V);
		static Vec1D Gbl Sgn(const Vec1D& V);
		///
		/// conventions
		///
	public:
		static String Gbl Str(const Vec1D& V);
		static Vec1D Gbl Val(const String& V);
	};
	///
	/// operators
	///
	bool I Gbl operator ==(const Vec1D& U, const Vec1D& V);
	bool I Gbl operator !=(const Vec1D& U, const Vec1D& V);
	Vec1D I Gbl operator +(const Vec1D& V);
	Vec1D I Gbl operator -(const Vec1D& V);
	Vec1D I Gbl operator +(const Vec1D& U, const Vec1D& V);
	Vec1D I Gbl operator -(const Vec1D& U, const Vec1D& V);
	Vec1D I Gbl operator *(const Vec1D& U, double V);
	Vec1D I Gbl operator *(double U, const Vec1D& V);
	Vec1D I Gbl operator /(const Vec1D& U, double V);
	struct I Cmplx
	{
		///
		/// constants
		///
	public:
		static const Cmplx Zero;
		static const Cmplx i;
		///
		/// basis
		///
	private:
		double Re;
		Vec1D Im;
	public:
		explicit Ths Cmplx();
		explicit Ths Cmplx(double s, const Vec1D& v);
		explicit Ths Cmplx(double s, double i);
		Ths Cmplx(double V);
		Ths Cmplx(const Vec1D& V);
		static double Gbl Scalar(const Cmplx& V);
		static Vec1D Gbl Vector(const Cmplx& V);
		///
		/// operators
		///
	public:
		Cmplx Ths operator ()() const;
		double& Ths operator [](std::size_t i) &;
		const double& Ths operator [](std::size_t i) const&;
		Cmplx& Ths operator ++() &;
		Cmplx Ths operator ++(int) &;
		Cmplx& Ths operator --() &;
		Cmplx Ths operator --(int) &;
		Cmplx& Ths operator +=(const Cmplx& O) &;
		Cmplx& Ths operator +=(const std::initializer_list<Cmplx>& O) &;
		Cmplx& Ths operator -=(const Cmplx& O) &;
		Cmplx& Ths operator -=(const std::initializer_list<Cmplx>& O) &;
		Cmplx& Ths operator *=(const Cmplx& O) &;
		Cmplx& Ths operator *=(const std::initializer_list<Cmplx>& O) &;
		Cmplx& Ths operator /=(const Cmplx& O) &;
		Cmplx& Ths operator /=(const std::initializer_list<Cmplx>& O) &;
		Cmplx& Ths operator ^=(std::int64_t O) &;
		Cmplx& Ths operator ^=(const std::initializer_list<std::int64_t>& O) &;
		///
		/// multiples
		///
	public:
		static double Gbl Dot(const Cmplx& U, const Cmplx& V);
		static Vec1D Gbl Outer(const Cmplx& U, const Cmplx& V);
		static Cmplx Gbl Even(const Cmplx& U, const Cmplx& V);
		static Vec1D Gbl Cross(const Cmplx& U, const Cmplx& V);
		///
		/// fundamentals
		///
	public:
		static double Gbl Abs(const Cmplx& V);
		static double Gbl Arg(const Cmplx& V, std::int64_t P);
		static double Gbl Arg(const Cmplx& V);
		static Cmplx Gbl Conjg(const Cmplx& V);
		static Cmplx Gbl Sgn(const Cmplx& V);
		static Cmplx Gbl Inverse(const Cmplx& V);
		static Cmplx Gbl Exp(const Cmplx& V);
		static Cmplx Gbl Ln(const Cmplx& V, std::int64_t P);
		static Cmplx Gbl Ln(const Cmplx& V);
		///
		/// exponentials
		///
	public:
		static Cmplx Gbl Power(const Cmplx& U, const Cmplx& V, std::int64_t z1);
		static Cmplx Gbl Power(const Cmplx& U, const Cmplx& V);
		static Cmplx Gbl Power(const Cmplx& U, double V, std::int64_t P);
		static Cmplx Gbl Power(const Cmplx& U, double V);
		static Cmplx Gbl Root(const Cmplx& U, const Cmplx& V, std::int64_t z1);
		static Cmplx Gbl Root(const Cmplx& U, const Cmplx& V);
		static Cmplx Gbl Root(const Cmplx& U, double V, std::int64_t P);
		static Cmplx Gbl Root(const Cmplx& U, double V);
		static Cmplx Gbl Log(const Cmplx& U, const Cmplx& V, std::int64_t z1, std::int64_t z2);
		static Cmplx Gbl Log(const Cmplx& U, const Cmplx& V);
		///
		/// trigonometrics
		///
	public:
		static Cmplx Gbl Sin(const Cmplx& V);
		static Cmplx Gbl Cos(const Cmplx& V);
		static Cmplx Gbl Tan(const Cmplx& V);
		static Cmplx Gbl Csc(const Cmplx& V);
		static Cmplx Gbl Sec(const Cmplx& V);
		static Cmplx Gbl Cot(const Cmplx& V);
		static Cmplx Gbl Sinh(const Cmplx& V);
		static Cmplx Gbl Cosh(const Cmplx& V);
		static Cmplx Gbl Tanh(const Cmplx& V);
		static Cmplx Gbl Csch(const Cmplx& V);
		static Cmplx Gbl Sech(const Cmplx& V);
		static Cmplx Gbl Coth(const Cmplx& V);
		static Cmplx Gbl Arcsin(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arcsin(const Cmplx& V);
		static Cmplx Gbl Arccos(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arccos(const Cmplx& V);
		static Cmplx Gbl Arctan(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arctan(const Cmplx& V);
		static Cmplx Gbl Arccsc(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arccsc(const Cmplx& V);
		static Cmplx Gbl Arcsec(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arcsec(const Cmplx& V);
		static Cmplx Gbl Arccot(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arccot(const Cmplx& V);
		static Cmplx Gbl Arcsinh(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arcsinh(const Cmplx& V);
		static Cmplx Gbl Arccosh(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arccosh(const Cmplx& V);
		static Cmplx Gbl Arctanh(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arctanh(const Cmplx& V);
		static Cmplx Gbl Arccsch(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arccsch(const Cmplx& V);
		static Cmplx Gbl Arcsech(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arcsech(const Cmplx& V);
		static Cmplx Gbl Arccoth(const Cmplx& V, bool S, std::int64_t P);
		static Cmplx Gbl Arccoth(const Cmplx& V);
		///
		/// conventions
		///
	public:
		static String Gbl Str(const Cmplx& V);
		static Cmplx Gbl Val(const String& V);
	};
	///
	/// operators
	///
	bool I Gbl operator ==(const Cmplx& U, const Cmplx& V);
	bool I Gbl operator !=(const Cmplx& U, const Cmplx& V);
	Cmplx I Gbl operator +(const Cmplx& V);
	Cmplx I Gbl operator -(const Cmplx& V);
	Cmplx I Gbl operator ~(const Cmplx& V);
	Cmplx I Gbl operator +(const Cmplx& U, const Cmplx& V);
	Cmplx I Gbl operator -(const Cmplx& U, const Cmplx& V);
	Cmplx I Gbl operator *(const Cmplx& U, const Cmplx& V);
	Cmplx I Gbl operator /(const Cmplx& U, const Cmplx& V);
	Cmplx I Gbl operator ^(const Cmplx& U, std::int64_t V);
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
#endif
#endif
