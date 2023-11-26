#include <algorithm>
#include <stdexcept>
template <std::size_t S, std::size_t E, std::size_t... I> requires (S <= E)
struct make_range_sequence : public make_range_sequence<S, E - 1, E - 1, I...> {};
template <std::size_t S, std::size_t... I>
struct make_range_sequence<S, S, I...> : public std::index_sequence<I...> {};
consteval bool is_number(std::size_t n) noexcept
{
	if (n == 1) { return true; }
	else if (n == 0 || (n >> 1 << 1 != n)) { return false; }
	return is_number(n >> 1);
};
template <std::size_t N>
struct Number
{
private:
	double data[N];
public:
	constexpr double& operator [](std::size_t i) & noexcept { return data[i]; };
	constexpr const double& operator [](std::size_t i) const& noexcept { return data[i]; };
private:
	template <typename... Args> requires (sizeof...(Args) == N)
	constexpr void store_impl(Args... args) const noexcept {};
	template <typename T, std::size_t... I>
	constexpr void store_impl(T&& tuple, std::integer_sequence<std::size_t, I...>) const noexcept
	{
		store_impl((*std::get<I>(tuple) = data[I])...);
	};
	template <std::size_t... I>
	static constexpr bool equal_impl(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return ((Union[I] == Value[I]) && ...);
	};
	template <std::size_t... I> requires (N == sizeof...(I))
	static constexpr Number<N> add_impl(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ (Union[I] + Value[I])... };
	};
	template <std::size_t... I> requires (N == sizeof...(I))
	static constexpr Number<N> neg_impl(const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ -Value[I]... };
	};
	template <std::size_t... I> requires (N == sizeof...(I) + 1)
	static constexpr Number<N> conjg_impl(const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ Value[0], -Value[I]... };
	};
	template <std::size_t... I>
	constexpr Number<sizeof...(I)> get(std::integer_sequence<std::size_t, I...>) const noexcept
	{
		return Number<sizeof...(I)>{ data[I]... };
	};
	template <std::size_t... I> requires (N == sizeof...(I))
	static constexpr Number<N> mul_impl(double Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ (Union * Value[I])... };
	};
public:
	template <typename... Args>
	constexpr Number(Args... args) noexcept : data{ static_cast<double>(args)... } {};
	template <typename... Args> requires (sizeof...(Args) == N)
	constexpr void store(Args&... args) const noexcept
	{
		store_impl(std::forward_as_tuple(&args...), std::index_sequence_for<Args...>{});
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
		return conjg_impl(Value, make_range_sequence<1, N>{});
	};
	template <std::size_t H = N / 2>
	constexpr Number<H> left() const noexcept requires (0 < H && H <= N)
	{
		return get(make_range_sequence<0, H>{});
	};
	template <std::size_t H = N / 2>
	constexpr Number<H> right() const noexcept requires (0 <= H && H < N)
	{
		return get(make_range_sequence<H, N>{});
	};
	static constexpr Number<N> mul(double Union, const Number<N>& Value) noexcept
	{
		return mul_impl(Union, Value, std::make_index_sequence<N>{});
	};
};
template <std::size_t N, std::size_t... U, std::size_t... V>
static constexpr Number<sizeof...(U) + sizeof...(V)> merge(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, U...>, std::integer_sequence<std::size_t, V...>) noexcept
{
	return Number<sizeof...(U) + sizeof...(V)>{ Union[U]..., Value[V]... };
};
template <std::size_t U, std::size_t V>
static constexpr Number<U + V> merge(const Number<U>& Union, const Number<V>& Value) noexcept
{
	return merge(Union, Value, std::make_index_sequence<U>{}, std::make_index_sequence<V>{});
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
constexpr Number<N> operator *(const Number<N>& Union, const Number<N>& Value) noexcept requires (is_number(N))
{
	if constexpr (N == 1) { return Number<1>{ Union[0] * Value[0] }; }
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
constexpr double vector_dot(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept requires (is_number(N + 1))
{
	return ((Union[I] * Value[I]) + ...);
};
template <std::size_t N>
constexpr double vector_dot(const Number<N>& Union, const Number<N>& Value) noexcept requires (is_number(N + 1))
{
	return vector_dot(Union, Value, std::make_index_sequence<N>{});
};
template <std::size_t N, std::size_t... I>
constexpr Number<N> vector_cross(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept requires (is_number(N + 1))
{
	Number<N + 1> Temp = Number<N + 1>{ 0, Union[I]... } * Number<N + 1>{ 0, Value[I]... };
	return Number<N>{ Temp[I + 1]... };
};
template <std::size_t N>
constexpr Number<N> vector_cross(const Number<N>& Union, const Number<N>& Value) noexcept requires (is_number(N + 1))
{
	return vector_cross(Union, Value, std::make_index_sequence<N>{});
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
	constexpr const double* get_data() const { return data; };
	constexpr std::size_t get_size() const { return size; };
	constexpr double& operator [](std::int64_t i) & noexcept { return data[i % size]; };
	constexpr const double& operator [](std::int64_t i) const& noexcept { return data[i % size]; };
	constexpr Factor(std::size_t size)
		: data{ nullptr }, size{ size }
	{
		data = new double[size] {};
	};
	constexpr Factor(const double* data, std::size_t size)
		: data{ nullptr }, size{ size }
	{
		this->data = new double[size] {};
		std::copy(data, data + size, this->data);
	};
	constexpr Factor(const std::initializer_list<double>& init)
		: data{ nullptr }, size{ init.size() }
	{
		data = new double[size] {};
		std::copy(init.begin(), init.end(), data);
	};
	constexpr Factor(const Factor& Value)
		: data(new double[Value.size] {}), size(Value.size)
	{
		std::copy(Value.data, Value.data + Value.size, data);
	};
	constexpr Factor(Factor&& Value) noexcept
		: data(Value.data), size(Value.size)
	{
		Value.data = nullptr;
		Value.size = 0;
	};
	constexpr Factor& operator =(const Factor& Value)&
	{
		if (this == &Value) { return *this; }
		delete[] data;
		data = new double[Value.size] {};
		size = Value.size;
		std::copy(Value.data, Value.data + Value.size, data);
		return *this;
	};
	constexpr Factor& operator =(Factor&& Value) & noexcept
	{
		data = Value.data;
		size = Value.size;
		Value.data = nullptr;
		Value.size = 0;
		return *this;
	};
	constexpr ~Factor() noexcept { delete[] data; };
	constexpr Factor& extend(std::size_t size)&
	{
		if (size > this->size)
		{
			double* new_data = new double[size] {};
			std::copy(data, data + this->size, new_data);
			delete[] data;
			data = new_data;
			this->size = size;
		};
		return *this;
	};
	static Factor merge(const Factor& Left, const Factor& Right)
	{
		Factor Result(Left.size + Right.size);
		std::copy(Right.data, Right.data + Right.size, std::copy(Left.data, Left.data + Left.size, Result.data));
		return Result;
	};
	constexpr Factor left(std::size_t count) const
	{
		if (0 >= count || count > size) { throw std::out_of_range("The count is out of range."); }
		Factor Result(count);
		std::copy(data, data + count, Result.data);
		return Result;
	};
	constexpr Factor right(std::size_t count) const
	{
		if (0 > count || count >= size) { throw std::out_of_range("The count is out of range."); }
		Factor Result(size - count);
		std::copy(data + count, data + size, Result.data);
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
	template <bool Shift>
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
template <bool Shift>
constexpr bool Check(Factor& Union, Factor& Value)
{
	std::size_t Offset = Shift ? 1 : 0;
	if (!is_factor(Union.size + Offset) || !is_factor(Value.size + Offset))
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
	Factor Result(Value.size + 1);
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
	if (Check<false>(NumUnion, NumValue)) { return Factor{ GetScalar(NumUnion) * GetScalar(NumValue) }; }
	Factor MergeLeft = NumUnion.left() * NumValue.left() - ~NumValue.right() * NumUnion.right();
	Factor MergeRight = NumValue.right() * NumUnion.left() + NumUnion.right() * ~NumValue.left();
	return Factor::merge(MergeLeft, MergeRight);
};
constexpr Factor operator *(double Union, const Factor& Value)
{
	Factor Result{ Value.data, Value.size };
	for (double* ite = Value.data; ite != Value.data + Value.size; ++ite) { *ite *= Union; }
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
	Check<false>(NumUnion, NumValue);
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
	Check<true>(VecUnion, VecValue);
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
	Check<true>(VecUnion, VecValue);
	return Factor{ ScaUnion * ScaValue - Dot(VecUnion, VecValue) } + ScaUnion * VecValue + ScaValue * VecUnion;
};
constexpr Factor number_cross(const Factor& Union, const Factor& Value)
{
	Factor NumUnion = Union;
	Factor NumValue = Value;
	Check<false>(NumUnion, NumValue);
	AsVector(NumUnion);
	AsVector(NumValue);
	Factor Result = NumUnion * NumValue;
	AsVector(Result);
	return Result;
};
