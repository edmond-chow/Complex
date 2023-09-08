using Cmplx3.BaseType;
using Cmplx3.MainType;
using System;
using System.Security;
using System.Runtime.Serialization;
using static Module;
using static Cmplx3.BaseType.Vector7DModule;
using static Cmplx3.MainType.Octonion;
using static Cmplx3.MainType.OctonionModule;
namespace Cmplx3
{
    namespace BaseType
    {
        public struct Vector7D
        {
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
            public Vector7D(double x1, double x2, double x3, double x4, double x5, double x6, double x7)
            {
                this.x1 = x1;
                this.x2 = x2;
                this.x3 = x3;
                this.x4 = x4;
                this.x5 = x5;
                this.x6 = x6;
                this.x7 = x7;
            }
            public override string ToString()
            {
                double[] Numbers = new double[] { x1, x2, x3, x4, x5, x6, x7 };
                return Numbers.ToString("e1", "e2", "e3", "e4", "e5", "e6", "e7");
            }
            public override bool Equals(object obj)
            {
                if (obj is Vector7D o) { return this == o; }
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
                        case 2: return x2;
                        case 3: return x3;
                        case 4: return x4;
                        case 5: return x5;
                        case 6: return x6;
                        case 7: return x7;
                        default: return this[index];
                    }
                }
                set
                {
                    index = PeriodShift(index, Period(GetType()));
                    switch (index)
                    {
                        case 1: x1 = value; break;
                        case 2: x2 = value; break;
                        case 3: x3 = value; break;
                        case 4: x4 = value; break;
                        case 5: x5 = value; break;
                        case 6: x6 = value; break;
                        case 7: x7 = value; break;
                        default: this[index] = value; break;
                    }
                }
            }
            public override int GetHashCode() { return 0; }
            public static explicit operator Vector7D(string Value) { return Vector7DModule.GetInstance(Value); }
            public static explicit operator string(Vector7D Value) { return GetString(Value); }
            public static implicit operator Vector7D(double Value)
            {
                if (Value == 0) { return new Vector7D(); }
                else { throw new Vector7DException("Non-zero value is not satisfy isomorphism to be a vector."); }
            }
            ///
            /// operators
            ///
            public static bool operator ==(Vector7D Union, Vector7D Value) { return Union.ToNumber() == Value.ToNumber(); }
            public static bool operator !=(Vector7D Union, Vector7D Value) { return !(Union == Value); }
            public static Vector7D operator +(Vector7D Value) { return Value; }
            public static Vector7D operator -(Vector7D Value) { return From(-Value.ToNumber()); }
            public static Vector7D operator +(Vector7D Union, Vector7D Value) { return From(Union.ToNumber() + Value.ToNumber()); }
            public static Octonion operator +(double Union, Vector7D Value) { return new Octonion(Union, Value); }
            public static Octonion operator +(Vector7D Union, double Value) { return Value + Union; }
            public static Vector7D operator -(Vector7D Union, Vector7D Value) { return From(Union.ToNumber() - Value.ToNumber()); }
            public static Octonion operator -(double s, Vector7D Value) { return s + (-Value); }
            public static Octonion operator -(Vector7D Union, double Value) { return Union + (-Value); }
            public static Vector7D operator *(double Union, Vector7D Value) { return From(Union * Value.ToNumber()); }
            public static Vector7D operator *(Vector7D Union, double Value) { return From(Union.ToNumber() * Value); }
            public static Vector7D operator /(Vector7D Union, double Value) { return From(Union.ToNumber() / Value); }
            ///
            /// casing
            ///
            internal Number ToNumber()
            {
                return new Number(0, x1, x2, x3, x4, x5, x6, x7);
            }
            internal static Vector7D From(Number Number)
            {
                return new Vector7D(Number[1], Number[2], Number[3], Number[4], Number[5], Number[6], Number[7]);
            }
        }
        [Serializable]
        internal class Vector7DException : Exception
        {
            public Vector7DException() : base() { }
            public Vector7DException(string message) : base(message) { }
            public Vector7DException(string message, Exception innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected Vector7DException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class Vector7DModule
        {
            ///
            /// constants
            ///
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Vector7D e1 = new Vector7D(1, 0, 0, 0, 0, 0, 0);
            public static readonly Vector7D e2 = new Vector7D(0, 1, 0, 0, 0, 0, 0);
            public static readonly Vector7D e3 = new Vector7D(0, 0, 1, 0, 0, 0, 0);
            public static readonly Vector7D e4 = new Vector7D(0, 0, 0, 1, 0, 0, 0);
            public static readonly Vector7D e5 = new Vector7D(0, 0, 0, 0, 1, 0, 0);
            public static readonly Vector7D e6 = new Vector7D(0, 0, 0, 0, 0, 1, 0);
            public static readonly Vector7D e7 = new Vector7D(0, 0, 0, 0, 0, 0, 1);
            ///
            /// fundamentals
            ///
            public static double Abs(Vector7D Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static Vector7D Sgn(Vector7D Value) { return Value / Abs(Value); }
            public static double Dot(Vector7D Union, Vector7D Value) { return DotWithNumbers(Union, Value); }
            public static Vector7D Cross(Vector7D Union, Vector7D Value) { return CrossWithNumbers(Union, Value); }
            ///
            /// traits
            ///
            private static double DotWithNumbers(Vector7D Union, Vector7D Value)
            {
                return OctonionModule.Dot(Union, Value);
            }
            private static Vector7D CrossWithNumbers(Vector7D Union, Vector7D Value)
            {
                return Vector7D.From(OctonionModule.Cross(Union, Value).ToNumber());
            }
            ///
            /// conventions
            ///
            public static string GetString(Vector7D Value) { return Value.ToString(); }
            public static Vector7D GetInstance(string Value)
            {
                Vector7D RetValue = 0;
                double[] Numbers;
                try { Numbers = Value.ToNumbers("e1", "e2", "e3", "e4", "e5", "e6", "e7"); }
                catch (Exception Exception) { throw new Vector7DException("The string cannot be converted as a number.", Exception); }
                for (long i = 0; i < Numbers.LongLength; i++) { RetValue[i + 1] = Numbers[i]; }
                return RetValue;
            }
            public static Vector7D ToVector7D(this string Value) { return GetInstance(Value); }
        }
    }
    namespace MainType
    {
        public struct Octonion
        {
            ///
            /// basis
            ///
            private double real;
            private Vector7D imaginary;
            public Octonion(double s, Vector7D v)
            {
                real = s;
                imaginary = v;
            }
            public Octonion(double s, double i, double j, double k, double l, double il, double jl, double kl)
            {
                real = s;
                imaginary = new Vector7D(i, j, k, l, il, jl, kl);
            }
            public override string ToString()
            {
                double[] Numbers = new double[] { real, imaginary[1], imaginary[2], imaginary[3], imaginary[4], imaginary[5], imaginary[6], imaginary[7] };
                return Numbers.ToString("", "i", "j", "k", "l", "il", "jl", "kl");
            }
            public override bool Equals(object obj)
            {
                if (obj is Octonion o) { return this == o; }
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
            public static explicit operator Octonion(string Value) { return OctonionModule.GetInstance(Value); }
            public static explicit operator string(Octonion Value) { return GetString(Value); }
            public static implicit operator Octonion(double Value) { return new Octonion(Value, new Vector7D()); }
            public static implicit operator Octonion(Vector7D Value) { return new Octonion(0, Value); }
            public static double Scalar(Octonion Value) { return Value.real; }
            public static Vector7D Vector(Octonion Value) { return Value.imaginary; }
            ///
            /// operators
            ///
            public static bool operator ==(Octonion Union, Octonion Value) { return Union.ToNumber() == Value.ToNumber(); }
            public static bool operator !=(Octonion Union, Octonion Value) { return !(Union == Value); }
            public static Octonion operator +(Octonion Value) { return Value; }
            public static Octonion operator -(Octonion Value) { return From(-Value.ToNumber()); }
            public static Octonion operator ~(Octonion Value) { return From(~Value.ToNumber()); }
            public static Octonion operator ++(Octonion Value) { return Value + 1; }
            public static Octonion operator --(Octonion Value) { return Value - 1; }
            public static Octonion operator +(Octonion Union, Octonion Value) { return From(Union.ToNumber() + Value.ToNumber()); }
            public static Octonion operator -(Octonion Union, Octonion Value) { return From(Union.ToNumber() - Value.ToNumber()); }
            public static Octonion operator *(Octonion Union, Octonion Value) { return From(Union.ToNumber() * Value.ToNumber()); }
            public static Octonion operator /(Octonion Union, Octonion Value)
            {
                if (Vector(Value) == 0) { return From(Union.ToNumber() / Scalar(Value)); }
                return Union * Inverse(Value);
            }
            public static Octonion operator ^(Octonion Base, long Exponent) { return Power(Base, Exponent); }
            ///
            /// casing
            ///
            internal Number ToNumber()
            {
                return new Number(real, imaginary[1], imaginary[2], imaginary[3], imaginary[4], imaginary[5], imaginary[6], imaginary[7]);
            }
            internal static Octonion From(Number Number)
            {
                return new Octonion(Number[0], Number[1], Number[2], Number[3], Number[4], Number[5], Number[6], Number[7]);
            }
        }
        [Serializable]
        internal class OctonionException : Exception
        {
            public OctonionException() : base() { }
            public OctonionException(string message) : base(message) { }
            public OctonionException(string message, Exception innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected OctonionException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class OctonionModule
        {
            ///
            /// constants
            ///
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Octonion i = new Octonion(0, 1, 0, 0, 0, 0, 0, 0);
            public static readonly Octonion j = new Octonion(0, 0, 1, 0, 0, 0, 0, 0);
            public static readonly Octonion k = new Octonion(0, 0, 0, 1, 0, 0, 0, 0);
            public static readonly Octonion l = new Octonion(0, 0, 0, 0, 1, 0, 0, 0);
            public static readonly Octonion il = new Octonion(0, 0, 0, 0, 0, 1, 0, 0);
            public static readonly Octonion jl = new Octonion(0, 0, 0, 0, 0, 0, 1, 0);
            public static readonly Octonion kl = new Octonion(0, 0, 0, 0, 0, 0, 0, 1);
            ///
            /// fundamentals
            ///
            public static double Abs(Octonion Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static double Arg(Octonion Value) { return Arg(Value, 0); }
            public static double Arg(Octonion Value, long Theta) { return Math.Acos(Scalar(Value) / Abs(Value)) + 2 * pi * Theta; }
            public static Octonion Conjg(Octonion Value) { return ~Value; }
            public static Octonion Sgn(Octonion Value) { return Value / Abs(Value); }
            public static Octonion Inverse(Octonion Value) { return Conjg(Value) / Dot(Value, Value); }
            public static Octonion Exp(Octonion Value) { return Math.Exp(Scalar(Value)) * (Math.Cos(Abs(Vector(Value))) + Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)))); }
            public static Octonion Ln(Octonion Value) { return Ln(Value, 0); }
            public static Octonion Ln(Octonion Value, long Theta) { return Math.Log(Abs(Value)) + (Vector(Value) == 0 ? 0 : Sgn(Vector(Value)) * Arg(Value, Theta)); }
            ///
            /// multiples
            ///
            public static double Dot(Octonion Union, Octonion Value) { return Scalar(Conjg(Union) * Value + Conjg(Value) * Union) / 2; }
            public static Octonion Outer(Octonion Union, Octonion Value) { return (Conjg(Union) * Value - Conjg(Value) * Union) / 2; }
            public static Octonion Even(Octonion Union, Octonion Value) { return (Union * Value + Value * Union) / 2; }
            public static Octonion Cross(Octonion Union, Octonion Value) { return (Union * Value - Value * Union) / 2; }
            ///
            /// exponentials
            ///
            public static Octonion Power(Octonion Base, Octonion Exponent) { return Power(Base, Exponent, 0, 0, 0); }
            public static Octonion Power(Octonion Base, Octonion Exponent, long Theta, long Phi, long Tau)
            {
                return Exp(Exp(Ln(Ln(Base, Theta), Phi) + Ln(Exponent, Tau)));
            }
            public static Octonion Power(Octonion Base, double Exponent) { return Power(Base, Exponent, 0); }
            public static Octonion Power(Octonion Base, double Exponent, long Theta)
            {
                if (Base == 0) { return Exponent == 0 ? 1 : 0; }
                return Math.Pow(Abs(Base), Exponent) *
                    (Math.Cos(Exponent * Arg(Base, Theta)) + Sgn(Vector(Base)) * Math.Sin(Exponent * Arg(Base, Theta)));
            }
            public static Octonion Root(Octonion Base, Octonion Exponent) { return Root(Base, Exponent, 0, 0, 0); }
            public static Octonion Root(Octonion Base, Octonion Exponent, long Theta, long Phi, long Tau) { return Power(Base, Inverse(Exponent), Theta, Phi, Tau); }
            public static Octonion Root(Octonion Base, double Exponent) { return Root(Base, Exponent, 0); }
            public static Octonion Root(Octonion Base, double Exponent, long Theta) { return Power(Base, 1 / Exponent, Theta); }
            public static Octonion Log(Octonion Base, Octonion Number) { return Log(Base, Number, 0, 0, 0, 0); }
            public static Octonion Log(Octonion Base, Octonion Number, long Theta, long Phi, long Tau, long Omega)
            {
                return Exp(Ln(Ln(Number, Theta), Phi) - Ln(Ln(Base, Tau), Omega));
            }
            ///
            /// trigonometrics
            ///
            public static Octonion Sin(Octonion Value)
            {
                return Math.Sin(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                    + Math.Cos(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
            }
            public static Octonion Arcsin(Octonion Value) { return Arcsin(Value, true, 0); }
            public static Octonion Arcsin(Octonion Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arcsinh(Value * Sgn(Vector(Value))); }
                else { return pi - Arcsin(Value, true, Period); }
            }
            public static Octonion Sinh(Octonion Value)
            {
                return Math.Sinh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                    + Math.Cosh(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)));
            }
            public static Octonion Arcsinh(Octonion Value) { return Arcsinh(Value, true, 0); }
            public static Octonion Arcsinh(Octonion Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Power(Value, 2) + 1, 2), Period); }
                else { return pi * Sgn(Vector(Value)) - Arcsinh(Value, true, Period); }
            }
            public static Octonion Cos(Octonion Value)
            {
                return Math.Cos(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                    - Math.Sin(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
            }
            public static Octonion Arccos(Octonion Value) { return Arccos(Value, true, 0); }
            public static Octonion Arccos(Octonion Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arccosh(Value); }
                else { return 2 * pi - Arccos(Value, true, Period); }
            }
            public static Octonion Cosh(Octonion Value)
            {
                return Math.Cosh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                    + Math.Sinh(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)));
            }
            public static Octonion Arccosh(Octonion Value) { return Arccosh(Value, true, 0); }
            public static Octonion Arccosh(Octonion Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Power(Value, 2) - 1, 2), Period); }
                else { return 2 * pi * Sgn(Vector(Value)) - Arccosh(Value, true, Period); }
            }
            public static Octonion Tan(Octonion Value)
            {
                return Root(Power(Sec(Value), 2) - 1, 2);
            }
            public static Octonion Arctan(Octonion Value) { return Arctan(Value, true, 0); }
            public static Octonion Arctan(Octonion Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arctanh(Value * Sgn(Vector(Value))); }
                else { return pi + Arctan(Value, true, Period); }
            }
            public static Octonion Tanh(Octonion Value)
            {
                return 1 - 2 * Inverse(Exp(2 * Value) + 1);
            }
            public static Octonion Arctanh(Octonion Value) { return Arctanh(Value, true, 0); }
            public static Octonion Arctanh(Octonion Value, bool Sign, long Period)
            {
                if (Sign == true) { return (Ln(1 + Value, Period) - Ln(1 - Value)) / 2; }
                else { return pi * Sgn(Vector(Value)) + Arctanh(Value, true, Period); }
            }
            public static Octonion Csc(Octonion Value) { return Inverse(Sin(Value)); }
            public static Octonion Arccsc(Octonion Value) { return Arccsc(Value, true, 0); }
            public static Octonion Arccsc(Octonion Value, bool Sign, long Period) { return Arcsin(Inverse(Value), Sign, Period); }
            public static Octonion Csch(Octonion Value) { return Inverse(Sinh(Value)); }
            public static Octonion Arccsch(Octonion Value) { return Arccsch(Value, true, 0); }
            public static Octonion Arccsch(Octonion Value, bool Sign, long Period) { return Arcsinh(Inverse(Value), Sign, Period); }
            public static Octonion Sec(Octonion Value) { return Inverse(Cos(Value)); }
            public static Octonion Arcsec(Octonion Value) { return Arcsec(Value, true, 0); }
            public static Octonion Arcsec(Octonion Value, bool Sign, long Period) { return Arccos(Inverse(Value), Sign, Period); }
            public static Octonion Sech(Octonion Value) { return Inverse(Cosh(Value)); }
            public static Octonion Arcsech(Octonion Value) { return Arcsech(Value, true, 0); }
            public static Octonion Arcsech(Octonion Value, bool Sign, long Period) { return Arccosh(Inverse(Value), Sign, Period); }
            public static Octonion Cot(Octonion Value) { return Inverse(Tan(Value)); }
            public static Octonion Arccot(Octonion Value) { return Arccot(Value, true, 0); }
            public static Octonion Arccot(Octonion Value, bool Sign, long Period) { return Arctan(Inverse(Value), Sign, Period); }
            public static Octonion Coth(Octonion Value) { return Inverse(Tanh(Value)); }
            public static Octonion Arccoth(Octonion Value) { return Arccoth(Value, true, 0); }
            public static Octonion Arccoth(Octonion Value, bool Sign, long Period) { return Arctanh(Inverse(Value), Sign, Period); }
            ///
            /// conventions
            ///
            public static string GetString(Octonion Value) { return Value.ToString(); }
            public static Octonion GetInstance(string Value)
            {
                Octonion RetValue = 0;
                double[] Numbers;
                try { Numbers = Value.ToNumbers("", "i", "j", "k", "l", "il", "jl", "kl"); }
                catch (Exception Exception) { throw new OctonionException("The string cannot be converted as a number.", Exception); }
                for (long i = 0; i < Numbers.LongLength; i++) { RetValue[i] = Numbers[i]; }
                return RetValue;
            }
            public static Octonion ToOctonion(this string Value) { return GetInstance(Value); }
        }
    }
}
