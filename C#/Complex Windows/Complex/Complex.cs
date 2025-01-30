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
using static Module;
namespace Num
{
    public struct Vec1D : INum
    {
        ///
        /// constants
        ///
        public static readonly Vec1D Zero = new Vec1D(0);
        public static readonly Vec1D e1 = new Vec1D(1);
        ///
        /// basis
        ///
        private double x1;
        public Vec1D(double e1)
        {
            x1 = e1;
        }
        public override string ToString()
        {
            double[] Numbers = new double[] { x1 };
            return Numbers.ToString("e1");
        }
        public override bool Equals(object obj)
        {
            if (obj is Vec1D o) { return this == o; }
            else { return false; }
        }
        public double this[int i]
        {
            get
            {
                switch (i)
                {
                    case 1: return x1;
                    default: return 0;
                }
            }
            set
            {
                switch (i)
                {
                    case 1: x1 = value; break;
                    default: break;
                }
            }
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public static explicit operator Vec1D(string V)
        {
            return Val(V);
        }
        public static explicit operator string(Vec1D V)
        {
            return Str(V);
        }
        ///
        /// operators
        ///
        public static bool operator ==(Vec1D U, Vec1D V)
        {
            return U.Num() == V.Num();
        }
        public static bool operator !=(Vec1D U, Vec1D V)
        {
            return !(U == V);
        }
        public static Vec1D operator +(Vec1D V)
        {
            return V;
        }
        public static Vec1D operator -(Vec1D V)
        {
            return Val(-V.Num());
        }
        public static Vec1D operator +(Vec1D U, Vec1D V)
        {
            return Val(U.Num() + V.Num());
        }
        public static Cmplx operator +(double U, Vec1D V)
        {
            return new Cmplx(U, V);
        }
        public static Cmplx operator +(Vec1D U, double V)
        {
            return V + U;
        }
        public static Vec1D operator -(Vec1D U, Vec1D V)
        {
            return Val(U.Num() - V.Num());
        }
        public static Cmplx operator -(double U, Vec1D V)
        {
            return U + (-V);
        }
        public static Cmplx operator -(Vec1D U, double V)
        {
            return U + (-V);
        }
        public static Vec1D operator *(Vec1D U, double V)
        {
            return Val(U.Num() * V);
        }
        public static Vec1D operator *(double U, Vec1D V)
        {
            return Val(U * V.Num());
        }
        public static Vec1D operator /(Vec1D U, double V)
        {
            return Val(U.Num() / V);
        }
        ///
        /// multiples
        ///
        public static double Dot(Vec1D U, Vec1D V)
        {
            return Number.Dot(U.Num(), V.Num());
        }
        public static Vec1D Cross(Vec1D U, Vec1D V)
        {
            return Val(Number.Cross(U.Num(), V.Num()));
        }
        ///
        /// fundamentals
        ///
        public static double Abs(Vec1D V)
        {
            return Ev.Sqrt(Dot(V, V));
        }
        public static Vec1D Sgn(Vec1D V)
        {
            return V / Abs(V);
        }
        ///
        /// conventions
        ///
        public static string Str(Vec1D V)
        {
            return V.ToString();
        }
        public static Vec1D Val(string V)
        {
            string Str = V.Replace(" ", "");
            Vec1D Rst = Zero;
            try { Str.ToNumbers(ref Rst, true, "e1"); }
            catch (Exception Ex) { throw new ArgumentException("The string cannot be converted as a number.", Ex); }
            return Rst;
        }
        ///
        /// casing
        ///
        internal Number Num()
        {
            return new Number(0, x1);
        }
        internal static Vec1D Val(Number N)
        {
            return new Vec1D(N[1]);
        }
    }
    public struct Cmplx : INum
    {
        ///
        /// constants
        ///
        public static readonly Cmplx Zero = new Cmplx(0, Vec1D.Zero);
        public static readonly Cmplx i = new Cmplx(0, Vec1D.e1);
        ///
        /// basis
        ///
        private double Re;
        private Vec1D Im;
        public Cmplx(double s, Vec1D v)
        {
            Re = s;
            Im = v;
        }
        public Cmplx(double s, double i)
        {
            Re = s;
            Im = new Vec1D(i);
        }
        public override string ToString()
        {
            double[] Numbers = new double[] { Re, Im[1] };
            return Numbers.ToString("", "i");
        }
        public override bool Equals(object obj)
        {
            if (obj is Cmplx o) { return this == o; }
            else { return false; }
        }
        public double this[int i]
        {
            get
            {
                switch (i)
                {
                    case 0: return Re;
                    default: return Im[i];
                }
            }
            set
            {
                switch (i)
                {
                    case 0: Re = value; break;
                    default: Im[i] = value; break;
                }
            }
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public static explicit operator Cmplx(string V)
        {
            return Val(V);
        }
        public static explicit operator string(Cmplx V)
        {
            return Str(V);
        }
        public static implicit operator Cmplx(double V)
        {
            return new Cmplx(V, Vec1D.Zero);
        }
        public static implicit operator Cmplx(Vec1D V)
        {
            return new Cmplx(0, V);
        }
        public static double Scalar(Cmplx V)
        {
            return V.Re;
        }
        public static Vec1D Vector(Cmplx V)
        {
            return V.Im;
        }
        ///
        /// operators
        ///
        public static bool operator ==(Cmplx U, Cmplx V)
        {
            return U.Num() == V.Num();
        }
        public static bool operator !=(Cmplx U, Cmplx V)
        {
            return !(U == V);
        }
        public static Cmplx operator +(Cmplx V)
        {
            return V;
        }
        public static Cmplx operator -(Cmplx V)
        {
            return Val(-V.Num());
        }
        public static Cmplx operator ~(Cmplx V)
        {
            return Val(~V.Num());
        }
        public static Cmplx operator ++(Cmplx V)
        {
            return V + 1;
        }
        public static Cmplx operator --(Cmplx V)
        {
            return V - 1;
        }
        public static Cmplx operator +(Cmplx U, Cmplx V)
        {
            return Val(U.Num() + V.Num());
        }
        public static Cmplx operator -(Cmplx U, Cmplx V)
        {
            return Val(U.Num() - V.Num());
        }
        public static Cmplx operator *(Cmplx U, Cmplx V)
        {
            return Val(U.Num() * V.Num());
        }
        public static Cmplx operator /(Cmplx U, Cmplx V)
        {
            if (Vector(V) == Vec1D.Zero) { return Val(U.Num() / Scalar(V)); }
            return U * Inverse(V);
        }
        public static Cmplx operator ^(Cmplx U, long V)
        {
            return Power(U, V);
        }
        ///
        /// multiples
        ///
        public static double Dot(Cmplx U, Cmplx V)
        {
            return Number.Dot(U.Num(), V.Num());
        }
        public static Vec1D Outer(Cmplx U, Cmplx V)
        {
            return Vec1D.Val(Number.Outer(U.Num(), V.Num()));
        }
        public static Cmplx Even(Cmplx U, Cmplx V)
        {
            return Val(Number.Even(U.Num(), V.Num()));
        }
        public static Vec1D Cross(Cmplx U, Cmplx V)
        {
            return Vec1D.Val(Number.Cross(U.Num(), V.Num()));
        }
        ///
        /// fundamentals
        ///
        public static double Abs(Cmplx V)
        {
            return Ev.Sqrt(Dot(V, V));
        }
        public static double Arg(Cmplx V, long P)
        {
            return Ev.Arccos(Scalar(V) / Abs(V)) + 2 * Ev.PI * P;
        }
        public static double Arg(Cmplx V)
        {
            return Arg(V, 0);
        }
        public static Cmplx Conjg(Cmplx V)
        {
            return ~V;
        }
        public static Cmplx Sgn(Cmplx V)
        {
            return V / Abs(V);
        }
        public static Cmplx Inverse(Cmplx V)
        {
            return Conjg(V) / Dot(V, V);
        }
        public static Cmplx Exp(Cmplx V)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return Ev.Exp(Re); }
            double Sz = Abs(Im);
            Cmplx Or = Sgn(Im);
            return Ev.Exp(Re) * (Ev.Cos(Sz) + Or * Ev.Sin(Sz));
        }
        public static Cmplx Ln(Cmplx V, long P)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero)
            {
                if (Re >= 0) { return Ev.Ln(Re) + 2 * P * Ev.PI * i; }
                else { return Ev.Ln(-Re) + (2 * P + 1) * Ev.PI * i; }
            }
            Cmplx Or = Sgn(Im);
            return Ev.Ln(Abs(V)) + Or * Arg(V, P);
        }
        public static Cmplx Ln(Cmplx V)
        {
            return Ln(V, 0);
        }
        ///
        /// exponentials
        ///
        public static Cmplx Power(Cmplx U, Cmplx V, long z1)
        {
            return Exp(V * Ln(U, z1));
        }
        public static Cmplx Power(Cmplx U, Cmplx V)
        {
            return Power(U, V, 0);
        }
        public static Cmplx Power(Cmplx U, double V, long P)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero)
            {
                if (Re >= 0)
                {
                    double Ai = 2 * P * Ev.PI * V;
                    return Ev.Power(Re, V) * (Ev.Cos(Ai) + i * Ev.Sin(Ai));
                }
                else
                {
                    double Ai = (2 * P + 1) * Ev.PI * V;
                    return Ev.Power(-Re, V) * (Ev.Cos(Ai) + i * Ev.Sin(Ai));
                }
            }
            Cmplx Or = Sgn(Im);
            double A = Arg(U, P) * V;
            return Ev.Power(Abs(U), V) * (Ev.Cos(A) + Or * Ev.Sin(A));
        }
        public static Cmplx Power(Cmplx U, double V)
        {
            return Power(U, V, 0);
        }
        public static Cmplx Root(Cmplx U, Cmplx V, long z1)
        {
            return Power(U, Inverse(V), z1);
        }
        public static Cmplx Root(Cmplx U, Cmplx V)
        {
            return Root(U, V, 0);
        }
        public static Cmplx Root(Cmplx U, double V, long P)
        {
            return Power(U, 1 / V, P);
        }
        public static Cmplx Root(Cmplx U, double V)
        {
            return Root(U, V, 0);
        }
        public static Cmplx Log(Cmplx U, Cmplx V, long z1, long z2)
        {
            return Ln(V, z1) / Ln(U, z2);
        }
        public static Cmplx Log(Cmplx U, Cmplx V)
        {
            return Log(U, V, 0, 0);
        }
        ///
        /// trigonometrics
        ///
        public static Cmplx Sin(Cmplx V)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return Ev.Sin(Re); }
            double Sz = Abs(Im);
            Cmplx Or = Sgn(Im);
            return Ev.Sin(Re) * Ev.Cosh(Sz) + Ev.Cos(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Cmplx Cos(Cmplx V)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return Ev.Cos(Re); }
            double Sz = Abs(Im);
            Cmplx Or = Sgn(Im);
            return Ev.Cos(Re) * Ev.Cosh(Sz) - Ev.Sin(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Cmplx Tan(Cmplx V)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            double T = Ev.Tan(Re);
            if (Im == Vec1D.Zero) { return T; }
            double Sz = Abs(Im);
            Cmplx Or = Sgn(Im);
            double Th = Ev.Tanh(Sz);
            double T2 = T * T;
            double Th2 = Th * Th;
            return (T * (1 - Th2) + Th * (1 + T2) * Or) / (1 + T2 * Th2);
        }
        public static Cmplx Csc(Cmplx V)
        {
            return Inverse(Sin(V));
        }
        public static Cmplx Sec(Cmplx V)
        {
            return Inverse(Cos(V));
        }
        public static Cmplx Cot(Cmplx V)
        {
            return Inverse(Tan(V));
        }
        public static Cmplx Sinh(Cmplx V)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return Ev.Sinh(Re); }
            double Sz = Abs(Im);
            Cmplx Or = Sgn(Im);
            return Ev.Sinh(Re) * Ev.Cos(Sz) + Ev.Cosh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Cmplx Cosh(Cmplx V)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return Ev.Cosh(Re); }
            double Sz = Abs(Im);
            Cmplx Or = Sgn(Im);
            return Ev.Cosh(Re) * Ev.Cos(Sz) + Ev.Sinh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Cmplx Tanh(Cmplx V)
        {
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            var Th = Ev.Tanh(Re);
            if (Im == Vec1D.Zero) { return Th; }
            double Sz = Abs(Im);
            Cmplx Or = Sgn(Im);
            var T = Ev.Tan(Sz);
            var Th2 = Th * Th;
            var T2 = T * T;
            return (Th * (1 - T2) + T * (1 + Th2) * Or) / (1 + Th2 * T2);
        }
        public static Cmplx Csch(Cmplx V)
        {
            return Inverse(Sinh(V));
        }
        public static Cmplx Sech(Cmplx V)
        {
            return Inverse(Cosh(V));
        }
        public static Cmplx Coth(Cmplx V)
        {
            return Inverse(Tanh(V));
        }
        public static Cmplx Arcsin(Cmplx V, bool S, long P)
        {
            if (!S) { return Ev.PI - Arcsin(V, true, P); }
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
            Cmplx Or = Sgn(Im);
            return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
        }
        public static Cmplx Arcsin(Cmplx V)
        {
            return Arcsin(V, true, 0);
        }
        public static Cmplx Arccos(Cmplx V, bool S, long P)
        {
            if (!S) { return 2 * Ev.PI - Arccos(V, true, P); }
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
            Cmplx Or = Sgn(Im);
            return -Or * Ln(V + Root(V * V - 1, 2), P);
        }
        public static Cmplx Arccos(Cmplx V)
        {
            return Arccos(V, true, 0);
        }
        public static Cmplx Arctan(Cmplx V, bool S, long P)
        {
            if (!S) { return Ev.PI + Arctan(V, true, P); }
            double Re = Scalar(V);
            Vec1D Im = Vector(V);
            if (Im == Vec1D.Zero) { return 2 * Ev.PI * P + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
            Cmplx Or = Sgn(Im);
            return 2 * Ev.PI * P + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
        }
        public static Cmplx Arctan(Cmplx V)
        {
            return Arctan(V, true, 0);
        }
        public static Cmplx Arccsc(Cmplx V, bool S, long P)
        {
            return Arcsin(Inverse(V), S, P);
        }
        public static Cmplx Arccsc(Cmplx V)
        {
            return Arccsc(V, true, 0);
        }
        public static Cmplx Arcsec(Cmplx V, bool S, long P)
        {
            return Arccos(Inverse(V), S, P);
        }
        public static Cmplx Arcsec(Cmplx V)
        {
            return Arcsec(V, true, 0);
        }
        public static Cmplx Arccot(Cmplx V, bool S, long P)
        {
            return Arctan(Inverse(V), S, P);
        }
        public static Cmplx Arccot(Cmplx V)
        {
            return Arccot(V, true, 0);
        }
        public static Cmplx Arcsinh(Cmplx V, bool S, long P)
        {
            Vec1D Im = Vector(V);
            Cmplx Or = Sgn(Im);
            if (!S) { return Ev.PI * Or - Arcsinh(V, true, P); }
            return Ln(V + Root(V * V + 1, 2), P);
        }
        public static Cmplx Arcsinh(Cmplx V)
        {
            return Arcsinh(V, true, 0);
        }
        public static Cmplx Arccosh(Cmplx V, bool S, long P)
        {
            Vec1D Im = Vector(V);
            Cmplx Or = Sgn(Im);
            if (!S) { return 2 * Ev.PI * Or - Arccosh(V, true, P); }
            return Ln(V + Root(V * V - 1, 2), P);
        }
        public static Cmplx Arccosh(Cmplx V)
        {
            return Arccosh(V, true, 0);
        }
        public static Cmplx Arctanh(Cmplx V, bool S, long P)
        {
            Vec1D Im = Vector(V);
            Cmplx Or = Sgn(Im);
            if (!S) { return Ev.PI * Or + Arctan(V, true, P); }
            return 2 * Ev.PI * P * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
        }
        public static Cmplx Arctanh(Cmplx V)
        {
            return Arctanh(V, true, 0);
        }
        public static Cmplx Arccsch(Cmplx V, bool S, long P)
        {
            return Arcsinh(Inverse(V), S, P);
        }
        public static Cmplx Arccsch(Cmplx V)
        {
            return Arccsch(V, true, 0);
        }
        public static Cmplx Arcsech(Cmplx V, bool S, long P)
        {
            return Arccosh(Inverse(V), S, P);
        }
        public static Cmplx Arcsech(Cmplx V)
        {
            return Arcsech(V, true, 0);
        }
        public static Cmplx Arccoth(Cmplx V, bool S, long P)
        {
            return Arctanh(Inverse(V), S, P);
        }
        public static Cmplx Arccoth(Cmplx V)
        {
            return Arccoth(V, true, 0);
        }
        ///
        /// conventions
        ///
        public static string Str(Cmplx V)
        {
            return V.ToString();
        }
        public static Cmplx Val(string V)
        {
            string Str = V.Replace(" ", "");
            Cmplx Rst = Zero;
            try { Str.ToNumbers(ref Rst, false, "", "i"); }
            catch (Exception Ex) { throw new ArgumentException("The string cannot be converted as a number.", Ex); }
            return Rst;
        }
        ///
        /// casing
        ///
        internal Number Num()
        {
            return new Number(Re, Im[1]);
        }
        internal static Cmplx Val(Number N)
        {
            return new Cmplx(N[0], N[1]);
        }
    }
}
