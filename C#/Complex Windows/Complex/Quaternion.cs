﻿/*
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
using Quter.BaseType;
using Quter.MainType;
using System;
using System.Security;
using System.Runtime.Serialization;
using static Module;
using static Quter.BaseType.Vector3DModule;
using static Quter.MainType.Quaternion;
using static Quter.MainType.QuaternionModule;
namespace Quter
{
    namespace BaseType
    {
        public struct Vector3D : INumber
        {
            ///
            /// basis
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
                    Adjust(ref index, Period(GetType()), true);
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
                    Adjust(ref index, Period(GetType()), true);
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
            public static explicit operator Vector3D(string Value) { return Vector3DModule.GetInstance(Value); }
            public static explicit operator string(Vector3D Value) { return GetString(Value); }
            public static implicit operator Vector3D(double Value)
            {
                if (Value == 0) { return new Vector3D(); }
                else { throw new Vector3DException("Non-zero value is not satisfy isomorphism to be a vector."); }
            }
            ///
            /// operators
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
            ///
            /// casing
            ///
            internal Number ToNumber()
            {
                return new Number(x1, x2, x3);
            }
            internal static Vector3D From(Number Number)
            {
                return new Vector3D(Number[0], Number[1], Number[2]);
            }
        }
        [Serializable]
        internal class Vector3DException : Exception
        {
            public Vector3DException() : base() { }
            public Vector3DException(string message) : base(message) { }
            public Vector3DException(string message, Exception innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected Vector3DException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class Vector3DModule
        {
            ///
            /// constants
            ///
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Vector3D e1 = new Vector3D(1, 0, 0);
            public static readonly Vector3D e2 = new Vector3D(0, 1, 0);
            public static readonly Vector3D e3 = new Vector3D(0, 0, 1);
            ///
            /// fundamentals
            ///
            public static double Abs(Vector3D Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static Vector3D Sgn(Vector3D Value) { return Value / Abs(Value); }
            public static double Dot(Vector3D Union, Vector3D Value)
            {
                return Number.VectorDot(Union.ToNumber(), Value.ToNumber());
            }
            public static Vector3D Cross(Vector3D Union, Vector3D Value)
            {
                return Vector3D.From(Number.VectorCross(Union.ToNumber(), Value.ToNumber()));
            }
            ///
            /// conventions
            ///
            public static string GetString(Vector3D Value) { return Value.ToString(); }
            public static Vector3D GetInstance(string Value)
            {
                string Replaced = Value.Replace(" ", "");
                Vector3D Result = 0;
                try { Replaced.ToNumbers(ref Result, true, "e1", "e2", "e3"); }
                catch (Exception Exception) { throw new Vector3DException("The string cannot be converted as a number.", Exception); }
                return Result;
            }
            public static Vector3D ToVector3D(this string Value) { return GetInstance(Value); }
        }
    }
    namespace MainType
    {
        public struct Quaternion : INumber
        {
            ///
            /// basis
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
                    Adjust(ref index, Period(GetType()), false);
                    switch (index)
                    {
                        case 0: return real;
                        default: return imaginary[index];
                    }
                }
                set
                {
                    Adjust(ref index, Period(GetType()), false);
                    switch (index)
                    {
                        case 0: real = value; break;
                        default: imaginary[index] = value; break;
                    }
                }
            }
            public override int GetHashCode() { return 0; }
            public static explicit operator Quaternion(string Value) { return QuaternionModule.GetInstance(Value); }
            public static explicit operator string(Quaternion Value) { return GetString(Value); }
            public static implicit operator Quaternion(double Value) { return new Quaternion(Value, new Vector3D()); }
            public static implicit operator Quaternion(Vector3D Value) { return new Quaternion(0, Value); }
            public static double Scalar(Quaternion Value) { return Value.real; }
            public static Vector3D Vector(Quaternion Value) { return Value.imaginary; }
            ///
            /// operators
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
            ///
            /// casing
            ///
            internal Number ToNumber()
            {
                return new Number(real, imaginary[1], imaginary[2], imaginary[3]);
            }
            internal static Quaternion From(Number Number)
            {
                return new Quaternion(Number[0], Number[1], Number[2], Number[3]);
            }
        }
        [Serializable]
        internal class QuaternionException : Exception
        {
            public QuaternionException() : base() { }
            public QuaternionException(string message) : base(message) { }
            public QuaternionException(string message, Exception innerException) : base(message, innerException) { }
            [SecuritySafeCritical]
            protected QuaternionException(SerializationInfo info, StreamingContext context) : base(info, context) { }
        }
        public static class QuaternionModule
        {
            ///
            /// constants
            ///
            public static readonly double pi = Math.PI;
            public static readonly double e = Math.E;
            public static readonly Quaternion i = new Quaternion(0, 1, 0, 0);
            public static readonly Quaternion j = new Quaternion(0, 0, 1, 0);
            public static readonly Quaternion k = new Quaternion(0, 0, 0, 1);
            ///
            /// fundamentals
            ///
            public static double Abs(Quaternion Value) { return Math.Sqrt(Dot(Value, Value)); }
            public static double Arg(Quaternion Value) { return Arg(Value, 0); }
            public static double Arg(Quaternion Value, long Theta) { return Math.Acos(Scalar(Value) / Abs(Value)) + 2 * pi * Theta; }
            public static Quaternion Conjg(Quaternion Value) { return ~Value; }
            public static Quaternion Sgn(Quaternion Value) { return Value / Abs(Value); }
            public static Quaternion Inverse(Quaternion Value) { return Conjg(Value) / Dot(Value, Value); }
            public static Quaternion Exp(Quaternion Value)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return Math.Exp(S); }
                return Math.Exp(S) * (Math.Cos(Abs(V)) + Sgn(V) * Math.Sin(Abs(V)));
            }
            public static Quaternion Ln(Quaternion Value) { return Ln(Value, 0); }
            public static Quaternion Ln(Quaternion Value, long Theta)
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
            public static double Dot(Quaternion Union, Quaternion Value)
            {
                return Scalar(Union) * Scalar(Value) + Vector3DModule.Dot(Vector(Union), Vector(Value));
            }
            public static Vector3D Outer(Quaternion Union, Quaternion Value)
            {
                return Vector3DModule.Cross(Vector(Union), Vector(Value)) + Scalar(Union) * Vector(Value) - Scalar(Value) * Vector(Union);
            }
            public static Quaternion Even(Quaternion Union, Quaternion Value)
            {
                return Scalar(Union) * Scalar(Value) - Vector3DModule.Dot(Vector(Union), Vector(Value)) + Scalar(Union) * Vector(Value) + Scalar(Value) * Vector(Union);
            }
            public static Vector3D Cross(Quaternion Union, Quaternion Value)
            {
                return Vector3DModule.Cross(Vector(Union), Vector(Value));
            }
            ///
            /// exponentials
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
            /// trigonometrics
            ///
            public static Quaternion Sin(Quaternion Value)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return Math.Sin(S); }
                return Math.Sin(S) * Math.Cosh(Abs(V)) + Sgn(V) * (Math.Cos(S) * Math.Sinh(Abs(V)));
            }
            public static Quaternion Arcsin(Quaternion Value) { return Arcsin(Value, true, 0); }
            public static Quaternion Arcsin(Quaternion Value, bool Sign, long Period)
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
            public static Quaternion Sinh(Quaternion Value)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return Math.Sinh(S); }
                return Math.Sinh(S) * Math.Cos(Abs(V)) + Sgn(V) * (Math.Cosh(S) * Math.Sin(Abs(V)));
            }
            public static Quaternion Arcsinh(Quaternion Value) { return Arcsinh(Value, true, 0); }
            public static Quaternion Arcsinh(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Value * Value + 1, 2), Period); }
                var V = Vector(Value);
                if (V == 0) { return pi * i - Arcsinh(Value, true, Period); }
                return pi * Sgn(V) - Arcsinh(Value, true, Period);
            }
            public static Quaternion Cos(Quaternion Value)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return Math.Cos(S); }
                return Math.Cos(S) * Math.Cosh(Abs(V)) - Sgn(V) * (Math.Sin(S) * Math.Sinh(Abs(V)));
            }
            public static Quaternion Arccos(Quaternion Value) { return Arccos(Value, true, 0); }
            public static Quaternion Arccos(Quaternion Value, bool Sign, long Period)
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
            public static Quaternion Cosh(Quaternion Value)
            {
                var S = Scalar(Value);
                var V = Vector(Value);
                if (V == 0) { return Math.Cosh(S); }
                return Math.Cosh(S) * Math.Cos(Abs(V)) + Sgn(V) * (Math.Sinh(S) * Math.Sin(Abs(V)));
            }
            public static Quaternion Arccosh(Quaternion Value) { return Arccosh(Value, true, 0); }
            public static Quaternion Arccosh(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return Ln(Value + Root(Value * Value - 1, 2), Period); }
                var V = Vector(Value);
                if (V == 0) { return 2 * pi * i - Arccosh(Value, true, Period); }
                return 2 * pi * Sgn(V) - Arccosh(Value, true, Period);
            }
            public static Quaternion Tan(Quaternion Value)
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
            public static Quaternion Arctan(Quaternion Value) { return Arctan(Value, true, 0); }
            public static Quaternion Arctan(Quaternion Value, bool Sign, long Period)
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
            public static Quaternion Tanh(Quaternion Value)
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
            public static Quaternion Arctanh(Quaternion Value) { return Arctanh(Value, true, 0); }
            public static Quaternion Arctanh(Quaternion Value, bool Sign, long Period)
            {
                if (Sign == true) { return 1 / 2 * (Ln(1 + Value, Period) - Ln(1 - Value)); }
                var V = Vector(Value);
                if (V == 0) { return pi * i + Arctanh(Value, true, Period); }
                return pi * Sgn(V) + Arctanh(Value, true, Period);
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
            /// conventions
            ///
            public static string GetString(Quaternion Value) { return Value.ToString(); }
            public static Quaternion GetInstance(string Value)
            {
                string Replaced = Value.Replace(" ", "");
                Quaternion Result = 0;
                try { Replaced.ToNumbers(ref Result, false, "", "i", "j", "k"); }
                catch (Exception Exception) { throw new QuaternionException("The string cannot be converted as a number.", Exception); }
                return Result;
            }
            public static Quaternion ToQuaternion(this string Value) { return GetInstance(Value); }
        }
    }
}
