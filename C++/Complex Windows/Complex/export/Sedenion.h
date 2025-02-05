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
#ifndef NUM_STRING
#define NUM_STRING
	class I String
	{
	private:
		wchar_t* Pointer;
	public:
		Ths String();
		String(const std::wstring& Content)
			: Pointer{ nullptr }
		{
			New(Content.c_str(), Content.size());
		};
		String(const String& Self) = delete;
		Ths String(String&& Self) noexcept;
		String& operator =(const String& O) & = delete;
		String& Ths operator =(String&& O) & noexcept;
		Ths ~String() noexcept;
		Ths operator const wchar_t*() &;
		operator std::wstring() const
		{
			return Dat();
		};
	private:
		void Ths New(const wchar_t* Pt, std::size_t Sz) &;
		const wchar_t* Ths Dat() const&;
	};
#endif
	class I Seden
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
		double* Data;
		std::size_t Size;
	public:
		explicit Ths Seden();
		explicit Ths Seden(const std::initializer_list<double>& N);
		Ths Seden(double V);
		Ths Seden(const Seden& Self);
		Ths Seden(Seden&& Self) noexcept;
		Ths ~Seden() noexcept;
		static double Gbl Scalar(const Seden& V);
		static Seden Gbl Vector(const Seden& V);
		///
		/// operators
		///
	public:
		Seden Ths operator ()() const;
		double& Ths operator [](std::size_t i) &;
		const double& Ths operator [](std::size_t i) const&;
		Seden& Ths operator =(const Seden& O) &;
		Seden& Ths operator =(Seden&& O) & noexcept;
		Seden& Ths operator ++() &;
		Seden Ths operator ++(int) &;
		Seden& Ths operator --() &;
		Seden Ths operator --(int) &;
		Seden& Ths operator +=(const Seden& O) &;
		Seden& Ths operator +=(const std::initializer_list<Seden>& O) &;
		Seden& Ths operator -=(const Seden& O) &;
		Seden& Ths operator -=(const std::initializer_list<Seden>& O) &;
		Seden& Ths operator *=(const Seden& O) &;
		Seden& Ths operator *=(const std::initializer_list<Seden>& O) &;
		Seden& Ths operator /=(const Seden& O) &;
		Seden& Ths operator /=(const std::initializer_list<Seden>& O) &;
		Seden& Ths operator ^=(std::int64_t O) &;
		Seden& Ths operator ^=(const std::initializer_list<std::int64_t>& O) &;
		///
		/// multiples
		///
	public:
		static double Gbl Dot(const Seden& U, const Seden& V);
		static Seden Gbl Outer(const Seden& U, const Seden& V);
		static Seden Gbl Even(const Seden& U, const Seden& V);
		static Seden Gbl Cross(const Seden& U, const Seden& V);
		///
		/// fundamentals
		///
	public:
		static double Gbl Abs(const Seden& V);
		static double Gbl Arg(const Seden& V, std::int64_t P);
		static double Gbl Arg(const Seden& V);
		static Seden Gbl Conjg(const Seden& V);
		static Seden Gbl Sgn(const Seden& V);
		static Seden Gbl Inverse(const Seden& V);
		static Seden Gbl Exp(const Seden& V);
		static Seden Gbl Ln(const Seden& V, std::int64_t P);
		static Seden Gbl Ln(const Seden& V);
		///
		/// exponentials
		///
	public:
		static Seden Gbl Power(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Seden Gbl Power(const Seden& U, const Seden& V);
		static Seden Gbl Power(const Seden& U, double V, std::int64_t P);
		static Seden Gbl Power(const Seden& U, double V);
		static Seden Gbl Root(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3);
		static Seden Gbl Root(const Seden& U, const Seden& V);
		static Seden Gbl Root(const Seden& U, double V, std::int64_t P);
		static Seden Gbl Root(const Seden& U, double V);
		static Seden Gbl Log(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4);
		static Seden Gbl Log(const Seden& U, const Seden& V);
		///
		/// trigonometrics
		///
	public:
		static Seden Gbl Sin(const Seden& V);
		static Seden Gbl Cos(const Seden& V);
		static Seden Gbl Tan(const Seden& V);
		static Seden Gbl Csc(const Seden& V);
		static Seden Gbl Sec(const Seden& V);
		static Seden Gbl Cot(const Seden& V);
		static Seden Gbl Sinh(const Seden& V);
		static Seden Gbl Cosh(const Seden& V);
		static Seden Gbl Tanh(const Seden& V);
		static Seden Gbl Csch(const Seden& V);
		static Seden Gbl Sech(const Seden& V);
		static Seden Gbl Coth(const Seden& V);
		static Seden Gbl Arcsin(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arcsin(const Seden& V);
		static Seden Gbl Arccos(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arccos(const Seden& V);
		static Seden Gbl Arctan(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arctan(const Seden& V);
		static Seden Gbl Arccsc(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arccsc(const Seden& V);
		static Seden Gbl Arcsec(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arcsec(const Seden& V);
		static Seden Gbl Arccot(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arccot(const Seden& V);
		static Seden Gbl Arcsinh(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arcsinh(const Seden& V);
		static Seden Gbl Arccosh(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arccosh(const Seden& V);
		static Seden Gbl Arctanh(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arctanh(const Seden& V);
		static Seden Gbl Arccsch(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arccsch(const Seden& V);
		static Seden Gbl Arcsech(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arcsech(const Seden& V);
		static Seden Gbl Arccoth(const Seden& V, bool S, std::int64_t P);
		static Seden Gbl Arccoth(const Seden& V);
		///
		/// conventions
		///
	public:
		static String Gbl Str(const Seden& V);
		static Seden Gbl Val(const String& V);
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
