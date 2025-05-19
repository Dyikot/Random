## About
**"Random"** is a modern, header-only C++20 library that simplifies random number generation with a clean, intuitive interface. It leverages C++20 features like concepts, ranges, and uniform distribution to provide type-safe, efficient random operations.

The library provides two main classes:
- `Random`: Basic random number generation with range operations
- `SharedRandom`: Thread-safe version with mutex protection
## Key Features
- **C++20 Concepts**: Type-safe range operations with `ArithmeticRange` concept
- **Range Support**: Fill and shuffle standard containers (`std::vector`, `std::array`, etc.)
- **Thread Safety**: `SharedRandom` class provides thread-safe operations
- **Uniform Distributions**: 
  - Integer distributions (`Next`, `NextInt`)
  - Floating point distributions (`NextDouble`)
- **Modern API**: Intuitive method names and parameter ordering
- **Header-only**: No compilation needed, just include and use
