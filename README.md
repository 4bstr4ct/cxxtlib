## Module cformat

| License | Version | Releases |
|:--------|:--------|:---------|
| [![License](https://img.shields.io/badge/license-GNU_3-blue.svg)](#) | [![Version](https://img.shields.io/badge/version-0.2.0-brightgreen.svg)](#) | [![Releases](https://img.shields.io/badge/releases-Latest-brightgreen.svg)](#) | |


| Compilers | Standards | Platforms |
|:----------|:----------|:----------|
| [![](https://img.shields.io/badge/compiler-MSVC-brightgreen)](#)| [![](https://img.shields.io/badge/c%2B%2B-11-brightgreen.svg)](#) | [![](https://img.shields.io/badge/c%2B%2B-Windows-brightgreen.svg)](#) |
| [![](https://img.shields.io/badge/compiler-Clang%2FLLVM-brightgreen)](#)| [![](https://img.shields.io/badge/c%2B%2B-14-brightgreen.svg)](#) | [![](https://img.shields.io/badge/c%2B%2B-Linux-brightgreen.svg)](#) |
| [![](https://img.shields.io/badge/compiler-GCC-brightgreen)](#) | [![](https://img.shields.io/badge/c%2B%2B-17-yellow.svg)](#) | [![](https://img.shields.io/badge/c%2B%2B-Macos-red.svg)](#) |


## Examples

Printing to c-like streams (such as stdout):
```c++
#include <cformat/format.hpp>

int main(int argc, char** argv)
{
	cformat::cprint(stdout, "Hello, World!\n");
	return 0;
}
```

Printing to c++-like streams (such as cout):
```c++
#include <cformat/format.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	cformat::print(std::cout, "Hello, World!\n");
	return 0;
}
```

Formatting into dynamic buffer:
```c++
#include <cformat/format.hpp>

int main(int argc, char** argv)
{
	char* buffer = cformat::format("Hello, {}!\n", "World");
	delete[] buffer;
	return 0;
}
```

Formatting into static buffer:
```c++
#include <cformat/format.hpp>

int main(int argc, char** argv)
{
	char buffer[100] = { };
	unsigned int length = cformat::formatTo<100>(buffer, "Hello, {}!\n", "World");
	return 0;
}
```

Formatting into a provided container type (f.e. std::string):
```c++
#include <cformat/format.hpp>

#include <string>

int main(int argc, char** argv)
{
	std::string formatted = cformat::sformat<std::string>("Hello, {}!\n", "World");
	return 0;
}
```

Printing a STL container:
```c++
#include <cformat/format.hpp>

#include <vector>

int main(int argc, char** argv)
{
	std::vector<int> container = { 1, 2, 3, 4, 5 };
	cformat::cprint(stdout, "Container values: {}!\n", container); // or you can use cformat::print(...)!
	return 0;
}
```

Define custom formatter:
```c++
#include <cformat/format.hpp>

// The custom type
struct Point
{
public:
	float x, y, z;
};

// Custom format of utility (critical!)
// First macro argument are template typenames that are needed for the Point type (in this case NONE),
// second argument is the type (Point).
struct_CUSTOM_FORMAT_OF(NONE, Point);

// Custom formatter (critical!)
// First macro argument are template typenames that are needed for the Point type (in this case NONE),
// second is the type (Point) and the last two are methods parse(...) and format(...)
struct_CUSTOM_FORMATTER(NONE, Point,
	void parse(Context& pContext)
	{
		// Ignoring parsing the specifiers for this type.
		PARSE_IGNORE(pContext);
	},
	void format(Context& pContext COMMA const Point& pValue)
	{
		pContext.append('[');
		Formatter<Point::Type>::template format<Context>(pContext COMMA pValue.x); // Using existing formatter for float type for the inner value x.
		pContext.append(' ');
		Formatter<Point::Type>::template format<Context>(pContext COMMA pValue.y); // Using existing formatter for float type for the inner value y.
		pContext.append(' ');
		Formatter<Point::Type>::template format<Context>(pContext COMMA pValue.z); // Using existing formatter for float type for the inner value z.
		pContext.append(']'); // Formatter for type char can also be used instead of a plain pContext.append(...)!
	}
);

int main(int argc, char** argv)
{
	Point point{ 4, 5, 6 };
	cformat::cprint(stdout, "Point is {}!\n", point);
	return 0;
}
```