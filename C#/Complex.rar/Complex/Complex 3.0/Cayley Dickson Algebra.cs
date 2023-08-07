using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
namespace Cmplx3
{
    internal class Number : IEnumerable<double>
    {
        public class NumberIterator : IEnumerator<double>
        {
            private readonly double[] numbers;
            private long index;
            public double Current => numbers[index];
            object IEnumerator.Current => numbers[index];
            public void Dispose() { }
            public bool MoveNext()
            {
                if (index < numbers.LongLength) { ++index; }
                if (index == numbers.LongLength) { return false; }
                return true;
            }
            public void Reset() { index = -1; }
            public NumberIterator(double[] data)
            {
                numbers = data;
                index = -1;
            }
        }
        public IEnumerator<double> GetEnumerator() { return new NumberIterator(data); }
        IEnumerator IEnumerable.GetEnumerator() { return new NumberIterator(data); }
        private static bool IsNumber(long n)
        {
            if (n < 0) { return false; }
            if (n == 1) { return true; }
            else if (n == 0 || (n >> 1 << 1 != n)) { return false; }
            return IsNumber(n >> 1);
        }
        private readonly double[] data;
        public double this[long i]
        {
            get => data[i];
            set => data[i] = value;
        }
        public int Length { get => data.Length; }
        public long LongLength { get => data.LongLength; }
        public Number(long size)
        {
            if (!IsNumber(size)) { throw new ArgumentException("The size must be a number which is 2 to the power of a natural number."); }
            data = new double[size];
        }
        public Number(params double[] args)
        {
            if (!IsNumber(args.LongLength)) { throw new ArgumentException("The size must be a number which is 2 to the power of a natural number."); }
            data = args;
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
            double[] doubles = Union.Where((double d) => { return true; }).ToArray();
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
}
