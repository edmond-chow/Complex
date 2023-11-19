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
	if (!is_factor(Union.size) || !is_factor(Value.size))
	{
		throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
	}
	else if (Union.size != Value.size)
	{
		std::size_t NewSize = std::max(Union.size, Value.size);
		Factor NewUnion = Union;
		NewUnion.extend(NewSize);
		Factor NewValue = Value;
		NewValue.extend(NewSize);
		return NewUnion * NewValue;
	}
	else if (Union.size == 1) { return Factor{ Union[0] * Value[0] }; }
	return Factor::merge(
		Union.left() * Value.left() - ~Value.right() * Union.right(),
		Value.right() * Union.left() + Union.right() * ~Value.left()
	);
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
	if (!is_factor(Union.size) || !is_factor(Value.size))
	{
		throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
	}
	else if (Union.size != Value.size)
	{
		std::size_t NewSize = std::max(Union.size, Value.size);
		Factor NewUnion = Union;
		NewUnion.extend(NewSize);
		Factor NewValue = Value;
		NewValue.extend(NewSize);
		return number_dot(NewUnion, NewValue);
	}
	double Result{ 0 };
	for (std::size_t i = 0; i < Union.size; ++i)
	{
		Result += Union[i] * Value[i];
	}
	return Result;
};
constexpr Factor number_outer(const Factor& Union, const Factor& Value)
{
	Factor VecUnion = Union;
	VecUnion[0] = 0;
	Factor VecValue = Value;
	VecValue[0] = 0;
	return number_cross(VecUnion, VecValue) + Union[0] * VecValue - Value[0] * VecUnion;
};
constexpr Factor number_even(const Factor& Union, const Factor& Value)
{
	Factor VecUnion = Union;
	VecUnion[0] = 0;
	Factor VecValue = Value;
	VecValue[0] = 0;
	return Factor{ Union[0] * Value[0] - number_dot(VecUnion, VecValue) } + Union[0] * VecValue + Value[0] * VecUnion;
};
constexpr Factor number_cross(const Factor& Union, const Factor& Value)
{
	if (!is_factor(Union.size) || !is_factor(Value.size))
	{
		throw std::invalid_argument("The size must be a number which is 2 to the power of a natural number.");
	}
	else if (Union.size != Value.size)
	{
		std::size_t NewSize = std::max(Union.size, Value.size);
		Factor NewUnion = Union;
		NewUnion.extend(NewSize);
		Factor NewValue = Value;
		NewValue.extend(NewSize);
		return number_cross(NewUnion, NewValue);
	}
	else if (Union[0] != 0 || Value[0] != 0)
	{
		Factor VecUnion = Union;
		VecUnion[0] = 0;
		Factor VecValue = Value;
		VecValue[0] = 0;
		return number_cross(VecUnion, VecValue);
	}
	Factor Result = Union * Value;
	Result[0] = 0;
	return Result;
};
