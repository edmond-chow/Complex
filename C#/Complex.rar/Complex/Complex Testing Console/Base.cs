using System;
using System.Text;
using System.Text.RegularExpressions;
namespace ComplexTestingConsole
{
    internal static class Base
    {
        ///
        /// Base
        ///
        private static readonly string[] TestingConsole = new string[] { "Exit", "Complex Testing Console", "Quaternion Testing Console", "Octonion Testing Console", "Sedenion Extended Module" };
        private static readonly Action[] Subroutine = new Action[] { null, CmplxConsole.Load, QuterConsole.Load, OctonConsole.Load, SedenConsole.Load };
        private const long DefaultIndex = 3;
        private static long Index = DefaultIndex;
        private static string AddSquares(this string Option)
        {
            return "[" + Option + "]";
        }
        public static string GetTitle()
        {
            return Index > DefaultIndex ? "Extended Module (Sedenion, Pathion, Chingon, Routon, Voudon, ...)" : TestingConsole[Index];
        }
        public static string GetStartupLine()
        {
            string Result = " >> ";
            bool First = true;
            for (long i = 1; i < TestingConsole.LongLength; ++i, First = false)
            {
                if (First == false) { Result += "   "; }
                Result += TestingConsole[i].AddSquares();
            }
            return Result;
        }
        public static bool IsSwitchTo(string Option)
        {
            for (long i = 0; i < TestingConsole.LongLength; ++i)
            {
                if (Option == TestingConsole[i].AddSquares())
                {
                    Index = i;
                    return true;
                }
            }
            return false;
        }
        ///
        /// Main Thread
        ///
        internal static void Main()
        {
            while (Subroutine[Index] != null)
            {
                Subroutine[Index].Invoke();
            }
            Index = DefaultIndex;
            Console.Clear();
        }
        ///
        /// Console Line Materials
        ///
        internal static string Exception(Exception Exception)
        {
            Console.WriteLine();
            while (Exception != null)
            {
                Console.ForegroundColor = ConsoleColor.DarkCyan;
                Console.Write("   [" + Exception.GetType().FullName + "] ");
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine(Exception.Message);
                Console.ForegroundColor = ConsoleColor.Gray;
                Console.WriteLine(Regex.Replace(Exception.StackTrace, "(^|\n)", "${0}   "));
                Exception = Exception.InnerException;
            }
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine("   Press any key to continue . . . ");
            Console.ReadKey(true);
            Console.WriteLine();
            return "";
        }
        internal static string Exception()
        {
            return Exception(new Exception());
        }
        internal static string Selection(string Content)
        {
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write(" %   ");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine(Content);
            return Content;
        }
        internal static string Selection()
        {
            return Selection("");
        }
        internal static string Input(string Content)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(" >   ");
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            Console.Write(Content);
            Console.ForegroundColor = ConsoleColor.Green;
            return Console.ReadLine();
        }
        internal static string Input()
        {
            return Input("");
        }
        internal static string Output(string Preceding, string Content)
        {
            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.Write(" #   ");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.Write(Preceding);
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(Content);
            return Content;
        }
        internal static string Output(string Content)
        {
            return Output("", Content);
        }
        internal static string Output()
        {
            return Output("");
        }
        internal static string Comment(string Preceding, string Content)
        {
            Console.ForegroundColor = ConsoleColor.White;
            Console.Write(" /   ");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.Write(Preceding);
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(Content);
            return Content;
        }
        internal static string Comment(string Content)
        {
            return Comment("", Content);
        }
        internal static string Comment()
        {
            return Comment("");
        }
        internal static void Startup(string Title)
        {
            Console.Clear();
            Console.Title = Title;
            Console.WriteLine();
        }
    }
    internal static class Module
    {
        private static readonly string Assign = " = ";
        private static readonly string[] Angle = { "Theta", "Phi", "Tau", "Omega" };
        private static string GetAngleName(long I, string[] Angle)
        {
            return I < Angle.LongLength ? Angle[I] : ("Angle" + I.ToString());
        }
        internal static void PowerGet(long[] Data)
        {
            for (long I = 0; I < Data.LongLength; ++I)
            {
                Data[I] = long.Parse(Base.Input(GetAngleName(I, Angle) + Assign));
            }
        }
        internal static void PowerGet(Tuple<long, long>[] Data)
        {
            for (long I = 0; I < Data.LongLength; ++I)
            {
                long Min = long.Parse(Base.Input(GetAngleName(I, Angle) + "Min" + Assign));
                long Max = long.Parse(Base.Input(GetAngleName(I, Angle) + "Max" + Assign));
                Data[I] = new Tuple<long, long>(Min, Max);
            }
        }
        internal static void PowerResult<N>(Delegate Subroutine, string RightValue, N Union, N Value, long[] Data)
        {
            if (RightValue == null) { return; }
            object[] Params = new object[Data.LongLength + 2];
            Params[0] = Union;
            Params[1] = Value;
            for (long i = 0; i < Data.LongLength; ++i) { Params[i + 2] = Data[i]; }
            Base.Output(((N)Subroutine.DynamicInvoke(Params)).ToString());
        }
        internal static void PowerResult<N>(Delegate Subroutine, string RightValue, N Union, N Value, Tuple<long, long>[] Data)
        {
            long[] Temp = new long[Data.LongLength];
            PowerResultImpl(Subroutine, RightValue, Union, Value, Data, Temp, 0);
        }
        private static void PowerResultImpl<N>(Delegate Subroutine, string RightValue, N Union, N Value, Tuple<long, long>[] Data, long[] Temp, long X)
        {
            if (X == Temp.LongLength)
            {
                object[] Params = new object[Temp.LongLength + 2];
                Params[0] = Union;
                Params[1] = Value;
                for (long i = 0; i < Temp.LongLength; ++i) { Params[i + 2] = Temp[i]; }
                Base.Output(GetOutputPrepend(RightValue, Temp), ((N)Subroutine.DynamicInvoke(Params)).ToString());
                return;
            }
            for (long I = Data[X].Item1; I <= Data[X].Item2; ++I)
            {
                Temp[X] = I;
                PowerResultImpl(Subroutine, RightValue, Union, Value, Data, Temp, X + 1);
            }
        }
        private static string GetOutputPrepend(string RightValue, long[] Temp)
        {
            StringBuilder Result = new StringBuilder();
            Result.Append(RightValue).Append("(");
            bool First = true;
            for (long i = 0; i < Temp.LongLength; ++i, First = false)
            {
                if (First == false) { Result.Append(", "); }
                Result.Append(Temp[i].ToString());
            }
            Result.Append(") = ");
            return Result.ToString();
        }
        private static string DoubleToString(this double Number)
        {
            return Regex.Replace(Number.ToString("G17").ToLower(), "e-0(?=[1-9])", "e-");
        }
        internal static string ToModuleString(this object Object)
        {
            if (Object is double DoubleValue) { return DoubleValue.DoubleToString(); }
            else if (Object is long LongValue) { return LongValue.ToString(); }
            else if (Object is bool BoolValue) { return BoolValue ? "true" : "false"; }
            return Object.ToString();
        }
    }
}
