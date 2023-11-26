using System;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
internal static class Module
{
    private static readonly string SignBefore = @"(-|\+|^)";
    private static readonly string UnsignedReal = @"(\d+)(\.\d+|)([Ee](-|\+|)(\d+)|)";
    private static readonly string SignAfter = @"(-|\+|$)";
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
    private static string DoubleToString(this double Number)
    {
        return Regex.Replace(Number.ToString("G17").ToLower(), "e-0(?=[1-9])", "e-");
    }
    internal static string ToString(this double[] Numbers, params string[] Terms)
    {
        if (Numbers.LongLength != Terms.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        StringBuilder Result = new StringBuilder();
        bool First = true;
        for (long i = 0; i < Numbers.LongLength; ++i)
        {
            if (Numbers[i] == 0) { continue; }
            if (Numbers[i] > 0 && First == false) { Result.Append("+"); }
            else if (Numbers[i] == -1) { Result.Append("-"); }
            if (Numbers[i] != 1 && Numbers[i] != -1) { Result.Append(Numbers[i].DoubleToString()); }
            else if (Terms[i].Length == 0) { Result.Append("1"); }
            if (Terms[i].Length > 0) { Result.Append(Terms[i]); }
            First = false;
        }
        if (First == true) { Result.Append("0"); }
        return Result.ToString();
    }
    internal static double[] ToNumbers(this string Value, params string[] Terms)
    {
        double[] Numbers = new double[Terms.LongLength];
        int Vaild = Value.Length;
        if (Vaild == 0) { throw new ArgumentException("The string is empty."); }
        for (long i = 0; i < Numbers.LongLength; ++i)
        {
            MatchCollection Match = new Regex(GetPattern(Terms[i])).Matches(Value);
            for (int j = 0; j < Match.Count; ++j)
            {
                string Captured = Match[j].Value;
                Vaild -= Captured.Length + Terms[i].Length;
                if (Captured.Length == 0 || Captured == "+") { ++Numbers[i]; }
                else if (Captured == "-") { --Numbers[i]; }
                else { Numbers[i] += double.Parse(Captured); }
            }
        }
        if (Vaild > 0) { throw new ArgumentException("The string is invalid."); }
        return Numbers;
    }
    internal static long Period(Type Type)
    {
        long Result = 0;
        if (!Type.IsValueType) { throw new NotImplementedException("The type should be a value type."); }
        foreach (FieldInfo Field in Type.GetRuntimeFields())
        {
            if (Field.FieldType == typeof(double)) { ++Result; }
            else if (Field.FieldType.IsValueType) { Result += Period(Field.FieldType); }
            else { throw new NotImplementedException("The subobjects of an object should be an instance of the double type."); }
        }
        return Result;
    }
    internal static void Adjust(ref long Index, long LongLength, bool Shift)
    {
        if (Shift)
        {
            --Index;
            Index %= LongLength;
            ++Index;
        }
        else { Index %= LongLength; }
    }
}
