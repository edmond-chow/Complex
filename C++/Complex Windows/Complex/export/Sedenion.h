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
#ifndef SEDEN
#define SEDEN
#include <string>
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
	class Seden
	{
	public:
		///
		/// constants
		///
	public:
		static const Seden Zero;
		///
		/// basis
		///
	private:
		std::vector<double> Data;
	public:
		I explicit Ths Seden();
		I explicit Ths Seden(const std::initializer_list<double>& N);
		I Ths Seden(double V);
		I Ths Seden(const Seden& Self);
		I Ths Seden(Seden&& Self);
		I Ths ~Seden() noexcept;
		static double I Gbl Scalar(const Seden& V);
		static Seden I Gbl Vector(const Seden& V);
		///
		/// operators
		///
	public:
		I Seden Ths operator ()() const;
		I double& Ths operator [](std::size_t i) &;
		I const double& Ths operator [](std::size_t i) const&;
		I Seden& Ths operator =(const Seden& O) = default;
		I Seden& Ths operator =(Seden&& O) = default;
		I Seden& Ths operator ++() &;
		I Seden Ths operator ++(int) &;
		I Seden& Ths operator --() &;
		I Seden Ths operator --(int) &;
		I Seden& Ths operator +=(const Seden& O) &;
		I Seden& Ths operator +=(const std::initializer_list<Seden>& O) &;
		I Seden& Ths operator -=(const Seden& O) &;
		I Seden& Ths operator -=(const std::initializer_list<Seden>& O) &;
		I Seden& Ths operator *=(const Seden& O) &;
		I Seden& Ths operator *=(const std::initializer_list<Seden>& O) &;
		I Seden& Ths operator /=(const Seden& O) &;
		I Seden& Ths operator /=(const std::initializer_list<Seden>& O) &;
		I Seden& Ths operator ^=(std::int64_t O) &;
		I Seden& Ths operator ^=(const std::initializer_list<std::int64_t>& O) &;
		///
		/// multiples
		///
	public:
		static double I Gbl Dot(const Seden& U, const Seden& V);
		static Seden I Gbl Outer(const Seden& U, const Seden& V);
		static Seden I Gbl Even(const Seden& U, const Seden& V);
		static Seden I Gbl Cross(const Seden& U, const Seden& V);
		///
		/// fundamentals
		///
	public:
		static double I Gbl Abs(const Seden& V);
		static double I Gbl Arg(const Seden& V, std::int64_t P);
		static double I Gbl Arg(const Seden& V);
		static Seden I Gbl Conjg(const Seden& V);
		static Seden I Gbl Sgn(const Seden& V);
		static Seden I Gbl Inverse(const Seden& V);
		static Seden I Gbl Exp(const Seden& V);
		static Seden I Gbl Ln(const Seden& V, std::int64_t P);
		static Seden I Gbl Ln(const Seden& V);
		///
		/// exponentials
		///
	public:
		static Seden I Gbl Power(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Seden I Gbl Power(const Seden& U, const Seden& V);
		static Seden I Gbl Power(const Seden& U, double V, std::int64_t P);
		static Seden I Gbl Power(const Seden& U, double V);
		static Seden I Gbl Root(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Seden I Gbl Root(const Seden& U, const Seden& V);
		static Seden I Gbl Root(const Seden& U, double V, std::int64_t P);
		static Seden I Gbl Root(const Seden& U, double V);
		static Seden I Gbl Log(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4);
		static Seden I Gbl Log(const Seden& U, const Seden& V);
		///
		/// trigonometrics
		///
	public:
		static Seden I Gbl Sin(const Seden& V);
		static Seden I Gbl Cos(const Seden& V);
		static Seden I Gbl Tan(const Seden& V);
		static Seden I Gbl Csc(const Seden& V);
		static Seden I Gbl Sec(const Seden& V);
		static Seden I Gbl Cot(const Seden& V);
		static Seden I Gbl Sinh(const Seden& V);
		static Seden I Gbl Cosh(const Seden& V);
		static Seden I Gbl Tanh(const Seden& V);
		static Seden I Gbl Csch(const Seden& V);
		static Seden I Gbl Sech(const Seden& V);
		static Seden I Gbl Coth(const Seden& V);
		static Seden I Gbl Arcsin(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arcsin(const Seden& V);
		static Seden I Gbl Arccos(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arccos(const Seden& V);
		static Seden I Gbl Arctan(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arctan(const Seden& V);
		static Seden I Gbl Arccsc(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arccsc(const Seden& V);
		static Seden I Gbl Arcsec(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arcsec(const Seden& V);
		static Seden I Gbl Arccot(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arccot(const Seden& V);
		static Seden I Gbl Arcsinh(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arcsinh(const Seden& V);
		static Seden I Gbl Arccosh(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arccosh(const Seden& V);
		static Seden I Gbl Arctanh(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arctanh(const Seden& V);
		static Seden I Gbl Arccsch(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arccsch(const Seden& V);
		static Seden I Gbl Arcsech(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arcsech(const Seden& V);
		static Seden I Gbl Arccoth(const Seden& V, bool S, std::int64_t P);
		static Seden I Gbl Arccoth(const Seden& V);
		///
		/// conventions
		///
	public:
		static std::wstring I Gbl Str(const Seden& V);
		static Seden I Gbl Val(const std::wstring& V);
	};
	/* class Seden */
	///
	/// operators
	///
	bool I Gbl operator ==(const Seden& U, const Seden& V);
	bool I Gbl operator !=(const Seden& U, const Seden& V);
	Seden I Gbl operator +(const Seden& V);
	Seden I Gbl operator -(const Seden& V);
	Seden I Gbl operator ~(const Seden& V);
	Seden I Gbl operator +(const Seden& U, const Seden& V);
	Seden I Gbl operator -(const Seden& U, const Seden& V);
	Seden I Gbl operator *(const Seden& U, const Seden& V);
	Seden I Gbl operator /(const Seden& U, const Seden& V);
	Seden I Gbl operator ^(const Seden& U, std::int64_t V);
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
#endif
#endif
