using System;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
internal static class Module
{
    private static readonly string SignBefore = @"(-|\+|^)";
    private static readonly string UnsignedReal = @"(\d+)(\.\d+|)([Ee](-|\+|)(\d+)|)";
    private static readonly string SignAfter = @"(-|\+|$)";
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
            string Result = Numbers[i].DoubleToString();
            if (Numbers[i] > 0)
            {
                if (Terms[i].Length > 0) { Result = Regex.Replace(Result, "^1$", ""); }
                TheString.Append('+').Append(Result).Append(Terms[i]);
            }
            else if (Numbers[i] < 0)
            {
                if (Terms[i].Length > 0) { Result = Regex.Replace(Result, "^-1$", "-"); }
                TheString.Append(Result).Append(Terms[i]);
            }
        }
        string RetString = TheString.ToString();
        RetString = Regex.Replace(RetString, "^$", "0");
        RetString = Regex.Replace(RetString, @"^\+", "");
        return RetString;
    }
    private static string AddGroup(this string Pattern, bool Optional)
    {
        return "(" + Pattern + (Optional ? "|" : "") + ")";
    }
    private static string FollowedBy(this string Pattern, string Text)
    {
        return Pattern + "(?=" + Text + ")";
    }
    private static string GetPattern(string Term)
    {
        return (SignBefore + UnsignedReal.AddGroup(Term.Length > 0)).FollowedBy(Term + SignAfter);
    }
    internal static double[] ToNumbers(this string Value, params string[] Terms)
    {
        string Replaced = Value.Replace(" ", "");
        double[] Numbers = new double[Terms.LongLength];
        int Vaild = Replaced.Length;
        if (Vaild == 0) { throw new ArgumentException("The string is empty."); }
        for (long i = 0; i < Numbers.LongLength; ++i)
        {
            MatchCollection Match = new Regex(GetPattern(Terms[i])).Matches(Replaced);
            for (int j = 0; j < Match.Count; ++j)
            {
                string Capture = Match[j].Value;
                Vaild -= Capture.Length + Terms[i].Length;
                if (Capture.Length == 0 || Capture == "+") { ++Numbers[i]; }
                else if (Capture == "-") { --Numbers[i]; }
                else { Numbers[i] += double.Parse(Capture); }
            }
        }
        if (Vaild > 0) { throw new ArgumentException("The string is invalid."); }
        return Numbers;
    }
    internal static long Period(Type Type)
    {
        long Output = 0;
        if (!Type.IsValueType) { throw new NotImplementedException("The type should be a value type."); }
        foreach (FieldInfo Field in Type.GetRuntimeFields())
        {
            if (Field.FieldType == typeof(double)) { ++Output; }
            else if (Field.FieldType.IsValueType) { Output += Period(Field.FieldType); }
            else { throw new NotImplementedException("The subobjects of an object should be an instance of the double type."); }
        }
        return Output;
    }
    internal static long PeriodShift(long Index, long LongLength)
    {
        --Index;
        Index %= LongLength;
        return ++Index;
    }
}
