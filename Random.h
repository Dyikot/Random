#pragma once
#include <random>

class Random
{
private:
	Random();

	std::random_device m_device;
	std::default_random_engine m_engine;
public:
	Random(const Random&) = delete;

	static Random& Current();

	int GenerateNumber(int min, int max);

	template<typename IEnumerable>
	void FillIntEnumerable(IEnumerable& collection, int min, int max);
};

template<typename IEnumerable>
void Random::FillIntEnumerable(IEnumerable& collection, int min, int max)
{
	for(auto& item : collection)
	{
		item = GenerateNumber(min, max);
	}
}
