using System;
using System.Text.RegularExpressions;
namespace Seden
{
    public class Sedenion
    {
        ///
        /// helpers
        ///
        private static long GetDimension(long Value)
        {
            long Result = 1;
            while (Value > 0)
            {
                Value >>= 1;
                Result <<= 1;
            }
            return Result;
        }
        ///
        /// constants
        ///
        public static readonly double pi = Math.PI;
        public static readonly double e = Math.E;
        internal static readonly Sedenion i = new Sedenion(0, 1);
        ///
        /// basis
        ///
        private readonly Number Data;
        public Sedenion()
        {
            Data = new Number(16);
        }
        public Sedenion(params double[] Numbers)
        {
            Data = new Number(Numbers);
        }
        public Sedenion(in double[] Numbers)
        {
            Data = new Number(in Numbers);
        }
        public Sedenion Clone()
        {
            return new Sedenion(Data.GetMemberwiseData());
        }
        internal Number GetMemberwiseData()
        {
            return Data;
        }
        public override string ToString()
        {
            double[] Numbers = Data.GetMemberwiseData();
            string[] Terms = new string[Numbers.LongLength];
            for (long i = 0; i < Terms.LongLength; ++i) { Terms[i] = "e" + i.ToString(); }
            return Numbers.ToString(Terms);
        }
        public override bool Equals(object obj)
        {
            if (obj is Sedenion o) { return this == o; }
            else { return false; }
        }
        public double this[long Index]
        {
            get { return Data[Index % Data.LongLength]; }
            set { Data[Index % Data.LongLength] = value; }
        }
        public override int GetHashCode() { return 0; }
        public static explicit operator Sedenion(string Value) { return GetInstance(Value); }
        public static explicit operator string(Sedenion Value) { return GetString(Value); }
        public static implicit operator Sedenion(double Value) { return new Sedenion(Value); }
        public static double Scalar(Sedenion Value) { return Value[0]; }
        public static Sedenion Vector(Sedenion Value)
        {
            Sedenion Result = Value.Clone();
            Result[0] = 0;
            return Result;
        }
        ///
        /// operators
        ///
        public static bool operator ==(Sedenion Union, Sedenion Value) { return Union.ToNumber() == Value.ToNumber(); }
        public static bool operator !=(Sedenion Union, Sedenion Value) { return !(Union == Value); }
        public static Sedenion operator +(Sedenion Value) { return Value; }
        public static Sedenion operator -(Sedenion Value) { return From(-Value.ToNumber()); }
        public static Sedenion operator ~(Sedenion Value) { return From(~Value.ToNumber()); }
        public static Sedenion operator ++(Sedenion Value) { return Value + 1; }
        public static Sedenion operator --(Sedenion Value) { return Value - 1; }
        public static Sedenion operator +(Sedenion Union, Sedenion Value) { return From(Union.ToNumber() + Value.ToNumber()); }
        public static Sedenion operator -(Sedenion Union, Sedenion Value) { return Union + (-Value); }
        public static Sedenion operator *(Sedenion Union, Sedenion Value) { return From(Union.ToNumber() * Value.ToNumber()); }
        public static Sedenion operator /(Sedenion Union, double Value) { return From(Union.ToNumber() / Value); }
        public static Sedenion operator ^(Sedenion Base, long Exponent) { return Power(Base, Exponent); }
        ///
        /// fundamentals
        ///
        public static double Abs(Sedenion Value) { return Math.Sqrt(Dot(Value, Value)); }
        public static double Arg(Sedenion Value) { return Arg(Value, 0); }
        public static double Arg(Sedenion Value, long Theta) { return Math.Acos(Scalar(Value) / Abs(Value)) + 2 * pi * Theta; }
        public static Sedenion Conjg(Sedenion Value) { return ~Value; }
        public static Sedenion Sgn(Sedenion Value) { return Value / Abs(Value); }
        public static Sedenion Inverse(Sedenion Value) { return Conjg(Value) / Dot(Value, Value); }
        public static Sedenion Exp(Sedenion Value)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            if (V == 0) { return Math.Exp(S); }
            return Math.Exp(S) * (Math.Cos(Abs(V)) + Sgn(V) * Math.Sin(Abs(V)));
        }
        public static Sedenion Ln(Sedenion Value) { return Ln(Value, 0); }
        public static Sedenion Ln(Sedenion Value, long Theta)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            if (V == 0)
            {
                if (S < 0) { return Math.Log(-S) + (2 * Theta + 1) * i * pi; }
                return Math.Log(S);
            }
            return Math.Log(Abs(Value)) + Sgn(V) * Arg(Value, Theta);
        }
        ///
        /// multiples
        ///
        public static double Dot(Sedenion Union, Sedenion Value)
        {
            return Number.NumberDot(Union.ToNumber(), Value.ToNumber());
        }
        public static Sedenion Outer(Sedenion Union, Sedenion Value)
        {
            return From(Number.NumberOuter(Union.ToNumber(), Value.ToNumber()));
        }
        public static Sedenion Even(Sedenion Union, Sedenion Value)
        {
            return From(Number.NumberEven(Union.ToNumber(), Value.ToNumber()));
        }
        public static Sedenion Cross(Sedenion Union, Sedenion Value)
        {
            return From(Number.NumberCross(Union.ToNumber(), Value.ToNumber()));
        }
        ///
        /// exponentials
        ///
        public static Sedenion Power(Sedenion Base, Sedenion Exponent) { return Power(Base, Exponent, 0, 0, 0); }
        public static Sedenion Power(Sedenion Base, Sedenion Exponent, long Theta, long Phi, long Tau)
        {
            return Exp(Exp(Ln(Ln(Base, Theta), Phi) + Ln(Exponent, Tau)));
        }
        public static Sedenion Power(Sedenion Base, double Exponent) { return Power(Base, Exponent, 0); }
        public static Sedenion Power(Sedenion Base, double Exponent, long Theta)
        {
            if (Base == 0) { return Exponent == 0 ? 1 : 0; }
            return Math.Pow(Abs(Base), Exponent) *
                (Math.Cos(Exponent * Arg(Base, Theta)) + Sgn(Vector(Base)) * Math.Sin(Exponent * Arg(Base, Theta)));
        }
        public static Sedenion Root(Sedenion Base, Sedenion Exponent) { return Root(Base, Exponent, 0, 0, 0); }
        public static Sedenion Root(Sedenion Base, Sedenion Exponent, long Theta, long Phi, long Tau) { return Power(Base, Inverse(Exponent), Theta, Phi, Tau); }
        public static Sedenion Root(Sedenion Base, double Exponent) { return Root(Base, Exponent, 0); }
        public static Sedenion Root(Sedenion Base, double Exponent, long Theta) { return Power(Base, 1 / Exponent, Theta); }
        public static Sedenion Log(Sedenion Base, Sedenion Number) { return Log(Base, Number, 0, 0, 0, 0); }
        public static Sedenion Log(Sedenion Base, Sedenion Number, long Theta, long Phi, long Tau, long Omega)
        {
            return Exp(Ln(Ln(Number, Theta), Phi) - Ln(Ln(Base, Tau), Omega));
        }
        ///
        /// trigonometrics
        ///
        public static Sedenion Sin(Sedenion Value)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            if (V == 0) { return Math.Sin(S); }
            return Math.Sin(S) * Math.Cosh(Abs(V)) + Sgn(V) * (Math.Cos(S) * Math.Sinh(Abs(V)));
        }
        public static Sedenion Arcsin(Sedenion Value) { return Arcsin(Value, true, 0); }
        public static Sedenion Arcsin(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return -i * Ln(i * S + Root(1 - S * S, 2), Period); }
                return -Sgn(V) * Ln(Sgn(V) * Value + Root(1 - Value * Value, 2), Period);
            }
            return pi - Arcsin(Value, true, Period);
        }
        public static Sedenion Sinh(Sedenion Value)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            if (V == 0) { return Math.Sinh(S); }
            return Math.Sinh(S) * Math.Cos(Abs(V)) + Sgn(V) * (Math.Cosh(S) * Math.Sin(Abs(V)));
        }
        public static Sedenion Arcsinh(Sedenion Value) { return Arcsinh(Value, true, 0); }
        public static Sedenion Arcsinh(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return Ln(Value + Root(Value * Value + 1, 2), Period); }
            var V = Vector(Value);
            if (V == 0) { return pi * i - Arcsinh(Value, true, Period); }
            return pi * Sgn(V) - Arcsinh(Value, true, Period);
        }
        public static Sedenion Cos(Sedenion Value)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            if (V == 0) { return Math.Cos(S); }
            return Math.Cos(S) * Math.Cosh(Abs(V)) - Sgn(V) * (Math.Sin(S) * Math.Sinh(Abs(V)));
        }
        public static Sedenion Arccos(Sedenion Value) { return Arccos(Value, true, 0); }
        public static Sedenion Arccos(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return -i * Ln(S + Root(S * S - 1, 2), Period); }
                return -Sgn(V) * Ln(Value + Root(Value * Value - 1, 2), Period);
            }
            return 2 * pi - Arccos(Value, true, Period);
        }
        public static Sedenion Cosh(Sedenion Value)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            if (V == 0) { return Math.Cosh(S); }
            return Math.Cosh(S) * Math.Cos(Abs(V)) + Sgn(V) * (Math.Sinh(S) * Math.Sin(Abs(V)));
        }
        public static Sedenion Arccosh(Sedenion Value) { return Arccosh(Value, true, 0); }
        public static Sedenion Arccosh(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return Ln(Value + Root(Value * Value - 1, 2), Period); }
            var V = Vector(Value);
            if (V == 0) { return 2 * pi * i - Arccosh(Value, true, Period); }
            return 2 * pi * Sgn(V) - Arccosh(Value, true, Period);
        }
        public static Sedenion Tan(Sedenion Value)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            var TanS = Math.Tan(S);
            if (V == 0) { return TanS; }
            var TanS2 = TanS * TanS;
            var TanhV = Math.Tanh(Abs(V));
            var TanhV2 = TanhV * TanhV;
            return (TanS * (1 - TanhV2) + Sgn(V) * (TanhV * (1 + TanS2))) / (1 + TanS2 * TanhV2);
        }
        public static Sedenion Arctan(Sedenion Value) { return Arctan(Value, true, 0); }
        public static Sedenion Arctan(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return i / 2 * (Ln(1 - i * S, Period) - Ln(1 + i * S)); }
                return Sgn(V) / 2 * (Ln(1 - Sgn(V) * Value, Period) - Ln(1 + Sgn(V) * Value));
            }
            return pi + Arctan(Value, true, Period);
        }
        public static Sedenion Tanh(Sedenion Value)
        {
            var S = Scalar(Value);
            var V = Vector(Value);
            var TanhS = Math.Tanh(S);
            if (V == 0) { return TanhS; }
            var TanhS2 = TanhS * TanhS;
            var TanV = Math.Tan(Abs(V));
            var TanV2 = TanV * TanV;
            return (TanhS * (1 - TanV2) + Sgn(V) * (TanV * (1 + TanhS2))) / (1 + TanhS2 * TanV2);
        }
        public static Sedenion Arctanh(Sedenion Value) { return Arctanh(Value, true, 0); }
        public static Sedenion Arctanh(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return 1 / 2 * (Ln(1 + Value, Period) - Ln(1 - Value)); }
            var V = Vector(Value);
            if (V == 0) { return pi * i + Arctanh(Value, true, Period); }
            return pi * Sgn(V) + Arctanh(Value, true, Period);
        }
        public static Sedenion Csc(Sedenion Value) { return Inverse(Sin(Value)); }
        public static Sedenion Arccsc(Sedenion Value) { return Arccsc(Value, true, 0); }
        public static Sedenion Arccsc(Sedenion Value, bool Sign, long Period) { return Arcsin(Inverse(Value), Sign, Period); }
        public static Sedenion Csch(Sedenion Value) { return Inverse(Sinh(Value)); }
        public static Sedenion Arccsch(Sedenion Value) { return Arccsch(Value, true, 0); }
        public static Sedenion Arccsch(Sedenion Value, bool Sign, long Period) { return Arcsinh(Inverse(Value), Sign, Period); }
        public static Sedenion Sec(Sedenion Value) { return Inverse(Cos(Value)); }
        public static Sedenion Arcsec(Sedenion Value) { return Arcsec(Value, true, 0); }
        public static Sedenion Arcsec(Sedenion Value, bool Sign, long Period) { return Arccos(Inverse(Value), Sign, Period); }
        public static Sedenion Sech(Sedenion Value) { return Inverse(Cosh(Value)); }
        public static Sedenion Arcsech(Sedenion Value) { return Arcsech(Value, true, 0); }
        public static Sedenion Arcsech(Sedenion Value, bool Sign, long Period) { return Arccosh(Inverse(Value), Sign, Period); }
        public static Sedenion Cot(Sedenion Value) { return Inverse(Tan(Value)); }
        public static Sedenion Arccot(Sedenion Value) { return Arccot(Value, true, 0); }
        public static Sedenion Arccot(Sedenion Value, bool Sign, long Period) { return Arctan(Inverse(Value), Sign, Period); }
        public static Sedenion Coth(Sedenion Value) { return Inverse(Tanh(Value)); }
        public static Sedenion Arccoth(Sedenion Value) { return Arccoth(Value, true, 0); }
        public static Sedenion Arccoth(Sedenion Value, bool Sign, long Period) { return Arctanh(Inverse(Value), Sign, Period); }
        ///
        /// conventions
        ///
        public static string GetString(Sedenion Value) { return Value.ToString(); }
        public static Sedenion GetInstance(string Value)
        {
            string Replaced = Value.Replace(" ", "");
            if (Replaced == "0") { return new Sedenion(); }
            MatchCollection Match = new Regex(@"e(\d+)(?=-|\+|$)").Matches(Replaced);
            long Dimension = 0;
            for (int i = 0; i < Match.Count; ++i)
            {
                Dimension = Math.Max(Dimension, long.Parse(Match[i].Groups[1].Value));
            }
            string[] Terms = new string[GetDimension(Dimension)];
            for (long i = 0; i < Terms.LongLength; ++i) { Terms[i] = "e" + i.ToString(); }
            double[] Numbers = Replaced.ToNumbers(Terms);
            return new Sedenion(in Numbers);
        }
        ///
        /// casing
        ///
        private Number ToNumber() { return GetMemberwiseData(); }
        private static Sedenion From(Number Number) { return new Sedenion(Number.GetMemberwiseData()); }
    }
}
