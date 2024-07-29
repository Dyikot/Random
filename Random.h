#pragma once

#include <random>
#include <ranges>
#include <concepts>

template<typename T>
concept Numeric = std::convertible_to<T, int>;

template<typename T>
concept NumericRange = std::ranges::range<T> && Numeric<std::ranges::range_value_t<T>>;

class Random
{
private:
	std::random_device _device;
	std::default_random_engine _engine;
	std::uniform_int_distribution<> _distribution;
public:
	Random()
	{
		_engine.seed(_device());
	}

	int NextInt(const int min, const int max)
	{
		_distribution.param(std::uniform_int<>::param_type(min, max));
		return _distribution(_engine);
	}

	template<Numeric Numeric>
	std::vector<Numeric> GenerateVector(const int min, const int max, const size_t size) const
	{
		std::vector<Numeric> range(size);

		for(auto& item : range)
		{
			item = NextInt(min, max);
		}

		return range;
	}

	template<NumericRange NumericRange>
	void FillRange(NumericRange& range, const int min, const int max)
	{
		for(auto& item : range)
		{
			item = NextInt(min, max);
		}
	}
};