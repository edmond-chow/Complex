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
    public struct Vec3D : INum
    {
        ///
        /// constants
        ///
        public static readonly Vec3D Zero = new Vec3D(0, 0, 0);
        public static readonly Vec3D e1 = new Vec3D(1, 0, 0);
        public static readonly Vec3D e2 = new Vec3D(0, 1, 0);
        public static readonly Vec3D e3 = new Vec3D(0, 0, 1);
        ///
        /// basis
        ///
        private double x1;
        private double x2;
        private double x3;
        public Vec3D(double e1, double e2, double e3)
        {
            x1 = e1;
            x2 = e2;
            x3 = e3;
        }
        public override string ToString()
        {
            double[] Numbers = new double[] { x1, x2, x3 };
            return Numbers.ToString("e1", "e2", "e3");
        }
        public override bool Equals(object obj)
        {
            if (obj is Vec3D o) { return this == o; }
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
                    default: break;
                }
            }
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public static explicit operator Vec3D(string V)
        {
            return Val(V);
        }
        public static explicit operator string(Vec3D V)
        {
            return Str(V);
        }
        ///
        /// operators
        ///
        public static bool operator ==(Vec3D U, Vec3D V)
        {
            return U.Num() == V.Num();
        }
        public static bool operator !=(Vec3D U, Vec3D V)
        {
            return !(U == V);
        }
        public static Vec3D operator +(Vec3D V)
        {
            return V;
        }
        public static Vec3D operator -(Vec3D V)
        {
            return Val(-V.Num());
        }
        public static Vec3D operator +(Vec3D U, Vec3D V)
        {
            return Val(U.Num() + V.Num());
        }
        public static Quter operator +(double U, Vec3D V)
        {
            return new Quter(U, V);
        }
        public static Quter operator +(Vec3D U, double V)
        {
            return V + U;
        }
        public static Vec3D operator -(Vec3D U, Vec3D V)
        {
            return Val(U.Num() - V.Num());
        }
        public static Quter operator -(double U, Vec3D V)
        {
            return U + (-V);
        }
        public static Quter operator -(Vec3D U, double V)
        {
            return U + (-V);
        }
        public static Vec3D operator *(Vec3D U, double V)
        {
            return Val(U.Num() * V);
        }
        public static Vec3D operator *(double U, Vec3D V)
        {
            return Val(U * V.Num());
        }
        public static Vec3D operator /(Vec3D U, double V)
        {
            return Val(U.Num() / V);
        }
        ///
        /// multiples
        ///
        public static double Dot(Vec3D U, Vec3D V)
        {
            return Number.Dot(U.Num(), V.Num());
        }
        public static Vec3D Cross(Vec3D U, Vec3D V)
        {
            return Val(Number.Cross(U.Num(), V.Num()));
        }
        ///
        /// fundamentals
        ///
        public static double Abs(Vec3D V)
        {
            return Ev.Sqrt(Dot(V, V));
        }
        public static Vec3D Sgn(Vec3D V)
        {
            return V / Abs(V);
        }
        ///
        /// conventions
        ///
        public static string Str(Vec3D V)
        {
            return V.ToString();
        }
        public static Vec3D Val(string V)
        {
            string Str = V.Replace(" ", "");
            Vec3D Rst = Zero;
            try { Str.ToNumbers(ref Rst, true, "e1", "e2", "e3"); }
            catch (Exception Ex) { throw new ArgumentException("The string cannot be converted as a number.", Ex); }
            return Rst;
        }
        ///
        /// casing
        ///
        internal Number Num()
        {
            return new Number(0, x1, x2, x3);
        }
        internal static Vec3D Val(Number N)
        {
            return new Vec3D(N[1], N[2], N[3]);
        }
    }
    public struct Quter : INum
    {
        ///
        /// constants
        ///
        public static readonly Quter Zero = new Quter(0, Vec3D.Zero);
        public static readonly Quter i = new Quter(0, Vec3D.e1);
        public static readonly Quter j = new Quter(0, Vec3D.e2);
        public static readonly Quter k = new Quter(0, Vec3D.e3);
        ///
        /// basis
        ///
        private double Re;
        private Vec3D Im;
        public Quter(double s, Vec3D v)
        {
            Re = s;
            Im = v;
        }
        public Quter(double s, double i, double j, double k)
        {
            Re = s;
            Im = new Vec3D(i, j, k);
        }
        public override string ToString()
        {
            double[] Numbers = new double[] { Re, Im[1], Im[2], Im[3] };
            return Numbers.ToString("", "i", "j", "k");
        }
        public override bool Equals(object obj)
        {
            if (obj is Quter o) { return this == o; }
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
        public static explicit operator Quter(string V)
        {
            return Val(V);
        }
        public static explicit operator string(Quter V)
        {
            return Str(V);
        }
        public static implicit operator Quter(double V)
        {
            return new Quter(V, Vec3D.Zero);
        }
        public static implicit operator Quter(Vec3D V)
        {
            return new Quter(0, V);
        }
        public static double Scalar(Quter V)
        {
            return V.Re;
        }
        public static Vec3D Vector(Quter V)
        {
            return V.Im;
        }
        ///
        /// operators
        ///
        public static bool operator ==(Quter U, Quter V)
        {
            return U.Num() == V.Num();
        }
        public static bool operator !=(Quter U, Quter V)
        {
            return !(U == V);
        }
        public static Quter operator +(Quter V)
        {
            return V;
        }
        public static Quter operator -(Quter V)
        {
            return Val(-V.Num());
        }
        public static Quter operator ~(Quter V)
        {
            return Val(~V.Num());
        }
        public static Quter operator ++(Quter V)
        {
            return V + 1;
        }
        public static Quter operator --(Quter V)
        {
            return V - 1;
        }
        public static Quter operator +(Quter U, Quter V)
        {
            return Val(U.Num() + V.Num());
        }
        public static Quter operator -(Quter U, Quter V)
        {
            return Val(U.Num() - V.Num());
        }
        public static Quter operator *(Quter U, Quter V)
        {
            return Val(U.Num() * V.Num());
        }
        public static Quter operator /(Quter U, Quter V)
        {
            if (Vector(V) == Vec3D.Zero) { return Val(U.Num() / Scalar(V)); }
            return U * Inverse(V);
        }
        public static Quter operator ^(Quter U, long V)
        {
            return Power(U, V);
        }
        ///
        /// multiples
        ///
        public static double Dot(Quter U, Quter V)
        {
            return Number.Dot(U.Num(), V.Num());
        }
        public static Vec3D Outer(Quter U, Quter V)
        {
            return Vec3D.Val(Number.Outer(U.Num(), V.Num()));
        }
        public static Quter Even(Quter U, Quter V)
        {
            return Val(Number.Even(U.Num(), V.Num()));
        }
        public static Vec3D Cross(Quter U, Quter V)
        {
            return Vec3D.Val(Number.Cross(U.Num(), V.Num()));
        }
        ///
        /// fundamentals
        ///
        public static double Abs(Quter V)
        {
            return Ev.Sqrt(Dot(V, V));
        }
        public static double Arg(Quter V, long P)
        {
            return Ev.Arccos(Scalar(V) / Abs(V)) + 2 * Ev.PI * P;
        }
        public static double Arg(Quter V)
        {
            return Arg(V, 0);
        }
        public static Quter Conjg(Quter V)
        {
            return ~V;
        }
        public static Quter Sgn(Quter V)
        {
            return V / Abs(V);
        }
        public static Quter Inverse(Quter V)
        {
            return Conjg(V) / Dot(V, V);
        }
        public static Quter Exp(Quter V)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return Ev.Exp(Re); }
            double Sz = Abs(Im);
            Quter Or = Sgn(Im);
            return Ev.Exp(Re) * (Ev.Cos(Sz) + Or * Ev.Sin(Sz));
        }
        public static Quter Ln(Quter V, long P)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero)
            {
                if (Re >= 0) { return Ev.Ln(Re) + 2 * P * Ev.PI * i; }
                else { return Ev.Ln(-Re) + (2 * P + 1) * Ev.PI * i; }
            }
            Quter Or = Sgn(Im);
            return Ev.Ln(Abs(V)) + Or * Arg(V, P);
        }
        public static Quter Ln(Quter V)
        {
            return Ln(V, 0);
        }
        ///
        /// exponentials
        ///
        public static Quter Power(Quter U, Quter V, long z1, long z2, long z3)
        {
            return Exp(Exp(Ln(V, z3) + Ln(Ln(U, z1), z2)));
        }
        public static Quter Power(Quter U, Quter V)
        {
            return Power(U, V, 0, 0, 0);
        }
        public static Quter Power(Quter U, double V, long P)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero)
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
            Quter Or = Sgn(Im);
            double A = Arg(U, P) * V;
            return Ev.Power(Abs(U), V) * (Ev.Cos(A) + Or * Ev.Sin(A));
        }
        public static Quter Power(Quter U, double V)
        {
            return Power(U, V, 0);
        }
        public static Quter Root(Quter U, Quter V, long z1, long z2, long z3)
        {
            return Power(U, Inverse(V), z1, z2, z3);
        }
        public static Quter Root(Quter U, Quter V)
        {
            return Root(U, V, 0, 0, 0);
        }
        public static Quter Root(Quter U, double V, long P)
        {
            return Power(U, 1 / V, P);
        }
        public static Quter Root(Quter U, double V)
        {
            return Root(U, V, 0);
        }
        public static Quter Log(Quter U, Quter V, long z1, long z2, long z3, long z4)
        {
            return Exp(Ln(Ln(V, z1), z3) - Ln(Ln(U, z2), z4));
        }
        public static Quter Log(Quter U, Quter V)
        {
            return Log(U, V, 0, 0, 0, 0);
        }
        ///
        /// trigonometrics
        ///
        public static Quter Sin(Quter V)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return Ev.Sin(Re); }
            double Sz = Abs(Im);
            Quter Or = Sgn(Im);
            return Ev.Sin(Re) * Ev.Cosh(Sz) + Ev.Cos(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Quter Cos(Quter V)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return Ev.Cos(Re); }
            double Sz = Abs(Im);
            Quter Or = Sgn(Im);
            return Ev.Cos(Re) * Ev.Cosh(Sz) - Ev.Sin(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Quter Tan(Quter V)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            double T = Ev.Tan(Re);
            if (Im == Vec3D.Zero) { return T; }
            double Sz = Abs(Im);
            Quter Or = Sgn(Im);
            double Th = Ev.Tanh(Sz);
            double T2 = T * T;
            double Th2 = Th * Th;
            return (T * (1 - Th2) + Th * (1 + T2) * Or) / (1 + T2 * Th2);
        }
        public static Quter Csc(Quter V)
        {
            return Inverse(Sin(V));
        }
        public static Quter Sec(Quter V)
        {
            return Inverse(Cos(V));
        }
        public static Quter Cot(Quter V)
        {
            return Inverse(Tan(V));
        }
        public static Quter Sinh(Quter V)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return Ev.Sinh(Re); }
            double Sz = Abs(Im);
            Quter Or = Sgn(Im);
            return Ev.Sinh(Re) * Ev.Cos(Sz) + Ev.Cosh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Quter Cosh(Quter V)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return Ev.Cosh(Re); }
            double Sz = Abs(Im);
            Quter Or = Sgn(Im);
            return Ev.Cosh(Re) * Ev.Cos(Sz) + Ev.Sinh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Quter Tanh(Quter V)
        {
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            var Th = Ev.Tanh(Re);
            if (Im == Vec3D.Zero) { return Th; }
            double Sz = Abs(Im);
            Quter Or = Sgn(Im);
            var T = Ev.Tan(Sz);
            var Th2 = Th * Th;
            var T2 = T * T;
            return (Th * (1 - T2) + T * (1 + Th2) * Or) / (1 + Th2 * T2);
        }
        public static Quter Csch(Quter V)
        {
            return Inverse(Sinh(V));
        }
        public static Quter Sech(Quter V)
        {
            return Inverse(Cosh(V));
        }
        public static Quter Coth(Quter V)
        {
            return Inverse(Tanh(V));
        }
        public static Quter Arcsin(Quter V, bool S, long P)
        {
            if (!S) { return Ev.PI - Arcsin(V, true, P); }
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
            Quter Or = Sgn(Im);
            return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
        }
        public static Quter Arcsin(Quter V)
        {
            return Arcsin(V, true, 0);
        }
        public static Quter Arccos(Quter V, bool S, long P)
        {
            if (!S) { return 2 * Ev.PI - Arccos(V, true, P); }
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
            Quter Or = Sgn(Im);
            return -Or * Ln(V + Root(V * V - 1, 2), P);
        }
        public static Quter Arccos(Quter V)
        {
            return Arccos(V, true, 0);
        }
        public static Quter Arctan(Quter V, bool S, long P)
        {
            if (!S) { return Ev.PI + Arctan(V, true, P); }
            double Re = Scalar(V);
            Vec3D Im = Vector(V);
            if (Im == Vec3D.Zero) { return 2 * Ev.PI * P + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
            Quter Or = Sgn(Im);
            return 2 * Ev.PI * P + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
        }
        public static Quter Arctan(Quter V)
        {
            return Arctan(V, true, 0);
        }
        public static Quter Arccsc(Quter V, bool S, long P)
        {
            return Arcsin(Inverse(V), S, P);
        }
        public static Quter Arccsc(Quter V)
        {
            return Arccsc(V, true, 0);
        }
        public static Quter Arcsec(Quter V, bool S, long P)
        {
            return Arccos(Inverse(V), S, P);
        }
        public static Quter Arcsec(Quter V)
        {
            return Arcsec(V, true, 0);
        }
        public static Quter Arccot(Quter V, bool S, long P)
        {
            return Arctan(Inverse(V), S, P);
        }
        public static Quter Arccot(Quter V)
        {
            return Arccot(V, true, 0);
        }
        public static Quter Arcsinh(Quter V, bool S, long P)
        {
            Vec3D Im = Vector(V);
            Quter Or = Sgn(Im);
            if (!S) { return Ev.PI * Or - Arcsinh(V, true, P); }
            return Ln(V + Root(V * V + 1, 2), P);
        }
        public static Quter Arcsinh(Quter V)
        {
            return Arcsinh(V, true, 0);
        }
        public static Quter Arccosh(Quter V, bool S, long P)
        {
            Vec3D Im = Vector(V);
            Quter Or = Sgn(Im);
            if (!S) { return 2 * Ev.PI * Or - Arccosh(V, true, P); }
            return Ln(V + Root(V * V - 1, 2), P);
        }
        public static Quter Arccosh(Quter V)
        {
            return Arccosh(V, true, 0);
        }
        public static Quter Arctanh(Quter V, bool S, long P)
        {
            Vec3D Im = Vector(V);
            Quter Or = Sgn(Im);
            if (!S) { return Ev.PI * Or + Arctan(V, true, P); }
            return 2 * Ev.PI * P * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
        }
        public static Quter Arctanh(Quter V)
        {
            return Arctanh(V, true, 0);
        }
        public static Quter Arccsch(Quter V, bool S, long P)
        {
            return Arcsinh(Inverse(V), S, P);
        }
        public static Quter Arccsch(Quter V)
        {
            return Arccsch(V, true, 0);
        }
        public static Quter Arcsech(Quter V, bool S, long P)
        {
            return Arccosh(Inverse(V), S, P);
        }
        public static Quter Arcsech(Quter V)
        {
            return Arcsech(V, true, 0);
        }
        public static Quter Arccoth(Quter V, bool S, long P)
        {
            return Arctanh(Inverse(V), S, P);
        }
        public static Quter Arccoth(Quter V)
        {
            return Arccoth(V, true, 0);
        }
        ///
        /// conventions
        ///
        public static string Str(Quter V)
        {
            return V.ToString();
        }
        public static Quter Val(string V)
        {
            string Str = V.Replace(" ", "");
            Quter Rst = Zero;
            try { Str.ToNumbers(ref Rst, false, "", "i", "j", "k"); }
            catch (Exception Ex) { throw new ArgumentException("The string cannot be converted as a number.", Ex); }
            return Rst;
        }
        ///
        /// casing
        ///
        internal Number Num()
        {
            return new Number(Re, Im[1], Im[2], Im[3]);
        }
        internal static Quter Val(Number N)
        {
            return new Quter(N[0], N[1], N[2], N[3]);
        }
    }
}
