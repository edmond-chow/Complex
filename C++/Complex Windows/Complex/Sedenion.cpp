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
namespace Num
{
	class Seden
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
		std::vector<double> Data;
	public:
		I explicit Ths Seden()
			: Data(BasicSize, 0)
		{};
		I explicit Ths Seden(const std::initializer_list<double>& N)
			: Data{ N }
		{
			while (Data.size() < BasicSize) { Data.push_back(0); }
		};
		I Ths Seden(double V)
			: Data{ V }
		{
			while (Data.size() < BasicSize) { Data.push_back(0); }
		};
	private:
		explicit Seden(const std::vector<double>& N)
			: Data{ N }
		{};
	public:
		I Ths Seden(const Seden& Self) = default;
		I Ths Seden(Seden&& Self) = default;
		I Ths ~Seden() noexcept = default;
		static double I Gbl Scalar(const Seden& V)
		{
			return V[0];
		};
		static Seden I Gbl Vector(const Seden& V)
		{
			Seden Rst = V;
			Rst[0] = 0;
			return Rst;
		};
		///
		/// operators
		///
	public:
		I Seden Ths operator ()() const
		{
			return *this;
		};
		I double& Ths operator [](std::size_t i) &
		{
			return Data[i];
		};
		I const double& Ths operator [](std::size_t i) const&
		{
			return Data[i];
		};
		I Seden& Ths operator =(const Seden& O) = default;
		I Seden& Ths operator =(Seden&& O) = default;
		friend bool I Gbl operator ==(const Seden& U, const Seden& V);
		friend bool I Gbl operator !=(const Seden& U, const Seden& V);
		friend Seden I Gbl operator +(const Seden& V);
		friend Seden I Gbl operator -(const Seden& V);
		friend Seden I Gbl operator ~(const Seden& V);
		I Seden& Ths operator ++() &
		{
			++(*this)[0];
			return *this;
		};
		I Seden Ths operator ++(int) &
		{
			Seden Rst = *this;
			++(*this)[0];
			return Rst;
		};
		I Seden& Ths operator --() &
		{
			--(*this)[0];
			return *this;
		};
		I Seden Ths operator --(int) &
		{
			Seden Rst = *this;
			--(*this)[0];
			return Rst;
		};
		friend Seden I Gbl operator +(const Seden& U, const Seden& V);
		friend Seden I Gbl operator -(const Seden& U, const Seden& V);
		friend Seden I Gbl operator *(const Seden& U, const Seden& V);
		friend Seden I Gbl operator /(const Seden& U, const Seden& V);
		friend Seden I Gbl operator ^(const Seden& U, std::int64_t V);
		I Seden& Ths operator +=(const Seden& O) &
		{
			return *this = *this + O;
		};
		I Seden& Ths operator +=(const std::initializer_list<Seden>& O) &
		{
			for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this += *ite; }
			return *this;
		};
		I Seden& Ths operator -=(const Seden& O) &
		{
			return *this = *this - O;
		};
		I Seden& Ths operator -=(const std::initializer_list<Seden>& O) &
		{
			for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this -= *ite; }
			return *this;
		};
		I Seden& Ths operator *=(const Seden& O) &
		{
			return *this = *this * O;
		};
		I Seden& Ths operator *=(const std::initializer_list<Seden>& O) &
		{
			for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this *= *ite; }
			return *this;
		};
		I Seden& Ths operator /=(const Seden& O) &
		{
			return *this = *this / O;
		};
		I Seden& Ths operator /=(const std::initializer_list<Seden>& O) &
		{
			for (std::initializer_list<Seden>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this /= *ite; }
			return *this;
		};
		I Seden& Ths operator ^=(std::int64_t O) &
		{
			return *this = *this ^ O;
		};
		I Seden& Ths operator ^=(const std::initializer_list<std::int64_t>& O) &
		{
			for (std::initializer_list<std::int64_t>::const_iterator ite = O.begin(); ite != O.end(); ++ite) { *this ^= *ite; }
			return *this;
		};
		///
		/// multiples
		///
	public:
		static double I Gbl Dot(const Seden& U, const Seden& V)
		{
			return Number::Dot(U.Num(), V.Num());
		};
		static Seden I Gbl Outer(const Seden& U, const Seden& V)
		{
			return Seden::Val(Number::Outer(U.Num(), V.Num()));
		};
		static Seden I Gbl Even(const Seden& U, const Seden& V)
		{
			return Val(Number::Even(U.Num(), V.Num()));
		};
		static Seden I Gbl Cross(const Seden& U, const Seden& V)
		{
			return Seden::Val(Number::Cross(U.Num(), V.Num()));
		};
		///
		/// fundamentals
		///
	public:
		static double I Gbl Abs(const Seden& V)
		{
			return Ev::Sqrt(Dot(V, V));
		};
		static double I Gbl Arg(const Seden& V, std::int64_t P)
		{
			return Ev::Arccos(Scalar(V) / Abs(V)) + 2 * Ev::PI * P;
		};
		static double I Gbl Arg(const Seden& V)
		{
			return Arg(V, 0);
		};
		static Seden I Gbl Conjg(const Seden& V)
		{
			return ~V;
		};
		static Seden I Gbl Sgn(const Seden& V)
		{
			return V / Abs(V);
		};
		static Seden I Gbl Inverse(const Seden& V)
		{
			return Conjg(V) / Dot(V, V);
		};
		static Seden I Gbl Exp(const Seden& V)
		{
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return Ev::Exp(Re); }
			double Sz = Abs(Im);
			Seden Or = Sgn(Im);
			return Ev::Exp(Re) * (Ev::Cos(Sz) + Or * Ev::Sin(Sz));
		};
		static Seden I Gbl Ln(const Seden& V, std::int64_t P)
		{
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero)
			{
				if (Re >= 0) { return Ev::Ln(Re) + 2 * P * Ev::PI * i; }
				else { return Ev::Ln(-Re) + (2 * P + 1) * Ev::PI * i; }
			}
			Seden Or = Sgn(Im);
			return Ev::Ln(Abs(V)) + Or * Arg(V, P);
		};
		static Seden I Gbl Ln(const Seden& V)
		{
			return Ln(V, 0);
		};
		///
		/// exponentials
		///
	public:
		static Seden I Gbl Power(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
		{
			return Exp(Exp(Ln(V, z3) + Ln(Ln(U, z1), z2)));
		};
		static Seden I Gbl Power(const Seden& U, const Seden& V)
		{
			return Power(U, V, 0, 0, 0);
		};
		static Seden I Gbl Power(const Seden& U, double V, std::int64_t P)
		{
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero)
			{
				if (Re >= 0)
				{
					double Ai = 2 * P * Ev::PI * V;
					return Ev::Power(Re, V) * (Ev::Cos(Ai) + i * Ev::Sin(Ai));
				}
				else
				{
					double Ai = (2 * P + 1) * Ev::PI * V;
					return Ev::Power(-Re, V) * (Ev::Cos(Ai) + i * Ev::Sin(Ai));
				}
			}
			Seden Or = Sgn(Im);
			double A = Arg(U, P) * V;
			return Ev::Power(Abs(U), V) * (Ev::Cos(A) + Or * Ev::Sin(A));
		};
		static Seden I Gbl Power(const Seden& U, double V)
		{
			return Power(U, V, 0);
		};
		static Seden I Gbl Root(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3)
		{
			return Power(U, Inverse(V), z1, z2, z3);
		};
		static Seden I Gbl Root(const Seden& U, const Seden& V)
		{
			return Root(U, V, 0, 0, 0);
		};
		static Seden I Gbl Root(const Seden& U, double V, std::int64_t P)
		{
			return Power(U, 1 / V, P);
		};
		static Seden I Gbl Root(const Seden& U, double V)
		{
			return Root(U, V, 0);
		};
		static Seden I Gbl Log(const Seden& U, const Seden& V, std::int64_t z1, std::int64_t z2, std::int64_t z3, std::int64_t z4)
		{
			return Exp(Ln(Ln(V, z1), z3) - Ln(Ln(U, z2), z4));
		};
		static Seden I Gbl Log(const Seden& U, const Seden& V)
		{
			return Log(U, V, 0, 0, 0, 0);
		};
		///
		/// trigonometrics
		///
	public:
		static Seden I Gbl Sin(const Seden& V)
		{
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return Ev::Sin(Re); }
			double Sz = Abs(Im);
			Seden Or = Sgn(Im);
			return Ev::Sin(Re) * Ev::Cosh(Sz) + Ev::Cos(Re) * Ev::Sinh(Sz) * Or;
		};
		static Seden I Gbl Cos(const Seden& V)
		{
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return Ev::Cos(Re); }
			double Sz = Abs(Im);
			Seden Or = Sgn(Im);
			return Ev::Cos(Re) * Ev::Cosh(Sz) - Ev::Sin(Re) * Ev::Sinh(Sz) * Or;
		};
		static Seden I Gbl Tan(const Seden& V)
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
		static Seden I Gbl Csc(const Seden& V)
		{
			return Inverse(Sin(V));
		};
		static Seden I Gbl Sec(const Seden& V)
		{
			return Inverse(Cos(V));
		};
		static Seden I Gbl Cot(const Seden& V)
		{
			return Inverse(Tan(V));
		};
		static Seden I Gbl Sinh(const Seden& V)
		{
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return Ev::Sinh(Re); }
			double Sz = Abs(Im);
			Seden Or = Sgn(Im);
			return Ev::Sinh(Re) * Ev::Cos(Sz) + Ev::Cosh(Re) * Ev::Sin(Sz) * Or;
		};
		static Seden I Gbl Cosh(const Seden& V)
		{
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return Ev::Cosh(Re); }
			double Sz = Abs(Im);
			Seden Or = Sgn(Im);
			return Ev::Cosh(Re) * Ev::Cos(Sz) + Ev::Sinh(Re) * Ev::Sin(Sz) * Or;
		};
		static Seden I Gbl Tanh(const Seden& V)
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
		static Seden I Gbl Csch(const Seden& V)
		{
			return Inverse(Sinh(V));
		};
		static Seden I Gbl Sech(const Seden& V)
		{
			return Inverse(Cosh(V));
		};
		static Seden I Gbl Coth(const Seden& V)
		{
			return Inverse(Tanh(V));
		};
		static Seden I Gbl Arcsin(const Seden& V, bool S, std::int64_t P)
		{
			if (!S) { return Ev::PI - Arcsin(V, true, P); }
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
			Seden Or = Sgn(Im);
			return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
		};
		static Seden I Gbl Arcsin(const Seden& V)
		{
			return Arcsin(V, true, 0);
		};
		static Seden I Gbl Arccos(const Seden& V, bool S, std::int64_t P)
		{
			if (!S) { return 2 * Ev::PI - Arccos(V, true, P); }
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
			Seden Or = Sgn(Im);
			return -Or * Ln(V + Root(V * V - 1, 2), P);
		};
		static Seden I Gbl Arccos(const Seden& V)
		{
			return Arccos(V, true, 0);
		};
		static Seden I Gbl Arctan(const Seden& V, bool S, std::int64_t P)
		{
			if (!S) { return Ev::PI + Arctan(V, true, P); }
			double Re = Scalar(V);
			Seden Im = Vector(V);
			if (Im == Seden::Zero) { return 2 * Ev::PI * P + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
			Seden Or = Sgn(Im);
			return 2 * Ev::PI * P + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
		};
		static Seden I Gbl Arctan(const Seden& V)
		{
			return Arctan(V, true, 0);
		};
		static Seden I Gbl Arccsc(const Seden& V, bool S, std::int64_t P)
		{
			return Arcsin(Inverse(V), S, P);
		};
		static Seden I Gbl Arccsc(const Seden& V)
		{
			return Arccsc(V, true, 0);
		};
		static Seden I Gbl Arcsec(const Seden& V, bool S, std::int64_t P)
		{
			return Arccos(Inverse(V), S, P);
		};
		static Seden I Gbl Arcsec(const Seden& V)
		{
			return Arcsec(V, true, 0);
		};
		static Seden I Gbl Arccot(const Seden& V, bool S, std::int64_t P)
		{
			return Arctan(Inverse(V), S, P);
		};
		static Seden I Gbl Arccot(const Seden& V)
		{
			return Arccot(V, true, 0);
		};
		static Seden I Gbl Arcsinh(const Seden& V, bool S, std::int64_t P)
		{
			Seden Im = Vector(V);
			Seden Or = Sgn(Im);
			if (!S) { return Ev::PI * Or - Arcsinh(V, true, P); }
			return Ln(V + Root(V * V + 1, 2), P);
		};
		static Seden I Gbl Arcsinh(const Seden& V)
		{
			return Arcsinh(V, true, 0);
		};
		static Seden I Gbl Arccosh(const Seden& V, bool S, std::int64_t P)
		{
			Seden Im = Vector(V);
			Seden Or = Sgn(Im);
			if (!S) { return 2 * Ev::PI * Or - Arccosh(V, true, P); }
			return Ln(V + Root(V * V - 1, 2), P);
		};
		static Seden I Gbl Arccosh(const Seden& V)
		{
			return Arccosh(V, true, 0);
		};
		static Seden I Gbl Arctanh(const Seden& V, bool S, std::int64_t P)
		{
			Seden Im = Vector(V);
			Seden Or = Sgn(Im);
			if (!S) { return Ev::PI * Or + Arctan(V, true, P); }
			return 2 * Ev::PI * P * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
		};
		static Seden I Gbl Arctanh(const Seden& V)
		{
			return Arctanh(V, true, 0);
		};
		static Seden I Gbl Arccsch(const Seden& V, bool S, std::int64_t P)
		{
			return Arcsinh(Inverse(V), S, P);
		};
		static Seden I Gbl Arccsch(const Seden& V)
		{
			return Arccsch(V, true, 0);
		};
		static Seden I Gbl Arcsech(const Seden& V, bool S, std::int64_t P)
		{
			return Arccosh(Inverse(V), S, P);
		};
		static Seden I Gbl Arcsech(const Seden& V)
		{
			return Arcsech(V, true, 0);
		};
		static Seden I Gbl Arccoth(const Seden& V, bool S, std::int64_t P)
		{
			return Arctanh(Inverse(V), S, P);
		};
		static Seden I Gbl Arccoth(const Seden& V)
		{
			return Arccoth(V, true, 0);
		};
		///
		/// conventions
		///
		static std::wstring I Gbl Str(const Seden& V)
		{
			std::size_t Dim = V.Data.size();
			std::vector<std::wstring> Trm(Dim, L"e");
			for (std::size_t i = 0; i < Dim; ++i) { Trm[i] += std::to_wstring(i); }
			return ToString(V.Data, Trm);
		};
		static Seden I Gbl Val(const std::wstring& V)
		{
			std::wstring Str = Replace(V, L" ", L"");
			if (Str == L"0") { return Seden::Zero; };
			std::size_t Dim = 0;
			std::wstring Rest = Str;
			std::wsmatch Mat;
			while (std::regex_search(Rest, Mat, std::wregex(LR"(e(\d+)(?=-|\+|$))")))
			{
				Dim = std::max(Dim, stos_t(Mat.str(1)));
				Rest = Mat.suffix().str();
			}
			Dim = Near(Dim);
			std::vector<std::wstring> Trm(Dim, L"e");
			for (std::size_t i = 0; i < Dim; ++i) { Trm[i] += std::to_wstring(i); }
			return Seden(ToNumbers(Str, Trm));
		};
		///
		/// casing
		///
	private:
		Number Num() const&
		{
			return Number(Data);
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
	/// operators
	///
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
}
#pragma pop_macro("Ths")
#pragma pop_macro("Gbl")
#pragma pop_macro("I")
#pragma pack(pop)
