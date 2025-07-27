## About
**"Random"** is a modern, header-only C++20 library that simplifies random number generation with a clean, intuitive interface. It leverages C++20 features like concepts, ranges, and uniform distribution to provide type-safe, efficient random operations.

## Key Features
- **C++20 Concepts**: Type-safe range operations with `ArithmeticRange` concept
- **Range Support**: Fill and shuffle standard containers (`std::vector`, `std::array`, etc.)
- **Thread Safety**: Thread-local storage provides automatic thread isolation (no locking overhead)
- **Uniform Distributions**: 
  - Integer distributions (`Next`, `NextInt`)
  - Floating point distributions (`NextDouble`)
- **Modern API**: Intuitive method names and parameter ordering
- **Header-only**: No compilation needed, just include and use
## Example
```
#include "Random.h"

int main() {
    Random random;  // Create with random seed
    
    // Generate random integers
    int i1 = random.Next(42);           // 0-42
    int i2 = random.NextInt(1, 100);    // 1-100
    
    // Generate random floating points
    double d1 = random.NextDouble();        // 0.0-1.0
    double d2 = random.NextDouble(1.5, 3.5); // 1.5-3.5
    
    // Fill a vector with random numbers
    std::vector<int> vec(10);
    random.Fill(vec, -10, 10);  // Fill with -10 to 10
    
    // Shuffle a container
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    random.Shuffle(numbers);
}
```
