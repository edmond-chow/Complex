﻿using System;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
internal static class Module
{
    private static readonly string RealRegExp = @"(-|\+|)(\d+)(\.\d+|)([Ee](-|\+|)(\d+)|)";
    private static readonly string NotOthers = @"(-|\+|$)";
    private static string DoubleToString(this double Number)
    {
        return Regex.Replace(Number.ToString("G17").ToLower(), "e-0(?=[1-9])", "e-");
    }
    internal static string ToString(this double[] Numbers, params string[] Terms)
    {
        if (Numbers.LongLength != Terms.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        StringBuilder TheString = new StringBuilder();
        for (long i = 0; i < Numbers.LongLength; ++i)
        {
            string Replace = Numbers[i].DoubleToString();
            if (Numbers[i] > 0)
            {
                if (Terms[i].Length > 0) { Replace = Regex.Replace(Replace, "^1$", ""); }
                TheString.Append('+').Append(Replace).Append(Terms[i]);
            }
            else if (Numbers[i] < 0)
            {
                if (Terms[i].Length > 0) { Replace = Regex.Replace(Replace, "^-1$", "-"); }
                TheString.Append(Replace).Append(Terms[i]);
            }
        }
        string RetString = TheString.ToString();
        RetString = Regex.Replace(RetString, "^$", "0");
        RetString = Regex.Replace(RetString, @"^\+", "");
        return RetString;
    }
    private static string GetInitTermRegexString(string[] Terms)
    {
        StringBuilder TheString = new StringBuilder();
        TheString.Append(@"(^|\+|-)(");
        for (long i = 0; i < Terms.LongLength; ++i)
        {
            if (Terms[i].Length > 0) { TheString.Append("(?=").Append(Terms[i]).Append(")|"); }
        }
        return Regex.Replace(TheString.ToString(), @"\)\|$", "))");
    }
    private static string GetRegexString(string Term, bool With)
    {
        return RealRegExp + (With ? Term : "") + "(?=" + (With ? "" : Term) + NotOthers + ")";
    }
    private static bool TestForValid(string Value, string[] Terms)
    {
        string Test = Value;
        for (long i = 0; i < Terms.LongLength; ++i) { Test = new Regex(GetRegexString(Terms[i], true)).Replace(Test, ""); }
        return Test.Length == 0;
    }
    private static void SetForValue(string TheValue, double[] Numbers, string[] Terms)
    {
        if (Numbers.LongLength != Terms.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        for (long i = 0; i < Numbers.LongLength; ++i)
        {
            MatchCollection Match = new Regex(GetRegexString(Terms[i], false)).Matches(TheValue);
            for (int j = 0; j < Match.Count; ++j) { Numbers[i] += double.Parse(Match[j].Value); }
        }
    }
    internal static double[] ToNumbers(this string Value, params string[] Terms)
    {
        double[] Numbers = new double[Terms.LongLength];
        string TheValue = new Regex(GetInitTermRegexString(Terms)).Replace(Value.Replace(" ", ""), "${0}1");
        if (!TestForValid(TheValue, Terms)) { throw new ArgumentException("The string is invalid."); }
        if (TheValue.Length == 0) { throw new ArgumentException("The string is empty."); }
        SetForValue(TheValue, Numbers, Terms);
        return Numbers;
    }
    internal static long Period(Type type)
    {
        long Output = 0;
        if (!type.IsValueType) { throw new NotImplementedException("The type should be a value type."); }
        foreach (FieldInfo Field in type.GetRuntimeFields())
        {
            if (Field.FieldType == typeof(double)) { ++Output; }
            else if (Field.FieldType.IsValueType) { Output += Period(Field.FieldType); }
            else { throw new NotImplementedException("The subobjects of an object should be an instance of the double type."); }
        }
        return Output;
    }
    internal static long PeriodShift(long i, long l)
    {
        --i;
        i %= l;
        return ++i;
    }
}