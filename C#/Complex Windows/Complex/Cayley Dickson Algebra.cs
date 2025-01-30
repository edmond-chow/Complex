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
using System;
using System.Collections.Generic;
public class Number
{
    ///
    /// basis
    ///
    private readonly List<double> Data;
    public Number(int Size)
    {
        if (Size < 1) { Size = 1; }
        Data = new List<double>(new double[Size]);
    }
    public Number(IEnumerable<double> Numbers)
    {
        Data = new List<double>(Numbers);
        if (Data.Count == 0) { Data.Add(0); }
    }
    public Number(params double[] Numbers)
    {
        Data = new List<double>(Numbers);
        if (Data.Count == 0) { Data.Add(0); }
    }
    public double this[int i]
    {
        get { return Data[i]; }
        set { Data[i] = value; }
    }
    public int Size
    {
        get { return Data.Count; }
    }
    public int Near
    {
        get
        {
            int Dim = Data.Count - 1;
            int Shift = 0;
            while (Dim >> Shift != 0)
            {
                ++Shift;
            }
            return 0b1 << Shift;
        }
    }
    public Number Clone()
    {
        return new Number(Data);
    }
    public Number GetMemberwiseClone()
    {
        return this;
    }
    public Number Retrieve(int Begin, int End)
    {
        if (Begin < 0 || End > Size) { return null; }
        int Cap = End - Begin;
        Number Result = new Number(Cap);
        for (int i = 0; i < Cap; ++i)
        {
            Result.Data[i] = Data[i + Begin];
        }
        return Result;
    }
    public Number L
    {
        get { return Retrieve(0, Size >> 1); }
    }
    public Number R
    {
        get { return Retrieve(Size >> 1, Size); }
    }
    public Number Extend(int Size)
    {
        if (Size < Data.Count) { Size = Data.Count; }
        Number Result = new Number(Size);
        for (int i = 0; i < Data.Count; ++i) { Result.Data[i] = Data[i]; }
        return Result;
    }
    public static Number Merge(Number U, Number V)
    {
        Number Result = U.Clone();
        Result.Data.AddRange(V.Data);
        return Result;
    }
    public override bool Equals(object obj)
    {
        if (obj as Number == this) { return true; }
        return false;
    }
    public override int GetHashCode()
    {
        return base.GetHashCode();
    }
    ///
    /// operators
    ///
    public static bool operator ==(Number U, Number V)
    {
        if (U.Data.Count > V.Data.Count) { return V == U; }
        for (int i = 0; i < U.Data.Count; ++i)
        {
            if (U.Data[i] != V.Data[i]) { return false; }
        }
        for (int i = U.Data.Count; i < V.Data.Count; ++i)
        {
            if (V.Data[i] != 0) { return false; }
        }
        return true;
    }
    public static bool operator !=(Number U, Number V)
    {
        return !(U == V);
    }
    public static Number operator +(Number U, Number V)
    {
        if (U.Data.Count > V.Data.Count) { return V + U; }
        Number Result = V.Clone();
        for (int i = 0; i < U.Data.Count; ++i) { Result.Data[i] += U.Data[i]; }
        return Result;
    }
    public static Number operator -(Number V)
    {
        Number Result = V.Clone();
        for (int i = 0; i < Result.Data.Count; ++i) { Result.Data[i] = -Result.Data[i]; }
        return Result;
    }
    public static Number operator -(Number U, Number V)
    {
        return U + (-V);
    }
    public static Number operator ~(Number V)
    {
        Number Result = V.Clone();
        for (int i = 1; i < Result.Data.Count; ++i) { Result.Data[i] = -Result.Data[i]; }
        return Result;
    }
    public static Number operator *(Number U, Number V)
    {
        int Near = U.Near < V.Near ? V.Near : U.Near;
        if (U.Size != Near) { return U.Extend(Near) * V; }
        else if (V.Size != Near) { return U * V.Extend(Near); }
        else if (Near == 1) {  return new Number(U[0] * V[0]); }
        Number L = U.L * V.L - ~V.R * U.R;
        Number R = V.R * U.L + U.R * ~V.L;
        return Merge(L, R);
    }
    public static Number operator *(Number U, double V)
    {
        Number Result = U.Clone();
        for (int i = 0; i < U.Data.Count; ++i) { Result.Data[i] *= V; }
        return Result;
    }
    public static Number operator *(double U, Number V)
    {
        return V * U;
    }
    public static Number operator /(Number U, double V)
    {
        return U * (1 / V);
    }
    ///
    /// multiples
    ///
    public static double Dot(Number U, Number V)
    {
        if (U.Data.Count > V.Data.Count) { return Dot(V, U); }
        double Result = 0;
        for (int i = 0; i < U.Data.Count; ++i)
        {
            Result += U.Data[i] * V.Data[i];
        }
        return Result;
    }
    public static Number Cross(Number U, Number V)
    {
        int Near = U.Near < V.Near ? V.Near : U.Near;
        if (U.Size != Near) { return Cross(U.Extend(Near), V); }
        else if (V.Size != Near) { return Cross(U, V.Extend(Near)); }
        Number X = U.Clone();
        Number Y = V.Clone();
        X[0] = 0;
        Y[0] = 0;
        Number Result = X * Y;
        Result[0] = 0;
        return Result;
    }
    public static Number Outer(Number U, Number V)
    {
        int Near = U.Near < V.Near ? V.Near : U.Near;
        if (U.Size != Near) { return Outer(U.Extend(Near), V); }
        else if (V.Size != Near) { return Outer(U, V.Extend(Near)); }
        Number X = U.Clone();
        Number Y = V.Clone();
        X[0] = 0;
        Y[0] = 0;
        Number Result = X * Y;
        Result[0] = 0;
        X *= V[0];
        Y *= U[0];
        Result -= X;
        Result += Y;
        return Result;
    }
    public static Number Even(Number U, Number V)
    {
        int Near = U.Near < V.Near ? V.Near : U.Near;
        if (U.Size != Near) { return Even(U.Extend(Near), V); }
        else if (V.Size != Near) { return Even(U, V.Extend(Near)); }
        Number X = U.Clone();
        Number Y = V.Clone();
        X[0] = 0;
        Y[0] = 0;
        Number Result = new Number(V.Size);
        X *= V[0];
        Y *= U[0];
        Result += X;
        Result += Y;
        Result[0] = Dot(U, ~V);
        return Result;
    }
}
internal class Ev
{
    public const double PI = Math.PI;
    public const double E = Math.E;
    public static double Sqrt(double V)
    {
        return Math.Sqrt(V);
    }
    public static double Exp(double V)
    {
        return Math.Exp(V);
    }
    public static double Ln(double V)
    {
        return Math.Log(V);
    }
    public static double Arccos(double V)
    {
        return Math.Acos(V);
    }
    public static double Power(double U, double V)
    {
        return Math.Pow(U, V);
    }
    public static double Sin(double V)
    {
        return Math.Sin(V);
    }
    public static double Cos(double V)
    {
        return Math.Cos(V);
    }
    public static double Tan(double V)
    {
        return Math.Tan(V);
    }
    public static double Sinh(double V)
    {
        return Math.Sinh(V);
    }
    public static double Cosh(double V)
    {
        return Math.Cosh(V);
    }
    public static double Tanh(double V)
    {
        return Math.Tanh(V);
    }
}
