#pragma once
#include <random>
#include <ranges>
#include <concepts>

template<typename IEnumerable>
concept IntRange = std::ranges::range<IEnumerable> &&
				   std::convertible_to<std::ranges::range_value_t<IEnumerable>, int>;

class Random
{
private:
	Random();

	std::random_device m_device;
	std::default_random_engine m_engine;
public:
	Random(const Random&) = delete;

	static Random& Current();

	int NextInt(int min, int max);	

	template<IntRange IEnumerable>
	void FillIntEnumerable(IEnumerable& source, int min, int max);
};

template<IntRange IEnumerable>
void Random::FillIntEnumerable(IEnumerable& source, int min, int max)
{
	for(auto& item : source)
	{
		item = NextInt(min, max);
	}
}
