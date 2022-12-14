using ComplexTestingConsole;
using Cmplx.MainType;
using System;
using System.Reflection;
using static ComplexTestingConsole.Module;
using static Mod;
using static Cmplx.MainType.ComplexModule;
internal static class Mod
{
    internal static void Op<R>(string str, string ptr, Func<Complex, Complex, R> f)
    {
        if (str == ptr)
        {
            Complex Union = CType_Complex(Base.Input("Union = "));
            Complex Value = CType_Complex(Base.Input("Value = "));
            Base.Output(f.Invoke(Union, Value).ToString());
        }
    }
    internal static void PowerOp(string str, string ptr, Func<Complex, long, Complex> f)
    {
        if (str == ptr)
        {
            Complex BaseNumber = CType_Complex(Base.Input("Base = "));
            long ExponentNumber = long.Parse(Base.Input("Exponent = "));
            Base.Output(f.Invoke(BaseNumber, ExponentNumber).ToString());
        }
    }
    internal static void Power(string str, string ptr, Func<Complex, Complex, long, Complex> f)
    {
        Power(str, ptr, Delegate.CreateDelegate(f.GetType(), f.GetMethodInfo()));
    }
    internal static void Power(string str, string ptr, Func<Complex, Complex, long, long, Complex> f)
    {
        Power(str, ptr, Delegate.CreateDelegate(f.GetType(), f.GetMethodInfo()));
    }
    internal static void Power(string str, string ptr, Delegate f)
    {
        if (str == ptr)
        {
            Complex Union = CType_Complex(Base.Input("Union = "));
            Complex Value = CType_Complex(Base.Input("Value = "));
            long[] Data = new long[f.GetMethodInfo().GetParameters().LongLength - 2];
            PowerGet(Data);
            PowerResult(f, ptr, Union, Value, Data);
        }
        else if (str == ptr + "()")
        {
            Complex Union = CType_Complex(Base.Input("Union = "));
            Complex Value = CType_Complex(Base.Input("Value = "));
            Tuple<long, long>[] Data = new Tuple<long, long>[f.GetMethodInfo().GetParameters().LongLength - 2];
            PowerGet(Data);
            PowerResult(f, ptr, Union, Value, Data);
        }
    }
    internal static void Basic<R>(string str, string ptr, Func<Complex, R> f)
    {
        if (str == ptr)
        {
            Complex Value = CType_Complex(Base.Input("Value = "));
            Base.Output(f.Invoke(Value).ToString());
        }
    }
    internal static void BasicWith<R>(string str, string ptr, Func<Complex, long, R> f)
    {
        if (str == ptr)
        {
            Complex Value = CType_Complex(Base.Input("Value = "));
            long Theta = long.Parse(Base.Input("Theta = "));
            Base.Output(f.Invoke(Value, Theta).ToString());
        }
        else if (str == ptr + "()")
        {
            Complex Value = CType_Complex(Base.Input("Value = "));
            long ThetaMin = long.Parse(Base.Input("ThetaMin = "));
            long ThetaMax = long.Parse(Base.Input("ThetaMax = "));
            for (long Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
            {
                Base.Output(ptr + "(" + Theta.ToString() + ") = ", f.Invoke(Value, Theta).ToString());
            }
        }
    }
    internal static void Tri(string str, string ptr, Func<Complex, Complex> f)
    {
        if (str == ptr)
        {
            Complex Value = CType_Complex(Base.Input("Value = "));
            Base.Output(f.Invoke(Value).ToString());
        }
    }
    internal static void Arctri(string str, string ptr, Func<Complex, bool, long, Complex> f)
    {
        if (str == ptr)
        {
            Complex Value = CType_Complex(Base.Input("Value = "));
            bool Sign = false;
            string Input = Base.Input("Sign : ");
            if (Input == "+" && Input != "-") { Sign = true; }
            long Period = long.Parse(Base.Input("Period = "));
            Base.Output(f.Invoke(Value, Sign, Period).ToString());
        }
        else if (str == ptr + "()")
        {
            Complex Value = CType_Complex(Base.Input("Value = "));
            long PeriodMin = long.Parse(Base.Input("PeriodMin = "));
            long PeriodMax = long.Parse(Base.Input("PeriodMax = "));
            for (long Period = PeriodMin; Period <= PeriodMax; ++Period)
            {
                Base.Output(ptr + "(+, " + Period.ToString() + ") = ", f.Invoke(Value, true, Period).ToString());
            }
            for (long Period = PeriodMin; Period <= PeriodMax; ++Period)
            {
                Base.Output(ptr + "(-, " + Period.ToString() + ") = ", f.Invoke(Value, false, Period).ToString());
            }
        }
    }
}
internal static class MyModule
{
    internal static void Load()
    {
        Base.Startup(Base.GetTitle());
        Base.Selection("=   +   -   *   /   ^   Power()   Root()   Log()");
        Base.Selection("abs   arg()   conjg   sgn   inverse   exp   ln()");
        Base.Selection("sin   cos   tan   csc   sec   cot   arcsin()   arccos()   arctan()   arccsc()   arcsec()   arccot()");
        Base.Selection("sinh   cosh   tanh   csch   sech   coth   arcsinh()   arccosh()   arctanh()   arccsch()   arcsech()   arccoth()");
        Base.Selection(Base.GetStartupLine());
        for (string Str = ""; !Base.IsSwitchTo(Str); Str = Base.Input())
        {
            if (Str == "") { continue; }
            try
            {
                Op(Str, "=", (Complex Union, Complex Value) => { return Union == Value; });
                Op(Str, "+", (Complex Union, Complex Value) => { return Union + Value; });
                Op(Str, "-", (Complex Union, Complex Value) => { return Union - Value; });
                Op(Str, "*", (Complex Union, Complex Value) => { return Union * Value; });
                Op(Str, "/", (Complex Union, Complex Value) => { return Union / Value; });
                /****/
                PowerOp(Str, "^", (Complex Union, long Value) => { return Union ^ Value; });
                Power(Str, "Power", Power);
                Power(Str, "Root", Root);
                Power(Str, "Log", Log);
                /****/
                Basic(Str, "abs", Abs);
                BasicWith(Str, "arg", Arg);
                Basic(Str, "conjg", Conjg);
                Basic(Str, "sgn", Sgn);
                Basic(Str, "inverse", Inverse);
                Basic(Str, "exp", Exp);
                BasicWith(Str, "ln", Ln);
                /****/
                Tri(Str, "sin", Sin);
                Tri(Str, "cos", Cos);
                Tri(Str, "tan", Tan);
                Tri(Str, "csc", Csc);
                Tri(Str, "sec", Sec);
                Tri(Str, "cot", Cot);
                Tri(Str, "sinh", Sinh);
                Tri(Str, "cosh", Cosh);
                Tri(Str, "tanh", Tanh);
                Tri(Str, "csch", Csch);
                Tri(Str, "sech", Sech);
                Tri(Str, "coth", Coth);
                Arctri(Str, "arcsin", Arcsin);
                Arctri(Str, "arccos", Arccos);
                Arctri(Str, "arctan", Arctan);
                Arctri(Str, "arccsc", Arccsc);
                Arctri(Str, "arcsec", Arcsec);
                Arctri(Str, "arccot", Arccot);
                Arctri(Str, "arcsinh", Arcsinh);
                Arctri(Str, "arccosh", Arccosh);
                Arctri(Str, "arctanh", Arctanh);
                Arctri(Str, "arccsch", Arccsch);
                Arctri(Str, "arcsech", Arcsech);
                Arctri(Str, "arccoth", Arccoth);
            }
            catch (Exception Ex) { Base.Exception(Ex); }
        }
    }
}
