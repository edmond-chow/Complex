using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
internal class Number : IEnumerable<double>
{
    public class NumberIterator : IEnumerator<double>
    {
        private readonly double[] Numbers;
        private long Index;
        public double Current
        {
            get { return Numbers[Index]; }
        }
        object IEnumerator.Current
        {
            get { return Numbers[Index]; }
        }
        public void Dispose() { }
        public bool MoveNext()
        {
            ++Index;
            return Index < Numbers.LongLength;
        }
        public void Reset()
        {
            Index = -1;
        }
        public NumberIterator(double[] Data)
        {
            Numbers = Data;
            Index = -1;
        }
    }
    public IEnumerator<double> GetEnumerator()
    {
        return new NumberIterator(Data);
    }
    IEnumerator IEnumerable.GetEnumerator()
    {
        return new NumberIterator(Data);
    }
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
        return Enumerable.SequenceEqual(Union, Value);
    }
    public static Number Add(Number Union, Number Value)
    {
        if (Union.LongLength > Value.LongLength) { Add(Value, Union); }
        return new Number(Enumerable.Zip(Union, Value, (double U, double V) => { return U + V; }).Concat(Value.Skip(Union.Length)).ToArray());
    }
    public static Number Neg(Number Value)
    {
        return new Number(Value.Select((double V) => { return -V; }).ToArray());
    }
    public static Number Conjg(Number Value)
    {
        return new Number(Value.Take(1).Concat(Value.Skip(1).Select((double V) => { return -V; })).ToArray());
    }
    public Number GetLeft(int Count)
    {
        if (0 >= Count || Count > Length) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        return new Number(this.Take(Count).ToArray());
    }
    public Number GetRight(int Count)
    {
        if (0 > Count || Count >= Length) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        return new Number(this.Skip(Count).ToArray());
    }
    public Number Left
    {
        get
        {
            return GetLeft(Length >> 1);
        }
    }
    public Number Right
    {
        get
        {
            return GetRight(Length >> 1);
        }
    }
    public Number Extend(int Size)
    {
        if (Size > Length) { Array.Resize(ref Data, Size); }
        return this;
    }
    public static Number Merge(Number Union, Number Value)
    {
        return new Number(Enumerable.Concat(Union, Value).ToArray());
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
        int Offset = Shift ? 1 : 0;
        if (!IsNumber(Union.Length + Offset) || !IsNumber(Value.Length + Offset))
        {
            throw new ArgumentException("The size must be a number which is 2 to the power of a natural number.");
        }
        else if (Union.Length < Value.Length)
        {
            Union.Extend(Value.Length);
        }
        else if (Value.Length < Union.Length)
        {
            Value.Extend(Union.Length);
        }
        return Union.Length == 1;
    }
    private static Number MakeNumber(Number Value)
    {
        return new Number(new double[] { 0 }.Concat(Value).ToArray());
    }
    private static Number MakeVector(Number Value)
    {
        return new Number(Value.Skip(1).ToArray());
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
        return new Number(Value.Select((double V) => { return V * Union; }).ToArray());
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
}
