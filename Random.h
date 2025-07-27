#pragma once

#include <random>
#include <ranges>
#include <concepts>
#include <array>

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
	template<ArithmeticRange TRange>
	void Fill(TRange&& range, int min, int max) noexcept
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
	template<ArithmeticRange TRange>
	void Fill(TRange&& range, double min, double max) noexcept
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
	template<ArithmeticRange TRange>
	void Fill(TRange&& range) noexcept
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
	template<std::ranges::random_access_range TRange>
	void Shuffle(TRange&& range) noexcept
	{
		std::ranges::shuffle(std::forward<TRange>(range), GetEngine());
	}

	/// <summary>
	/// Randomly selects a fixed number of items from a range and returns them in an array.
	/// </summary>
	/// <param name="choises"> - the range to select items from</param>
	/// <returns>An array containing Length randomly selected items from the input range</returns>
	template<size_t Length, std::ranges::random_access_range TRange,
		typename T = std::ranges::range_value_t<TRange>>
		std::array<T, Length> GetItems(TRange&& choises)
	{
		const size_t length = std::ranges::size(choises);
		std::array<T, Length> array;

		if(length == 0)
		{
			return array;
		}

		const size_t last = length - 1;
		for(size_t i = 0; i < Length; i++)
		{
			array[i] = choises[Next(last)];
		}

		return array;
	}

	/// <summary>
	/// Randomly selects items from a source range and fills a destination range with them. Both ranges must contain the same type of elements.
	/// </summary>
	/// <param name="choises"> - the source range to select items from</param>
	/// <param name="destination"> - the destination range to fill with selected items</param>
	template<std::ranges::random_access_range TChoisesRange,
		std::ranges::random_access_range TDestinationRange>
		requires std::same_as<std::ranges::range_value_t<TChoisesRange>,
	std::ranges::range_value_t<TDestinationRange>>
		void GetItems(TChoisesRange&& choises, TDestinationRange& destination)
	{
		const size_t choisesLength = std::ranges::size(choises);
		const size_t destinationLength = std::ranges::size(destination);

		if(choisesLength == 0 || destinationLength == 0)
		{
			return;
		}

		const size_t last = choisesLength - 1;

		for(size_t i = 0; i < destinationLength; i++)
		{
			destination[i] = choises[Next(last)];
		}
	}
private:
	Engine& GetEngine()
	{
		thread_local Engine engine;
		return engine;
	}
};