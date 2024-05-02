#include "Random.h"

Random::Random()
{
    _engine.seed(_device());
}

Random& Random::Current()
{
    static Random instance;
    return instance;
}

int Random::NextInt(int min, int max)
{
    std::uniform_int_distribution<int> range(min, max);
    return range(_engine);
}
