using Cmplx.MainType;
using System;
using System.Reflection;
using ComplexTestingConsole;
using static ComplexTestingConsole.Module;
using static CmplxBasis;
using static Cmplx.MainType.ComplexModule;
internal static class CmplxBasis
{
    internal static void Multiple<R>(string LeftValue, string RightValue, Func<Complex, Complex, R> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex Union = GetInstance(Base.Input("Union = "));
            Complex Value = GetInstance(Base.Input("Value = "));
            object Result = Subroutine.Invoke(Union, Value);
            if (Result is Cmplx.BaseType.Vector1D V) { Result = new Complex(0, V); }
            Base.Output(Result.ToModuleString());
        }
    }
    internal static void Op<R>(string LeftValue, string RightValue, Func<Complex, Complex, R> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex Union = GetInstance(Base.Input("Union = "));
            Complex Value = GetInstance(Base.Input("Value = "));
            Base.Output(Subroutine.Invoke(Union, Value).ToModuleString());
        }
    }
    internal static void PowerOp(string LeftValue, string RightValue, Func<Complex, long, Complex> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex BaseNumber = GetInstance(Base.Input("Base = "));
            long ExponentNumber = Base.Input("Exponent = ").AsInteger();
            Base.Output(Subroutine.Invoke(BaseNumber, ExponentNumber).ToModuleString());
        }
    }
    internal static void Power(string LeftValue, string RightValue, Func<Complex, Complex, long, Complex> Subroutine)
    {
        Power(LeftValue, RightValue, Delegate.CreateDelegate(Subroutine.GetType(), Subroutine.GetMethodInfo()));
    }
    internal static void Power(string LeftValue, string RightValue, Func<Complex, Complex, long, long, Complex> Subroutine)
    {
        Power(LeftValue, RightValue, Delegate.CreateDelegate(Subroutine.GetType(), Subroutine.GetMethodInfo()));
    }
    internal static void Power(string LeftValue, string RightValue, Delegate Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex Union = GetInstance(Base.Input("Union = "));
            Complex Value = GetInstance(Base.Input("Value = "));
            long[] Data = new long[Subroutine.GetMethodInfo().GetParameters().LongLength - 2];
            PowerGet(Data);
            PowerResult(Subroutine, RightValue, Union, Value, Data);
        }
        else if (LeftValue == RightValue + "()")
        {
            Complex Union = GetInstance(Base.Input("Union = "));
            Complex Value = GetInstance(Base.Input("Value = "));
            Tuple<long, long>[] Data = new Tuple<long, long>[Subroutine.GetMethodInfo().GetParameters().LongLength - 2];
            PowerGet(Data);
            PowerResult(Subroutine, RightValue, Union, Value, Data);
        }
    }
    internal static void Basic<R>(string LeftValue, string RightValue, Func<Complex, R> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex Value = GetInstance(Base.Input("Value = "));
            Base.Output(Subroutine.Invoke(Value).ToModuleString());
        }
    }
    internal static void BasicWith<R>(string LeftValue, string RightValue, Func<Complex, long, R> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex Value = GetInstance(Base.Input("Value = "));
            long Theta = Base.Input("Theta = ").AsInteger();
            Base.Output(Subroutine.Invoke(Value, Theta).ToModuleString());
        }
        else if (LeftValue == RightValue + "()")
        {
            Complex Value = GetInstance(Base.Input("Value = "));
            long ThetaMin = Base.Input("ThetaMin = ").AsInteger();
            long ThetaMax = Base.Input("ThetaMax = ").AsInteger();
            for (long Theta = ThetaMin; Theta <= ThetaMax; ++Theta)
            {
                Base.Output(RightValue + "(" + Theta.ToModuleString() + ") = ", Subroutine.Invoke(Value, Theta).ToModuleString());
            }
        }
    }
    internal static void Tri(string LeftValue, string RightValue, Func<Complex, Complex> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex Value = GetInstance(Base.Input("Value = "));
            Base.Output(Subroutine.Invoke(Value).ToModuleString());
        }
    }
    internal static void Arctri(string LeftValue, string RightValue, Func<Complex, bool, long, Complex> Subroutine)
    {
        if (LeftValue == RightValue)
        {
            Complex Value = GetInstance(Base.Input("Value = "));
            bool Sign = false;
            string Input = Base.Input("Sign : ").Replace(" ", "");
            if (Input == "+") { Sign = true; }
            else if (Input != "-") { throw new ArgumentException("A string interpretation of the sign cannot be converted as a bool value."); }
            long Period = Base.Input("Period = ").AsInteger();
            Base.Output(Subroutine.Invoke(Value, Sign, Period).ToModuleString());
        }
        else if (LeftValue == RightValue + "()")
        {
            Complex Value = GetInstance(Base.Input("Value = "));
            long PeriodMin = Base.Input("PeriodMin = ").AsInteger();
            long PeriodMax = Base.Input("PeriodMax = ").AsInteger();
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
internal static class CmplxConsole
{
    internal static void Load()
    {
        Base.Startup(Base.GetTitle());
        Base.Selection("=   +   -   *   /   ^   power()   root()   log()");
        Base.Selection("abs   arg()   conjg   sgn   inverse   exp   ln()   dot   outer   even   cross");
        Base.Selection("sin   cos   tan   csc   sec   cot   arcsin()   arccos()   arctan()   arccsc()   arcsec()   arccot()");
        Base.Selection("sinh   cosh   tanh   csch   sech   coth   arcsinh()   arccosh()   arctanh()   arccsch()   arcsech()   arccoth()");
        Base.Selection(Base.GetStartupLine());
        for (string Line = ""; !Base.IsSwitchTo(Line); Line = Base.Input())
        {
            if (Line == "") { continue; }
            try
            {
                Op(Line, "=", (Complex Union, Complex Value) => { return Union == Value; });
                Op(Line, "+", (Complex Union, Complex Value) => { return Union + Value; });
                Op(Line, "-", (Complex Union, Complex Value) => { return Union - Value; });
                Op(Line, "*", (Complex Union, Complex Value) => { return Union * Value; });
                Op(Line, "/", (Complex Union, Complex Value) => { return Union / Value; });
                /****/
                PowerOp(Line, "^", (Complex Union, long Value) => { return Union ^ Value; });
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
                Multiple(Line, "dot", Dot);
                Multiple(Line, "outer", Outer);
                Multiple(Line, "even", Even);
                Multiple(Line, "cross", Cross);
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
