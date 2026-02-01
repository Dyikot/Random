## About
**"Random"** is a modern, header-only C++20 library that simplifies random number generation with a clean, intuitive interface. It leverages C++20 features like concepts, ranges, and uniform distribution to provide type-safe, efficient random operations.

## Key Features
- **C++20 Concepts**: Type-safe range operations with `ArithmeticRange` concept
- **Range Support**: Fill and shuffle standard containers (`std::vector`, `std::array`, etc.)
- **Thread Safety**: Thread-local storage provides automatic thread isolation (no locking overhead)
- **Unified Template API**: Single templated `Next` method works with any arithmetic type
- **Automatic Type Detection**: Distributions automatically adapt to integer vs floating-point types
- **Modern API**: Intuitive method names and parameter ordering
- **Header-only**: No compilation needed, just include and use

## Example
```cpp
#include "Random.h"

int main()
{
    Random random;  // Create with random seed
    Random randomWithSeed(12345u);  // Create with specific seed

    // Generate random integers
    int i1 = random.Next<int>(42);                      // 0-42
    int i2 = random.Next<int>(1, 100);                  // 1-100
    uint32_t u = random.Next<uint32_t>(0, UINT32_MAX);  // Full uint32 range

    // Generate random floating points
    double d1 = random.Next<double>();         // 0.0-1.0
    double d2 = random.Next<double>(1.5, 3.5); // 1.5-3.5
    float f1 = random.Next<float>(0.0f, 1.0f); // 0.0-1.0 as float

    // Generate random number in [0, 1] range with default type (double)
    double normalized = random.Next();

    // Fill a vector with random numbers
    std::vector<int> vec(10);
    random.Fill(vec, -10, 10);  // Fill with -10 to 10

    std::vector<float> fvec(5);
    random.Fill(fvec, 0.0f, 1.0f);  // Fill with 0.0 to 1.0 floats

    // Fill with default [0, 1] range based on container type
    std::vector<double> dvec(8);
    random.Fill(dvec);  // Fill with 0.0 to 1.0 doubles

    // Shuffle a container
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    random.Shuffle(numbers);

    std::array<std::string, 4> choices = { "Anna", "Jane", "Felix", "Max" };
    auto name = random.GetItem(choices); // Get random item from choices    
    auto names = random.GetItems<2>(choices); // Get random items from choices

    // Get random items and add them to destination range
    std::vector<std::string> destination(4);
    random.GetItems(choices, destination);
}
```
