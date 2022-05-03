#define ENABLE_STD_FORMATTERS 1
#include <cformat/format.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

namespace fmt = ::cformat;

int main(void)
{
	// Opening the data file.
	constexpr const unsigned int length = 9u;
	constexpr const char path[length] = "data.txt";
	std::ifstream stream = std::ifstream(path);

	// If file fails.
	if (stream.fail())
	{
		fmt::cprint(stdout, "Failed to open file {}!\nExiting program with error code {}...\n", path, -1);
		return -1;
	}
	else
	{
		fmt::cprint(stdout, "Successfully opened file {}!\n", path);
	}

	// Reading data from file and setting it up.
	unsigned int count;
	stream >> count;

	std::vector<unsigned int> values = std::vector<unsigned int>(count);
	for (unsigned int index = 0, value; stream >> value; index++) values[index] = value;

	// Closing file.
	stream.close();

	// Calculating sum of values.
	unsigned int sum = 0;
	for (unsigned int index = 0; index < values.size(); index++) sum += values[index];

	std::array<unsigned int, 10> arr;
	for (unsigned int index = 0; index < arr.size(); index++)
		arr[index] = values[index];

	// Printing sum of the values.
	fmt::cprint(stdout, "Sum of {} is {}.\n{}\n", values, sum, arr);
	return 0;
}

