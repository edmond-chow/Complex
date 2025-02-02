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
using System.Text.RegularExpressions;
namespace Num
{
    public class Seden
    {
        ///
        /// helpers
        ///
        private static int Near(int Dim)
        {
            int Shift = 0;
            while (Dim >> Shift != 0)
            {
                ++Shift;
            }
            int Rst = 0b1;
            Rst <<= Shift;
            return Rst;
        }
        ///
        /// constants
        ///
        public static readonly Seden Zero = new Seden();
        internal static readonly Seden i = new Seden(0, 1);
        ///
        /// basis
        ///
        private const int BasicSize = 16;
        private readonly Number Data;
        public Seden()
        {
            Data = new Number(BasicSize);
        }
        public Seden(params double[] N)
        {
            Data = new Number(N);
            if (Data.Size < BasicSize) { Data = Data.Extend(BasicSize); }
        }
        internal Seden(Number N)
        {
            Data = N;
        }
        public Seden Clone()
        {
            return new Seden(Data.Clone());
        }
        public override string ToString()
        {
            double[] Numbers = new double[Data.Size];
            string[] Terms = new string[Data.Size];
            for (int i = 0; i < Data.Size; ++i)
            {
                Numbers[i] = Data[i];
                Terms[i] = "e" + i.ToString();
            }
            return Numbers.ToString(Terms);
        }
        public override bool Equals(object obj)
        {
            if (obj is Seden o) { return this == o; }
            else { return false; }
        }
        public double this[int i]
        {
            get { return Data[i]; }
            set { Data[i] = value; }
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public static explicit operator Seden(string V)
        {
            return Val(V);
        }
        public static explicit operator string(Seden V)
        {
            return Str(V);
        }
        public static implicit operator Seden(double V)
        {
            return new Seden(V);
        }
        public static double Scalar(Seden V)
        {
            return V[0];
        }
        public static Seden Vector(Seden V)
        {
            Seden Rst = V.Clone();
            Rst[0] = 0;
            return Rst;
        }
        ///
        /// operators
        ///
        public static bool operator ==(Seden U, Seden V)
        {
            if (ReferenceEquals(U, V)) { return true; }
            else if (U == null || V == null) { return false; }
            return U.Num() == V.Num();
        }
        public static bool operator !=(Seden U, Seden V)
        {
            return !(U == V);
        }
        public static Seden operator +(Seden V)
        {
            return V;
        }
        public static Seden operator -(Seden V)
        {
            return Val(-V.Num());
        }
        public static Seden operator ~(Seden V)
        {
            return Val(~V.Num());
        }
        public static Seden operator ++(Seden V)
        {
            ++V[0];
            return V;
        }
        public static Seden operator --(Seden V)
        {
            --V[0];
            return V;
        }
        public static Seden operator +(Seden U, Seden V)
        {
            return Val(U.Num() + V.Num());
        }
        public static Seden operator -(Seden U, Seden V)
        {
            return Val(U.Num() - V.Num());
        }
        public static Seden operator *(Seden U, Seden V)
        {
            return Val(U.Num() * V.Num());
        }
        public static Seden operator /(Seden U, Seden V)
        {
            if (Vector(V) == Zero) { return Val(U.Num() / Scalar(V)); }
            return U * Inverse(V);
        }
        public static Seden operator ^(Seden U, long V)
        {
            return Power(U, V);
        }
        ///
        /// multiples
        ///
        public static double Dot(Seden U, Seden V)
        {
            return Number.Dot(U.Num(), V.Num());
        }
        public static Seden Outer(Seden U, Seden V)
        {
            return Val(Number.Outer(U.Num(), V.Num()));
        }
        public static Seden Even(Seden U, Seden V)
        {
            return Val(Number.Even(U.Num(), V.Num()));
        }
        public static Seden Cross(Seden U, Seden V)
        {
            return Val(Number.Cross(U.Num(), V.Num()));
        }
        ///
        /// fundamentals
        ///
        public static double Abs(Seden V)
        {
            return Ev.Sqrt(Dot(V, V));
        }
        public static double Arg(Seden V, long P)
        {
            return Ev.Arccos(Scalar(V) / Abs(V)) + 2 * Ev.PI * P;
        }
        public static double Arg(Seden V)
        {
            return Arg(V, 0);
        }
        public static Seden Conjg(Seden V)
        {
            return ~V;
        }
        public static Seden Sgn(Seden V)
        {
            return V / Abs(V);
        }
        public static Seden Inverse(Seden V)
        {
            return Conjg(V) / Dot(V, V);
        }
        public static Seden Exp(Seden V)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return Ev.Exp(Re); }
            double Sz = Abs(Im);
            Seden Or = Sgn(Im);
            return Ev.Exp(Re) * (Ev.Cos(Sz) + Or * Ev.Sin(Sz));
        }
        public static Seden Ln(Seden V, long P)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero)
            {
                if (Re >= 0) { return Ev.Ln(Re) + 2 * P * Ev.PI * i; }
                else { return Ev.Ln(-Re) + (2 * P + 1) * Ev.PI * i; }
            }
            Seden Or = Sgn(Im);
            return Ev.Ln(Abs(V)) + Or * Arg(V, P);
        }
        public static Seden Ln(Seden V)
        {
            return Ln(V, 0);
        }
        ///
        /// exponentials
        ///
        public static Seden Power(Seden U, Seden V, long z1, long z2, long z3)
        {
            return Exp(Exp(Ln(V, z3) + Ln(Ln(U, z1), z2)));
        }
        public static Seden Power(Seden U, Seden V)
        {
            return Power(U, V, 0, 0, 0);
        }
        public static Seden Power(Seden U, double V, long P)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero)
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
            Seden Or = Sgn(Im);
            double A = Arg(U, P) * V;
            return Ev.Power(Abs(U), V) * (Ev.Cos(A) + Or * Ev.Sin(A));
        }
        public static Seden Power(Seden U, double V)
        {
            return Power(U, V, 0);
        }
        public static Seden Root(Seden U, Seden V, long z1, long z2, long z3)
        {
            return Power(U, Inverse(V), z1, z2, z3);
        }
        public static Seden Root(Seden U, Seden V)
        {
            return Root(U, V, 0, 0, 0);
        }
        public static Seden Root(Seden U, double V, long P)
        {
            return Power(U, 1 / V, P);
        }
        public static Seden Root(Seden U, double V)
        {
            return Root(U, V, 0);
        }
        public static Seden Log(Seden U, Seden V, long z1, long z2, long z3, long z4)
        {
            return Exp(Ln(Ln(V, z1), z3) - Ln(Ln(U, z2), z4));
        }
        public static Seden Log(Seden U, Seden V)
        {
            return Log(U, V, 0, 0, 0, 0);
        }
        ///
        /// trigonometrics
        ///
        public static Seden Sin(Seden V)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return Ev.Sin(Re); }
            double Sz = Abs(Im);
            Seden Or = Sgn(Im);
            return Ev.Sin(Re) * Ev.Cosh(Sz) + Ev.Cos(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Seden Cos(Seden V)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return Ev.Cos(Re); }
            double Sz = Abs(Im);
            Seden Or = Sgn(Im);
            return Ev.Cos(Re) * Ev.Cosh(Sz) - Ev.Sin(Re) * Ev.Sinh(Sz) * Or;
        }
        public static Seden Tan(Seden V)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            double T = Ev.Tan(Re);
            if (Im == Zero) { return T; }
            double Sz = Abs(Im);
            Seden Or = Sgn(Im);
            double Th = Ev.Tanh(Sz);
            double T2 = T * T;
            double Th2 = Th * Th;
            return (T * (1 - Th2) + Th * (1 + T2) * Or) / (1 + T2 * Th2);
        }
        public static Seden Csc(Seden V)
        {
            return Inverse(Sin(V));
        }
        public static Seden Sec(Seden V)
        {
            return Inverse(Cos(V));
        }
        public static Seden Cot(Seden V)
        {
            return Inverse(Tan(V));
        }
        public static Seden Sinh(Seden V)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return Ev.Sinh(Re); }
            double Sz = Abs(Im);
            Seden Or = Sgn(Im);
            return Ev.Sinh(Re) * Ev.Cos(Sz) + Ev.Cosh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Seden Cosh(Seden V)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return Ev.Cosh(Re); }
            double Sz = Abs(Im);
            Seden Or = Sgn(Im);
            return Ev.Cosh(Re) * Ev.Cos(Sz) + Ev.Sinh(Re) * Ev.Sin(Sz) * Or;
        }
        public static Seden Tanh(Seden V)
        {
            double Re = Scalar(V);
            Seden Im = Vector(V);
            double Th = Ev.Tanh(Re);
            if (Im == Zero) { return Th; }
            double Sz = Abs(Im);
            Seden Or = Sgn(Im);
            double T = Ev.Tan(Sz);
            double Th2 = Th * Th;
            double T2 = T * T;
            return (Th * (1 - T2) + T * (1 + Th2) * Or) / (1 + Th2 * T2);
        }
        public static Seden Csch(Seden V)
        {
            return Inverse(Sinh(V));
        }
        public static Seden Sech(Seden V)
        {
            return Inverse(Cosh(V));
        }
        public static Seden Coth(Seden V)
        {
            return Inverse(Tanh(V));
        }
        public static Seden Arcsin(Seden V, bool S, long P)
        {
            if (!S) { return Ev.PI - Arcsin(V, true, P); }
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return -i * Ln(i * Re + Root(1 - Re * Re, 2), P); }
            Seden Or = Sgn(Im);
            return -Or * Ln(Or * V + Root(1 - V * V, 2), P);
        }
        public static Seden Arcsin(Seden V)
        {
            return Arcsin(V, true, 0);
        }
        public static Seden Arccos(Seden V, bool S, long P)
        {
            if (!S) { return 2 * Ev.PI - Arccos(V, true, P); }
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return -i * Ln(Re + Root(Re * Re - 1, 2), P); }
            Seden Or = Sgn(Im);
            return -Or * Ln(V + Root(V * V - 1, 2), P);
        }
        public static Seden Arccos(Seden V)
        {
            return Arccos(V, true, 0);
        }
        public static Seden Arctan(Seden V, bool S, long P)
        {
            if (!S) { return Ev.PI + Arctan(V, true, P); }
            double Re = Scalar(V);
            Seden Im = Vector(V);
            if (Im == Zero) { return 2 * Ev.PI * P + i * (Ln(1 - i * Re) - Ln(1 + i * Re)) / 2; }
            Seden Or = Sgn(Im);
            return 2 * Ev.PI * P + Or * (Ln(1 - Or * V) - Ln(1 + Or * V)) / 2;
        }
        public static Seden Arctan(Seden V)
        {
            return Arctan(V, true, 0);
        }
        public static Seden Arccsc(Seden V, bool S, long P)
        {
            return Arcsin(Inverse(V), S, P);
        }
        public static Seden Arccsc(Seden V)
        {
            return Arccsc(V, true, 0);
        }
        public static Seden Arcsec(Seden V, bool S, long P)
        {
            return Arccos(Inverse(V), S, P);
        }
        public static Seden Arcsec(Seden V)
        {
            return Arcsec(V, true, 0);
        }
        public static Seden Arccot(Seden V, bool S, long P)
        {
            return Arctan(Inverse(V), S, P);
        }
        public static Seden Arccot(Seden V)
        {
            return Arccot(V, true, 0);
        }
        public static Seden Arcsinh(Seden V, bool S, long P)
        {
            Seden Im = Vector(V);
            Seden Or = Sgn(Im);
            if (!S) { return Ev.PI * Or - Arcsinh(V, true, P); }
            return Ln(V + Root(V * V + 1, 2), P);
        }
        public static Seden Arcsinh(Seden V)
        {
            return Arcsinh(V, true, 0);
        }
        public static Seden Arccosh(Seden V, bool S, long P)
        {
            Seden Im = Vector(V);
            Seden Or = Sgn(Im);
            if (!S) { return 2 * Ev.PI * Or - Arccosh(V, true, P); }
            return Ln(V + Root(V * V - 1, 2), P);
        }
        public static Seden Arccosh(Seden V)
        {
            return Arccosh(V, true, 0);
        }
        public static Seden Arctanh(Seden V, bool S, long P)
        {
            Seden Im = Vector(V);
            Seden Or = Sgn(Im);
            if (!S) { return Ev.PI * Or + Arctan(V, true, P); }
            return 2 * Ev.PI * P * Or + (Ln(1 + V) - Ln(1 - V)) / 2;
        }
        public static Seden Arctanh(Seden V)
        {
            return Arctanh(V, true, 0);
        }
        public static Seden Arccsch(Seden V, bool S, long P)
        {
            return Arcsinh(Inverse(V), S, P);
        }
        public static Seden Arccsch(Seden V)
        {
            return Arccsch(V, true, 0);
        }
        public static Seden Arcsech(Seden V, bool S, long P)
        {
            return Arccosh(Inverse(V), S, P);
        }
        public static Seden Arcsech(Seden V)
        {
            return Arcsech(V, true, 0);
        }
        public static Seden Arccoth(Seden V, bool S, long P)
        {
            return Arctanh(Inverse(V), S, P);
        }
        public static Seden Arccoth(Seden V)
        {
            return Arccoth(V, true, 0);
        }
        ///
        /// conventions
        ///
        public static string Str(Seden V)
        {
            return V.ToString();
        }
        public static Seden Val(string V)
        {
            string Str = V.Replace(" ", "");
            if (Str == "0") { return Zero; }
            MatchCollection Mat = new Regex(@"e(\d+)(?=-|\+|$)").Matches(Str);
            int Dim = 0;
            for (int i = 0; i < Mat.Count; ++i)
            {
                int NewDim = int.Parse(Mat[i].Groups[1].Value);
                if (NewDim > Dim) { Dim = NewDim; }
            }
            Dim = Near(Dim);
            string[] Trm = new string[Dim];
            for (int i = 0; i < Trm.Length; ++i) { Trm[i] = "e" + i.ToString(); }
            double[] Num = Str.ToNumbers(Trm);
            return new Seden(Num);
        }
        ///
        /// casing
        ///
        private Number Num()
        {
            return Data;
        }
        private static Seden Val(Number N)
        {
            return new Seden(N);
        }
    }
}
