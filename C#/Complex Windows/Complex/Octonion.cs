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
    public struct Vec7D : INum
    {
        ///
        /// constants
        ///
        public static readonly Vec7D Zero = new Vec7D(0, 0, 0, 0, 0, 0, 0);
        public static readonly Vec7D e1 = new Vec7D(1, 0, 0, 0, 0, 0, 0);
        public static readonly Vec7D e2 = new Vec7D(0, 1, 0, 0, 0, 0, 0);
        public static readonly Vec7D e3 = new Vec7D(0, 0, 1, 0, 0, 0, 0);
        public static readonly Vec7D e4 = new Vec7D(0, 0, 0, 1, 0, 0, 0);
        public static readonly Vec7D e5 = new Vec7D(0, 0, 0, 0, 1, 0, 0);
        public static readonly Vec7D e6 = new Vec7D(0, 0, 0, 0, 0, 1, 0);
        public static readonly Vec7D e7 = new Vec7D(0, 0, 0, 0, 0, 0, 1);
        ///
        /// basis
        ///
        private double x1;
        private double x2;
        private double x3;
        private double x4;
        private double x5;
        private double x6;
        private double x7;
        public Vec7D(double e1, double e2, double e3, double e4, double e5, double e6, double e7)
        {
            x1 = e1;
            x2 = e2;
            x3 = e3;
            x4 = e4;
            x5 = e5;
            x6 = e6;
            x7 = e7;
        }
        public override string ToString()
        {
            double[] Numbers = new double[] { x1, x2, x3, x4, x5, x6, x7 };
            return Numbers.ToString("e1", "e2", "e3", "e4", "e5", "e6", "e7");
        }
        public override bool Equals(object obj)
        {
            if (obj is Vec7D o) { return this == o; }
            else { return false; }
        }
        public double this[int i]
        {
            get
            {
                switch (i)
                {
                    case 1: return x1;
                    case 2: return x2;
                    case 3: return x3;
                    case 4: return x4;
                    case 5: return x5;
                    case 6: return x6;
                    case 7: return x7;
                    default: return 0;
                }
            }
            set
            {
                switch (i)
                {
                    case 1: x1 = value; break;
                    case 2: x2 = value; break;
                    case 3: x3 = value; break;
                    case 4: x4 = value; break;
                    case 5: x5 = value; break;
                    case 6: x6 = value; break;
                    case 7: x7 = value; break;
                    default: break;
                }
            }
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public static explicit operator Vec7D(string V)
        {
            return Val(V);
        }
        public static explicit operator string(Vec7D V)
        {
            return Str(V);
        }
        ///
        /// operators
        ///
        public static bool operator ==(Vec7D U, Vec7D V)
        {
            return U.Num() == V.Num();
        }
        public static bool operator !=(Vec7D U, Vec7D V)
        {
            return !(U == V);
        }
        public static Vec7D operator +(Vec7D V)
        {
            return V;
        }
        public static Vec7D operator -(Vec7D V)
        {
            return Val(-V.Num());
        }
        public static Vec7D operator +(Vec7D U, Vec7D V)
        {
            return Val(U.Num() + V.Num());
        }
        public static Octon operator +(double U, Vec7D V)
        {
            return new Octon(U, V);
        }
        public static Octon operator +(Vec7D U, double V)
        {
            return V + U;
        }
        public static Vec7D operator -(Vec7D U, Vec7D V)
        {
            return Val(U.Num() - V.Num());
        }
        public static Octon operator -(double U, Vec7D V)
        {
            return U + (-V);
        }
        public static Octon operator -(Vec7D U, double V)
        {
            return U + (-V);
        }
        public static Vec7D operator *(Vec7D U, double V)
        {
            return Val(U.Num() * V);
        }
        public static Vec7D operator *(double U, Vec7D V)
        {
            return Val(U * V.Num());
        }
        public static Vec7D operator /(Vec7D U, double V)
        {
            return Val(U.Num() / V);
        }
        ///
        /// multiples
        ///
        public static double Dot(Vec7D U, Vec7D V)
        {
            return Number.Dot(U.Num(), V.Num());
        }
        public static Vec7D Cross(Vec7D U, Vec7D V)
        {
            return Val(Number.Cross(U.Num(), V.Num()));
        }
        ///
        /// fundamentals
        ///
        public static double Abs(Vec7D V)
        {
            return Ev.Sqrt(Dot(V, V));
        }
        public static Vec7D Sgn(Vec7D V)
        {
            return V / Abs(V);
        }
        ///
        /// conventions
        ///
        public static string Str(Vec7D V)
        {
            return V.ToString();
        }
        public static Vec7D Val(string V)
        {
            string Str = V.Replace(" ", "");
            Vec7D Rst = Zero;
            try { Str.ToNumbers(ref Rst, true, "e1", "e2", "e3", "e4", "e5", "e6", "e7"); }
            catch (Exception Ex) { throw new ArgumentException("The string cannot be converted as a number.", Ex); }
            return Rst;
        }
        ///
        /// casing
        ///
        internal Number Num()
        {
            return new Number(0, x1, x2, x3, x4, x5, x6, x7);
        }
        internal static Vec7D Val(Number N)
        {
            return new Vec7D(N[1], N[2], N[3], N[4], N[5], N[6], N[7]);
        }
    }
    public struct Octon : INum
    {
        ///
        /// constants
        ///
        public static readonly Octon Zero = new Octon(0, Vec7D.Zero);
        public static readonly Octon i = new Octon(0, Vec7D.e1);
        public static readonly Octon j = new Octon(0, Vec7D.e2);
        public static readonly Octon k = new Octon(0, Vec7D.e3);
        public static readonly Octon l = new Octon(0, Vec7D.e4);
        public static readonly Octon il = new Octon(0, Vec7D.e5);
        public static readonly Octon jl = new Octon(0, Vec7D.e6);
        public static readonly Octon kl = new Octon(0, Vec7D.e7);
        ///
        /// basis
        ///
        private double Re;
        private Vec7D Im;
        public Octon(double s, Vec7D v)
        {
            Re = s;
            Im = v;
        }
        public Octon(double s, double i, double j, double k, double l, double il, double jl, double kl)
        {
            Re = s;
            Im = new Vec7D(i, j, k, l, il, jl, kl);
        }
        public override string ToString()
        {
            double[] Numbers = new double[] { Re, Im[1], Im[2], Im[3], Im[4], Im[5], Im[6], Im[7] };
            return Numbers.ToString("", "i", "j", "k", "l", "il", "jl", "kl");
        }
        public override bool Equals(object obj)
        {
            if (obj is Octon o) { return this == o; }
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
        public static explicit operator Octon(string V)
        {
            return Val(V);
        }
        public static explicit operator string(Octon V)
        {
            return Str(V);
        }
        public static implicit operator Octon(double V)
        {
            return new Octon(V, Vec7D.Zero);
        }
        public static implicit operator Octon(Vec7D V)
        {
            return new Octon(0, V);
        }
        public static double Scalar(Octon V)
        {
            return V.Re;
        }
        public static Vec7D Vector(Octon V)
        {
            return V.Im;
        }
        ///
        /// operators
        ///
        public static bool operator ==(Octon U, Octon V)
        {
            return U.Num() == V.Num();
        }
        public static bool operator !=(Octon U, Octon V)
        {
            return !(U == V);
        }
        public static Octon operator +(Octon V)
        {
            return V;
        }
        public static Octon operator -(Octon V)
        {
            return Val(-V.Num());
        }
        public static Octon operator ~(Octon V)
        {
            return Val(~V.Num());
        }
        public static Octon operator ++(Octon V)
        {
            return V + 1;
        }
        public static Octon operator --(Octon V)
        {
            return V - 1;
        }
        public static Octon operator +(Octon U, Octon V)
        {
            return Val(U.Num() + V.Num());
        }
        public static Octon operator -(Octon U, Octon V)
        {
            return Val(U.Num() - V.Num());
        }
        public static Octon operator *(Octon U, Octon V)
        {
            return Val(U.Num() * V.Num());
        }
        public static Octon operator /(Octon U, Octon V)
        {
            if (Vector(V) == Vec7D.Zero) { return Val(U.Num() / Scalar(V)); }
            return U * Inverse(V);
        }
        public static Octon operator ^(Octon U, long V)
        {
            return Power(U, V);
        }
        ///
        /// multiples
        ///
        public static double Dot(Octon U, Octon V)
        {
            return Number.Dot(U.Num(), V.Num());
        }
        public static Vec7D Outer(Octon U, Octon V)
        {
            return Vec7D.Val(Number.Outer(U.Num(), V.Num()));
        }
        public static Octon Even(Octon U, Octon V)
        {
            return Val(Number.Even(U.Num(), V.Num()));
        }
        public static Vec7D Cross(Octon U, Octon V)
        {
            return Vec7D.Val(Number.Cross(U.Num(), V.Num()));
        }
        ///
        /// fundamentals
        ///
        public static double Abs(Octon V)
        {
            return Ev.Sqrt(Dot(V, V));
        }
        public static double Arg(Octon V, long P)
        {
            return Ev.Arccos(Scalar(V) / Abs(V)) + 2 * Ev.PI * P;
        }
        public static double Arg(Octon V)
        {
            return Arg(V, 0);
        }
        public static Octon Conjg(Octon V)
        {
            return ~V;
        }
        public static Octon Sgn(Octon V)
        {
            return V / Abs(V);
        }
        public static Octon Inverse(Octon V)
        {
            return Conjg(V) / Dot(V, V);
        }
        public static Octon Exp(Octon V)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return Ev.Exp(Re); }
            double Sz = Abs(Im);
            Octon Or = Sgn(Im);
            return Ev.Exp(Re) * (Ev.Cos(Sz) + Or * Ev.Sin(Sz));
        }
        public static Octon Ln(Octon V, long P)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero)
            {
                if (Re >= 0) { return Ev.Ln(Re) + 2 * P * Ev.PI * i; }
                else { return Ev.Ln(-Re) + (2 * P + 1) * Ev.PI * i; }
            }
            Octon Or = Sgn(Im);
            return Ev.Ln(Abs(V)) + Or * Arg(V, P);
        }
        public static Octon Ln(Octon V)
        {
            return Ln(V, 0);
        }
        ///
        /// exponentials
        ///
        public static Octon Power(Octon U, Octon V, long z1, long z2, long z3)
        {
            return Exp(Exp(Ln(V, z3) + Ln(Ln(U, z1), z2)));
        }
        public static Octon Power(Octon U, Octon V)
        {
            return Power(U, V, 0, 0, 0);
        }
        public static Octon Power(Octon U, double V, long P)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero)
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
            Octon Or = Sgn(Im);
            double A = Arg(U, P) * V;
            return Ev.Power(Abs(U), V) * (Ev.Cos(A) + Or * Ev.Sin(A));
        }
        public static Octon Power(Octon U, double V)
        {
            return Power(U, V, 0);
        }
        public static Octon Root(Octon U, Octon V, long z1, long z2, long z3)
        {
            return Power(U, Inverse(V), z1, z2, z3);
        }
        public static Octon Root(Octon U, Octon V)
        {
            return Root(U, V, 0, 0, 0);
        }
        public static Octon Root(Octon U, double V, long P)
        {
            return Power(U, 1 / V, P);
        }
        public static Octon Root(Octon U, double V)
        {
            return Root(U, V, 0);
        }
        public static Octon Log(Octon U, Octon V, long z1, long z2, long z3, long z4)
        {
            return Exp(Ln(Ln(V, z1), z3) - Ln(Ln(U, z2), z4));
        }
        public static Octon Log(Octon U, Octon V)
        {
            return Log(U, V, 0, 0, 0, 0);
        }
        ///
        /// trigonometrics
        ///
        public static Octon Sin(Octon V)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return Ev.Sin(Re); }
            double Sz = Abs(Im);
            Octon Or = Sgn(Im);
            return Ev.Sin(Re) * Ev.Cosh(Sz) + Ev.Cos(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Octon Cos(Octon V)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return Ev.Cos(Re); }
            double Sz = Abs(Im);
            Octon Or = Sgn(Im);
            return Ev.Cos(Re) * Ev.Cosh(Sz) - Ev.Sin(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Octon Tan(Octon V)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            double T = Ev.Tan(Re);
            if (Im == Vec7D.Zero) { return T; }
            double Sz = Abs(Im);
            Octon Or = Sgn(Im);
            double Th = Ev.Tanh(Sz);
            double T2 = T * T;
            double Th2 = Th * Th;
            return (T * (1 - Th2) + Th * (1 + T2) * Or) / (1 + T2 * Th2);
        }
        public static Octon Csc(Octon V)
        {
            return Inverse(Sin(V));
        }
        public static Octon Sec(Octon V)
        {
            return Inverse(Cos(V));
        }
        public static Octon Cot(Octon V)
        {
            return Inverse(Tan(V));
        }
        public static Octon Sinh(Octon V)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return Ev.Sinh(Re); }
            double Sz = Abs(Im);
            Octon Or = Sgn(Im);
            return Ev.Sinh(Re) * Ev.Cos(Sz) + Ev.Cosh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Octon Cosh(Octon V)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return Ev.Cosh(Re); }
            double Sz = Abs(Im);
            Octon Or = Sgn(Im);
            return Ev.Cosh(Re) * Ev.Cos(Sz) + Ev.Sinh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Octon Tanh(Octon V)
        {
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            var Th = Ev.Tanh(Re);
            if (Im == Vec7D.Zero) { return Th; }
            double Sz = Abs(Im);
            Octon Or = Sgn(Im);
            var T = Ev.Tan(Sz);
            var Th2 = Th * Th;
            var T2 = T * T;
            return (Th * (1 - T2) + T * (1 + Th2) * Or) / (1 + Th2 * T2);
        }
        public static Octon Csch(Octon V)
        {
            return Inverse(Sinh(V));
        }
        public static Octon Sech(Octon V)
        {
            return Inverse(Cosh(V));
        }
        public static Octon Coth(Octon V)
        {
            return Inverse(Tanh(V));
        }
        public static Octon Arcsin(Octon V, bool S, long P)
        {
            if (!S) { return Ev.PI - Arcsin(V, true, P); }
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
            Octon Or = Sgn(Im);
            return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
        }
        public static Octon Arcsin(Octon V)
        {
            return Arcsin(V, true, 0);
        }
        public static Octon Arccos(Octon V, bool S, long P)
        {
            if (!S) { return 2 * Ev.PI - Arccos(V, true, P); }
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
            Octon Or = Sgn(Im);
            return -Or * Ln(V + Root(V * V - 1, 2), P);
        }
        public static Octon Arccos(Octon V)
        {
            return Arccos(V, true, 0);
        }
        public static Octon Arctan(Octon V, bool S, long P)
        {
            if (!S) { return Ev.PI + Arctan(V, true, P); }
            double Re = Scalar(V);
            Vec7D Im = Vector(V);
            if (Im == Vec7D.Zero) { return 2 * Ev.PI * P + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
            Octon Or = Sgn(Im);
            return 2 * Ev.PI * P + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
        }
        public static Octon Arctan(Octon V)
        {
            return Arctan(V, true, 0);
        }
        public static Octon Arccsc(Octon V, bool S, long P)
        {
            return Arcsin(Inverse(V), S, P);
        }
        public static Octon Arccsc(Octon V)
        {
            return Arccsc(V, true, 0);
        }
        public static Octon Arcsec(Octon V, bool S, long P)
        {
            return Arccos(Inverse(V), S, P);
        }
        public static Octon Arcsec(Octon V)
        {
            return Arcsec(V, true, 0);
        }
        public static Octon Arccot(Octon V, bool S, long P)
        {
            return Arctan(Inverse(V), S, P);
        }
        public static Octon Arccot(Octon V)
        {
            return Arccot(V, true, 0);
        }
        public static Octon Arcsinh(Octon V, bool S, long P)
        {
            Vec7D Im = Vector(V);
            Octon Or = Sgn(Im);
            if (!S) { return Ev.PI * Or - Arcsinh(V, true, P); }
            return Ln(V + Root(V * V + 1, 2), P);
        }
        public static Octon Arcsinh(Octon V)
        {
            return Arcsinh(V, true, 0);
        }
        public static Octon Arccosh(Octon V, bool S, long P)
        {
            Vec7D Im = Vector(V);
            Octon Or = Sgn(Im);
            if (!S) { return 2 * Ev.PI * Or - Arccosh(V, true, P); }
            return Ln(V + Root(V * V - 1, 2), P);
        }
        public static Octon Arccosh(Octon V)
        {
            return Arccosh(V, true, 0);
        }
        public static Octon Arctanh(Octon V, bool S, long P)
        {
            Vec7D Im = Vector(V);
            Octon Or = Sgn(Im);
            if (!S) { return Ev.PI * Or + Arctan(V, true, P); }
            return 2 * Ev.PI * P * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
        }
        public static Octon Arctanh(Octon V)
        {
            return Arctanh(V, true, 0);
        }
        public static Octon Arccsch(Octon V, bool S, long P)
        {
            return Arcsinh(Inverse(V), S, P);
        }
        public static Octon Arccsch(Octon V)
        {
            return Arccsch(V, true, 0);
        }
        public static Octon Arcsech(Octon V, bool S, long P)
        {
            return Arccosh(Inverse(V), S, P);
        }
        public static Octon Arcsech(Octon V)
        {
            return Arcsech(V, true, 0);
        }
        public static Octon Arccoth(Octon V, bool S, long P)
        {
            return Arctanh(Inverse(V), S, P);
        }
        public static Octon Arccoth(Octon V)
        {
            return Arccoth(V, true, 0);
        }
        ///
        /// conventions
        ///
        public static string Str(Octon V)
        {
            return V.ToString();
        }
        public static Octon Val(string V)
        {
            string Str = V.Replace(" ", "");
            Octon Rst = Zero;
            try { Str.ToNumbers(ref Rst, false, "", "i", "j", "k", "l", "il", "jl", "kl"); }
            catch (Exception Ex) { throw new ArgumentException("The string cannot be converted as a number.", Ex); }
            return Rst;
        }
        ///
        /// casing
        ///
        internal Number Num()
        {
            return new Number(Re, Im[1], Im[2], Im[3], Im[4], Im[5], Im[6], Im[7]);
        }
        internal static Octon Val(Number N)
        {
            return new Octon(N[0], N[1], N[2], N[3], N[4], N[5], N[6], N[7]);
        }
    }
}
