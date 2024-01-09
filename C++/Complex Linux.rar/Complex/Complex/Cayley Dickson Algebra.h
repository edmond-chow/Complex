#pragma once
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream>
#include <tuple>
#include <array>
#include <algorithm>
#include <stdexcept>
template <std::size_t S, std::size_t E, std::size_t... I> requires (S <= E)
struct make_range_sequence : public make_range_sequence<S, E - 1, E - 1, I...> {};
template <std::size_t S, std::size_t... I>
struct make_range_sequence<S, S, I...> : public std::index_sequence<I...> {};
inline thread_local double null_data[1]{};
consteval bool is_number(std::size_t n) noexcept
{
	if (n == 1) { return true; }
	else if (n == 0 || (n >> 1 << 1 != n)) { return false; }
	return is_number(n >> 1);
};
template <std::size_t N>
struct Number
{
public:
	static constexpr const std::size_t Half = N >> 1;
private:
	double data[N > 0 ? N : 1];
public:
	constexpr double& operator [](std::size_t i) & noexcept
	{
		if constexpr (N > 0) { return data[i % N]; }
		else { return data[0]; }
	};
	constexpr const double& operator [](std::size_t i) const& noexcept
	{
		if constexpr (N > 0) { return data[i % N]; }
		else { return data[0]; }
	};
private:
	template <std::size_t I, typename... Args>
	constexpr void store_impl(Args&... args) const noexcept {};
	template <std::size_t I = 0, typename Head, typename... Tail>
	constexpr void store_impl(Head& head, Tail&... tail) const noexcept
	{
		if constexpr (I < N)
		{
			head = data[I];
			store_impl<I + 1, Tail...>(tail...);
		}
	};
	template <std::size_t... I>
	static constexpr bool equal_impl(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return ((Union.data[I] == Value.data[I]) && ...);
	};
	template <std::size_t... I>
	static constexpr Number<N> add_impl(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ (Union.data[I] + Value.data[I])... };
	};
	template <std::size_t... I>
	static constexpr Number<N> neg_impl(const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ -Value.data[I]... };
	};
	template <std::size_t... I>
	static constexpr Number<N> conjg_impl(const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ Value.data[0], -Value.data[I]... };
	};
	template <std::size_t... I>
	constexpr Number<sizeof...(I)> get(std::integer_sequence<std::size_t, I...>) const noexcept
	{
		return Number<sizeof...(I)>{ data[I]... };
	};
	template <std::size_t... I>
	static constexpr Number<N> mul_impl(double Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ (Union * Value.data[I])... };
	};
public:
	template <typename... Args>
	constexpr Number(Args... args) noexcept : data{ static_cast<double>(args)... } {};
	template <typename... Args>
	constexpr void store(Args&... args) const noexcept
	{
		store_impl(args...);
	};
	static constexpr bool equal(const Number<N>& Union, const Number<N>& Value) noexcept
	{
		return equal_impl(Union, Value, std::make_index_sequence<N>{});
	};
	static constexpr Number<N> add(const Number<N>& Union, const Number<N>& Value) noexcept
	{
		return add_impl(Union, Value, std::make_index_sequence<N>{});
	};
	static constexpr Number<N> neg(const Number<N>& Value) noexcept
	{
		return neg_impl(Value, std::make_index_sequence<N>{});
	};
	static constexpr Number<N> conjg(const Number<N>& Value) noexcept
	{
		if constexpr (N > 0) { return conjg_impl(Value, make_range_sequence<1, N>{}); }
		return Number<N>{};
	};
	template <std::size_t Count = Half>
	constexpr Number<Count> left() const noexcept
	{
		return get(make_range_sequence<0, Count>{});
	};
	template <std::size_t Count = Half>
	constexpr Number<Count> right() const noexcept
	{
		return get(make_range_sequence<N - Count, N>{});
	};
	static constexpr Number<N> mul(double Union, const Number<N>& Value) noexcept
	{
		return mul_impl(Union, Value, std::make_index_sequence<N>{});
	};
	template <std::size_t U, std::size_t V, std::size_t... I, std::size_t... J>
	friend constexpr Number<U + V> merge_impl(const Number<U>& Union, const Number<V>& Value, std::integer_sequence<std::size_t, I...>, std::integer_sequence<std::size_t, J...>) noexcept;
	template <std::size_t S>
	friend constexpr Number<S> operator *(const Number<S>& Union, const Number<S>& Value) noexcept;
	template <std::size_t S, std::size_t... I>
	friend constexpr double vector_dot_impl(const Number<S>& Union, const Number<S>& Value, std::integer_sequence<std::size_t, I...>) noexcept;
	template <std::size_t S, std::size_t... I>
	friend constexpr Number<S> vector_cross_impl(const Number<S>& Union, const Number<S>& Value, std::integer_sequence<std::size_t, I...>) noexcept;
};
template <std::size_t U, std::size_t V, std::size_t... I, std::size_t... J>
constexpr Number<U + V> merge_impl(const Number<U>& Union, const Number<V>& Value, std::integer_sequence<std::size_t, I...>, std::integer_sequence<std::size_t, J...>) noexcept
{
	return Number<U + V>{ Union.data[I]..., Value.data[J]... };
};
template <std::size_t U, std::size_t V>
constexpr Number<U + V> merge(const Number<U>& Union, const Number<V>& Value) noexcept
{
	return merge_impl(Union, Value, std::make_index_sequence<U>{}, std::make_index_sequence<V>{});
};
template <typename... Args>
constexpr Number<sizeof...(Args)> forward_as_number(Args... args) noexcept
{
	return Number<sizeof...(Args)>{ args... };
};
template <std::size_t N>
constexpr bool operator ==(const Number<N>& Union, const Number<N>& Value) noexcept
{
	return Number<N>::equal(Union, Value);
};
template <std::size_t N>
constexpr Number<N> operator +(const Number<N>& Union, const Number<N>& Value) noexcept
{
	return Number<N>::add(Union, Value);
};
template <std::size_t N>
constexpr Number<N> operator -(const Number<N>& Value) noexcept
{
	return Number<N>::neg(Value);
};
template <std::size_t N>
constexpr Number<N> operator -(const Number<N>& Union, const Number<N>& Value) noexcept
{
	return Union + (-Value);
};
template <std::size_t N>
constexpr Number<N> operator ~(const Number<N>& Value) noexcept
{
	return Number<N>::conjg(Value);
};
template <std::size_t N>
constexpr Number<N> operator *(const Number<N>& Union, const Number<N>& Value) noexcept
{
	static_assert(is_number(N), "The size must be a number which is 2 to the power of a natural number.");
	if constexpr (N == 1) { return Number<1>{ Union.data[0] * Value.data[0] }; }
	else
	{
		return merge(
			Union.left() * Value.left() - ~Value.right() * Union.right(),
			Value.right() * Union.left() + Union.right() * ~Value.left()
		);
	}
};
template <std::size_t N>
constexpr Number<N> operator *(double Union, const Number<N>& Value) noexcept
{
	return Number<N>::mul(Union, Value);
};
template <std::size_t N>
constexpr Number<N> operator *(const Number<N>& Union, double Value) noexcept
{
	return Value * Union;
};
template <std::size_t N>
constexpr Number<N> operator /(const Number<N>& Union, double Value) noexcept
{
	return Union * (1 / Value);
};
template <std::size_t N, std::size_t... I>
constexpr double vector_dot_impl(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
{
	return ((Union.data[I] * Value.data[I]) + ...);
};
template <std::size_t N>
constexpr double vector_dot(const Number<N>& Union, const Number<N>& Value) noexcept
{
	static_assert(is_number(N + 1), "The size must be a number which is 2 to the power of a natural number.");
	return vector_dot_impl(Union, Value, std::make_index_sequence<N>{});
};
template <std::size_t N, std::size_t... I>
constexpr Number<N> vector_cross_impl(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
{
	Number<N + 1> Result = Number<N + 1>{ 0, Union.data[I]... } * Number<N + 1>{ 0, Value.data[I]... };
	return Number<N>{ Result.data[I + 1]... };
};
template <std::size_t N>
constexpr Number<N> vector_cross(const Number<N>& Union, const Number<N>& Value) noexcept
{
	static_assert(is_number(N + 1), "The size must be a number which is 2 to the power of a natural number.");
	return vector_cross_impl(Union, Value, std::make_index_sequence<N>{});
};
constexpr bool is_factor(std::size_t n) noexcept
{
	if (n == 1) { return true; }
	else if (n == 0 || (n >> 1 << 1 != n)) { return false; }
	return is_factor(n >> 1);
};
class Factor
{
private:
	double* data;
	std::size_t size;
public:
	constexpr const double* get_data() const
	{
		return this->data;
	};
	constexpr std::size_t get_size() const
	{
		return this->size;
	};
	constexpr double& operator [](std::size_t i) & noexcept
	{
		if (this->size == 0) { return null_data[0]; }
		return this->data[i % this->size];
	};
	constexpr const double& operator [](std::size_t i) const& noexcept
	{
		if (this->size == 0) { return null_data[0]; }
		return this->data[i % this->size];
	};
	constexpr Factor(std::nullptr_t data, std::size_t size) : data{ nullptr }, size{ size }
	{
		if (this->size > 0)
		{
			this->data = new double[this->size] {};
		}
	};
	constexpr Factor(const double* data, std::size_t size) : data{ nullptr }, size{ size }
	{
		if (this->size > 0)
		{
			this->data = new double[this->size] {};
			std::copy(data, data + size, this->data);
		}
	};
	constexpr Factor(const std::initializer_list<double>& list) : data{ nullptr }, size{ list.size() }
	{
		if (this->size > 0)
		{
			this->data = new double[this->size] {};
			std::copy(list.begin(), list.end(), this->data);
		}
	};
	constexpr Factor(const Factor& Value) : data{ nullptr }, size{ Value.size }
	{
		if (this->size > 0)
		{
			this->data = new double[this->size] {};
			std::copy(Value.data, Value.data + Value.size, this->data);
		}
	};
	constexpr Factor(Factor&& Value) noexcept : data{ Value.data }, size{ Value.size }
	{
		Value.data = nullptr;
		Value.size = 0;
	};
	constexpr Factor& operator =(const Factor& Value) &
	{
		if (this == &Value) { return *this; }
		delete[] this->data;
		this->data = new double[Value.size] {};
		this->size = Value.size;
		std::copy(Value.data, Value.data + Value.size, this->data);
		return *this;
	};
	constexpr Factor& operator =(Factor&& Value) & noexcept
	{
		this->data = Value.data;
		this->size = Value.size;
		Value.data = nullptr;
		Value.size = 0;
		return *this;
	};
	constexpr ~Factor() noexcept
	{
		delete[] data;
		this->data = nullptr;
		this->size = 0;
	};
	constexpr Factor& extend(std::size_t size) &
	{
		if (size > this->size)
		{
			double* data = new double[size] {};
			std::copy(this->data, this->data + this->size, data);
			delete[] this->data;
			this->data = data;
			this->size = size;
		};
		return *this;
	};
	static Factor merge(const Factor& Left, const Factor& Right)
	{
		Factor Result{ nullptr, Left.size + Right.size };
		std::copy(Right.data, Right.data + Right.size, std::copy(Left.data, Left.data + Left.size, Result.data));
		return Result;
	};
	constexpr Factor left(std::size_t count) const
	{
		if (count > size) { throw std::out_of_range("The count is out of range."); }
		Factor Result{ nullptr, count };
		std::copy(data, data + count, Result.data);
		return Result;
	};
	constexpr Factor right(std::size_t count) const
	{
		if (count > size) { throw std::out_of_range("The count is out of range."); }
		Factor Result{ nullptr, count };
		std::copy(data + size - count, data + size, Result.data);
		return Result;
	};
	constexpr Factor left() const
	{
		return left(size >> 1);
	};
	constexpr Factor right() const
	{
		return right(size >> 1);
	};
	friend constexpr bool Check(Factor& Union, Factor& Value);
	friend constexpr Factor MakeFactor(const Factor& Value);
	friend constexpr void AsVector(Factor& Value);
	friend constexpr double GetScalar(const Factor& Value);
	friend constexpr double Dot(const Factor& Union, const Factor& Value);
	friend constexpr bool operator ==(const Factor& Union, const Factor& Value);
	friend constexpr Factor operator -(const Factor& Value);
	friend constexpr Factor operator ~(const Factor& Value);
	friend constexpr Factor operator +(const Factor& Union, const Factor& Value);
	friend constexpr Factor operator -(const Factor& Union, const Factor& Value);
	friend constexpr Factor operator *(const Factor& Union, const Factor& Value);
	friend constexpr Factor operator *(double Union, const Factor& Value);
	friend constexpr Factor operator *(const Factor& Union, double Value);
	friend constexpr Factor operator /(const Factor& Union, double Value);
	friend constexpr double number_dot(const Factor& Union, const Factor& Value);
	friend constexpr Factor number_outer(const Factor& Union, const Factor& Value);
	friend constexpr Factor number_even(const Factor& Union, const Factor& Value);
	friend constexpr Factor number_cross(const Factor& Union, const Factor& Value);
};
constexpr bool Check(Factor& Union, Factor& Value)
{
	if (!is_factor(Union.size) || !is_factor(Value.size))
	{
		throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
	}
	else if (Union.size < Value.size)
	{
		Union.extend(Value.size);
	}
	else if (Value.size < Union.size)
	{
		Value.extend(Union.size);
	}
	return Union.size == 1;
};
constexpr Factor MakeFactor(const Factor& Value)
{
	Factor Result{ nullptr, Value.size + 1 };
	std::copy(Value.data, Value.data + Value.size, Result.data + 1);
	return Result;
};
constexpr void AsVector(Factor& Value)
{
	Value.data[0] = 0;
};
constexpr double GetScalar(const Factor& Value)
{
	return Value.data[0];
};
constexpr double Dot(const Factor& Union, const Factor& Value)
{
	double Result{ 0 };
	for (std::size_t i = 0; i < Union.size; ++i)
	{
		Result += Union.data[i] * Value.data[i];
	}
	return Result;
};
constexpr bool operator ==(const Factor& Union, const Factor& Value)
{
	if (Union.size != Value.size) { return false; }
	return std::equal(Union.data, Union.data + Union.size, Value.data);
};
constexpr Factor operator -(const Factor& Value)
{
	Factor Result{ Value.data, Value.size };
	const double* ite_oe = Result.data + Result.size;
	for (double* ite_o = Result.data; ite_o != ite_oe; ++ite_o) { *ite_o = -*ite_o; }
	return Result;
};
constexpr Factor operator ~(const Factor& Value)
{
	Factor Result{ Value.data, Value.size };
	const double* ite_oe = Result.data + Result.size;
	for (double* ite_o = Result.data + 1; ite_o != ite_oe; ++ite_o) { *ite_o = -*ite_o; }
	return Result;
};
constexpr Factor operator +(const Factor& Union, const Factor& Value)
{
	if (Union.size > Value.size) { return Value + Union; }
	Factor Result{ Value.data, Value.size };
	const double* ite_u = Union.data;
	const double* ite_ue = Union.data + Union.size;
	for (double* ite_o = Result.data; ite_u != ite_ue; ++ite_o, ++ite_u) { *ite_o += *ite_u; }
	return Result;
};
constexpr Factor operator -(const Factor& Union, const Factor& Value)
{
	return Union + (-Value);
};
constexpr Factor operator *(const Factor& Union, const Factor& Value)
{
	Factor NumUnion = Union;
	Factor NumValue = Value;
	if (Check(NumUnion, NumValue)) { return Factor{ GetScalar(NumUnion) * GetScalar(NumValue) }; }
	Factor MergeLeft = NumUnion.left() * NumValue.left() - ~NumValue.right() * NumUnion.right();
	Factor MergeRight = NumValue.right() * NumUnion.left() + NumUnion.right() * ~NumValue.left();
	return Factor::merge(MergeLeft, MergeRight);
};
constexpr Factor operator *(double Union, const Factor& Value)
{
	Factor Result{ Value.data, Value.size };
	const double* ite_oe = Result.data + Result.size;
	for (double* ite_o = Result.data; ite_o != ite_oe; ++ite_o) { *ite_o *= Union; }
	return Result;
};
constexpr Factor operator *(const Factor& Union, double Value)
{
	return Value * Union;
};
constexpr Factor operator /(const Factor& Union, double Value)
{
	return Union * (1 / Value);
};
constexpr double number_dot(const Factor& Union, const Factor& Value)
{
	Factor NumUnion = Union;
	Factor NumValue = Value;
	Check(NumUnion, NumValue);
	return Dot(NumUnion, NumValue);
};
constexpr Factor number_outer(const Factor& Union, const Factor& Value)
{
	double ScaUnion = GetScalar(Union);
	Factor VecUnion = Union;
	AsVector(VecUnion);
	double ScaValue = GetScalar(Value);
	Factor VecValue = Value;
	AsVector(VecValue);
	Check(VecUnion, VecValue);
	return number_cross(VecUnion, VecValue) + ScaUnion * VecValue - ScaValue * VecUnion;
};
constexpr Factor number_even(const Factor& Union, const Factor& Value)
{
	double ScaUnion = GetScalar(Union);
	Factor VecUnion = Union;
	AsVector(VecUnion);
	double ScaValue = GetScalar(Value);
	Factor VecValue = Value;
	AsVector(VecValue);
	Check(VecUnion, VecValue);
	return Factor{ ScaUnion * ScaValue - Dot(VecUnion, VecValue) } + ScaUnion * VecValue + ScaValue * VecUnion;
};
constexpr Factor number_cross(const Factor& Union, const Factor& Value)
{
	Factor NumUnion = Union;
	Factor NumValue = Value;
	Check(NumUnion, NumValue);
	AsVector(NumUnion);
	AsVector(NumValue);
	Factor Result = NumUnion * NumValue;
	AsVector(Result);
	return Result;
};
