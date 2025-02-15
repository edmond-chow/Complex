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
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
internal static class Module
{
    internal interface INum
    {
        double this[int i] { get; set; }
    }
    internal readonly struct Terms
    {
        private readonly string[] Rf;
        private readonly int Sz;
        public Terms(string[] Trm)
        {
            Rf = Trm;
            Sz = 0;
        }
        public Terms(int Dim)
        {
            Rf = null;
            Sz = Dim;
        }
        public bool Null()
        {
            return Rf is null;
        }
        public int Size()
        {
            return Rf is null ? Sz : Rf.Length;
        }
        public string this[int i]
        {
            get
            {
                return Rf is null ? "e" + i.ToString() : Rf[i];
            }
        }
    }
    private static readonly string Beg = @"(-|\+|^)";
    private static readonly string Sig = @"((\d+)(\.\d+|)([Ee](-|\+|)(\d+)|)|)";
    private static readonly string End = @"(?=(-|\+|$))";
    private const int BegI = 1;
    private const int SigI = 2;
    private const int TrmI = 8;
    private static string Group(this Terms Trm)
    {
        if (Trm.Null()) { return "(e\\d+)"; }
        StringBuilder Rst = new StringBuilder();
        Rst.Append("(");
        for (int i = 0; i < Trm.Size(); ++i)
        {
            Rst.Append(i == 0 ? "" : "|").Append(Trm[i]);
        }
        Rst.Append(")");
        return Rst.ToString();
    }
    private static string Pat(ref Terms Trm)
    {
        return Beg + Sig + Trm.Group() + End;
    }
    private static string Str(this double Num)
    {
        return Regex.Replace(Num.ToString("G17").ToLower(), "e-0(?=[1-9])", "e-");
    }
    internal static string ToString(this double[] Num, ref Terms Trm)
    {
        if (Num.Length != Trm.Size()) { throw new NotImplementedException("The branch should unreachable."); }
        StringBuilder Rst = new StringBuilder();
        bool Fst = true;
        for (int i = 0; i < Num.Length; ++i)
        {
            if (Num[i] == 0) { continue; }
            if (Num[i] > 0 && !Fst) { Rst.Append("+"); }
            else if (Num[i] == -1) { Rst.Append("-"); }
            if (Num[i] != 1 && Num[i] != -1) { Rst.Append(Num[i].Str()); }
            else if (Trm[i].Length == 0) { Rst.Append("1"); }
            Rst.Append(Trm[i]);
            Fst = false;
        }
        if (Fst) { Rst.Append("0"); }
        return Rst.ToString();
    }
    internal static string ToString<N>(ref N Rst, bool Vec, params string[] Trm) where N : INum
    {
        Terms RTrm = new Terms(Trm);
        double[] Num = new double[Trm.Length];
        for (int i = 0, o = Vec ? 1 : 0; i < Num.Length; ++i) { Num[i] = Rst[i + o]; }
        return Num.ToString(ref RTrm);
    }
    internal static double[] ToNumbers(this string Val, ref Terms Trm)
    {
        int Siz = Trm.Size();
        double[] Num = new double[Siz];
        int Suf = 0;
        string Reg = Pat(ref Trm);
        Match Mat = Regex.Match(Val, Reg);
        while (Mat.Success)
        {
            if (Suf != Mat.Index) { throw new ArgumentException("The string is invalid."); }
            string BegV = Mat.Groups[BegI].Value;
            string SigV = Mat.Groups[SigI].Value;
            string TrmV = Mat.Groups[TrmI].Value;
            string Cap = BegV + SigV;
            int i = 0;
            if (Trm.Null()) { i = int.Parse(TrmV.Substring(1)); }
            else
            {
                while (Trm[i] != TrmV && i < Siz) { ++i; }
                if (i == Siz) { throw new NotImplementedException("The branch should unreachable."); }
            }
            if (SigV.Length == 0 && TrmV.Length == 0) { throw new ArgumentException("The string is invalid."); }
            else if (Cap.Length == 0 || Cap == "+") { ++Num[i]; }
            else if (Cap == "-") { --Num[i]; }
            else { Num[i] += double.Parse(Cap); }
            Suf = Mat.Index + Mat.Length;
            Mat = Mat.NextMatch();
        }
        if (Suf != Val.Length) { throw new ArgumentException("The string is invalid."); }
        return Num;
    }
    internal static void ToNumbers<N>(this string Val, ref N Rst, bool Vec, params string[] Trm) where N : INum
    {
        Terms RTrm = new Terms(Trm);
        double[] Num = Val.ToNumbers(ref RTrm);
        for (int i = 0, o = Vec ? 1 : 0; i < Num.Length; ++i) { Rst[i + o] = Num[i]; }
    }
}
