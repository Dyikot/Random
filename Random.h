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
	std::uniform_int_distribution<> _intDistribution;
	std::uniform_real_distribution<> _realDistribution;
public:
	Random() noexcept
	{
		_engine.seed(_device());
	}

	Random(uint32_t seed) noexcept
	{
		_engine.seed(seed);
	}

	/// <summary>
	/// Generate a random uint32 number in a range [0, max]
	/// </summary>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random uint32 number in a range [0, max]</returns>
	uint32_t Next(uint32_t max) noexcept
	{
		_intDistribution.param(std::uniform_int_distribution<>::param_type(0, max));
		return _intDistribution(_engine);
	}

	/// <summary>
	/// Generate a random int number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random number in a range [min, max]</returns>
	int NextInt(int min, int max) noexcept
	{
		_intDistribution.param(std::uniform_int_distribution<>::param_type(min, max));
		return _intDistribution(_engine);
	}

	/// <summary>
	/// Generate a random real number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random real number in a range [min, max]</returns>
	double NextDouble(double min, double max) noexcept
	{
		_realDistribution.param(std::uniform_real_distribution<>::param_type(min, max));
		return _realDistribution(_engine);
	}

	/// <summary>
	/// Generate a random real number in a range [0, 1]
	/// </summary>
	/// <returns>a random real number in a range [0, 1]</returns>
	double NextDouble() noexcept
	{
		NextDouble(0, 1);
	}

	/// <summary>
	/// Fill a numeric range with random int numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	template<typename TRange> requires NumericRange<TRange>
	void Fill(TRange&& range, int min, int max) noexcept
	{
		for(auto& item : range)
		{
			item = NextInt(min, max);
		}
	}

	/// <summary>
	/// Fill a numeric range with random double numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	template<typename TRange> requires NumericRange<TRange>
	void Fill(TRange&& range, double min, double max) noexcept
	{
		for(auto& item : range)
		{
			item = NextDouble(min, max);
		}
	}

	/// <summary>
	/// Fill a numeric range with random double numbers in a range [0, 1]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	template<typename TRange> requires NumericRange<TRange>
	void Fill(TRange&& range) noexcept
	{
		for(auto& item : range)
		{
			item = NextDouble();
		}
	}

	/// <summary>
	/// Reorders the elements in the given range such
	/// that each possible permutation of those elements has equal probability of appearance.
	/// </summary>
	/// <param name="range"> - 	the range of elements to shuffle randomly</param>
	template<typename TRange> requires std::ranges::range<TRange>
	void Shuffle(TRange&& range) noexcept
	{
		std::ranges::shuffle(std::forward<TRange>(range), _engine);
	}
};