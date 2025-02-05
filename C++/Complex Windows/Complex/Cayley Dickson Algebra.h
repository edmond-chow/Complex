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
#pragma once
#include <cmath>
#include <cstdint>
#include <numbers>
struct Number
{
	///
	/// basis
	///
private:
	std::vector<double> Data;
public:
	Number(std::size_t Size)
		: Data(Size, 0)
	{};
	Number(const std::initializer_list<double>& Numbers)
		: Data{ Numbers }
	{};
	Number(const std::vector<double>& Numbers)
		: Data{ Numbers }
	{};
	Number(const Number& N)
		: Data{ N.Data }
	{};
	Number(Number&& N) noexcept
		: Data{ std::move(N.Data) }
	{};
	const std::vector<double>& operator ()() const&
	{
		return Data;
	};
	double& operator [](std::size_t i) &
	{
		return Data[i];
	};
	const double& operator [](std::size_t i) const&
	{
		return Data[i];
	};
	std::size_t Size() const&
	{
		return Data.size();
	};
	std::size_t Near() const&
	{
		std::size_t OriSize = Data.size();
		if (OriSize == 0) { return 0; }
		std::size_t Dim = OriSize - 1;
		int Shift = 0;
		while (Dim >> Shift != 0)
		{
			++Shift;
		}
		std::size_t Rst = 0b1;
		Rst <<= Shift;
		return Rst;
	};
	Number Retrieve(std::size_t Begin, std::size_t End) const&
	{
		std::size_t OriSize = Data.size();
		if (Begin >= End || End > OriSize) { return Number{}; }
		std::size_t Cap = End - Begin;
		Number Rst = Number(Cap);
		for (std::size_t i = 0; i < Cap; ++i)
		{
			Rst.Data[i] = Data[i + Begin];
		}
		return Rst;
	};
	Number L() const&
	{
		std::size_t OriSize = Data.size();
		return Retrieve(0, OriSize >> 1);
	};
	Number R() const&
	{
		std::size_t OriSize = Data.size();
		return Retrieve(OriSize >> 1, OriSize);
	};
	Number Extend(std::size_t Size) const&
	{
		std::size_t OriSize = Data.size();
		if (Size < OriSize) { Size = OriSize; }
		Number Rst = Number(Size);
		for (std::size_t i = 0; i < OriSize; ++i) { Rst.Data[i] = Data[i]; }
		return Rst;
	};
	Number InPlaceExtend(std::size_t Size) &
	{
		std::size_t OriSize = Data.size();
		while (Size < OriSize)
		{
			Data.push_back(0);
			++Size;
		}
		return *this;
	};
	static Number Merge(const Number& U, const Number& V)
	{
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		Number Rst = U.Extend(UOriSize + VOriSize);
		for (std::size_t i = 0; i < VOriSize; ++i)
		{
			Rst.Data[UOriSize + i] = V.Data[i];
		}
		return Rst;
	};
	///
	/// operators
	///
public:
	friend bool operator ==(const Number& U, const Number& V)
	{
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		if (UOriSize > VOriSize) { return V == U; }
		for (std::size_t i = 0; i < UOriSize; ++i)
		{
			if (U.Data[i] != V.Data[i]) { return false; }
		}
		for (std::size_t i = UOriSize; i < VOriSize; ++i)
		{
			if (V.Data[i] != 0) { return false; }
		}
		return true;
	};
	friend bool operator !=(const Number& U, const Number& V)
	{
		return !(U == V);
	};
	friend Number operator +(const Number& U, const Number& V)
	{
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		if (UOriSize > VOriSize) { return V + U; }
		Number Rst = V;
		for (std::size_t i = 0; i < UOriSize; ++i) { Rst.Data[i] += U.Data[i]; }
		return Rst;
	};
	Number& operator +=(const Number& O) &
	{
		std::size_t OOriSize = O.Data.size();
		InPlaceExtend(OOriSize);
		for (std::size_t i = 0; i < OOriSize; ++i) { Data[i] += O.Data[i]; }
		return *this;
	};
	friend Number operator -(const Number& V)
	{
		Number Rst = V;
		for (std::size_t i = 0; i < Rst.Data.size(); ++i) { Rst.Data[i] = -Rst.Data[i]; }
		return Rst;
	};
	friend Number operator -(const Number& U, const Number& V)
	{
		return U + (-V);
	};
	Number& operator -=(const Number& O) &
	{
		std::size_t OOriSize = O.Data.size();
		InPlaceExtend(OOriSize);
		for (std::size_t i = 0; i < OOriSize; ++i) { Data[i] -= O.Data[i]; }
		return *this;
	};
	friend Number operator ~(const Number& V)
	{
		Number Rst = V;
		for (std::size_t i = 1; i < Rst.Data.size(); ++i) { Rst.Data[i] = -Rst.Data[i]; }
		return Rst;
	};
	friend Number operator *(const Number& U, const Number& V)
	{
		std::size_t UNear = U.Near();
		std::size_t VNear = V.Near();
		std::size_t Near = UNear < VNear ? VNear : UNear;
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		if (UOriSize != Near) { return U.Extend(Near) * V; }
		else if (VOriSize != Near) { return U * V.Extend(Near); }
		else if (Near == 1) { return Number{ U[0] * V[0] }; }
		Number UL = U.L();
		Number UR = U.R();
		Number VL = V.L();
		Number VR = V.R();
		Number L = UL * VL - ~VR * UR;
		Number R = VR * UL + UR * ~VL;
		return Merge(L, R);
	};
	friend Number operator *(Number U, double V)
	{
		Number Rst = U;
		std::size_t UOriSize = U.Data.size();
		for (std::size_t i = 0; i < UOriSize; ++i) { Rst.Data[i] *= V; }
		return Rst;
	};
	friend Number operator *(double U, const Number& V)
	{
		return V * U;
	};
	Number& operator *=(double O) &
	{
		std::size_t OriSize = Data.size();
		for (std::size_t i = 0; i < OriSize; ++i) { Data[i] *= O; }
		return *this;
	};
	friend Number operator /(Number U, double V)
	{
		return U * (1 / V);
	};
	Number& operator /=(double O) &
	{
		for (std::size_t i = 0; i < Data.size(); ++i) { Data[i] /= O; }
		return *this;
	};
	///
	/// multiples
	///
public:
	static double Dot(const Number& U, const Number& V)
	{
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		if (UOriSize > VOriSize) { return Dot(V, U); }
		double Rst = 0;
		for (std::size_t i = 0; i < UOriSize; ++i)
		{
			Rst += U.Data[i] * V.Data[i];
		}
		return Rst;
	};
	static Number Cross(const Number& U, const Number& V)
	{
		std::size_t UNear = U.Near();
		std::size_t VNear = V.Near();
		std::size_t Near = UNear < VNear ? VNear : UNear;
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		if (UOriSize != Near) { return Cross(U.Extend(Near), V); }
		else if (VOriSize != Near) { return Cross(U, V.Extend(Near)); }
		Number X = U;
		Number Y = V;
		X[0] = 0;
		Y[0] = 0;
		Number Rst = X * Y;
		Rst[0] = 0;
		return Rst;
	};
	static Number Outer(const Number& U, const Number& V)
	{
		std::size_t UNear = U.Near();
		std::size_t VNear = V.Near();
		std::size_t Near = UNear < VNear ? VNear : UNear;
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		if (UOriSize != Near) { return Outer(U.Extend(Near), V); }
		else if (VOriSize != Near) { return Outer(U, V.Extend(Near)); }
		Number X = U;
		Number Y = V;
		X[0] = 0;
		Y[0] = 0;
		Number Rst = X * Y;
		Rst[0] = 0;
		X *= V[0];
		Y *= U[0];
		Rst -= X;
		Rst += Y;
		return Rst;
	};
	static Number Even(const Number& U, const Number& V)
	{
		std::size_t UNear = U.Near();
		std::size_t VNear = V.Near();
		std::size_t Near = UNear < VNear ? VNear : UNear;
		std::size_t UOriSize = U.Data.size();
		std::size_t VOriSize = V.Data.size();
		if (UOriSize != Near) { return Even(U.Extend(Near), V); }
		else if (VOriSize != Near) { return Even(U, V.Extend(Near)); }
		Number X = U;
		Number Y = V;
		X[0] = 0;
		Y[0] = 0;
		Number Rst = Number(VOriSize);
		X *= V[0];
		Y *= U[0];
		Rst += X;
		Rst += Y;
		Rst[0] = Dot(U, ~V);
		return Rst;
	};
};
struct Ev
{
public:
	static constexpr const double PI = std::numbers::pi;
	static constexpr const double E = std::numbers::e;
	static double Sqrt(double V)
	{
		return std::sqrt(V);
	};
	static double Exp(double V)
	{
		return std::exp(V);
	};
	static double Ln(double V)
	{
		return std::log(V);
	};
	static double Arccos(double V)
	{
		return std::acos(V);
	};
	static double Power(double U, double V)
	{
		return std::pow(U, V);
	};
	static double Sin(double V)
	{
		return std::sin(V);
	};
	static double Cos(double V)
	{
		return std::cos(V);
	};
	static double Tan(double V)
	{
		return std::tan(V);
	};
	static double Sinh(double V)
	{
		return std::sinh(V);
	};
	static double Cosh(double V)
	{
		return std::cosh(V);
	};
	static double Tanh(double V)
	{
		return std::tanh(V);
	};
};
