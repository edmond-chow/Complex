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
	constexpr Factor(const double* data, std::size_t size)
		: data{ new double[size] {} }, size{ size }
	{
		if (!is_factor(size))
		{
			delete[] this->data;
			throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
		}
		std::copy(data, data + size, this->data);
	};
	constexpr Factor(const std::initializer_list<double>& init)
		: data{ new double[init.size()] {} }, size{ init.size() }
	{
		if (!is_factor(init.size()))
		{
			delete[] data;
			throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
		}
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
	static Factor merge(const Factor& Left, const Factor& Right)
	{
		std::size_t Size = Left.size + Right.size;
		double* Temp = new double[Size] {};
		Factor Output{ Temp, Size };
		delete[] Temp;
		std::copy(Right.data, Right.data + Right.size, std::copy(Left.data, Left.data + Left.size, Output.data));
		return Output;
	};
	constexpr Factor left() const
	{
		if (size == 1) { return *this; }
		double* Temp = new double[size >> 1] {};
		Factor Output{ Temp, size >> 1 };
		delete[] Temp;
		std::copy(data, data + (size >> 1), Output.data);
		return Output;
	};
	constexpr Factor right() const
	{
		if (size == 1) { return *this; }
		double* Temp = new double[size >> 1] {};
		Factor Output{ Temp, size >> 1 };
		delete[] Temp;
		std::copy(data + (size >> 1), data + size, Output.data);
		return Output;
	};
};
constexpr Factor operator -(const Factor& Value)
{
	double* Temp = new double[Value.get_size()] {};
	std::transform(Value.get_data(), Value.get_data() + Value.get_size(), Temp, [](double V) -> double { return -V; });
	Factor Output{ Temp, Value.get_size()};
	delete[] Temp;
	return Output;
};
constexpr Factor operator ~(const Factor& Value)
{
	Factor ret = -Value;
	ret[0] = -ret[0];
	return ret;
};
constexpr Factor operator +(const Factor& Union, const Factor& Value)
{
	std::size_t SizeMid = Union.get_size();
	std::size_t SizeLast = Value.get_size();
	if (SizeMid > SizeLast) { return Value + Union; }
	double* Temp = new double[SizeLast] {};
	for (std::size_t i = 0; i < SizeMid && SizeMid <= SizeLast; ++i) { Temp[i] = Union[i] + Value[i]; }
	std::copy(Value.get_data() + SizeMid, Value.get_data() + SizeLast, Temp + SizeMid);
	Factor Output{ Temp, SizeLast };
	delete[] Temp;
	return Output;
};
constexpr Factor operator -(const Factor& Union, const Factor& Value) { return Union + (-Value); };
constexpr Factor operator *(const Factor& Union, const Factor& Value)
{
	std::size_t SizeMid = Union.get_size();
	std::size_t SizeLast = Value.get_size();
	if (SizeMid > SizeLast) { return Value * Union; }
	if (SizeMid < SizeLast)
	{
		double* Temp = new double[SizeLast] {};
		std::copy(Union.get_data(), Union.get_data() + Union.get_size(), Temp);
		Factor Output{ Temp, SizeLast };
		delete[] Temp;
		return Output * Value;
	}
	if (Union.get_size() == 1) { return Factor{ Union[0] * Value[0] }; }
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
	double* Temp = new double[Value.get_size()] {};
	std::transform(Value.get_data(), Value.get_data() + Value.get_size(), Temp, [Union](double V) -> double { return Union * V; });
	Factor Output{ Temp, Value.get_size() };
	delete[] Temp;
	return Output;
};
constexpr Factor operator *(const Factor& Union, double Value) { return Value * Union; };
constexpr Factor operator /(const Factor& Union, double Value) { return Union * (1 / Value); };
