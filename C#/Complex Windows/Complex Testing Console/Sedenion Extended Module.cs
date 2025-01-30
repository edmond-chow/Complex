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
using Num;
using System;
using System.Reflection;
using ComplexTestingConsole;
using static ComplexTestingConsole.Module;
using static SedenBasis;
using static Num.Seden;
internal static class SedenBasis
{
    internal static void Mul<T>(string L, string R, Func<Seden, Seden, T> S)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            Base.Output(S.Invoke(U, V).ToModStr());
        }
    }
    internal static void Op<T>(string L, string R, Func<Seden, Seden, T> S)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            Base.Output(S.Invoke(U, V).ToModStr());
        }
    }
    internal static void Op(string L, string R, Func<Seden, double, Seden> S)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            double V = Base.Input("V = ").AsReal();
            Base.Output(S.Invoke(U, V).ToModStr());
        }
    }
    internal static void PowOp(string L, string R, Func<Seden, long, Seden> S)
    {
        if (L == R)
        {
            Seden BaseNumber = Val(Base.Input("Base = "));
            long ExponentNumber = Base.Input("Exponent = ").AsInt();
            Base.Output(S.Invoke(BaseNumber, ExponentNumber).ToModStr());
        }
    }
    internal static void Pow(string L, string R, Func<Seden, Seden, long, long, long, Seden> S)
    {
        Pow(L, R, Delegate.CreateDelegate(S.GetType(), S.GetMethodInfo()));
    }
    internal static void Pow(string L, string R, Func<Seden, Seden, long, long, long, long, Seden> S)
    {
        Pow(L, R, Delegate.CreateDelegate(S.GetType(), S.GetMethodInfo()));
    }
    internal static void Pow(string L, string R, Delegate S)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            object[] Args = new object[S.GetMethodInfo().GetParameters().Length];
            Args[0] = U;
            Args[1] = V;
            PowGet(Args);
            PowRst(S, Args);
        }
        else if (L == R + "()")
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            object[] Args = new object[S.GetMethodInfo().GetParameters().Length];
            long[] Upper = new long[Args.Length - 2];
            Args[0] = U;
            Args[1] = V;
            PowGet(Args, Upper);
            PowRst(S, R, Args, Upper);
        }
    }
    internal static void Bas<T>(string L, string R, Func<Seden, T> S)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            Base.Output(S.Invoke(V).ToModStr());
        }
    }
    internal static void BasP<T>(string L, string R, Func<Seden, long, T> S)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            long P = Base.Input("P = ").AsInt();
            Base.Output(S.Invoke(V, P).ToModStr());
        }
        else if (L == R + "()")
        {
            Seden V = Val(Base.Input("V = "));
            long PMin = Base.Input("P(min) = ").AsInt();
            long PMax = Base.Input("P(max) = ").AsInt();
            for (long P = PMin; P <= PMax; ++P)
            {
                Base.Output(R + "(" + P.ToModStr() + ") = ", S.Invoke(V, P).ToModStr());
            }
        }
    }
    internal static void Tri(string L, string R, Func<Seden, Seden> S)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            Base.Output(S.Invoke(V).ToModStr());
        }
    }
    internal static void Atri(string L, string R, Func<Seden, bool, long, Seden> S)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            bool Sign = false;
            string Input = Base.Input("Sign : ").Replace(" ", "");
            if (Input == "+") { Sign = true; }
            else if (Input != "-") { throw new ArgumentException("A string interpretation of the sign cannot be converted as a bool value."); }
            long P = Base.Input("P = ").AsInt();
            Base.Output(S.Invoke(V, Sign, P).ToModStr());
        }
        else if (L == R + "()")
        {
            Seden V = Val(Base.Input("V = "));
            long PMin = Base.Input("P(min) = ").AsInt();
            long PMax = Base.Input("P(max) = ").AsInt();
            for (long P = PMin; P <= PMax; ++P)
            {
                Base.Output(R + "(+, " + P.ToModStr() + ") = ", S.Invoke(V, true, P).ToModStr());
            }
            for (long P = PMin; P <= PMax; ++P)
            {
                Base.Output(R + "(-, " + P.ToModStr() + ") = ", S.Invoke(V, false, P).ToModStr());
            }
        }
    }
}
internal static class SedenConsole
{
    internal static void Load()
    {
        Base.Startup(Base.GetTitle());
        Base.Selection("=   +   -   *   /   ^   power()   root()   log()");
        Base.Selection("abs   arg()   conjg   sgn   inverse   exp   ln()   dot   outer   even   cross");
        Base.Selection("sin   cos   tan   csc   sec   cot   arcsin()   arccos()   arctan()   arccsc()   arcsec()   arccot()");
        Base.Selection("sinh   cosh   tanh   csch   sech   coth   arcsinh()   arccosh()   arctanh()   arccsch()   arcsech()   arccoth()");
        Base.Selection(Base.GetStartupLine());
        for (string Ln = ""; !Base.IsSwitchTo(Ln); Ln = Base.Input())
        {
            if (Ln == "") { continue; }
            try
            {
                Op(Ln, "=", (Seden U, Seden V) => { return U == V; });
                Op(Ln, "+", (Seden U, Seden V) => { return U + V; });
                Op(Ln, "-", (Seden U, Seden V) => { return U - V; });
                Op(Ln, "*", (Seden U, Seden V) => { return U * V; });
                Op(Ln, "/", (Seden U, double V) => { return U / V; });
                /****/
                PowOp(Ln, "^", (Seden U, long V) => { return U ^ V; });
                Pow(Ln, "power", Power);
                Pow(Ln, "root", Root);
                Pow(Ln, "log", Log);
                /****/
                Mul(Ln, "dot", Dot);
                Mul(Ln, "outer", Outer);
                Mul(Ln, "even", Even);
                Mul(Ln, "cross", Cross);
                /****/
                Bas(Ln, "abs", Abs);
                BasP(Ln, "arg", Arg);
                Bas(Ln, "conjg", Conjg);
                Bas(Ln, "sgn", Sgn);
                Bas(Ln, "inverse", Inverse);
                Bas(Ln, "exp", Exp);
                BasP(Ln, "ln", Seden.Ln);
                /****/
                Tri(Ln, "sin", Sin);
                Tri(Ln, "cos", Cos);
                Tri(Ln, "tan", Tan);
                Tri(Ln, "csc", Csc);
                Tri(Ln, "sec", Sec);
                Tri(Ln, "cot", Cot);
                Tri(Ln, "sinh", Sinh);
                Tri(Ln, "cosh", Cosh);
                Tri(Ln, "tanh", Tanh);
                Tri(Ln, "csch", Csch);
                Tri(Ln, "sech", Sech);
                Tri(Ln, "coth", Coth);
                Atri(Ln, "arcsin", Arcsin);
                Atri(Ln, "arccos", Arccos);
                Atri(Ln, "arctan", Arctan);
                Atri(Ln, "arccsc", Arccsc);
                Atri(Ln, "arcsec", Arcsec);
                Atri(Ln, "arccot", Arccot);
                Atri(Ln, "arcsinh", Arcsinh);
                Atri(Ln, "arccosh", Arccosh);
                Atri(Ln, "arctanh", Arctanh);
                Atri(Ln, "arccsch", Arccsch);
                Atri(Ln, "arcsech", Arcsech);
                Atri(Ln, "arccoth", Arccoth);
            }
            catch (Exception Ex) { Base.Exception(Ex); }
        }
    }
}
