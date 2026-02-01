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
public:
	/// <summary>
	/// Constructs a Random instance with a seed generated from std::random_device
	/// </summary>
	Random() noexcept
	{
		GetEngine().seed(std::random_device()());
	}

	/// <summary>
	/// Constructs a Random instance with a specified seed value
	/// </summary>
	/// <param name="seed"> - the seed value for the random number generator</param>
	explicit Random(uint32_t seed) noexcept
	{
		GetEngine().seed(seed);
	}

	/// <summary>
	/// Generate a random number in a range [min, max]
	/// </summary>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random number in a range [min, max]</returns>
	template<typename T>
	T Next(T min, T max) const noexcept requires std::is_arithmetic_v<T>
	{
		if constexpr (std::is_integral_v<T>)
		{
			return std::uniform_int_distribution<T>(min, max)(GetEngine());
		}
		else
		{
			return std::uniform_real_distribution<T>(min, max)(GetEngine());
		}
	}

	/// <summary>
	/// Generate a random number in a range [0, max]
	/// </summary>
	/// <param name="max"> - maximum value</param>
	/// <returns>a random number in a range [0, max]</returns>
	template<typename T>
	T Next(T max) const noexcept requires std::is_arithmetic_v<T>
	{
		return Next(T(0), max);
	}

	/// <summary>
	/// Generate a random number in a range [0, 1]
	/// </summary>
	/// <returns>a random number in a range [0, 1]</returns>
	template<typename T = double>
	T Next() const noexcept requires std::is_arithmetic_v<T>
	{
		return Next(T(0), T(1));
	}

	/// <summary>
	/// Fill a numeric range with random numbers in a range [min, max]
	/// </summary>
	/// <param name="range"> - numeric range</param>
	/// <param name="min"> - minimal value</param>
	/// <param name="max"> - maximum value</param>
	template<ArithmeticRange TRange, typename T = std::ranges::range_value_t<TRange>>
	void Fill(TRange& range, T min, T max) const noexcept
	{
		using Distribution = std::conditional_t<
			std::is_integral_v<T>,
			std::uniform_int_distribution<T>,
			std::uniform_real_distribution<T>
		>;

		auto dist = Distribution(min, max);
		auto& engine = GetEngine();
		for(auto& item : range)
		{
			item = dist(engine);
		}
	}

	/// <summary>
	/// Reorders the elements in the given range such
	/// that each possible permutation of those elements has equal probability of appearance.
	/// </summary>
	/// <param name="range"> - 	the range of elements to shuffle randomly</param>
	template<std::ranges::random_access_range TRange>
	void Shuffle(TRange&& range) const noexcept
	{
		std::ranges::shuffle(std::forward<TRange>(range), GetEngine());
	}

	/// <summary>
	/// Randomly selects an item from a range.
	/// </summary>
	/// <param name="choises"> - the range to select items from</param>
	/// <returns>A random selected item from the input range</returns>
	template<std::ranges::random_access_range TRange, typename T = std::ranges::range_value_t<TRange>>
	T GetItem(TRange&& choises) const
	{
		const size_t length = std::ranges::size(choises);
		if(length == 0)
		{
			throw std::invalid_argument("Choises range cannot be empty");
		}
		
		return choises[Next(length - 1)];
	}

	/// <summary>
	/// Randomly selects a fixed number of items from a range and returns them in an array.
	/// </summary>
	/// <param name="choises"> - the range to select items from</param>
	/// <returns>An array containing Length randomly selected items from the input range</returns>
	template<size_t Length, std::ranges::random_access_range TRange,
			 typename T = std::ranges::range_value_t<TRange>>
	std::array<T, Length> GetItems(TRange&& choises) const
	{
		const size_t length = std::ranges::size(choises);

		if(length == 0)
		{
			throw std::invalid_argument("Choises range cannot be empty");
		}

		std::array<T, Length> array;
		const size_t last = length - 1;
		auto& engine = GetEngine();
		std::uniform_int_distribution<size_t> dist(0, last);

		for(size_t i = 0; i < Length; i++)
		{
			array[i] = choises[dist(engine)];
		}

		return array;
	}

	/// <summary>
	/// Randomly selects items from a source range and fills a destination range with them. Both ranges must contain the same type of elements.
	/// </summary>
	/// <param name="choises"> - the source range to select items from</param>
	/// <param name="destination"> - the destination range to fill with selected items</param>
	template<std::ranges::random_access_range TChoisesRange, std::ranges::random_access_range TDestinationRange>
		requires std::same_as<std::ranges::range_value_t<TChoisesRange>,
							  std::ranges::range_value_t<TDestinationRange>>
	void GetItems(TChoisesRange&& choises, TDestinationRange& destination) const
	{
		const size_t choisesLength = std::ranges::size(choises);
		const size_t destinationLength = std::ranges::size(destination);

		if(choisesLength == 0)
		{
			throw std::invalid_argument("Choises range cannot be empty");
		}

		if(destinationLength == 0)
		{
			throw std::invalid_argument("Destination range cannot be empty");
		}

		const size_t last = choisesLength - 1;
		auto& engine = GetEngine();
		std::uniform_int_distribution<size_t> dist(0, last);

		for(size_t i = 0; i < destinationLength; i++)
		{
			destination[i] = choises[dist(engine)];
		}
	}
private:
	Engine& GetEngine() const noexcept
	{
		thread_local Engine engine;
		return engine;
	}
};