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
    internal static void Idt(string L, string R)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            Base.Output(V.ToModStr());
        }
    }
    internal static void Mul<T>(string L, string R, Func<Seden, Seden, T> F)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            Base.Output(F.Invoke(U, V).ToModStr());
        }
    }
    internal static void Op<T>(string L, string R, Func<Seden, Seden, T> F)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            Base.Output(F.Invoke(U, V).ToModStr());
        }
    }
    internal static void PowOp(string L, string R, Func<Seden, long, Seden> F)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            long V = Base.Input("V = ").Int();
            Base.Output(F.Invoke(U, V).ToModStr());
        }
    }
    internal static void Pow(string L, string R, Func<Seden, Seden, long, long, long, Seden> F)
    {
        Pow(L, R, Delegate.CreateDelegate(F.GetType(), F.GetMethodInfo()));
    }
    internal static void Pow(string L, string R, Func<Seden, Seden, long, long, long, long, Seden> F)
    {
        Pow(L, R, Delegate.CreateDelegate(F.GetType(), F.GetMethodInfo()));
    }
    internal static void Pow(string L, string R, Delegate F)
    {
        if (L == R)
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            object[] Args = new object[F.GetMethodInfo().GetParameters().Length];
            Args[0] = U;
            Args[1] = V;
            PowGet(Args);
            PowRst(F, Args);
        }
        else if (L == R + "()")
        {
            Seden U = Val(Base.Input("U = "));
            Seden V = Val(Base.Input("V = "));
            object[] Args = new object[F.GetMethodInfo().GetParameters().Length];
            long[] Upper = new long[Args.Length - 2];
            Args[0] = U;
            Args[1] = V;
            PowGet(Args, Upper);
            PowRst(F, R, Args, Upper);
        }
    }
    internal static void Bas<T>(string L, string R, Func<Seden, T> F)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            Base.Output(F.Invoke(V).ToModStr());
        }
    }
    internal static void BasP<T>(string L, string R, Func<Seden, long, T> F)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            long P = Base.Input("P = ").Int();
            Base.Output(F.Invoke(V, P).ToModStr());
        }
        else if (L == R + "()")
        {
            Seden V = Val(Base.Input("V = "));
            long PMin = Base.Input("P(min) = ").Int();
            long PMax = Base.Input("P(max) = ").Int();
            for (long P = PMin; P <= PMax; ++P)
            {
                Base.Output(R + "(" + P.ToModStr() + ") = ", F.Invoke(V, P).ToModStr());
            }
        }
    }
    internal static void Tri(string L, string R, Func<Seden, Seden> F)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            Base.Output(F.Invoke(V).ToModStr());
        }
    }
    internal static void Atri(string L, string R, Func<Seden, bool, long, Seden> F)
    {
        if (L == R)
        {
            Seden V = Val(Base.Input("V = "));
            bool S = false;
            string Ipt = Base.Input("Sign : ").Replace(" ", "");
            if (Ipt == "+") { S = true; }
            else if (Ipt != "-") { throw new ArgumentException("A string interpretation of the sign cannot be converted as a bool value."); }
            long P = Base.Input("P = ").Int();
            Base.Output(F.Invoke(V, S, P).ToModStr());
        }
        else if (L == R + "()")
        {
            Seden V = Val(Base.Input("V = "));
            long PMin = Base.Input("P(min) = ").Int();
            long PMax = Base.Input("P(max) = ").Int();
            for (long P = PMin; P <= PMax; ++P)
            {
                Base.Output(R + "(+, " + P.ToModStr() + ") = ", F.Invoke(V, true, P).ToModStr());
            }
            for (long P = PMin; P <= PMax; ++P)
            {
                Base.Output(R + "(-, " + P.ToModStr() + ") = ", F.Invoke(V, false, P).ToModStr());
            }
        }
    }
}
internal static class SedenConsole
{
    internal static void Load()
    {
        Base.Startup(Base.GetTitle());
        Base.Selection("&   =   +   -   *   /   ^   Power()   Root()   Log()");
        Base.Selection("Abs   Arg()   Conjg   Sgn   Inverse   Exp   Ln()   Dot   Outer   Even   Cross");
        Base.Selection("Sin   Cos   Tan   Csc   Sec   Cot   Arcsin()   Arccos()   Arctan()   Arccsc()   Arcsec()   Arccot()");
        Base.Selection("Sinh   Cosh   Tanh   Csch   Sech   Coth   Arcsinh()   Arccosh()   Arctanh()   Arccsch()   Arcsech()   Arccoth()");
        Base.Selection(Base.GetStartupLine());
        for (string L = ""; !Base.IsSwitchTo(L); L = Base.Input().Trim())
        {
            if (L == "") { continue; }
            try
            {
                Idt(L, "&");
                Op(L, "=", (Seden U, Seden V) => { return U == V; });
                Op(L, "+", (Seden U, Seden V) => { return U + V; });
                Op(L, "-", (Seden U, Seden V) => { return U - V; });
                Op(L, "*", (Seden U, Seden V) => { return U * V; });
                Op(L, "/", (Seden U, Seden V) => { return U / V; });
                /****/
                PowOp(L, "^", (Seden U, long V) => { return U ^ V; });
                Pow(L, "Power", Power);
                Pow(L, "Root", Root);
                Pow(L, "Log", Log);
                /****/
                Mul(L, "Dot", Dot);
                Mul(L, "Outer", Outer);
                Mul(L, "Even", Even);
                Mul(L, "Cross", Cross);
                /****/
                Bas(L, "Abs", Abs);
                BasP(L, "Arg", Arg);
                Bas(L, "Conjg", Conjg);
                Bas(L, "Sgn", Sgn);
                Bas(L, "Inverse", Inverse);
                Bas(L, "Exp", Exp);
                BasP(L, "Ln", Ln);
                /****/
                Tri(L, "Sin", Sin);
                Tri(L, "Cos", Cos);
                Tri(L, "Tan", Tan);
                Tri(L, "Csc", Csc);
                Tri(L, "Sec", Sec);
                Tri(L, "Cot", Cot);
                Tri(L, "Sinh", Sinh);
                Tri(L, "Cosh", Cosh);
                Tri(L, "Tanh", Tanh);
                Tri(L, "Csch", Csch);
                Tri(L, "Sech", Sech);
                Tri(L, "Coth", Coth);
                Atri(L, "Arcsin", Arcsin);
                Atri(L, "Arccos", Arccos);
                Atri(L, "Arctan", Arctan);
                Atri(L, "Arccsc", Arccsc);
                Atri(L, "Arcsec", Arcsec);
                Atri(L, "Arccot", Arccot);
                Atri(L, "Arcsinh", Arcsinh);
                Atri(L, "Arccosh", Arccosh);
                Atri(L, "Arctanh", Arctanh);
                Atri(L, "Arccsch", Arccsch);
                Atri(L, "Arcsech", Arcsech);
                Atri(L, "Arccoth", Arccoth);
            }
            catch (Exception Ex) { Base.Exception(Ex); }
        }
    }
}
