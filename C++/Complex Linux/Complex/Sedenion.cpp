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
	class I Seden
	{
		///
		/// helpers
		///
	private:
		static std::size_t Near(std::size_t Dim)
		{
			int Shift = 0;
			while (Dim >> Shift != 0)
			{
				++Shift;
			}
			std::size_t Rst = 0b1;
			Rst <<= Shift;
			return Rst;
		};
		///
		/// constants
		///
	public:
		static const Seden Zero;
	private:
		static const Seden i;
		///
		/// basis
		///
	private:
		static constexpr const std::size_t BasicSize = 16;
		double* Data;
		std::size_t Size;
	public:
		explicit Ths Seden();
		explicit Ths Seden(const std::initializer_list<double>& N);
		Ths Seden(double V);
	private:
		explicit Seden(const std::vector<double>& N)
			: Data{ nullptr }, Size{ 0 }
		{
			Size = N.size();
			if (Size < BasicSize) { Size = BasicSize; }
			Data = new double[Size] {};
			std::copy(N.begin(), N.end(), Data);
		};
	public:
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
		friend bool I Gbl operator ==(const Seden& U, const Seden& V);
		friend bool I Gbl operator !=(const Seden& U, const Seden& V);
		friend Seden I Gbl operator +(const Seden& V);
		friend Seden I Gbl operator -(const Seden& V);
		friend Seden I Gbl operator ~(const Seden& V);
		Seden& Ths operator ++() &;
		Seden Ths operator ++(int) &;
		Seden& Ths operator --() &;
		Seden Ths operator --(int) &;
		friend Seden I Gbl operator +(const Seden& U, const Seden& V);
		friend Seden I Gbl operator -(const Seden& U, const Seden& V);
		friend Seden I Gbl operator *(const Seden& U, const Seden& V);
		friend Seden I Gbl operator /(const Seden& U, const Seden& V);
		friend Seden I Gbl operator ^(const Seden& U, std::int64_t V);
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
		///
		/// casing
		///
	private:
		Number Num() const&
		{
			std::size_t Dim = Size;
			std::vector<double> Num(Dim);
			for (std::size_t i = 0; i < Dim; ++i) { Num[i] = Data[i]; }
			return Number(Num);
		};
		static Seden Val(const Number& N)
		{
			return Seden(N());
		};
	};
	/* class Seden */
	///
	/// constants
	///
	const Seden Seden::Zero{};
	const Seden Seden::i{ 0, 1 };
	///
	/// basis
	///
	Ths Seden::Seden()
		: Data{ nullptr }, Size{ 0 }
	{
		Size = BasicSize;
		Data = new double[Size] {};
	};
	Ths Seden::Seden(const std::initializer_list<double>& N)
		: Data{ nullptr }, Size{ 0 }
	{
		Size = N.size();
		if (Size < BasicSize) { Size = BasicSize; }
		Data = new double[Size] {};
		std::copy(N.begin(), N.end(), Data);
	};
	Ths Seden::Seden(double V)
		: Data{ nullptr }, Size{ 0 }
	{
		Size = BasicSize;
		Data = new double[Size] { V };
	};
	Ths Seden::Seden(const Seden& Self)
		: Data{ nullptr }, Size{ 0 }
	{
		Size = Self.Size;
		Data = new double[Size] {};
		std::copy(Self.Data, Self.Data + Self.Size, Data);
	};
	Ths Seden::Seden(Seden&& Self) noexcept
		: Data{ nullptr }, Size{ 0 }
	{
		Data = Self.Data;
		Size = Self.Size;
		Self.Data = nullptr;
		Self.Size = 0;
	};
	Ths Seden::~Seden() noexcept
	{
		delete[] Data;
		Data = nullptr;
		Size = 0;
	};
	double Gbl Seden::Scalar(const Seden& V)
	{
		return V[0];
	};
	Seden Gbl Seden::Vector(const Seden& V)
	{
		Seden Rst = V;
		Rst[0] = 0;
		return Rst;
	};
	///
	/// operators
	///
	Seden Ths Seden::operator ()() const
	{
		return *this;
	};
	double& Ths Seden::operator [](std::size_t i) &
	{
		return Data[i];
	};
	const double& Ths Seden::operator [](std::size_t i) const&
	{
		return Data[i];
	};
	Seden& Ths Seden::operator =(const Seden& O) &
	{
		if (O == *this) { return *this; }
		Size = O.Size;
		Data = new double[Size] {};
		std::copy(O.Data, O.Data + O.Size, Data);
		return *this;
	};
	Seden& Ths Seden::operator =(Seden&& O) & noexcept
	{
		delete[] Data;
		Data = O.Data;
		Size = O.Size;
		O.Data = nullptr;
		O.Size = 0;
		return *this;
	};
	bool I Gbl operator ==(const Seden& U, const Seden& V)
	{
		return U.Num() == V.Num();
	};
	bool I Gbl operator !=(const Seden& U, const Seden& V)
	{
		return !(U == V);
	};
	Seden I Gbl operator +(const Seden& V)
	{
		return V;
	};
	Seden I Gbl operator -(const Seden& V)
	{
		return Seden::Val(-V.Num());
	};
	Seden I Gbl operator ~(const Seden& V)
	{
		return Seden::Val(~V.Num());
	};
	Seden& Ths Seden::operator ++() &
	{
		++(*this)[0];
		return *this;
	};
	Seden Ths Seden::operator ++(int) &
	{
		Seden Rst = *this;
		++(*this)[0];
		return Rst;
	};
	Seden& Ths Seden::operator --() &
	{
		--(*this)[0];
		return *this;
	};
	Seden Ths Seden::operator --(int) &
	{
		Seden Rst = *this;
		--(*this)[0];
		return Rst;
	};
	Seden I Gbl operator +(const Seden& U, const Seden& V)
	{
		return Seden::Val(U.Num() + V.Num());
	};
	Seden I Gbl operator -(const Seden& U, const Seden& V)
	{
		return Seden::Val(U.Num() - V.Num());
	};
	Seden I Gbl operator *(const Seden& U, const Seden& V)
	{
		return Seden::Val(U.Num() * V.Num());
	};
	Seden I Gbl operator /(const Seden& U, const Seden& V)
	{
		if (Seden::Vector(V) == Seden::Zero) { return Seden::Val(U.Num() / Seden::Scalar(V)); }
		return U * Seden::Inverse(V);
	};
	Seden I Gbl operator ^(const Seden& U, std::int64_t V)
	{
		return Seden::Power(U, static_cast<double>(V));
	};
	Seden& Ths Seden::operator +=(const Seden& O) &
	{
		return *this = *this + O;
	};
	Seden& Ths Seden::operator +=(const std::initializer_list<Seden>& O) &
	{
		for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this += *ite; }
		return *this;
	};
	Seden& Ths Seden::operator -=(const Seden& O) &
	{
		return *this = *this - O;
	};
	Seden& Ths Seden::operator -=(const std::initializer_list<Seden>& O) &
	{
		for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this -= *ite; }
		return *this;
	};
	Seden& Ths Seden::operator *=(const Seden& O) &
	{
		return *this = *this * O;
	};
	Seden& Ths Seden::operator *=(const std::initializer_list<Seden>& O) &
	{
		for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this *= *ite; }
		return *this;
	};
	Seden& Ths Seden::operator /=(const Seden& O) &
	{
		return *this = *this / O;
	};
	Seden& Ths Seden::operator /=(const std::initializer_list<Seden>& O) &
	{
		for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this /= *ite; }
		return *this;
	};
	Seden& Ths Seden::operator ^=(std::int64_t O) &
	{
		return *this = *this ^ O;
	};
	Seden& Ths Seden::operator ^=(const std::initializer_list<std::int64_t>& O) &
	{
		for (std::initializer_list<std::int64_t>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this ^= *ite; }
		return *this;
	};
	///
	/// multiples
	///
	double Gbl Seden::Dot(const Seden& U, const Seden& V)
	{
		return Number::Dot(U.Num(), V.Num());
	};
	Seden Gbl Seden::Outer(const Seden& U, const Seden& V)
	{
		return Seden::Val(Number::Outer(U.Num(), V.Num()));
	};
	Seden Gbl Seden::Even(const Seden& U, const Seden& V)
	{
		return Val(Number::Even(U.Num(), V.Num()));
	};
	Seden Gbl Seden::Cross(const Seden& U, const Seden& V)
	{
		return Seden::Val(Number::Cross(U.Num(), V.Num()));
	};
	///
	/// fundamentals
	///
	double Gbl Seden::Abs(const Seden& V)
	{
		return Ev::Sqrt(Dot(V, V));
	};
	double Gbl Seden::Arg(const Seden& V, std::int64_t P)
	{
		return Ev::Arccos(Scalar(V) / Abs(V)) + 2 * Ev::PI * static_cast<double>(P);
	};
	double Gbl Seden::Arg(const Seden& V)
	{
		return Arg(V, 0);
	};
	Seden Gbl Seden::Conjg(const Seden& V)
	{
		return ~V;
	};
	Seden Gbl Seden::Sgn(const Seden& V)
	{
		return V / Abs(V);
	};
	Seden Gbl Seden::Inverse(const Seden& V)
	{
		return Conjg(V) / Dot(V, V);
	};
	Seden Gbl Seden::Exp(const Seden& V)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return Ev::Exp(Re); }
		double Sz = Abs(Im);
		Seden Or = Sgn(Im);
		return Ev::Exp(Re) * (Ev::Cos(Sz) + Or * Ev::Sin(Sz));
	};
	Seden Gbl Seden::Ln(const Seden& V, std::int64_t P)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero)
		{
			if (Re >= 0) { return Ev::Ln(Re) + 2 * static_cast<double>(P) * Ev::PI * i; }
			else { return Ev::Ln(-Re) + (2 * static_cast<double>(P) + 1) * Ev::PI * i; }
		}
		Seden Or = Sgn(Im);
		return Ev::Ln(Abs(V)) + Or * Arg(V, P);
	};
	Seden Gbl Seden::Ln(const Seden& V)
	{
		return Ln(V, 0);
	};
	///
	/// exponentials
	///
	Seden Gbl Seden::Power(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
	{
		return Exp(Exp(Ln(V, z3) + Ln(Ln(U, z1), z2)));
	};
	Seden Gbl Seden::Power(const Seden& U, const Seden& V)
	{
		return Power(U, V, 0, 0, 0);
	};
	Seden Gbl Seden::Power(const Seden& U, double V, std::int64_t P)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero)
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
		Seden Or = Sgn(Im);
		double A = Arg(U, P) * V;
		return Ev::Power(Abs(U), V) * (Ev::Cos(A) + Or * Ev::Sin(A));
	};
	Seden Gbl Seden::Power(const Seden& U, double V)
	{
		return Power(U, V, 0);
	};
	Seden Gbl Seden::Root(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
	{
		return Power(U, Inverse(V), z1, z2, z3);
	};
	Seden Gbl Seden::Root(const Seden& U, const Seden& V)
	{
		return Root(U, V, 0, 0, 0);
	};
	Seden Gbl Seden::Root(const Seden& U, double V, std::int64_t P)
	{
		return Power(U, 1 / V, P);
	};
	Seden Gbl Seden::Root(const Seden& U, double V)
	{
		return Root(U, V, 0);
	};
	Seden Gbl Seden::Log(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4)
	{
		return Exp(Ln(Ln(V, z1), z3) - Ln(Ln(U, z2), z4));
	};
	Seden Gbl Seden::Log(const Seden& U, const Seden& V)
	{
		return Log(U, V, 0, 0, 0, 0);
	};
	///
	/// trigonometrics
	///
	Seden Gbl Seden::Sin(const Seden& V)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return Ev::Sin(Re); }
		double Sz = Abs(Im);
		Seden Or = Sgn(Im);
		return Ev::Sin(Re) * Ev::Cosh(Sz) + Ev::Cos(Re) * Ev::Sinh(Sz) * Or;
	};
	Seden Gbl Seden::Cos(const Seden& V)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return Ev::Cos(Re); }
		double Sz = Abs(Im);
		Seden Or = Sgn(Im);
		return Ev::Cos(Re) * Ev::Cosh(Sz) - Ev::Sin(Re) * Ev::Sinh(Sz) * Or;
	};
	Seden Gbl Seden::Tan(const Seden& V)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		double T = Ev::Tan(Re);
		if (Im == Seden::Zero) { return T; }
		double Sz = Abs(Im);
		Seden Or = Sgn(Im);
		double Th = Ev::Tanh(Sz);
		double T2 = T * T;
		double Th2 = Th * Th;
		return (T * (1 - Th2) + Th * (1 + T2) * Or) / (1 + T2 * Th2);
	};
	Seden Gbl Seden::Csc(const Seden& V)
	{
		return Inverse(Sin(V));
	};
	Seden Gbl Seden::Sec(const Seden& V)
	{
		return Inverse(Cos(V));
	};
	Seden Gbl Seden::Cot(const Seden& V)
	{
		return Inverse(Tan(V));
	};
	Seden Gbl Seden::Sinh(const Seden& V)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return Ev::Sinh(Re); }
		double Sz = Abs(Im);
		Seden Or = Sgn(Im);
		return Ev::Sinh(Re) * Ev::Cos(Sz) + Ev::Cosh(Re) * Ev::Sin(Sz) * Or;
	};
	Seden Gbl Seden::Cosh(const Seden& V)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return Ev::Cosh(Re); }
		double Sz = Abs(Im);
		Seden Or = Sgn(Im);
		return Ev::Cosh(Re) * Ev::Cos(Sz) + Ev::Sinh(Re) * Ev::Sin(Sz) * Or;
	};
	Seden Gbl Seden::Tanh(const Seden& V)
	{
		double Re = Scalar(V);
		Seden Im = Vector(V);
		double Th = Ev::Tanh(Re);
		if (Im == Seden::Zero) { return Th; }
		double Sz = Abs(Im);
		Seden Or = Sgn(Im);
		double T = Ev::Tan(Sz);
		double Th2 = Th * Th;
		double T2 = T * T;
		return (Th * (1 - T2) + T * (1 + Th2) * Or) / (1 + Th2 * T2);
	};
	Seden Gbl Seden::Csch(const Seden& V)
	{
		return Inverse(Sinh(V));
	};
	Seden Gbl Seden::Sech(const Seden& V)
	{
		return Inverse(Cosh(V));
	};
	Seden Gbl Seden::Coth(const Seden& V)
	{
		return Inverse(Tanh(V));
	};
	Seden Gbl Seden::Arcsin(const Seden& V, bool S, std::int64_t P)
	{
		if (!S) { return Ev::PI - Arcsin(V, true, P); }
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
		Seden Or = Sgn(Im);
		return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
	};
	Seden Gbl Seden::Arcsin(const Seden& V)
	{
		return Arcsin(V, true, 0);
	};
	Seden Gbl Seden::Arccos(const Seden& V, bool S, std::int64_t P)
	{
		if (!S) { return 2 * Ev::PI - Arccos(V, true, P); }
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
		Seden Or = Sgn(Im);
		return -Or * Ln(V + Root(V * V - 1, 2), P);
	};
	Seden Gbl Seden::Arccos(const Seden& V)
	{
		return Arccos(V, true, 0);
	};
	Seden Gbl Seden::Arctan(const Seden& V, bool S, std::int64_t P)
	{
		if (!S) { return Ev::PI + Arctan(V, true, P); }
		double Re = Scalar(V);
		Seden Im = Vector(V);
		if (Im == Seden::Zero) { return 2 * Ev::PI * static_cast<double>(P) + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
		Seden Or = Sgn(Im);
		return 2 * Ev::PI * static_cast<double>(P) + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
	};
	Seden Gbl Seden::Arctan(const Seden& V)
	{
		return Arctan(V, true, 0);
	};
	Seden Gbl Seden::Arccsc(const Seden& V, bool S, std::int64_t P)
	{
		return Arcsin(Inverse(V), S, P);
	};
	Seden Gbl Seden::Arccsc(const Seden& V)
	{
		return Arccsc(V, true, 0);
	};
	Seden Gbl Seden::Arcsec(const Seden& V, bool S, std::int64_t P)
	{
		return Arccos(Inverse(V), S, P);
	};
	Seden Gbl Seden::Arcsec(const Seden& V)
	{
		return Arcsec(V, true, 0);
	};
	Seden Gbl Seden::Arccot(const Seden& V, bool S, std::int64_t P)
	{
		return Arctan(Inverse(V), S, P);
	};
	Seden Gbl Seden::Arccot(const Seden& V)
	{
		return Arccot(V, true, 0);
	};
	Seden Gbl Seden::Arcsinh(const Seden& V, bool S, std::int64_t P)
	{
		Seden Im = Vector(V);
		Seden Or = Sgn(Im);
		if (!S) { return Ev::PI * Or - Arcsinh(V, true, P); }
		return Ln(V + Root(V * V + 1, 2), P);
	};
	Seden Gbl Seden::Arcsinh(const Seden& V)
	{
		return Arcsinh(V, true, 0);
	};
	Seden Gbl Seden::Arccosh(const Seden& V, bool S, std::int64_t P)
	{
		Seden Im = Vector(V);
		Seden Or = Sgn(Im);
		if (!S) { return 2 * Ev::PI * Or - Arccosh(V, true, P); }
		return Ln(V + Root(V * V - 1, 2), P);
	};
	Seden Gbl Seden::Arccosh(const Seden& V)
	{
		return Arccosh(V, true, 0);
	};
	Seden Gbl Seden::Arctanh(const Seden& V, bool S, std::int64_t P)
	{
		Seden Im = Vector(V);
		Seden Or = Sgn(Im);
		if (!S) { return Ev::PI * Or + Arctan(V, true, P); }
		return 2 * Ev::PI * static_cast<double>(P) * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
	};
	Seden Gbl Seden::Arctanh(const Seden& V)
	{
		return Arctanh(V, true, 0);
	};
	Seden Gbl Seden::Arccsch(const Seden& V, bool S, std::int64_t P)
	{
		return Arcsinh(Inverse(V), S, P);
	};
	Seden Gbl Seden::Arccsch(const Seden& V)
	{
		return Arccsch(V, true, 0);
	};
	Seden Gbl Seden::Arcsech(const Seden& V, bool S, std::int64_t P)
	{
		return Arccosh(Inverse(V), S, P);
	};
	Seden Gbl Seden::Arcsech(const Seden& V)
	{
		return Arcsech(V, true, 0);
	};
	Seden Gbl Seden::Arccoth(const Seden& V, bool S, std::int64_t P)
	{
		return Arctanh(Inverse(V), S, P);
	};
	Seden Gbl Seden::Arccoth(const Seden& V)
	{
		return Arccoth(V, true, 0);
	};
	///
	/// conventions
	///
	String Gbl Seden::Str(const Seden& V)
	{
		std::size_t Dim{ V.Size };
		std::vector<double> Num(Dim);
		for (std::size_t i = 0; i < Dim; ++i)
		{
			Num[i] = V.Data[i];
		}
		std::wstring Rst = ToString(Num, Terms{ Dim });
		return String{ Rst.data() };
	};
	Seden Gbl Seden::Val(const String& V)
	{
		std::wstring Str = Replace(V.Ptr(), L" ", L"");
		if (Str == L"0") { return Seden::Zero; };
		std::size_t Dim{ 0 };
		std::wstring::const_iterator Suf{ Str.begin() };
		std::wstring::const_iterator End{ Str.end() };
		std::wsmatch Mat;
		while (std::regex_search(Suf, End, Mat, std::wregex(LR"(e(\d+)(?=-|\+|$))")))
		{
			std::size_t NewDim = stos_t(Mat.str(1));
			if (NewDim > Dim) { Dim = NewDim; }
			Suf = Mat.suffix().first;
		}
		Dim = Near(Dim);
		return Seden(ToNumbers(Str, Terms{ Dim }));
	};
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
