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
        private static readonly string[] Name = new string[] { "Exit", "Complex Testing Console", "Quaternion Testing Console", "Octonion Testing Console", "Sedenion Extended Module" };
        private static readonly Action[] Func = new Action[] { null, CmplxConsole.Load, QuterConsole.Load, OctonConsole.Load, SedenConsole.Load };
        private const long HidLen = 1;
        private const long DefIdx = 3;
        private static long Idx = DefIdx;
        private static string AddSquares(this string Opt)
        {
            return "[" + Opt + "]";
        }
        public static string GetTitle()
        {
            return Idx > DefIdx ? "Extended Module (Sedenion, Pathion, Chingon, Routon, Voudon, ...)" : Name[Idx];
        }
        public static string GetStartupLine()
        {
            string Rst = " >> ";
            bool Fst = true;
            for (long i = HidLen; i < Name.Length; ++i, Fst = false)
            {
                if (Fst == false) { Rst += "   "; }
                Rst += Name[i].AddSquares();
            }
            return Rst;
        }
        public static bool IsSwitchTo(string Opt)
        {
            for (long i = 0; i < Name.Length; ++i)
            {
                if (Opt == Name[i].AddSquares())
                {
                    Idx = i;
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
            while (Func[Idx] != null)
            {
                Func[Idx].Invoke();
            }
            Idx = DefIdx;
            Console.Clear();
        }
        ///
        /// Console Line Materials
        ///
        internal static string Exception(Exception Exc)
        {
            Console.WriteLine();
            while (Exc != null)
            {
                Console.ForegroundColor = ConsoleColor.DarkCyan;
                Console.Write("   [" + Exc.GetType().FullName + "] ");
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine(Exc.Message);
                Console.ForegroundColor = ConsoleColor.Gray;
                Console.WriteLine(Regex.Replace(Exc.StackTrace, "^", "   ", RegexOptions.Multiline));
                Exc = Exc.InnerException;
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
        internal static string Selection(string Con)
        {
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write(" %   ");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine(Con);
            return Con;
        }
        internal static string Selection()
        {
            return Selection("");
        }
        internal static string Input(string Con)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(" >   ");
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            Console.Write(Con);
            Console.ForegroundColor = ConsoleColor.Green;
            return Console.ReadLine();
        }
        internal static string Input()
        {
            return Input("");
        }
        internal static string Output(string Pre, string Con)
        {
            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.Write(" #   ");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.Write(Pre);
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(Con);
            return Con;
        }
        internal static string Output(string Con)
        {
            return Output("", Con);
        }
        internal static string Output()
        {
            return Output("");
        }
        internal static string Comment(string Pre, string Con)
        {
            Console.ForegroundColor = ConsoleColor.White;
            Console.Write(" /   ");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.Write(Pre);
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(Con);
            return Con;
        }
        internal static string Comment(string Con)
        {
            return Comment("", Con);
        }
        internal static string Comment()
        {
            return Comment("");
        }
        internal static void Startup(string Tit)
        {
            Console.Clear();
            Console.Title = Tit;
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
        private static string PowBeg(string R, object[] Args)
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
        internal static void PowGet(object[] Args)
        {
            for (int i = 2; i < Args.Length; ++i)
            {
                Args[i] = Base.Input(GetName(i) + Assign).Int();
            }
        }
        internal static void PowGet(object[] Args, long[] Upper)
        {
            for (int i = 2; i < Args.Length; ++i)
            {
                long Min = Base.Input(GetName(i - 2) + "(min)" + Assign).Int();
                long Max = Base.Input(GetName(i - 2) + "(max)" + Assign).Int();
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
        private static void PowRstLoop(Delegate S, string R, object[] Args, long[] Upper, int Dim)
        {
            if (Dim == Upper.Length)
            {
                Base.Output(PowBeg(R, Args), S.DynamicInvoke(Args).ToString());
                return;
            }
            object Lower = Args[Dim + 2];
            while ((long)Args[Dim + 2] <= Upper[Dim])
            {
                PowRstLoop(S, R, Args, Upper, Dim + 1);
                Args[Dim + 2] = (long)Args[Dim + 2] + 1;
            }
            Args[Dim + 2] = Lower;
        }
        internal static void PowRst(Delegate S, object[] Args)
        {
            Base.Output(S.DynamicInvoke(Args).ToString());
        }
        internal static void PowRst(Delegate S, string R, object[] Args, long[] Upper)
        {
            PowRstLoop(S, R, Args, Upper, 0);
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
        internal static long Int(this string Val)
        {
            return long.Parse(Val.Replace(" ", ""));
        }
    }
}
