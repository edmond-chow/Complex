using System;
using System.Linq;
using System.Text.RegularExpressions;
namespace Seden
{
    public class Sedenion
    {
        private static long GetDimension(long Value)
        {
            int n = 0;
            while (Value > 0)
            {
                Value >>= 1;
                ++n;
            }
            return 1 << n;
        }
        public static readonly double pi = Math.PI;
        public static readonly double e = Math.E;
        ///
        /// Initializer
        ///
        private readonly Number numbers;
        private Number Data => numbers;
        private int Length => numbers.Length;
        private long LongLength => numbers.LongLength;
        public Sedenion() { numbers = new Number(16); }
        public Sedenion(params double[] numbers) { this.numbers = new Number(numbers); }
        public override string ToString()
        {
            double[] Numbers = Data.ToArray();
            string[] Strings = new string[LongLength];
            for (long i = 0; i < Strings.LongLength; ++i) { Strings[i] = "e" + i.ToString(); }
            return Numbers.ToString(Strings);
        }
        public override bool Equals(object obj)
        {
            if (obj is Sedenion o) { return this == o; }
            else { return false; }
        }
        public double this[long Index]
        {
            get => Data[Index % LongLength];
            set => Data[Index % LongLength] = value;
        }
        public override int GetHashCode() { return 0; }
        public static explicit operator Sedenion(string Value) { return GetInstance(Value); }
        public static explicit operator string(Sedenion Value) { return GetString(Value); }
        public static implicit operator Sedenion(double Value) { return new Sedenion(Value); }
        public static double Scalar(Sedenion Value) { return Value.ToNumber()[0]; }
        public static Sedenion Vector(Sedenion Value) { return new Sedenion(new double[] { 0 }.Concat(Value.ToNumber().Skip(1)).ToArray()); }
        ///
        /// Operators
        ///
        public static bool operator ==(Sedenion Union, Sedenion Value)
        {
            int D = Math.Max(Union.Length, Value.Length);
            return Union.ToNumber(D) == Value.ToNumber(D);
        }
        public static bool operator !=(Sedenion Union, Sedenion Value) { return !(Union == Value); }
        public static Sedenion operator +(Sedenion Value) { return Value; }
        public static Sedenion operator -(Sedenion Value) { return From(-Value.ToNumber()); }
        public static Sedenion operator ~(Sedenion Value) { return From(~Value.ToNumber()); }
        public static Sedenion operator ++(Sedenion Value) { return Value + 1; }
        public static Sedenion operator --(Sedenion Value) { return Value - 1; }
        public static Sedenion operator +(Sedenion Union, Sedenion Value)
        {
            int D = Math.Max(Union.Length, Value.Length);
            return From(Union.ToNumber(D) + Value.ToNumber(D));
        }
        public static Sedenion operator -(Sedenion Union, Sedenion Value) { return Union + (-Value); }
        public static Sedenion operator *(Sedenion Union, Sedenion Value)
        {
            int D = Math.Max(Union.Length, Value.Length);
            return From(Union.ToNumber(D) * Value.ToNumber(D));
        }
        public static Sedenion operator /(Sedenion Union, double Value) { return From(Union.ToNumber() / Value); }
        public static Sedenion operator ^(Sedenion Base, long Exponent) { return Power(Base, Exponent); }
        ///
        /// Basic functions for constructing numbers
        ///
        public static double Abs(Sedenion Value) { return Math.Sqrt(Dot(Value, Value)); }
        public static double Arg(Sedenion Value) { return Arg(Value, 0); }
        public static double Arg(Sedenion Value, long Theta) { return Math.Acos(Scalar(Value) / Abs(Value)) + 2 * pi * Theta; }
        public static Sedenion Conjg(Sedenion Value) { return ~Value; }
        public static Sedenion Sgn(Sedenion Value) { return Value / Abs(Value); }
        public static Sedenion Inverse(Sedenion Value) { return Conjg(Value) / Dot(Value, Value); }
        public static Sedenion Exp(Sedenion Value) { return Math.Exp(Scalar(Value)) * (Math.Cos(Abs(Vector(Value))) + Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)))); }
        public static Sedenion Ln(Sedenion Value) { return Ln(Value, 0); }
        public static Sedenion Ln(Sedenion Value, long Theta) { return Math.Log(Abs(Value)) + Sgn(Vector(Value)) * Arg(Value, Theta); }
        ///
        /// 1st rank tensor algorithms
        ///
        public static double Dot(Sedenion Union, Sedenion Value) { return Scalar(Conjg(Union) * Value + Conjg(Value) * Union) / 2; }
        public static Sedenion Outer(Sedenion Union, Sedenion Value) { return (Conjg(Union) * Value - Conjg(Value) * Union) / 2; }
        public static Sedenion Even(Sedenion Union, Sedenion Value) { return (Union * Value + Value * Union) / 2; }
        public static Sedenion Cross(Sedenion Union, Sedenion Value) { return (Union * Value - Value * Union) / 2; }
        ///
        /// Operation 3 algorithms
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
        /// Trigonometric functions
        ///
        public static Sedenion Sin(Sedenion Value)
        {
            return Math.Sin(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                + Math.Cos(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
        }
        public static Sedenion Arcsin(Sedenion Value) { return Arcsin(Value, true, 0); }
        public static Sedenion Arcsin(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return -Sgn(Vector(Value)) * Arcsinh(Value * Sgn(Vector(Value))); }
            else { return pi - Arcsin(Value, true, Period); }
        }
        public static Sedenion Sinh(Sedenion Value)
        {
            return Math.Sinh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                + Math.Cosh(Scalar(Value)) * Sgn(Abs(Vector(Value))) * Math.Sin(Abs(Vector(Value)));
        }
        public static Sedenion Arcsinh(Sedenion Value) { return Arcsinh(Value, true, 0); }
        public static Sedenion Arcsinh(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return Ln(Value + Root(Power(Value, 2) + 1, 2), Period); }
            else { return pi * Sgn(Vector(Value)) - Arcsinh(Value, true, Period); }
        }
        public static Sedenion Cos(Sedenion Value)
        {
            return Math.Cos(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                - Math.Sin(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
        }
        public static Sedenion Arccos(Sedenion Value) { return Arccos(Value, true, 0); }
        public static Sedenion Arccos(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return -Sgn(Vector(Value)) * Arccosh(Value); }
            else { return 2 * pi - Arccos(Value, true, Period); }
        }
        public static Sedenion Cosh(Sedenion Value)
        {
            return Math.Cosh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                + Math.Sinh(Scalar(Value)) * Sgn(Abs(Vector(Value))) * Math.Sin(Abs(Vector(Value)));
        }
        public static Sedenion Arccosh(Sedenion Value) { return Arccosh(Value, true, 0); }
        public static Sedenion Arccosh(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return Ln(Value + Root(Power(Value, 2) - 1, 2), Period); }
            else { return 2 * pi * Sgn(Vector(Value)) - Arccosh(Value, true, Period); }
        }
        public static Sedenion Tan(Sedenion Value)
        {
            return Root(Power(Sec(Value), 2) - 1, 2);
        }
        public static Sedenion Arctan(Sedenion Value) { return Arctan(Value, true, 0); }
        public static Sedenion Arctan(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return -Sgn(Vector(Value)) * Arctanh(Value * Sgn(Vector(Value))); }
            else { return pi + Arctan(Value, true, Period); }
        }
        public static Sedenion Tanh(Sedenion Value)
        {
            return 1 - 2 * Inverse(Exp(2 * Value) + 1);
        }
        public static Sedenion Arctanh(Sedenion Value) { return Arctanh(Value, true, 0); }
        public static Sedenion Arctanh(Sedenion Value, bool Sign, long Period)
        {
            if (Sign == true) { return (Ln(1 + Value, Period) - Ln(1 - Value)) / 2; }
            else { return pi * Sgn(Vector(Value)) + Arctanh(Value, true, Period); }
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
        /// Conversion of Types
        ///
        public static string GetString(Sedenion Value) { return Value.ToString(); }
        public static Sedenion GetInstance(string Value)
        {
            if (Value.Replace(" ", "") == "0") { return new Sedenion(); }
            MatchCollection Matches = new Regex("e\\d+(?=-|\\+|$)").Matches(Value);
            if (Matches.Count == 0) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
            long Dimension = 0;
            for (int i = 0; i < Matches.Count; ++i)
            {
                Dimension = Math.Max(Dimension, long.Parse(Matches[i].Value.Substring(1)));
            }
            string[] Strings = new string[GetDimension(Dimension)];
            for (long i = 0; i < Strings.LongLength; ++i) { Strings[i] = "e" + i.ToString(); }
            return new Sedenion(Value.ToNumbers(Strings));
        }
        /* Casting */
        private Number ToNumber() { return numbers; }
        private Number ToNumber(int Dimension)
        {
            double[] Numbers = Data.ToArray();
            Array.Resize(ref Numbers, Math.Max(Length, Dimension));
            return new Number(Numbers);
        }
        private static Sedenion From(Number Number) { return new Sedenion(Number.ToArray()); }
    }
}
