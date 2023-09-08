using Cmplx.BaseType;
using Cmplx.MainType;
using System;
using System.Security;
using System.Runtime.Serialization;
using static Module;
using static Cmplx.BaseType.Vector1DModule;
using static Cmplx.MainType.Complex;
using static Cmplx.MainType.ComplexModule;
namespace Cmplx
{
    namespace BaseType
    {
        public struct Vector1D
        {
            ///
            /// basis
            ///
            private double x1;
            public Vector1D(double x1)
            {
                this.x1 = x1;
            }
            public override string ToString()
            {
                double[] Numbers = new double[] { x1 };
                return Numbers.ToString("e1");
            }
            public override bool Equals(object obj) {
                if (obj is Vector1D o) { return this == o; }
                else { return false; }
            }
            public double this[long index]
            {
                get
                {
                    index = PeriodShift(index, Period(GetType()));
                    switch (index)
                    {
                        case 1: return x1;
                        default: return this[index];
                    }
                }
                set
                {
                    index = PeriodShift(index, Period(GetType()));
                    switch (index)
                    {
                        case 1: x1 = value; break;
                        default: this[index] = value; break;
                    }
                }
            }
            public override int GetHashCode() { return 0; }
            public static explicit operator Vector1D(string Value) { return Vector1DModule.GetInstance(Value); }
            public static explicit operator string(Vector1D Value) { return GetString(Value); }
            public static implicit operator Vector1D(double Value)
            {
                if (Value == 0) { return new Vector1D(); }
                else { throw new Vector1DException("Non-zero value is not satisfy isomorphism to be a vector."); }
            }
            ///
            /// operators
            ///
            public static bool operator ==(Vector1D Union, Vector1D Value) { return Union.ToNumber() == Value.ToNumber(); }
            public static bool operator !=(Vector1D Union, Vector1D Value) { return !(Union == Value); }
            public static Vector1D operator +(Vector1D Value) { return Value; }
            public static Vector1D operator -(Vector1D Value) { return From(-Value.ToNumber()); }
            public static Vector1D operator +(Vector1D Union, Vector1D Value) { return From(Union.ToNumber() + Value.ToNumber()); }
            public static Complex operator +(double Union, Vector1D Value) { return new Complex(Union, Value); }
            public static Complex operator +(Vector1D Union, double Value) { return Value + Union; }
            public static Vector1D operator -(Vector1D Union, Vector1D Value) { return From(Union.ToNumber() - Value.ToNumber()); }
            public static Complex operator -(double Union, Vector1D Value) { return Union + (-Value); }
            public static Complex operator -(Vector1D Union, double Value) { return Union + (-Value); }
            public static Vector1D operator *(double Union, Vector1D Value) { return From(Union * Value.ToNumber()); }
            public static Vector1D operator *(Vector1D Union, double Value) { return From(Union.ToNumber() * Value); }
            public static Vector1D operator /(Vector1D Union, double Value) { return From(Union.ToNumber() / Value); }
            ///
            /// casing
            ///
            internal Number ToNumber()
            {
                return new Number(0, x1);
            }
            internal static Vector1D From(Number Number)
            {
                return new Vector1D(Number[1]);
            }
        }
        [Serializable]
        internal class Vector1DException : Exception
        {
            public Vector1DException() : base() { }
            public Vector1DException(string message) : base(message) { }
            public Vector1DException(string message, Exception innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected Vector1DException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class Vector1DModule
        {
            ///
            /// constants
            ///
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Vector1D e1 = new Vector1D(1);
            ///
            /// fundamentals
            ///
            public static double Abs(Vector1D Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static Vector1D Sgn(Vector1D Value) { return Value / Abs(Value); }
            public static double Dot(Vector1D Union, Vector1D Value) { return DotWithNumbers(Union, Value); }
            public static Vector1D Cross(Vector1D Union, Vector1D Value) { return CrossWithNumbers(Union, Value); }
            ///
            /// traits
            ///
            private static double DotWithNumbers(Vector1D Union, Vector1D Value)
            {
                return ComplexModule.Dot(Union, Value);
            }
            private static Vector1D CrossWithNumbers(Vector1D Union, Vector1D Value)
            {
                return Vector1D.From(ComplexModule.Cross(Union, Value).ToNumber());
            }
            ///
            /// conventions
            ///
            public static string GetString(Vector1D Value) { return Value.ToString(); }
            public static Vector1D GetInstance(string Value)
            {
                Vector1D RetValue = 0;
                double[] Numbers;
                try { Numbers = Value.ToNumbers("e1"); }
                catch (Exception Exception) { throw new Vector1DException("The string cannot be converted as a number.", Exception); }
                for (long i = 0; i < Numbers.LongLength; i++) { RetValue[i + 1] = Numbers[i]; }
                return RetValue;
            }
            public static Vector1D ToVector1D(this string Value) { return GetInstance(Value); }
        }
    }
    namespace MainType
    {
        public struct Complex
        {
            ///
            /// basis
            ///
            private double real;
            private Vector1D imaginary;
            public Complex(double s, Vector1D v)
            {
                real = s;
                imaginary = v;
            }
            public Complex(double s, double i)
            {
                real = s;
                imaginary = new Vector1D(i);
            }
            public override string ToString()
            {
                double[] Numbers = new double[] { real, imaginary[1] };
                return Numbers.ToString("", "i");
            }
            public override bool Equals(object obj)
            {
                if (obj is Complex o) { return this == o; }
                else { return false; }
            }
            public double this[long index]
            {
                get
                {
                    index %= Period(GetType());
                    switch (index)
                    {
                        case 0: return real;
                        default: return imaginary[index];
                    }
                }
                set
                {
                    index %= Period(GetType());
                    switch (index)
                    {
                        case 0: real = value; break;
                        default: imaginary[index] = value; break;
                    }
                }
            }
            public override int GetHashCode() { return 0; }
            public static explicit operator Complex(string Value) { return ComplexModule.GetInstance(Value); }
            public static explicit operator string(Complex Value) { return GetString(Value); }
            public static implicit operator Complex(double Value) { return new Complex(Value, new Vector1D()); }
            public static implicit operator Complex(Vector1D Value) { return new Complex(0, Value); }
            public static double Scalar(Complex Value) { return Value.real; }
            public static Vector1D Vector(Complex Value) { return Value.imaginary; }
            ///
            /// operators
            ///
            public static bool operator ==(Complex Union, Complex Value) { return Union.ToNumber() == Value.ToNumber(); }
            public static bool operator !=(Complex Union, Complex Value) { return !(Union == Value); }
            public static Complex operator +(Complex Value) { return Value; }
            public static Complex operator -(Complex Value) { return From(-Value.ToNumber()); }
            public static Complex operator ~(Complex Value) { return From(~Value.ToNumber()); }
            public static Complex operator ++(Complex Value) { return Value + 1; }
            public static Complex operator --(Complex Value) { return Value - 1; }
            public static Complex operator +(Complex Union, Complex Value) { return From(Union.ToNumber() + Value.ToNumber()); }
            public static Complex operator -(Complex Union, Complex Value) { return From(Union.ToNumber() - Value.ToNumber()); }
            public static Complex operator *(Complex Union, Complex Value) { return From(Union.ToNumber() * Value.ToNumber()); }
            public static Complex operator /(Complex Union, Complex Value)
            {
                if (Vector(Value) == 0) { return From(Union.ToNumber() / Scalar(Value)); }
                return Union * Inverse(Value);
            }
            public static Complex operator ^(Complex Base, long Exponent) { return Power(Base, Exponent); }
            ///
            /// casing
            ///
            internal Number ToNumber()
            {
                return new Number(real, imaginary[1]);
            }
            internal static Complex From(Number Number)
            {
                return new Complex(Number[0], Number[1]);
            }
        }
        [Serializable]
        internal class ComplexException : Exception
        {
            public ComplexException() : base() { }
            public ComplexException(string message) : base(message) { }
            public ComplexException(string message, Exception innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected ComplexException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class ComplexModule
        {
            ///
            /// constants
            ///
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Complex i = new Complex(0, 1);
            public static double Re(Complex z) { return Scalar(z); }
            public static double Im(Complex z) { return Vector(z)[0]; }
            ///
            /// fundamentals
            ///
            public static double Abs(Complex Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static double Arg(Complex Value) { return Arg(Value, 0); }
            public static double Arg(Complex Value, long Theta) { return Math.Acos(Scalar(Value) / Abs(Value)) + 2 * pi * Theta; }
            public static Complex Conjg(Complex Value) { return ~Value; }
            public static Complex Sgn(Complex Value) { return Value / Abs(Value); }
            public static Complex Inverse(Complex Value) { return Conjg(Value) / Dot(Value, Value); }
            public static Complex Exp(Complex Value) { return Math.Exp(Scalar(Value)) * (Math.Cos(Abs(Vector(Value))) + Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)))); }
            public static Complex Ln(Complex Value) { return Ln(Value, 0); }
            public static Complex Ln(Complex Value, long Theta) { return Math.Log(Abs(Value)) + (Vector(Value) == 0 ? 0 : Sgn(Vector(Value)) * Arg(Value, Theta)); }
            ///
            /// multiples
            ///
            public static double Dot(Complex Union, Complex Value) { return Scalar(Conjg(Union) * Value + Conjg(Value) * Union) / 2; }
            public static Complex Outer(Complex Union, Complex Value) { return (Conjg(Union) * Value - Conjg(Value) * Union) / 2; }
            public static Complex Even(Complex Union, Complex Value) { return (Union * Value + Value * Union) / 2; }
            public static Complex Cross(Complex Union, Complex Value) { return (Union * Value - Value * Union) / 2; }
            ///
            /// exponentials
            ///
            public static Complex Power(Complex Base, Complex Exponent) { return Power(Base, Exponent, 0); }
            public static Complex Power(Complex Base, Complex Exponent, long Theta)
            {
                return Exp(Exponent * Ln(Base, Theta));
            }
            public static Complex Power(Complex Base, double Exponent) { return Power(Base, Exponent, 0); }
            public static Complex Power(Complex Base, double Exponent, long Theta)
            {
                if (Base == 0) { return Exponent == 0 ? 1 : 0; }
                return Math.Pow(Abs(Base), Exponent) *
                    (Math.Cos(Exponent * Arg(Base, Theta)) + Sgn(Vector(Base)) * Math.Sin(Exponent * Arg(Base, Theta)));
            }
            public static Complex Root(Complex Base, Complex Exponent) { return Root(Base, Exponent, 0); }
            public static Complex Root(Complex Base, Complex Exponent, long Theta) { return Power(Base, Inverse(Exponent), Theta); }
            public static Complex Root(Complex Base, double Exponent) { return Root(Base, Exponent, 0); }
            public static Complex Root(Complex Base, double Exponent, long Theta) { return Power(Base, 1 / Exponent, Theta); }
            public static Complex Log(Complex Base, Complex Number) { return Log(Base, Number, 0, 0); }
            public static Complex Log(Complex Base, Complex Number, long Theta, long Phi)
            {
                return Ln(Number, Theta) / Ln(Base, Phi);
            }
            ///
            /// trigonometrics
            ///
            public static Complex Sin(Complex Value)
            {
                return Math.Sin(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                    + Math.Cos(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
            }
            public static Complex Arcsin(Complex Value) { return Arcsin(Value, true, 0); }
            public static Complex Arcsin(Complex Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arcsinh(Value * Sgn(Vector(Value))); }
                else { return pi - Arcsin(Value, true, Period); }
            }
            public static Complex Sinh(Complex Value)
            {
                return Math.Sinh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                    + Math.Cosh(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)));
            }
            public static Complex Arcsinh(Complex Value) { return Arcsinh(Value, true, 0); }
            public static Complex Arcsinh(Complex Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Power(Value, 2) + 1, 2), Period); }
                else { return pi * Sgn(Vector(Value)) - Arcsinh(Value, true, Period); }
            }
            public static Complex Cos(Complex Value)
            {
                return Math.Cos(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                    - Math.Sin(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
            }
            public static Complex Arccos(Complex Value) { return Arccos(Value, true, 0); }
            public static Complex Arccos(Complex Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arccosh(Value); }
                else { return 2 * pi - Arccos(Value, true, Period); }
            }
            public static Complex Cosh(Complex Value)
            {
                return Math.Cosh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                    + Math.Sinh(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)));
            }
            public static Complex Arccosh(Complex Value) { return Arccosh(Value, true, 0); }
            public static Complex Arccosh(Complex Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Power(Value, 2) - 1, 2), Period); }
                else { return 2 * pi * Sgn(Vector(Value)) - Arccosh(Value, true, Period); }
            }
            public static Complex Tan(Complex Value)
            {
                return Root(Power(Sec(Value), 2) - 1, 2);
            }
            public static Complex Arctan(Complex Value) { return Arctan(Value, true, 0); }
            public static Complex Arctan(Complex Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arctanh(Value * Sgn(Vector(Value))); }
                else { return pi + Arctan(Value, true, Period); }
            }
            public static Complex Tanh(Complex Value)
            {
                return 1 - 2 * Inverse(Exp(2 * Value) + 1);
            }
            public static Complex Arctanh(Complex Value) { return Arctanh(Value, true, 0); }
            public static Complex Arctanh(Complex Value, bool Sign, long Period)
            {
                if (Sign == true) { return (Ln(1 + Value, Period) - Ln(1 - Value)) / 2; }
                else { return pi * Sgn(Vector(Value)) + Arctanh(Value, true, Period); }
            }
            public static Complex Csc(Complex Value) { return Inverse(Sin(Value)); }
            public static Complex Arccsc(Complex Value) { return Arccsc(Value, true, 0); }
            public static Complex Arccsc(Complex Value, bool Sign, long Period) { return Arcsin(Inverse(Value), Sign, Period); }
            public static Complex Csch(Complex Value) { return Inverse(Sinh(Value)); }
            public static Complex Arccsch(Complex Value) { return Arccsch(Value, true, 0); }
            public static Complex Arccsch(Complex Value, bool Sign, long Period) { return Arcsinh(Inverse(Value), Sign, Period); }
            public static Complex Sec(Complex Value) { return Inverse(Cos(Value)); }
            public static Complex Arcsec(Complex Value) { return Arcsec(Value, true, 0); }
            public static Complex Arcsec(Complex Value, bool Sign, long Period) { return Arccos(Inverse(Value), Sign, Period); }
            public static Complex Sech(Complex Value) { return Inverse(Cosh(Value)); }
            public static Complex Arcsech(Complex Value) { return Arcsech(Value, true, 0); }
            public static Complex Arcsech(Complex Value, bool Sign, long Period) { return Arccosh(Inverse(Value), Sign, Period); }
            public static Complex Cot(Complex Value) { return Inverse(Tan(Value)); }
            public static Complex Arccot(Complex Value) { return Arccot(Value, true, 0); }
            public static Complex Arccot(Complex Value, bool Sign, long Period) { return Arctan(Inverse(Value), Sign, Period); }
            public static Complex Coth(Complex Value) { return Inverse(Tanh(Value)); }
            public static Complex Arccoth(Complex Value) { return Arccoth(Value, true, 0); }
            public static Complex Arccoth(Complex Value, bool Sign, long Period) { return Arctanh(Inverse(Value), Sign, Period); }
            ///
            /// conventions
            ///
            public static string GetString(Complex Value) { return Value.ToString(); }
            public static Complex GetInstance(string Value)
            {
                Complex RetValue = 0;
                double[] Numbers;
                try { Numbers = Value.ToNumbers("", "i"); }
                catch (Exception Exception) { throw new ComplexException("The string cannot be converted as a number.", Exception); }
                for (long i = 0; i < Numbers.LongLength; i++) { RetValue[i] = Numbers[i]; }
                return RetValue;
            }
            public static Complex ToComplex(this string Value) { return GetInstance(Value); }
        }
    }
}
