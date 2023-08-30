﻿using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
internal class Number : IEnumerable<double>
{
    public class NumberIterator : IEnumerator<double>
    {
        private readonly double[] Numbers;
        private long Index;
        public double Current => Numbers[Index];
        object IEnumerator.Current => Numbers[Index];
        public void Dispose() { }
        public bool MoveNext()
        {
            if (Index < Numbers.LongLength) { ++Index; }
            if (Index == Numbers.LongLength) { return false; }
            return true;
        }
        public void Reset() { Index = -1; }
        public NumberIterator(double[] Data)
        {
            Numbers = Data;
            Index = -1;
        }
    }
    public IEnumerator<double> GetEnumerator() { return new NumberIterator(Data); }
    IEnumerator IEnumerable.GetEnumerator() { return new NumberIterator(Data); }
    private static bool IsNumber(long Number)
    {
        if (Number < 0) { return false; }
        if (Number == 1) { return true; }
        else if (Number == 0 || (Number >> 1 << 1 != Number)) { return false; }
        return IsNumber(Number >> 1);
    }
    private readonly double[] Data;
    public double this[long Index]
    {
        get => Data[Index];
        set => Data[Index] = value;
    }
    public int Length { get => Data.Length; }
    public long LongLength { get => Data.LongLength; }
    public Number(long Size)
    {
        if (!IsNumber(Size)) { throw new ArgumentException("The size must be a number which is 2 to the power of a natural number."); }
        Data = new double[Size];
    }
    public Number(params double[] Args)
    {
        if (!IsNumber(Args.LongLength)) { throw new ArgumentException("The size must be a number which is 2 to the power of a natural number."); }
        Data = Args;
    }
    public static bool Equal(Number Union, Number Value)
    {
        if (Union.LongLength != Value.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        return Enumerable.SequenceEqual(Union, Value);
    }
    public static Number Add(Number Union, Number Value)
    {
        if (Union.LongLength != Value.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        return new Number(Enumerable.Zip(Union, Value, (double U, double V) => { return U + V; }).ToArray());
    }
    public static Number Neg(Number Value)
    {
        return new Number(Value.Select((double V) => { return -V; }).ToArray());
    }
    public static Number Conjg(Number Value)
    {
        Number Output = Neg(Value);
        Output[0] = -Output[0];
        return Output;
    }
    public Number Left
    {
        get
        {
            if (LongLength == 1) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
            return new Number(this.Take(Length / 2).ToArray());
        }
    }
    public Number Right
    {
        get
        {
            if (LongLength == 1) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
            return new Number(this.Skip(Length / 2).ToArray());
        }
    }
    public static Number Merge(Number Union, Number Value)
    {
        if (Union.LongLength != Value.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        return new Number(Enumerable.Concat(Union, Value).ToArray());
    }
    public override bool Equals(object obj)
    {
        if (obj as Number == this) { return true; }
        return false;
    }
    public override int GetHashCode() { return 0; }
    public static bool operator ==(Number Union, Number Value) { return Equal(Union, Value); }
    public static bool operator !=(Number Union, Number Value) { return !(Union == Value); }
    public static Number operator +(Number Union, Number Value) { return Add(Union, Value); }
    public static Number operator -(Number Value) { return Neg(Value); }
    public static Number operator -(Number Union, Number Value) { return Union + (-Value); }
    public static Number operator ~(Number Value) { return Conjg(Value); }
    public static Number operator *(Number Union, Number Value)
    {
        if (Union.LongLength != Value.LongLength) { throw new NotImplementedException("The branch should ensure not instantiated at compile time."); }
        if (Union.LongLength == 1) { return new Number(Union[0] * Value[0]); }
        return Merge(
            Union.Left * Value.Left - ~Value.Right * Union.Right,
            Value.Right * Union.Left + Union.Right * ~Value.Left
        );
    }
    public static Number operator *(double Union, Number Value)
    {
        return new Number(Value.Select((double V) => { return V * Union; }).ToArray());
    }
    public static Number operator *(Number Union, double Value) { return Value * Union; }
    public static Number operator /(Number Union, double Value) { return Union * (1 / Value); }
}