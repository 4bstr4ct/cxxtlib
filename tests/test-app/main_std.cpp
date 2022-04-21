



#include <iostream>
#include <fstream>
#include <vector>

#define std ::std


int main(void)
{
	// Opening the data file.
	constexpr const unsigned int length = 9u;
	constexpr const char path[length] = "data.txt";
	std::ifstream stream = std::ifstream(path);

	// If file fails.
	if (stream.fail())
	{
		std::cout << "Failed to open file " << path << "!\nExiting program with error code " << -1 << "...\n";
		return -1;
	}
	else
	{
		std::cout << "Successfully opened file " << path << "!\n";
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

	// Printing sum of the values.
	std::cout << "Sum of [";
	for (unsigned int index = 0; index < values.size(); index++)
	{
		std::cout << values[index];

		if (index + 1u < values.size())
			std::cout << ' ';
	}

	std::cout << "] is " << sum << ".\n";
	return 0;
}
