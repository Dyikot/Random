#include "Random.h"

Random::Random()
{
    m_engine.seed(m_device());
}

Random& Random::Current()
{
    static Random instance;
    return instance;
}

int Random::NextInt(int min, int max)
{
    std::uniform_int_distribution<int> range(min, max);
    return range(m_engine);
}
