using Cmplx3.MainType;
using System;
using System.Reflection;
using ComplexTestingConsole;
using static ComplexTestingConsole.Module;
using static Mod3;
using static Cmplx3.MainType.OctonionModule;
internal static class Mod3
{
    internal static void Op<R>(string LeftValue, string RightValue, Func<Octonion, Octonion, R> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Octonion Union = GetInstance(Base.Input("Union = "));
            Octonion Value = GetInstance(Base.Input("Value = "));
            Base.Output(Subroutine.Invoke(Union, Value).ToModuleString());
        }
    }
    internal static void PowerOp(string LeftValue, string RightValue, Func<Octonion, long, Octonion> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Octonion BaseNumber = GetInstance(Base.Input("Base = "));
            long ExponentNumber = long.Parse(Base.Input("Exponent = ").Replace(" ", ""));
            Base.Output(Subroutine.Invoke(BaseNumber, ExponentNumber).ToModuleString());
        }
    }
    internal static void Power(string LeftValue, string RightValue, Func<Octonion, Octonion, long, long, long, Octonion> Subroutine)
    {
        Power(LeftValue, RightValue, Delegate.CreateDelegate(Subroutine.GetType(), Subroutine.GetMethodInfo()));
    }
    internal static void Power(string LeftValue, string RightValue, Func<Octonion, Octonion, long, long, long, long, Octonion> Subroutine)
    {
        Power(LeftValue, RightValue, Delegate.CreateDelegate(Subroutine.GetType(), Subroutine.GetMethodInfo()));
    }
    internal static void Power(string LeftValue, string RightValue, Delegate Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Octonion Union = GetInstance(Base.Input("Union = "));
            Octonion Value = GetInstance(Base.Input("Value = "));
            long[] Data = new long[Subroutine.GetMethodInfo().GetParameters().LongLength - 2];
            PowerGet(Data);
            PowerResult(Subroutine, RightValue, Union, Value, Data);
        }
        else if (LeftValue == RightValue + "()")
        {
            Octonion Union = GetInstance(Base.Input("Union = "));
            Octonion Value = GetInstance(Base.Input("Value = "));
            Tuple<long, long>[] Data = new Tuple<long, long>[Subroutine.GetMethodInfo().GetParameters().LongLength - 2];
            PowerGet(Data);
            PowerResult(Subroutine, RightValue, Union, Value, Data);
        }
    }
    internal static void Basic<R>(string LeftValue, string RightValue, Func<Octonion, R> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Octonion Value = GetInstance(Base.Input("Value = "));
            Base.Output(Subroutine.Invoke(Value).ToModuleString());
        }
    }
    internal static void BasicWith<R>(string LeftValue, string RightValue, Func<Octonion, long, R> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Octonion Value = GetInstance(Base.Input("Value = "));
            long Theta = long.Parse(Base.Input("Theta = ").Replace(" ", ""));
            Base.Output(Subroutine.Invoke(Value, Theta).ToModuleString());
        }
        else if (LeftValue == RightValue + "()")
        {
            Octonion Value = GetInstance(Base.Input("Value = "));
            long ThetaMin = long.Parse(Base.Input("ThetaMin = ").Replace(" ", ""));
            long ThetaMax = long.Parse(Base.Input("ThetaMax = ").Replace(" ", ""));
            for (long Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
            {
                Base.Output(RightValue + "(" + Theta.ToModuleString() + ") = ", Subroutine.Invoke(Value, Theta).ToModuleString());
            }
        }
    }
    internal static void Tri(string LeftValue, string RightValue, Func<Octonion, Octonion> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Octonion Value = GetInstance(Base.Input("Value = "));
            Base.Output(Subroutine.Invoke(Value).ToModuleString());
        }
    }
    internal static void Arctri(string LeftValue, string RightValue, Func<Octonion, bool, long, Octonion> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Octonion Value = GetInstance(Base.Input("Value = "));
            bool Sign = false;
            string Input = Base.Input("Sign : ").Replace(" ", "");
            if (Input == "+") { Sign = true; }
            else if (Input != "-") { throw new ArgumentException("A string interpretation of the sign cannot be converted as a bool value."); }
            long Period = long.Parse(Base.Input("Period = ").Replace(" ", ""));
            Base.Output(Subroutine.Invoke(Value, Sign, Period).ToModuleString());
        }
        else if (LeftValue == RightValue + "()")
        {
            Octonion Value = GetInstance(Base.Input("Value = "));
            long PeriodMin = long.Parse(Base.Input("PeriodMin = ").Replace(" ", ""));
            long PeriodMax = long.Parse(Base.Input("PeriodMax = ").Replace(" ", ""));
            for (long Period = PeriodMin; Period <= PeriodMax; ++Period)
            {
                Base.Output(RightValue + "(+, " + Period.ToModuleString() + ") = ", Subroutine.Invoke(Value, true, Period).ToModuleString());
            }
            for (long Period = PeriodMin; Period <= PeriodMax; ++Period)
            {
                Base.Output(RightValue + "(-, " + Period.ToModuleString() + ") = ", Subroutine.Invoke(Value, false, Period).ToModuleString());
            }
        }
    }
}
internal static class MyModule3
{
    internal static void Load()
    {
        Base.Startup(Base.GetTitle());
        Base.Selection("=   +   -   *   /   ^   Power()   Root()   Log()");
        Base.Selection("abs   arg()   conjg   sgn   inverse   exp   ln()");
        Base.Selection("sin   cos   tan   csc   sec   cot   arcsin()   arccos()   arctan()   arccsc()   arcsec()   arccot()");
        Base.Selection("sinh   cosh   tanh   csch   sech   coth   arcsinh()   arccosh()   arctanh()   arccsch()   arcsech()   arccoth()");
        Base.Selection(Base.GetStartupLine());
        for (string Line = ""; !Base.IsSwitchTo(Line); Line = Base.Input().Trim().ToLower())
        {
            if (Line == "") { continue; }
            try
            {
                Op(Line, "=", (Octonion Union, Octonion Value) => { return Union == Value; });
                Op(Line, "+", (Octonion Union, Octonion Value) => { return Union + Value; });
                Op(Line, "-", (Octonion Union, Octonion Value) => { return Union - Value; });
                Op(Line, "*", (Octonion Union, Octonion Value) => { return Union * Value; });
                Op(Line, "/", (Octonion Union, Octonion Value) => { return Union / Value; });
                /****/
                PowerOp(Line, "^", (Octonion Union, long Value) => { return Union ^ Value; });
                Power(Line, "power", Power);
                Power(Line, "root", Root);
                Power(Line, "log", Log);
                /****/
                Basic(Line, "abs", Abs);
                BasicWith(Line, "arg", Arg);
                Basic(Line, "conjg", Conjg);
                Basic(Line, "sgn", Sgn);
                Basic(Line, "inverse", Inverse);
                Basic(Line, "exp", Exp);
                BasicWith(Line, "ln", Ln);
                /****/
                Tri(Line, "sin", Sin);
                Tri(Line, "cos", Cos);
                Tri(Line, "tan", Tan);
                Tri(Line, "csc", Csc);
                Tri(Line, "sec", Sec);
                Tri(Line, "cot", Cot);
                Tri(Line, "sinh", Sinh);
                Tri(Line, "cosh", Cosh);
                Tri(Line, "tanh", Tanh);
                Tri(Line, "csch", Csch);
                Tri(Line, "sech", Sech);
                Tri(Line, "coth", Coth);
                Arctri(Line, "arcsin", Arcsin);
                Arctri(Line, "arccos", Arccos);
                Arctri(Line, "arctan", Arctan);
                Arctri(Line, "arccsc", Arccsc);
                Arctri(Line, "arcsec", Arcsec);
                Arctri(Line, "arccot", Arccot);
                Arctri(Line, "arcsinh", Arcsinh);
                Arctri(Line, "arccosh", Arccosh);
                Arctri(Line, "arctanh", Arctanh);
                Arctri(Line, "arccsch", Arccsch);
                Arctri(Line, "arcsech", Arcsech);
                Arctri(Line, "arccoth", Arccoth);
            }
            catch (Exception Exception) { Base.Exception(Exception); }
        }
    }
}
