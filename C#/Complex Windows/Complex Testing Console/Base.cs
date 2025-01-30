/*
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
using System.Text;
using System.Text.RegularExpressions;
namespace ComplexTestingConsole
{
    internal static class Base
    {
        ///
        /// Base
        ///
        private static readonly string[] Alternative = new string[] { "Exit", "Complex Testing Console", "Quaternion Testing Console", "Octonion Testing Console", "Sedenion Extended Module" };
        private static readonly Action[] Subroutine = new Action[] { null, CmplxConsole.Load, QuterConsole.Load, OctonConsole.Load, SedenConsole.Load };
        private const long HiddenLength = 1;
        private const long DefaultIndex = 3;
        private static long Index = DefaultIndex;
        private static string AddSquares(this string Option)
        {
            return "[" + Option + "]";
        }
        public static string GetTitle()
        {
            return Index > DefaultIndex ? "Extended Module (Sedenion, Pathion, Chingon, Routon, Voudon, ...)" : Alternative[Index];
        }
        public static string GetStartupLine()
        {
            string Result = " >> ";
            bool First = true;
            for (long i = HiddenLength; i < Alternative.Length; ++i, First = false)
            {
                if (First == false) { Result += "   "; }
                Result += Alternative[i].AddSquares();
            }
            return Result;
        }
        public static bool IsSwitchTo(string Option)
        {
            for (long i = 0; i < Alternative.Length; ++i)
            {
                if (Option == Alternative[i].AddSquares())
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
                Console.WriteLine(Regex.Replace(Exception.StackTrace, "^", "   ", RegexOptions.Multiline));
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
        private const string Assign = " = ";
        private static string GetName(int i)
        {
            return "z" + i.ToString();
        }
        internal static void PowGet(object[] Args)
        {
            for (int i = 2; i < Args.Length; ++i)
            {
                Args[i] = Base.Input(GetName(i) + Assign).AsInt();
            }
        }
        internal static void PowGet(object[] Args, long[] Upper)
        {
            for (int i = 2; i < Args.Length; ++i)
            {
                long Min = Base.Input(GetName(i - 2) + "(min)" + Assign).AsInt();
                long Max = Base.Input(GetName(i - 2) + "(max)" + Assign).AsInt();
                if (Min <= Max)
                {
                    Args[i] = Min;
                    Upper[i - 2] = Max;
                }
                else
                {
                    Args[i] = Max;
                    Upper[i - 2] = Min;
                }
            }
        }
        internal static void PowRst(Delegate S, object[] Args)
        {
            Base.Output(S.DynamicInvoke(Args).ToString());
        }
        internal static void PowRst(Delegate S, string R, object[] Args, long[] Upper)
        {
            PowRstImpl(S, R, Args, Upper, 0);
        }
        private static void PowRstImpl(Delegate S, string R, object[] Args, long[] Upper, int Dim)
        {
            if (Dim == Upper.Length)
            {
                Base.Output(PowPrepend(R, Args), S.DynamicInvoke(Args).ToString());
                return;
            }
            object Lower = Args[Dim + 2];
            while ((long)Args[Dim + 2] <= Upper[Dim])
            {
                PowRstImpl(S, R, Args, Upper, Dim + 1);
                Args[Dim + 2] = (long)Args[Dim + 2] + 1;
            }
            Args[Dim + 2] = Lower;
        }
        private static string PowPrepend(string R, object[] Args)
        {
            StringBuilder Rst = new StringBuilder();
            Rst.Append(R).Append("(");
            bool Fst = true;
            for (int i = 2; i < Args.Length; ++i, Fst = false)
            {
                if (!Fst) { Rst.Append(", "); }
                Rst.Append(Args[i].ToString());
            }
            Rst.Append(") = ");
            return Rst.ToString();
        }
        private static string Str(this double Num)
        {
            return Regex.Replace(Num.ToString("G17").ToLower(), "e-0(?=[1-9])", "e-");
        }
        internal static string ToModStr(this object Obj)
        {
            if (Obj is double D) { return D.Str(); }
            else if (Obj is long L) { return L.ToString(); }
            else if (Obj is bool B) { return B ? "true" : "false"; }
            return Obj.ToString();
        }
        internal static long AsInt(this string Val)
        {
            return long.Parse(Val.Replace(" ", ""));
        }
        internal static double AsReal(this string Val)
        {
            return double.Parse(Val.Replace(" ", ""));
        }
    }
}
