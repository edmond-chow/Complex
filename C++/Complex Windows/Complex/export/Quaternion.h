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
	};
	///
	/// operators
	///
	bool I Gbl operator ==(const Vec3D& U, const Vec3D& V);
	bool I Gbl operator !=(const Vec3D& U, const Vec3D& V);
	Vec3D I Gbl operator +(const Vec3D& V);
	Vec3D I Gbl operator -(const Vec3D& V);
	Vec3D I Gbl operator +(const Vec3D& U, const Vec3D& V);
	Vec3D I Gbl operator -(const Vec3D& U, const Vec3D& V);
	Vec3D I Gbl operator *(const Vec3D& U, double V);
	Vec3D I Gbl operator *(double U, const Vec3D& V);
	Vec3D I Gbl operator /(const Vec3D& U, double V);
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
		Quter& Ths operator ++() &;
		Quter Ths operator ++(int) &;
		Quter& Ths operator --() &;
		Quter Ths operator --(int) &;
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
	};
	///
	/// operators
	///
	bool I Gbl operator ==(const Quter& U, const Quter& V);
	bool I Gbl operator !=(const Quter& U, const Quter& V);
	Quter I Gbl operator +(const Quter& V);
	Quter I Gbl operator -(const Quter& V);
	Quter I Gbl operator ~(const Quter& V);
	Quter I Gbl operator +(const Quter& U, const Quter& V);
	Quter I Gbl operator -(const Quter& U, const Quter& V);
	Quter I Gbl operator *(const Quter& U, const Quter& V);
	Quter I Gbl operator /(const Quter& U, const Quter& V);
	Quter I Gbl operator ^(const Quter& U, std::int64_t V);
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
#endif
#endif
