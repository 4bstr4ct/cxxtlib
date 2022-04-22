



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
	std::cout << "Sum of [" << values[0];
	for (unsigned int index = 1; index < values.size(); index++)
		std::cout << ' ' << values[index];

	std::cout << "] is " << sum << ".\n";
	return 0;
}

#define EMPTY

		#define INTERNAL_TYPE_OF(TTypes, Type, FType) \
		template<TTypes> \
		struct TypeOf<Type> \
		{ \
		public: \
			static CXXTLIB_FORMAT_CONSTEXPR const FormatArgumentType value = FType; \
		}

		#define TEST(Types) template<Types> struct T{};
		TEST(int, char, (std::vector<float, CustoimAllocator>));

		INTERNAL_TYPE_OF(EMPTY, bool, FormatArgumentType::Bool);
		INTERNAL_TYPE_OF(EMPTY, char, FormatArgumentType::Char);
		INTERNAL_TYPE_OF(EMPTY, details::int8, FormatArgumentType::Int8);
		INTERNAL_TYPE_OF(EMPTY, details::uint8, FormatArgumentType::UInt8);
		INTERNAL_TYPE_OF(EMPTY, details::int16, FormatArgumentType::Int16);
		INTERNAL_TYPE_OF(EMPTY, details::uint16, FormatArgumentType::UInt16);
		INTERNAL_TYPE_OF(EMPTY, details::int32, FormatArgumentType::Int32);
		INTERNAL_TYPE_OF(EMPTY, details::uint32, FormatArgumentType::UInt32);
		INTERNAL_TYPE_OF(EMPTY, details::int64, FormatArgumentType::Int64);
		INTERNAL_TYPE_OF(EMPTY, details::uint64, FormatArgumentType::UInt64);
		INTERNAL_TYPE_OF(EMPTY, float, FormatArgumentType::Float);
		INTERNAL_TYPE_OF(EMPTY, double, FormatArgumentType::Double);
		INTERNAL_TYPE_OF(EMPTY, details::ldouble, FormatArgumentType::LDouble);
		INTERNAL_TYPE_OF(typename Type, Type*, FormatArgumentType::Pointer);
		INTERNAL_TYPE_OF(typename Type, const Type*, FormatArgumentType::Pointer);
		INTERNAL_TYPE_OF(EMPTY, details::null, FormatArgumentType::Pointer);
		INTERNAL_TYPE_OF(EMPTY, const char*, FormatArgumentType::CString);
		INTERNAL_TYPE_OF(EMPTY, const char[], FormatArgumentType::CString);
		INTERNAL_TYPE_OF(typename details::uint32 tSize, const char[tSize], FormatArgumentType::CString);
