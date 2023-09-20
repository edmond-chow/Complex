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
template <std::size_t N> requires (is_number(N))
struct Number
{
private:
	double data[N];
public:
	constexpr double& operator [](std::size_t i) & { return data[i]; };
	constexpr const double& operator [](std::size_t i) const& { return data[i]; };
private:
	template <typename... Args> requires (sizeof...(Args) == N)
	constexpr void store_impl(Args... args) const noexcept {};
	template <typename T, std::size_t... I> requires (std::tuple_size_v<T> == sizeof...(I))
	constexpr void store_impl(T&& tuple, std::integer_sequence<std::size_t, I...>) const noexcept
	{
		store_impl((*std::get<I>(tuple) = data[I])...);
	};
	template <std::size_t... I> requires (N == sizeof...(I))
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
	template <std::size_t... I> requires (sizeof...(I) <= N)
	constexpr Number<sizeof...(I)> get(std::integer_sequence<std::size_t, I...>) const
	{
		return Number<sizeof...(I)>{ data[I]... };
	};
	template <std::size_t... I> requires (N == sizeof...(I))
	static constexpr Number<2 * N> merge_impl(const Number<N>& Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<2 * N>{ Union[I]..., Value[I]... };
	};
	template <std::size_t... I> requires (N == sizeof...(I))
	static constexpr Number<N> mul_impl(double Union, const Number<N>& Value, std::integer_sequence<std::size_t, I...>) noexcept
	{
		return Number<N>{ (Union * Value[I])... };
	};
public:
	template <typename... Args>
	constexpr Number(Args... args) : data{ static_cast<double>(args)... } {};
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
	constexpr Number<H> left() const noexcept requires (H > 0)
	{
		return get(make_range_sequence<0, H>{});
	};
	template <std::size_t H = N / 2>
	constexpr Number<H> right() const noexcept requires (H > 0)
	{
		return get(make_range_sequence<H, N>{});
	};
	static constexpr Number<2 * N> merge(const Number<N>& Union, const Number<N>& Value) noexcept
	{
		return merge_impl(Union, Value, std::make_index_sequence<N>{});
	};
	static constexpr Number<N> mul(double Union, const Number<N>& Value) noexcept
	{
		return mul_impl(Union, Value, std::make_index_sequence<N>{});
	};
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
	if constexpr (N == 1) { return Number<1>{ Union[0] * Value[0] }; }
	else
	{
		return Number<N / 2>::merge(
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
