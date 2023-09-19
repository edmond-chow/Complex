#include <algorithm>
#include <stdexcept>
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
	constexpr double& operator [](std::int64_t i) & { return data[i % size]; };
	constexpr const double& operator [](std::int64_t i) const& { return data[i % size]; };
	constexpr Factor(std::size_t size)
		: data{ nullptr }, size{ size }
	{
		if (!is_factor(size))
		{
			throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
		}
		data = new double[size] {};
	};
	constexpr Factor(const double* data, std::size_t size)
		: data{ nullptr }, size{ size }
	{
		if (!is_factor(size))
		{
			throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
		}
		this->data = new double[size] {};
		std::copy(data, data + size, this->data);
	};
	constexpr Factor(const std::initializer_list<double>& init)
		: data{ nullptr }, size{ init.size() }
	{
		if (!is_factor(init.size()))
		{
			throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
		}
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
	constexpr Factor& operator =(const Factor& Value) &
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
	constexpr Factor& extend(std::size_t size) &
	{
		if (!is_factor(size))
		{
			throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
		}
		else if (size > this->size)
		{
			double* new_data = new double[size] {};
			std::copy(data, data + this->size, new_data);
			delete[] data;
			data = new_data;
		};
		return *this;
	};
	static Factor merge(const Factor& Left, const Factor& Right)
	{
		Factor Output(Left.size + Right.size);
		std::copy(Right.data, Right.data + Right.size, std::copy(Left.data, Left.data + Left.size, Output.data));
		return Output;
	};
	constexpr Factor left() const
	{
		if (size == 1) { return *this; }
		Factor Output(size >> 1);
		std::copy(data, data + (size >> 1), Output.data);
		return Output;
	};
	constexpr Factor right() const
	{
		if (size == 1) { return *this; }
		Factor Output(size >> 1);
		std::copy(data + (size >> 1), data + size, Output.data);
		return Output;
	};
	friend constexpr Factor operator -(const Factor& Value);
	friend constexpr Factor operator ~(const Factor& Value);
	friend constexpr Factor operator +(const Factor& Union, const Factor& Value);
	friend constexpr Factor operator -(const Factor& Union, const Factor& Value);
	friend constexpr Factor operator *(const Factor& Union, const Factor& Value);
	friend constexpr Factor operator *(double Union, const Factor& Value);
	friend constexpr Factor operator *(const Factor& Union, double Value);
	friend constexpr Factor operator /(const Factor& Union, double Value);
};
constexpr Factor operator -(const Factor& Value)
{
	Factor Output{ Value.data, Value.size };
	for (double* ite = Value.data; ite != Value.data + Value.size; ++ite) { *ite = -*ite; }
	return Output;
};
constexpr Factor operator ~(const Factor& Value)
{
	Factor Output{ Value.data, Value.size };
	for (double* ite = Value.data + 1; ite != Value.data + Value.size; ++ite) { *ite = -*ite; }
	return Output;
};
constexpr Factor operator +(const Factor& Union, const Factor& Value)
{
	if (Union.size > Value.size) { return Value + Union; }
	Factor Output{ Value.data, Value.size };
	for (double* ite = Union.data, *ite_o = Output.data; ite != Union.data + Union.size; ++ite, ++ite_o) { *ite_o += *ite; }
	return Output;
};
constexpr Factor operator -(const Factor& Union, const Factor& Value)
{
	return Union + (-Value);
};
constexpr Factor operator *(const Factor& Union, const Factor& Value)
{
	if (Union.size > Value.size) { return Value * Union; }
	else if (Union.size < Value.size)
	{
		Factor NewUnion = Union;
		NewUnion.extend(Value.size);
		return NewUnion * Value;
	}
	else if (Union.size == 1) { return Factor{ Union[0] * Value[0] }; }
	else
	{
		return Factor::merge(
			Union.left() * Value.left() - ~Value.right() * Union.right(),
			Value.right() * Union.left() + Union.right() * ~Value.left()
		);
	}
};
constexpr Factor operator *(double Union, const Factor& Value)
{
	Factor Output{ Value.data, Value.size };
	for (double* ite = Value.data; ite != Value.data + Value.size; ++ite) { *ite *= Union; }
	return Output;
};
constexpr Factor operator *(const Factor& Union, double Value)
{
	return Value * Union;
};
constexpr Factor operator /(const Factor& Union, double Value)
{
	return Union * (1 / Value);
};
