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
using System;
using System.Reflection;
using ComplexTestingConsole;
using static ComplexTestingConsole.Module;
using Num;
using static Num.Octon;
using static OctonBasis;
internal static class OctonBasis
{
    internal static void Mul<T>(string L, string R, Func<Octon, Octon, T> S)
    {
        if (L == R)
        {
            Octon U = Val(Base.Input("U = "));
            Octon V = Val(Base.Input("V = "));
            object Result = S.Invoke(U, V);
            if (Result is Vec7D Ve) { Result = new Octon(0, Ve); }
            Base.Output(Result.ToModStr());
        }
    }
    internal static void Op<T>(string L, string R, Func<Octon, Octon, T> S)
    {
        if (L == R)
        {
            Octon U = Val(Base.Input("U = "));
            Octon V = Val(Base.Input("V = "));
            Base.Output(S.Invoke(U, V).ToModStr());
        }
    }
    internal static void PowOp(string L, string R, Func<Octon, long, Octon> S)
    {
        if (L == R)
        {
            Octon U = Val(Base.Input("U = "));
            long V = Base.Input("V = ").AsInt();
            Base.Output(S.Invoke(U, V).ToModStr());
        }
    }
    internal static void Pow(string L, string R, Func<Octon, Octon, long, long, long, Octon> S)
    {
        Pow(L, R, Delegate.CreateDelegate(S.GetType(), S.GetMethodInfo()));
    }
    internal static void Pow(string L, string R, Func<Octon, Octon, long, long, long, long, Octon> S)
    {
        Pow(L, R, Delegate.CreateDelegate(S.GetType(), S.GetMethodInfo()));
    }
    internal static void Pow(string L, string R, Delegate S)
    {
        if (L == R)
        {
            Octon U = Val(Base.Input("U = "));
            Octon V = Val(Base.Input("V = "));
            object[] Args = new object[S.GetMethodInfo().GetParameters().Length];
            Args[0] = U;
            Args[1] = V;
            PowGet(Args);
            PowRst(S, Args);
        }
        else if (L == R + "()")
        {
            Octon U = Val(Base.Input("U = "));
            Octon V = Val(Base.Input("V = "));
            object[] Args = new object[S.GetMethodInfo().GetParameters().Length];
            long[] Upper = new long[Args.Length - 2];
            Args[0] = U;
            Args[1] = V;
            PowGet(Args, Upper);
            PowRst(S, R, Args, Upper);
        }
    }
    internal static void Bas<T>(string L, string R, Func<Octon, T> S)
    {
        if (L == R)
        {
            Octon V = Val(Base.Input("V = "));
            Base.Output(S.Invoke(V).ToModStr());
        }
    }
    internal static void BasP<T>(string L, string R, Func<Octon, long, T> S)
    {
        if (L == R)
        {
            Octon V = Val(Base.Input("V = "));
            long P = Base.Input("P = ").AsInt();
            Base.Output(S.Invoke(V, P).ToModStr());
        }
        else if (L == R + "()")
        {
            Octon V = Val(Base.Input("V = "));
            long PMin = Base.Input("P(min) = ").AsInt();
            long PMax = Base.Input("P(max) = ").AsInt();
            for (long P = PMin; P <= PMax; ++P)
            {
                Base.Output(R + "(" + P.ToModStr() + ") = ", S.Invoke(V, P).ToModStr());
            }
        }
    }
    internal static void Tri(string L, string R, Func<Octon, Octon> S)
    {
        if (L == R)
        {
            Octon V = Val(Base.Input("V = "));
            Base.Output(S.Invoke(V).ToModStr());
        }
    }
    internal static void Atri(string L, string R, Func<Octon, bool, long, Octon> S)
    {
        if (L == R)
        {
            Octon V = Val(Base.Input("V = "));
            bool Sign = false;
            string Input = Base.Input("Sign : ").Replace(" ", "");
            if (Input == "+") { Sign = true; }
            else if (Input != "-") { throw new ArgumentException("A string interpretation of the sign cannot be converted as a bool value."); }
            long P = Base.Input("P = ").AsInt();
            Base.Output(S.Invoke(V, Sign, P).ToModStr());
        }
        else if (L == R + "()")
        {
            Octon V = Val(Base.Input("V = "));
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
internal static class OctonConsole
{
    internal static void Load()
    {
        Base.Startup(Base.GetTitle());
        Base.Selection("=   +   -   *   /   ^   power()   root()   log()");
        Base.Selection("abs   arg()   conjg   sgn   inverse   exp   ln()   dot   outer   even   cross");
        Base.Selection("sin   cos   tan   csc   sec   cot   arcsin()   arccos()   arctan()   arccsc()   arcsec()   arccot()");
        Base.Selection("sinh   cosh   tanh   csch   sech   coth   arcsinh()   arccosh()   arctanh()   arccsch()   arcsech()   arccoth()");
        Base.Selection(Base.GetStartupLine());
        for (string L = ""; !Base.IsSwitchTo(L); L = Base.Input())
        {
            if (L == "") { continue; }
            try
            {
                Op(L, "=", (Octon U, Octon V) => { return U == V; });
                Op(L, "+", (Octon U, Octon V) => { return U + V; });
                Op(L, "-", (Octon U, Octon V) => { return U - V; });
                Op(L, "*", (Octon U, Octon V) => { return U * V; });
                Op(L, "/", (Octon U, Octon V) => { return U / V; });
                /****/
                PowOp(L, "^", (Octon U, long V) => { return U ^ V; });
                Pow(L, "power", Power);
                Pow(L, "root", Root);
                Pow(L, "log", Log);
                /****/
                Mul(L, "dot", Dot);
                Mul(L, "outer", Outer);
                Mul(L, "even", Even);
                Mul(L, "cross", Cross);
                /****/
                Bas(L, "abs", Abs);
                BasP(L, "arg", Arg);
                Bas(L, "conjg", Conjg);
                Bas(L, "sgn", Sgn);
                Bas(L, "inverse", Inverse);
                Bas(L, "exp", Exp);
                BasP(L, "ln", Ln);
                /****/
                Tri(L, "sin", Sin);
                Tri(L, "cos", Cos);
                Tri(L, "tan", Tan);
                Tri(L, "csc", Csc);
                Tri(L, "sec", Sec);
                Tri(L, "cot", Cot);
                Tri(L, "sinh", Sinh);
                Tri(L, "cosh", Cosh);
                Tri(L, "tanh", Tanh);
                Tri(L, "csch", Csch);
                Tri(L, "sech", Sech);
                Tri(L, "coth", Coth);
                Atri(L, "arcsin", Arcsin);
                Atri(L, "arccos", Arccos);
                Atri(L, "arctan", Arctan);
                Atri(L, "arccsc", Arccsc);
                Atri(L, "arcsec", Arcsec);
                Atri(L, "arccot", Arccot);
                Atri(L, "arcsinh", Arcsinh);
                Atri(L, "arccosh", Arccosh);
                Atri(L, "arctanh", Arctanh);
                Atri(L, "arccsch", Arccsch);
                Atri(L, "arcsech", Arcsech);
                Atri(L, "arccoth", Arccoth);
            }
            catch (Exception Ex) { Base.Exception(Ex); }
        }
    }
}
