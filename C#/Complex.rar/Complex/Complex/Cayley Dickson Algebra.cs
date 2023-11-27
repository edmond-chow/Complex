using System;
internal class Number
{
    private static bool IsNumber(long Number)
    {
        if (Number < 0) { return false; }
        if (Number == 1) { return true; }
        else if (Number == 0 || (Number >> 1 << 1 != Number)) { return false; }
        return IsNumber(Number >> 1);
    }
    private double[] Data;
    public double this[long Index]
    {
        get { return Data[Index]; }
        set { Data[Index] = value; }
    }
    public int Length
    {
        get { return Data.Length; }
    }
    public long LongLength
    {
        get { return Data.LongLength; }
    }
    public Number(long Size)
    {
        Data = new double[Size];
    }
    public Number(params double[] Args)
    {
        Data = Args;
    }
    public static bool Equal(Number Union, Number Value)
    {
        if (Union.Data.LongLength != Value.Data.LongLength) { return false; }
        for (long i = 0; i < Value.Data.LongLength; ++i)
        {
            if (Union.Data[i] != Value.Data[i]) { return false; }
        }
        return true;
    }
    public static Number Add(Number Union, Number Value)
    {
        if (Union.LongLength > Value.LongLength) { Add(Value, Union); }
        Number Result = Value;
        for (long i = 0; i < Union.LongLength; ++i) { Result.Data[i] += Union.Data[i]; }
        return Result;
    }
    public static Number Neg(Number Value)
    {
        Number Result = Value;
        for (long i = 0; i < Result.LongLength; ++i) { Result.Data[i] = -Result.Data[i]; }
        return Result;
    }
    public static Number Conjg(Number Value)
    {
        Number Result = Value;
        for (long i = 1; i < Result.LongLength; ++i) { Result.Data[i] = -Result.Data[i]; }
        return Result;
    }
    public Number GetLeft(long Count)
    {
        if (Count < 0 || Count > Data.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        double[] Numbers = new double[Count];
        for (long i = 0; i < Count; ++i) { Numbers[i] = Data[i]; }
        return new Number(Numbers);
    }
    public Number GetRight(long Count)
    {
        if (Count < 0 || Count > Data.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        double[] Numbers = new double[Count];
        for (long o = Data.LongLength - Count, i = 0; i < Count; ++i) { Numbers[i] = Data[o + i]; }
        return new Number(Numbers);
    }
    public Number Left
    {
        get { return GetLeft(Data.LongLength >> 1); }
    }
    public Number Right
    {
        get { return GetRight(Data.LongLength >> 1); }
    }
    public Number Extend(long Size)
    {
        if (Size > Data.LongLength)
        {
            double[] Numbers = new double[Size];
            for (long i = 0; i < Data.LongLength; ++i) { Numbers[i] = Data[i]; }
            Data = Numbers;
        }
        return this;
    }
    public static Number Merge(Number Union, Number Value)
    {
        double[] Numbers = new double[Union.Data.LongLength + Value.Data.LongLength];
        for (long o = Union.Data.LongLength, i = 0; i < o; ++i) { Numbers[i] = Union.Data[i]; }
        for (long o = Value.Data.LongLength, i = 0; i < o; ++i) { Numbers[o + i] = Value.Data[i]; }
        return new Number(Numbers);
    }
    public override bool Equals(object obj)
    {
        if (obj as Number == this) { return true; }
        return false;
    }
    public override int GetHashCode()
    {
        return 0;
    }
    private static bool Check(ref Number Union, ref Number Value, bool Shift)
    {
        long Offset = Shift ? 1 : 0;
        if (!IsNumber(Union.LongLength + Offset) || !IsNumber(Value.LongLength + Offset))
        {
            throw new ArgumentException("The size must be a number which is 2 to the power of a natural number.");
        }
        else if (Union.LongLength < Value.LongLength)
        {
            Union.Extend(Value.LongLength);
        }
        else if (Value.LongLength < Union.LongLength)
        {
            Value.Extend(Union.LongLength);
        }
        return Union.LongLength == 1;
    }
    private static Number MakeNumber(Number Value)
    {
        double[] Result = new double[Value.LongLength + 1];
        for (long i = 0; i < Value.LongLength; ++i) { Result[i + 1] = Value.Data[i]; }
        return new Number(Result);
    }
    private static Number MakeVector(Number Value)
    {
        return Value.GetRight(Value.LongLength - 1);
    }
    private static void AsVector(ref Number Value)
    {
        Value.Data[0] = 0;
    }
    private static double GetScalar(Number Value)
    {
        return Value.Data[0];
    }
    private static double Dot(Number Union, Number Value)
    {
        double Result = 0;
        for (long i = 0; i < Union.Data.LongLength; ++i)
        {
            Result += Union.Data[i] * Value.Data[i];
        }
        return Result;
    }
    public static bool operator ==(Number Union, Number Value)
    {
        return Equal(Union, Value);
    }
    public static bool operator !=(Number Union, Number Value)
    {
        return !(Union == Value);
    }
    public static Number operator +(Number Union, Number Value)
    {
        return Add(Union, Value);
    }
    public static Number operator -(Number Value)
    {
        return Neg(Value);
    }
    public static Number operator -(Number Union, Number Value)
    {
        return Union + (-Value);
    }
    public static Number operator ~(Number Value)
    {
        return Conjg(Value);
    }
    public static Number operator *(Number Union, Number Value)
    {
        Number NumUnion = Union;
        Number NumValue = Value;
        if (Check(ref NumUnion, ref NumValue, false)) { return new Number(GetScalar(NumUnion) * GetScalar(NumValue)); };
        Number MergeLeft = NumUnion.Left * NumValue.Left - ~NumValue.Right * NumUnion.Right;
        Number MergeRight = NumValue.Right * NumUnion.Left + NumUnion.Right * ~NumValue.Left;
        return Merge(MergeLeft, MergeRight);
    }
    public static Number operator *(double Union, Number Value)
    {
        Number Result = Value;
        for (long i = 0; i < Result.LongLength; ++i) { Result.Data[i] *= Union; }
        return Result;
    }
    public static Number operator *(Number Union, double Value)
    {
        return Value * Union;
    }
    public static Number operator /(Number Union, double Value)
    {
        return Union * (1 / Value);
    }
    public static double VectorDot(Number Union, Number Value)
    {
        Number VecUnion = Union;
        Number VecValue = Value;
        Check(ref VecUnion, ref VecValue, true);
        return Dot(VecUnion, VecValue);
    }
    public static Number VectorCross(Number Union, Number Value)
    {
        Number VecUnion = Union;
        Number VecValue = Value;
        Check(ref VecUnion, ref VecValue, true);
        return MakeVector(MakeNumber(VecUnion) * MakeNumber(VecValue));
    }
    public static double NumberDot(Number Union, Number Value)
    {
        Number NumUnion = Union;
        Number NumValue = Value;
        Check(ref NumUnion, ref NumValue, false);
        return Dot(NumUnion, NumValue);
    }
    public static Number NumberOuter(Number Union, Number Value)
    {
        double ScaUnion = GetScalar(Union);
        Number VecUnion = Union;
        AsVector(ref VecUnion);
        double ScaValue = GetScalar(Value);
        Number VecValue = Value;
        AsVector(ref VecValue);
        Check(ref VecUnion, ref VecValue, true);
        return NumberCross(VecUnion, VecValue) + ScaUnion * VecValue - ScaValue * VecUnion;
    }
    public static Number NumberEven(Number Union, Number Value)
    {
        double ScaUnion = GetScalar(Union);
        Number VecUnion = Union;
        AsVector(ref VecUnion);
        double ScaValue = GetScalar(Value);
        Number VecValue = Value;
        AsVector(ref VecValue);
        Check(ref VecUnion, ref VecValue, true);
        return new Number(ScaUnion * ScaValue - Dot(VecUnion, VecValue)) + ScaUnion * VecValue + ScaValue * VecUnion;
    }
    public static Number NumberCross(Number Union, Number Value)
    {
        Number NumUnion = Union;
        Number NumValue = Value;
        Check(ref NumUnion, ref NumValue, false);
        AsVector(ref NumUnion);
        AsVector(ref NumValue);
        Number Result = NumUnion * NumValue;
        AsVector(ref Result);
        return Result;
    }
    public double[] ToArray()
    {
        return Data;
    }
}
