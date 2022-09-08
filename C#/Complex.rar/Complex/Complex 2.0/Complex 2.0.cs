using Cmplx2.BaseType;
using Cmplx2.MainType;
using System;
using System.Security;
using System.Runtime.Serialization;
using static Cmplx2.Module;
using static Cmplx2.BaseType.Vector3DModule;
using static Cmplx2.MainType.Quaternion;
using static Cmplx2.MainType.QuaternionModule;
namespace Cmplx2
{
    namespace BaseType
    {
        public struct Vector3D
        {
            ///
            /// Initializer
            ///
            private double x1;
            private double x2;
            private double x3;
            public Vector3D(double x1, double x2, double x3)
            {
                this.x1 = x1;
                this.x2 = x2;
                this.x3 = x3;
            }
            public override string ToString()
            {
                double[] Numbers = new double[] { x1, x2, x3 };
                return Numbers.ToString("e1", "e2", "e3");
            }
            public override bool Equals(object obj)
            {
                if (obj is Vector3D o) { return this == o; }
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
                        default: this[index] = value; break;
                    }
                }
            }
            public override int GetHashCode() { return 0; }
            public static explicit operator Vector3D(string Value) { return CType_Vector3D(Value); }
            public static explicit operator string(Vector3D Value) { return CType_String(Value); }
            public static implicit operator Vector3D(double Value)
            {
                if (Value == 0) { return new Vector3D(); }
                else { throw new Vector3DException("Non-zero value is not satisfy isomorphism to be a vector."); }
            }
            ///
            /// Operators
            ///
            public static bool operator ==(Vector3D Union, Vector3D Value) { return Union.ToNumber() == Value.ToNumber(); }
            public static bool operator !=(Vector3D Union, Vector3D Value) { return !(Union == Value); }
            public static Vector3D operator +(Vector3D Value) { return Value; }
            public static Vector3D operator -(Vector3D Value) { return From(-Value.ToNumber()); }
            public static Vector3D operator +(Vector3D Union, Vector3D Value) { return From(Union.ToNumber() + Value.ToNumber()); }
            public static Quaternion operator +(double Union, Vector3D Value) { return new Quaternion(Union, Value); }
            public static Quaternion operator +(Vector3D Union, double Value) { return Value + Union; }
            public static Vector3D operator -(Vector3D Union, Vector3D Value) { return From(Union.ToNumber() - Value.ToNumber()); }
            public static Quaternion operator -(double Union, Vector3D Value) { return Union + (-Value); }
            public static Quaternion operator -(Vector3D Union, double Value) { return Union + (-Value); }
            public static Vector3D operator *(double Union, Vector3D Value) { return From(Union * Value.ToNumber()); }
            public static Vector3D operator *(Vector3D Union, double Value) { return From(Union.ToNumber() * Value); }
            public static Vector3D operator /(Vector3D Union, double Value) { return From(Union.ToNumber() / Value); }
            /* Casting */
            internal Number ToNumber()
            {
                return new Number(0, x1, x2, x3);
            }
            internal static Vector3D From(Number N)
            {
                return new Vector3D(N[1], N[2], N[3]);
            }
        }
        [Serializable]
        internal class Vector3DException : Exception
        {
            public Vector3DException() : base() { }
            public Vector3DException(string message) : base(message) { }
            public Vector3DException(string message, Vector3DException innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected Vector3DException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class Vector3DModule
        {
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Vector3D e1 = new Vector3D(1, 0, 0);
            public static readonly Vector3D e2 = new Vector3D(0, 1, 0);
            public static readonly Vector3D e3 = new Vector3D(0, 0, 1);
            ///
            /// Basic functions for constructing vectors
            ///
            public static double Abs(Vector3D Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static Vector3D Sgn(Vector3D Value) { return Value / Abs(Value); }
            public static double Dot(Vector3D Union, Vector3D Value) { return Build_In_Dot(Union, Value); }
            public static Vector3D Cross(Vector3D Union, Vector3D Value) { return Build_In_Cross(Union, Value); }
            /* Build_In */
            private static double Build_In_Dot(Vector3D Union, Vector3D Value)
            {
                return QuaternionModule.Dot(Union, Value);
            }
            private static Vector3D Build_In_Cross(Vector3D Union, Vector3D Value)
            {
                return Vector3D.From(QuaternionModule.Cross(Union, Value).ToNumber());
            }
            ///
            /// Conversion of Types
            ///
            public static string CType_String(Vector3D Value) { return Value.ToString(); }
            public static Vector3D CType_Vector3D(string Value)
            {
                Vector3D RetValue = 0;
                double[] Numbers;
                try { Numbers = Value.ToNumbers("e1", "e2", "e3"); }
                catch (Exception) { throw new Vector3DException("The string cannot be converted as a number."); }
                RetValue[1] = Numbers[1];
                RetValue[2] = Numbers[2];
                RetValue[3] = Numbers[3];
                return RetValue;
            }
            public static Vector3D ToVector3D(this string Value) { return CType_Vector3D(Value); }
        }
    }
    namespace MainType
    {
        public struct Quaternion
        {
            ///
            /// Initializer
            ///
            private double real;
            private Vector3D imaginary;
            public Quaternion(double s, Vector3D v)
            {
                real = s;
                imaginary = v;
            }
            public Quaternion(double s, double i, double j, double k)
            {
                real = s;
                imaginary = new Vector3D(i, j, k);
            }
            public override string ToString()
            {
                double[] Numbers = new double[] { real, imaginary[1], imaginary[2], imaginary[3] };
                return Numbers.ToString("", "i", "j", "k");
            }
            public override bool Equals(object obj)
            {
                if (obj is Quaternion o) { return this == o; }
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
            public static explicit operator Quaternion(string Value) { return CType_Quaternion(Value); }
            public static explicit operator string(Quaternion Value) { return CType_String(Value); }
            public static implicit operator Quaternion(double Value) { return new Quaternion(Value, new Vector3D()); }
            public static implicit operator Quaternion(Vector3D Value) { return new Quaternion(0, Value); }
            public static double Scalar(Quaternion Value) { return Value.real; }
            public static Vector3D Vector(Quaternion Value) { return Value.imaginary; }
            ///
            /// Operators
            ///
            public static bool operator ==(Quaternion Union, Quaternion Value) { return Union.ToNumber() == Value.ToNumber(); }
            public static bool operator !=(Quaternion Union, Quaternion Value) { return !(Union == Value); }
            public static Quaternion operator +(Quaternion Value) { return Value; }
            public static Quaternion operator -(Quaternion Value) { return From(-Value.ToNumber()); }
            public static Quaternion operator ~(Quaternion Value) { return From(~Value.ToNumber()); }
            public static Quaternion operator ++(Quaternion Value) { return Value + 1; }
            public static Quaternion operator --(Quaternion Value) { return Value - 1; }
            public static Quaternion operator +(Quaternion Union, Quaternion Value) { return From(Union.ToNumber() + Value.ToNumber()); }
            public static Quaternion operator -(Quaternion Union, Quaternion Value) { return From(Union.ToNumber() - Value.ToNumber()); }
            public static Quaternion operator *(Quaternion Union, Quaternion Value) { return From(Union.ToNumber() * Value.ToNumber()); }
            public static Quaternion operator /(Quaternion Union, Quaternion Value)
            {
                if (Vector(Value) == 0) { return From(Union.ToNumber() / Scalar(Value)); }
                return Union * Inverse(Value);
            }
            public static Quaternion operator ^(Quaternion Base, long Exponent) { return Power(Base, Exponent); }
            /* Casting */
            internal Number ToNumber()
            {
                return new Number(real, imaginary[1], imaginary[2], imaginary[3]);
            }
            internal static Quaternion From(Number N)
            {
                return new Quaternion(N[0], N[1], N[2], N[3]);
            }
        }
        [Serializable]
        internal class QuaternionException : Exception
        {
            public QuaternionException() : base() { }
            public QuaternionException(string message) : base(message) { }
            public QuaternionException(string message, QuaternionException innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected QuaternionException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class QuaternionModule
        {
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Quaternion i = new Quaternion(0, 1, 0, 0);
            public static readonly Quaternion j = new Quaternion(0, 0, 1, 0);
            public static readonly Quaternion k = new Quaternion(0, 0, 0, 1);
            ///
            /// Basic functions for constructing numbers
            ///
            public static double Abs(Quaternion Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static double Arg(Quaternion Value) { return Arg(Value, 0); }
            public static double Arg(Quaternion Value, long Theta) { return Math.Acos(Scalar(Value) / Abs(Value)) + 2 * pi * Theta; }
            public static Quaternion Conjg(Quaternion Value) { return ~Value; }
            public static Quaternion Sgn(Quaternion Value) { return Value / Abs(Value); }
            public static Quaternion Inverse(Quaternion Value) { return Conjg(Value) / Dot(Value, Value); }
            public static Quaternion Exp(Quaternion Value) { return Math.Exp(Scalar(Value)) * (Math.Cos(Abs(Vector(Value))) + Sgn(Vector(Value)) * Math.Sin(Abs(Vector(Value)))); }
            public static Quaternion Ln(Quaternion Value) { return Ln(Value, 0); }
            public static Quaternion Ln(Quaternion Value, long Theta) { return Math.Log(Abs(Value)) + Sgn(Vector(Value)) * Arg(Value, Theta); }
            ///
            /// 1st rank tensor algorithms
            ///
            public static double Dot(Quaternion Union, Quaternion Value) { return Scalar(Conjg(Union) * Value + Conjg(Value) * Union) / 2; }
            public static Quaternion Outer(Quaternion Union, Quaternion Value) { return (Conjg(Union) * Value - Conjg(Value) * Union) / 2; }
            public static Quaternion Even(Quaternion Union, Quaternion Value) { return (Union * Value + Value * Union) / 2; }
            public static Quaternion Cross(Quaternion Union, Quaternion Value) { return (Union * Value - Value * Union) / 2; }
            ///
            /// Operation 3 algorithms
            ///
            public static Quaternion Power(Quaternion Base, Quaternion Exponent) { return Power(Base, Exponent, 0, 0, 0); }
            public static Quaternion Power(Quaternion Base, Quaternion Exponent, long Theta, long Phi, long Tau)
            {
                return Exp(Exp(Ln(Ln(Base, Theta), Phi) + Ln(Exponent, Tau)));
            }
            public static Quaternion Power(Quaternion Base, double Exponent) { return Power(Base, Exponent, 0); }
            public static Quaternion Power(Quaternion Base, double Exponent, long Theta)
            {
                if (Base == 0) { return Exponent == 0 ? 1 : 0; }
                return Math.Pow(Abs(Base), Exponent) *
                    (Math.Cos(Exponent * Arg(Base, Theta)) + Sgn(Vector(Base)) * Math.Sin(Exponent * Arg(Base, Theta)));
            }
            public static Quaternion Root(Quaternion Base, Quaternion Exponent) { return Root(Base, Exponent, 0, 0, 0); }
            public static Quaternion Root(Quaternion Base, Quaternion Exponent, long Theta, long Phi, long Tau) { return Power(Base, Inverse(Exponent), Theta, Phi, Tau); }
            public static Quaternion Root(Quaternion Base, double Exponent) { return Root(Base, Exponent, 0); }
            public static Quaternion Root(Quaternion Base, double Exponent, long Theta) { return Power(Base, 1 / Exponent, Theta); }
            public static Quaternion Log(Quaternion Base, Quaternion Number) { return Log(Base, Number, 0, 0, 0, 0); }
            public static Quaternion Log(Quaternion Base, Quaternion Number, long Theta, long Phi, long Tau, long Omega)
            {
                return Exp(Ln(Ln(Number, Theta), Phi) - Ln(Ln(Base, Tau), Omega));
            }
            ///
            /// Trigonometric functions
            ///
            public static Quaternion Sin(Quaternion Value)
            {
                return Math.Sin(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                    + Math.Cos(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
            }
            public static Quaternion Arcsin(Quaternion Value) { return Arcsin(Value, true, 0); }
            public static Quaternion Arcsin(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arcsinh(Value * Sgn(Vector(Value))); }
                else { return pi - Arcsin(Value, true, Period); }
            }
            public static Quaternion Sinh(Quaternion Value)
            {
                return Math.Sinh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                    + Math.Cosh(Scalar(Value)) * Sgn(Abs(Vector(Value))) * Math.Sin(Abs(Vector(Value)));
            }
            public static Quaternion Arcsinh(Quaternion Value) { return Arcsinh(Value, true, 0); }
            public static Quaternion Arcsinh(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Power(Value, 2) + 1, 2), Period); }
                else { return pi * Sgn(Vector(Value)) - Arcsinh(Value, true, Period); }
            }
            public static Quaternion Cos(Quaternion Value)
            {
                return Math.Cos(Scalar(Value)) * Math.Cosh(Abs(Vector(Value)))
                    - Math.Sin(Scalar(Value)) * Sgn(Vector(Value)) * Math.Sinh(Abs(Vector(Value)));
            }
            public static Quaternion Arccos(Quaternion Value) { return Arccos(Value, true, 0); }
            public static Quaternion Arccos(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arccosh(Value); }
                else { return 2 * pi - Arccos(Value, true, Period); }
            }
            public static Quaternion Cosh(Quaternion Value)
            {
                return Math.Cosh(Scalar(Value)) * Math.Cos(Abs(Vector(Value)))
                    + Math.Sinh(Scalar(Value)) * Sgn(Abs(Vector(Value))) * Math.Sin(Abs(Vector(Value)));
            }
            public static Quaternion Arccosh(Quaternion Value) { return Arccosh(Value, true, 0); }
            public static Quaternion Arccosh(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Power(Value, 2) - 1, 2), Period); }
                else { return 2 * pi * Sgn(Vector(Value)) - Arccosh(Value, true, Period); }
            }
            public static Quaternion Tan(Quaternion Value)
            {
                return Root(Power(Sec(Value), 2) - 1, 2);
            }
            public static Quaternion Arctan(Quaternion Value) { return Arctan(Value, true, 0); }
            public static Quaternion Arctan(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return -Sgn(Vector(Value)) * Arctanh(Value * Sgn(Vector(Value))); }
                else { return pi + Arctan(Value, true, Period); }
            }
            public static Quaternion Tanh(Quaternion Value)
            {
                return 1 - 2 * Inverse(Exp(2 * Value) + 1);
            }
            public static Quaternion Arctanh(Quaternion Value) { return Arctanh(Value, true, 0); }
            public static Quaternion Arctanh(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return (Ln(1 + Value, Period) - Ln(1 - Value)) / 2; }
                else { return pi * Sgn(Vector(Value)) + Arctanh(Value, true, Period); }
            }
            public static Quaternion Csc(Quaternion Value) { return Inverse(Sin(Value)); }
            public static Quaternion Arccsc(Quaternion Value) { return Arccsc(Value, true, 0); }
            public static Quaternion Arccsc(Quaternion Value, bool Sign, long Period) { return Arcsin(Inverse(Value), Sign, Period); }
            public static Quaternion Csch(Quaternion Value) { return Inverse(Sinh(Value)); }
            public static Quaternion Arccsch(Quaternion Value) { return Arccsch(Value, true, 0); }
            public static Quaternion Arccsch(Quaternion Value, bool Sign, long Period) { return Arcsinh(Inverse(Value), Sign, Period); }
            public static Quaternion Sec(Quaternion Value) { return Inverse(Cos(Value)); }
            public static Quaternion Arcsec(Quaternion Value) { return Arcsec(Value, true, 0); }
            public static Quaternion Arcsec(Quaternion Value, bool Sign, long Period) { return Arccos(Inverse(Value), Sign, Period); }
            public static Quaternion Sech(Quaternion Value) { return Inverse(Cosh(Value)); }
            public static Quaternion Arcsech(Quaternion Value) { return Arcsech(Value, true, 0); }
            public static Quaternion Arcsech(Quaternion Value, bool Sign, long Period) { return Arccosh(Inverse(Value), Sign, Period); }
            public static Quaternion Cot(Quaternion Value) { return Inverse(Tan(Value)); }
            public static Quaternion Arccot(Quaternion Value) { return Arccot(Value, true, 0); }
            public static Quaternion Arccot(Quaternion Value, bool Sign, long Period) { return Arctan(Inverse(Value), Sign, Period); }
            public static Quaternion Coth(Quaternion Value) { return Inverse(Tanh(Value)); }
            public static Quaternion Arccoth(Quaternion Value) { return Arccoth(Value, true, 0); }
            public static Quaternion Arccoth(Quaternion Value, bool Sign, long Period) { return Arctanh(Inverse(Value), Sign, Period); }
            ///
            /// Conversion of Types
            ///
            public static string CType_String(Quaternion Value) { return Value.ToString(); }
            public static Quaternion CType_Quaternion(string Value)
            {
                Quaternion RetValue = 0;
                double[] Numbers;
                try { Numbers = Value.ToNumbers("", "i", "j", "k"); }
                catch (Exception) { throw new QuaternionException("The string cannot be converted as a number."); }
                RetValue[0] = Numbers[0];
                RetValue[1] = Numbers[1];
                RetValue[2] = Numbers[2];
                RetValue[3] = Numbers[3];
                return RetValue;
            }
            public static Quaternion ToQuaternion(this string Value) { return CType_Quaternion(Value); }
        }
    }
}
