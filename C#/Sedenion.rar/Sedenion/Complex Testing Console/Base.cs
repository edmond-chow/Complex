using System;
using System.Linq;
using System.Threading;
namespace ComplexTestingConsole
{
    internal static class Base
    {
        ///
        /// Base
        ///
        private static readonly string[] TestingConsole = new string[] { "Exit", "ComplexTestingConsole", "QuaternionTestingConsole", "OctonionTestingConsole" };
        private static readonly string[] SedenionModeConsole = new string[] { "SedenionMode", "Sedenion", "Trigintaduonion", "Sexagintaquatronion", "Centumduodetrigintanion", "Ducentiquinquagintasexion" };
        private static string[] ConsoleList => TestingConsole.Concat(new string[] { SedenionModeConsole[0] }).ToArray();
        private static long Index = TestingConsole.LongLength - 1;
        public static string GetTitle() { return ConsoleList[Index]; }
        public static string GetStartupLine()
        {
            string Output = " >> ";
            foreach (string Name in ConsoleList)
            {
                if (Name == TestingConsole[0]) { continue; }
                Output += "[";
                Output += Name;
                Output += "]   ";
            }
            return Output.Substring(0, Output.Length - 3);
        }
        public static string GetSedenTitle()
        {
            string Output = "";
            foreach (string Name in SedenionModeConsole.Skip(1))
            {
                Output += Name;
                Output += ", ";
            }
            return Output += "...";
        }
        public static bool IsSwitchTo(string Str)
        {
            for (long i = 0; i < ConsoleList.LongLength; ++i)
            {
                if (Str == "[" + ConsoleList[i] + "]")
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
            while (true)
            {
                switch (Index)
                {
                    case 0:
                        Console.Clear();
                        return;
                    case 1:
                        MyModule.Load();
                        break;
                    case 2:
                        MyModule2.Load();
                        break;
                    case 3:
                        MyModule3.Load();
                        break;
                    case 4:
                        MySedenionTestor.Load();
                        break;
                    default:
                        throw new NotImplementedException();
                }
            }
        }
        ///
        /// Console Line Materials
        ///
        internal static string Exception(Exception ex)
        {
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine(ex);
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine("Press any key to continue . . . ");
            Console.ReadKey(true);
            return "";
        }
        internal static string Exception()
        {
            return Exception(new Exception());
        }
        internal static string Selection(string str)
        {
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write(" %   ");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine(str);
            return str;
        }
        internal static string Selection()
        {
            return Selection("");
        }
        internal static string Input(string str)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(" >   ");
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            Console.Write(str);
            Console.ForegroundColor = ConsoleColor.Green;
            return Console.ReadLine();
        }
        internal static string Input()
        {
            return Input("");
        }
        internal static string Output(string main, string str)
        {
            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.Write(" #   ");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.Write(main);
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(str);
            return str;
        }
        internal static string Output(string str)
        {
            return Output("", str);
        }
        internal static string Output()
        {
            return Output("");
        }
        internal static string Comment(string head, string str)
        {
            Console.ForegroundColor = ConsoleColor.White;
            Console.Write(" /   ");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.Write(head);
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(str);
            return str;
        }
        internal static string Comment(string str)
        {
            return Comment("", str);
        }
        internal static string Comment()
        {
            return Comment("");
        }
        internal static void Startup(string title)
        {
            Console.Clear();
            Console.Title = title;
            Console.WriteLine();
        }
    }
    internal static class Module
    {
        private static void Swap(ref long U, ref long V)
        {
            Interlocked.Exchange(ref V, Interlocked.Exchange(ref U, V));
        }
        internal static string GetAngleName(long I, string[] Angle)
        {
            return I < Angle.LongLength ? Angle[I] : ("Angle" + I.ToString());
        }
        internal static void PowerGet(long[] Data)
        {
            string Assign = " = ";
            string[] Angle = { "Theta", "Phi", "Tau", "Omega" };
            for (long I = 0; I < Data.LongLength; ++I)
            {
                Data[I] = long.Parse(Base.Input(GetAngleName(I, Angle) + Assign));
            }
        }
        internal static void PowerGet(Tuple<long, long>[] Data)
        {
            string Assign = " = ";
            string[] Angle = { "Theta", "Phi", "Tau", "Omega" };
            for (long I = 0; I < Data.LongLength; ++I)
            {
                long Min = long.Parse(Base.Input(GetAngleName(I, Angle) + "Min" + Assign));
                long Max = long.Parse(Base.Input(GetAngleName(I, Angle) + "Max" + Assign));
                if (Min > Max) { Swap(ref Min, ref Max); }
                Data[I] = new Tuple<long, long>(Min, Max);
            }
        }
        internal static void PowerResult<N>(Delegate f, string str, N Union, N Value, long[] Data)
        {
            if (str == null) { return; }
            object[] Params = new object[Data.LongLength + 2];
            Params[0] = Union;
            Params[1] = Value;
            for (long i = 0; i < Data.LongLength; ++i) { Params[i + 2] = Data[i]; }
            Base.Output(((N)f.DynamicInvoke(Params)).ToString());
        }
        internal static void PowerResult<N>(Delegate f, string str, N Union, N Value, Tuple<long, long>[] Data)
        {
            long[] Temp = new long[Data.LongLength];
            PowerResultImpl(f, str, Union, Value, Data, Temp, 0);
        }
        internal static void PowerResultImpl<N>(Delegate f, string str, N Union, N Value, Tuple<long, long>[] Data, long[] Temp, long X)
        {
            if (X == Temp.LongLength)
            {
                object[] Params = new object[Temp.LongLength + 2];
                Params[0] = Union;
                Params[1] = Value;
                for (long i = 0; i < Temp.LongLength; ++i) { Params[i + 2] = Temp[i]; }
                Base.Output(GetOutputPrepend(str, Temp), ((N)f.DynamicInvoke(Params)).ToString());
                return;
            }
            for (long I = Data[X].Item1; I <= Data[X].Item2; ++I)
            {
                Temp[X] = I;
                PowerResultImpl(f, str, Union, Value, Data, Temp, X + 1);
            }
        }
        internal static string GetOutputPrepend(string str, long[] integers)
        {
            string ret = str + "(";
            for (long i = 0; i < integers.LongLength ; ++i)
            {
                ret += integers[i].ToString() + ", ";
            }
            ret = ret.Substring(0, ret.Length - 2);
            ret += ") = ";
            return ret;
        }
    }
}
