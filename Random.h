#pragma once

#include <random>
#include <ranges>
#include <concepts>
#include <mutex>
#include <type_traits>


template<typename TRange>
concept ArithmeticRange = std::ranges::range<TRange> &&
						  std::is_arithmetic_v<std::ranges::range_value_t<TRange>>;

class Random
{
protected:	
	static inline std::default_random_engine _engine;
	std::random_device _device;
public:
	Random() noexcept
	{
		_engine.seed(_device());
	}

	Random(unsigned int seed) noexcept
	{
		_engine.seed(seed);
	}

	/// <summary>
	/// Generate a random unsigned int number in a range [0, max]
	/// </summary>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random unsigned int number in a range [0, max]</returns>
	unsigned int Next(unsigned int max) noexcept
	{
		return std::uniform_int_distribution<>(0, max)(_engine);
	}

	/// <summary>
	/// Generate a random int number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random number in a range [min, max]</returns>
	int NextInt(int min, int max) noexcept
	{
		return std::uniform_int_distribution<>(min, max)(_engine);
	}

	/// <summary>
	/// Generate a random real number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random real number in a range [min, max]</returns>
	double NextDouble(double min, double max) noexcept
	{
		return std::uniform_real_distribution<>(min, max)(_engine);
	}

	/// <summary>
	/// Generate a random real number in a range [0, 1]
	/// </summary>
	/// <returns>a random real number in a range [0, 1]</returns>
	double NextDouble() noexcept
	{
		NextDouble(0.0, 1.0);
	}

	/// <summary>
	/// Fill a numeric range with random int numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	void Fill(ArithmeticRange auto&& range, int min, int max) noexcept
	{
		for(auto& item : range)
		{
			item = std::uniform_int_distribution<>(min, max)(_engine);
		}
	}

	/// <summary>
	/// Fill a numeric range with random double numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	void Fill(ArithmeticRange auto&& range, double min, double max) noexcept
	{
		for(auto& item : range)
		{
			item = std::uniform_real_distribution<>(min, max)(_engine);
		}
	}

	/// <summary>
	/// Fill a numeric range with random double numbers in a range [0, 1]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	void Fill(ArithmeticRange auto&& range) noexcept
	{
		for(auto& item : range)
		{
			item = std::uniform_real_distribution<>(0, 1)(_engine);
		}
	}

	/// <summary>
	/// Reorders the elements in the given range such
	/// that each possible permutation of those elements has equal probability of appearance.
	/// </summary>
	/// <param name="range"> - 	the range of elements to shuffle randomly</param>
	void Shuffle(std::ranges::random_access_range auto&& range) noexcept
	{
		std::ranges::shuffle(std::forward<decltype(range)>(range), _engine);
	}
};

class SharedRandom: public Random
{
protected:
	static inline std::mutex _mutex;
public:
	SharedRandom() noexcept:
		Random()
	{}

	SharedRandom(unsigned int seed) noexcept:
		Random(seed)
	{}

	/// <summary>
	/// Generate a random uint32 number in a range [0, max]
	/// </summary>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random uint32 number in a range [0, max]</returns>
	unsigned int Next(unsigned int max) noexcept
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return Random::Next(max);
	}

	/// <summary>
	/// Generate a random int number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random number in a range [min, max]</returns>
	int NextInt(int min, int max) noexcept
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return Random::NextInt(min, max);
	}

	/// <summary>
	/// Generate a random real number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random real number in a range [min, max]</returns>
	double NextDouble(double min, double max) noexcept
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return Random::NextDouble(min, max);
	}

	/// <summary>
	/// Generate a random real number in a range [0, 1]
	/// </summary>
	/// <returns>a random real number in a range [0, 1]</returns>
	double NextDouble() noexcept
	{
		Random::NextDouble(0.0, 1.0);
	}

	/// <summary>
	/// Fill a numeric range with random int numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	void Fill(ArithmeticRange auto&& range, int min, int max) noexcept
	{
		std::lock_guard<std::mutex> lock(_mutex);
		Random::Fill(std::forward<decltype(range)>(range), min, max);
	}

	/// <summary>
	/// Fill a numeric range with random double numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	void Fill(ArithmeticRange auto&& range, double min, double max) noexcept
	{
		std::lock_guard<std::mutex> lock(_mutex);
		Random::Fill(std::forward<decltype(range)>(range), min, max);
	}

	/// <summary>
	/// Fill a numeric range with random double numbers in a range [0, 1]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	void Fill(ArithmeticRange auto&& range) noexcept
	{
		std::lock_guard<std::mutex> lock(_mutex);
		Random::Fill(std::forward<decltype(range)>(range));
	}

	/// <summary>
	/// Reorders the elements in the given range such
	/// that each possible permutation of those elements has equal probability of appearance.
	/// </summary>
	/// <param name="range"> - 	the range of elements to shuffle randomly</param>
	void Shuffle(std::ranges::random_access_range auto&& range) noexcept
	{
		std::lock_guard<std::mutex> lock(_mutex);
		Random::Shuffle(std::forward<decltype(range)>(range));
	}
};