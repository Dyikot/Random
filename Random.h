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
private:
	using Engine = std::mt19937;
	using IntDistribution = std::uniform_int_distribution<>;
	using RealDistribution = std::uniform_real_distribution<>;
public:
	Random() noexcept
	{
		GetEngine().seed(std::random_device()());
	}

	Random(unsigned int seed) noexcept
	{
		GetEngine().seed(seed);
	}

	/// <summary>
	/// Generate a random unsigned int number in a range [0, max]
	/// </summary>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random unsigned int number in a range [0, max]</returns>
	unsigned int Next(unsigned int max) noexcept
	{
		return IntDistribution(0, max)(GetEngine());
	}

	/// <summary>
	/// Generate a random int number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random number in a range [min, max]</returns>
	int NextInt(int min, int max) noexcept
	{
		return IntDistribution(min, max)(GetEngine());
	}

	/// <summary>
	/// Generate a random real number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random real number in a range [min, max]</returns>
	double NextDouble(double min, double max) noexcept
	{
		return RealDistribution(min, max)(GetEngine());
	}

	/// <summary>
	/// Generate a random real number in a range [0, 1]
	/// </summary>
	/// <returns>a random real number in a range [0, 1]</returns>
	double NextDouble() noexcept
	{
		return NextDouble(0.0, 1.0);
	}

	/// <summary>
	/// Fill a numeric range with random int numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	void Fill(ArithmeticRange auto&& range, int min, int max) noexcept
	{
		auto& engine = GetEngine();
		for(auto& item : range)
		{
			item = IntDistribution(min, max)(engine);
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
		auto& engine = GetEngine();
		for(auto& item : range)
		{
			item = RealDistribution(min, max)(engine);
		}
	}

	/// <summary>
	/// Fill a numeric range with random double numbers in a range [0, 1]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	void Fill(ArithmeticRange auto&& range) noexcept
	{
		auto& engine = GetEngine();
		for(auto& item : range)
		{
			item = RealDistribution(0, 1)(engine);
		}
	}

	/// <summary>
	/// Reorders the elements in the given range such
	/// that each possible permutation of those elements has equal probability of appearance.
	/// </summary>
	/// <param name="range"> - 	the range of elements to shuffle randomly</param>
	void Shuffle(std::ranges::random_access_range auto&& range) noexcept
	{
		std::ranges::shuffle(std::forward<decltype(range)>(range), GetEngine());
	}
private:
	Engine& GetEngine()
	{
		thread_local Engine engine;
		return engine;
	}
};