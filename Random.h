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
	Random() noexcept
	{
		_engine.seed(_device());
	}

	/// <summary>
	/// Generate a random int number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random number in a range [min, max]</returns>
	int NextInt(const int min, const int max) noexcept
	{
		_distribution.param(std::uniform_int_distribution<>::param_type(min, max));
		return _distribution(_engine);
	}

	
	/// <summary>
	/// Generate std::vector&lt;Numeric&gt; in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <param name="size"> - length of vector</param>
	/// <returns>a vector with random numbers in a range [min, max]</returns>
	template<Numeric Numeric>
	std::vector<Numeric> GenerateVector(const int min, const int max, const size_t size) noexcept
	{
		std::vector<Numeric> range(size);

		for(auto& item : range)
		{
			item = NextInt(min, max);
		}

		return range;
	}

	/// <summary>
	/// Fill a numeric range with random numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	template<NumericRange NumericRange>
	void FillRange(NumericRange& range, const int min, const int max) noexcept
	{
		for(auto& item : range)
		{
			item = NextInt(min, max);
		}
	}
};