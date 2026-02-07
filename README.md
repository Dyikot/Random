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
    // Create with random seed
    Random random;

    // Generate random numbers
    int i1 = random.Next(50);
    int i2 = random.Next(1, 100);
    
    float f1 = random.Next(0.0f, 1.0f);

    double d1 = random.Next();
    double d2 = random.Next(1e3);    

    // Fill a vector with random numbers
    std::vector<int> vec(10);
    random.Fill(vec, -10, 10);

    // Shuffle a container
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    random.Shuffle(numbers);

    // Get random items from choises range
    std::array<std::string, 4> choices = { "Anna", "Jane", "Felix", "Max" };
    std::string name = random.GetItem(choices);
    std::array names = random.GetItems<2>(choices);
    std::vector names = random.GetItems(choices, 2);

    // Get random items and add them to destination range
    std::vector<std::string> destination(4);
    random.GetItems(choices, destination);

    // Generate a vector<T> with a random numbers
    std::vector v = random.RandomVector<int>(-10, 10, 100);
}
```
