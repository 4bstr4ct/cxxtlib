#define ENABLE_STD_FORMATTERS 1
#include <cxxtlib/format/format.hpp>

#include <stdio.h>
#include <iostream>
#include <initializer_list>
#include <forward_list>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <sstream>

struct Point
{
public:
	using Type = int;

public:
	Type x, y, z;
};

struct_CUSTOM_FORMAT_OF(NONE, Point);

struct_CUSTOM_FORMATTER(NONE, Point,
	void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	void format(Context& pContext COMMA const Point& pValue)
	{
		Formatter<char>::template format<Context>(pContext COMMA '[');
		Formatter<Point::Type>::template format<Context>(pContext COMMA pValue.x);
		Formatter<char>::template format<Context>(pContext COMMA ' ');
		Formatter<Point::Type>::template format<Context>(pContext COMMA pValue.y);
		Formatter<char>::template format<Context>(pContext COMMA ' ');
		Formatter<Point::Type>::template format<Context>(pContext COMMA pValue.z);
		Formatter<char>::template format<Context>(pContext COMMA ']');
	}
);

#include <chrono>
#include <functional>

class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
	std::function<void(long double)> function;

public:
	Timer(std::function<void(long double)> function)
		: startTimePoint(std::chrono::high_resolution_clock::now()), function(function) { }

	~Timer()
	{
		stop();
	}

public:
	void stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(this->startTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

		long double duration = (long double)(end - start);
		this->function(duration);
	}
};

#define TEST_OPERATION(title, Operation) \
{ \
	cprint(stdout COMMA title); \
	Timer timer = Timer([](long double duration) { std::cout << "Operation worked for " << duration << " ms.\n\n"; }); \
	{ \
		Operation \
	} \
}

int main(void)
{
	using namespace ::std;
	using namespace ::cformat;
	using namespace ::cformat::details;

	cprint(stdout, "+----------------------------------+\nEnter any key to start usage tests:\n");
	cin.get();

	TEST_OPERATION("Testing FORMATTER with dynamic chars buffer:\n",
		{
			char* buffer = format("{} + {} = {} and it is {} operation.\n" COMMA 3 COMMA 5 COMMA 8 COMMA "mathematical");
			cout << buffer;
			print(cout COMMA buffer);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with static chars buffer:\n",
		{
			char buffer[256] = { };
			unsigned int length = formatTo<256>(buffer COMMA "{} + {} = {} and it is {} operation.\n" COMMA 3 COMMA 5 COMMA 8 COMMA "mathematical");
			cout << buffer;
			print(cout COMMA buffer);
			cprint(stdout COMMA buffer);
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::string:\n",
		{
			string formatted = sformat<string>("{} + {} = {} and it is {} operation.\n" COMMA 3 COMMA 5 COMMA 8 COMMA "mathematical");
			cout << formatted.c_str();
			print(cout COMMA formatted.c_str());
			cprint(stdout COMMA formatted.c_str());
		}
	);

	cprint(stdout, "+----------------------------------+\nEnter any key to start std tests:\n");
	cin.get();

	TEST_OPERATION("Testing FORMATTER with std::string:\n",
		{
			string container = "std string label as text";
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::array:\n",
		{
			array<int COMMA 5> container = { 1 COMMA 2 COMMA 3 COMMA 4 COMMA 5 };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::vector:\n",
		{
			vector<int> container = { 1 COMMA 2 COMMA 3 COMMA 4 COMMA 5 };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::list:\n",
		{
			list<int> container = { 1 COMMA 2 COMMA 3 COMMA 4 COMMA 5 };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::deque:\n",
		{
			deque<int> container = { 1 COMMA 2 COMMA 3 COMMA 4 COMMA 5 };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::set:\n",
		{
			set<int> container = { 1 COMMA 2 COMMA 3 COMMA 4 COMMA 5 };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::unordered_set:\n",
		{
			unordered_set<int> container = { 1 COMMA 2 COMMA 3 COMMA 4 COMMA 5 };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::pair:\n",
		{
			pair<int COMMA bool> container = { 1 COMMA false };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);
	
	TEST_OPERATION("Testing FORMATTER with std::map:\n",
		{
			map<int COMMA bool> container = { { 1 COMMA true } COMMA { 2 COMMA true } COMMA { 3 COMMA true } COMMA { 4 COMMA true } COMMA { 5 COMMA false } };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	TEST_OPERATION("Testing FORMATTER with std::unordered_map:\n",
		{
			unordered_map<int COMMA bool> container = { { 1 COMMA true } COMMA { 2 COMMA true } COMMA { 3 COMMA true } COMMA { 4 COMMA true } COMMA { 5 COMMA false } };
			char* buffer = format("Container: {}.\n" COMMA container);
			cprint(stdout COMMA buffer);
			delete[] buffer;
		}
	);

	cprint(stdout, "+----------------------------------+\nEnter any key to start performance tests:\n");
	cin.get();

	const unsigned int count = 10000000u;

	TEST_OPERATION("Testing FORMATTER using heap:\n",
		{
			for (uint32 i = 0; i < count; i++)
			{
				auto formatted = format("Boolean value is : {}\nChar value is : {}\nInt8 value is : {}\nUInt8 value is : {}\nInt16 value is : {}\nUInt16 value is : {}\nInt32 value is : {}\nUInt32 value is : {}\nLongLong value is : {}\nULongLong value is : {}\nFloat value is : {}\nFloat value with precision is : {p:3.5}\nDouble value is : {}\nDouble value with precision is : {p:3.5}\nLongDouble value is : {}\nLongDouble value with precision is : {p:3.5}\nNullptr stringified is : {}\nPoint here goes brrr : [{} {} {}]\nSome string value is : {}\n" COMMA
					bool() COMMA
					char(67) COMMA
					int8(1) COMMA
					uint8() COMMA
					int16() COMMA
					uint16() COMMA
					int32() COMMA
					uint32() COMMA
					int64() COMMA
					uint64() COMMA
					float() COMMA
					float(8125.5432) COMMA
					double(2135.354684343565435) COMMA
					double(2135.354684343565435) COMMA
					ldouble() COMMA
					ldouble(156.698461) COMMA
					nullptr COMMA
					7 COMMA 8 COMMA 9 COMMA
					std::string("jejejejejejej")
				);
				delete[] formatted;
			}
		}
	);

	TEST_OPERATION("Testing FORMATTER using stack:\n",
		{
			for (uint32 i = 0; i < count; i++)
			{
				char buffer[2048];
				uint32 written = formatTo<2048>(buffer COMMA "Boolean value is : {}\nChar value is : {}\nInt8 value is : {}\nUInt8 value is : {}\nInt16 value is : {}\nUInt16 value is : {}\nInt32 value is : {}\nUInt32 value is : {}\nLongLong value is : {}\nULongLong value is : {}\nFloat value is : {}\nFloat value with precision is : {p:3.5}\nDouble value is : {}\nDouble value with precision is : {p:3.5}\nLongDouble value is : {}\nLongDouble value with precision is : {p:3.5}\nNullptr stringified is : {}\nPoint here goes brrr : [{} {} {}]\nSome string value is : {}\n" COMMA
					bool() COMMA
					char(67) COMMA
					int8(1) COMMA
					uint8() COMMA
					int16() COMMA
					uint16() COMMA
					int32() COMMA
					uint32() COMMA
					int64() COMMA
					uint64() COMMA
					float() COMMA
					float(8125.5432) COMMA
					double(2135.354684343565435) COMMA
					double(2135.354684343565435) COMMA
					ldouble() COMMA
					ldouble(156.698461) COMMA
					nullptr COMMA
					7 COMMA 8 COMMA 9 COMMA
					std::string("jejejejejejej")
				);
			}
		}
	);

	TEST_OPERATION("Testing SNPRINTF:\n",
		{
			for (uint32 i = 0; i < count; i++)
			{
				char buffer[2048];
				snprintf(buffer COMMA 2048 COMMA "Boolean value is : %d\nChar value is : %c\nInt8 value is : %d\nUInt8 value is : %u\nInt16 value is : %d\nUInt16 value is : %u\nInt32 value is : %d\nUInt32 value is : %u\nLongLong value is : %lld\nULongLong value is : %llu\nFloat value is : %f\nFloat value with precision is : %3.5f\nDouble value is : %f\nDouble value with precision is : %3.5f\nLongDouble value is : %Lf\nLongDouble value with precision is : %3.5Lf\nNullptr stringified is : %s\nPoint here goes brrr : [%d %d %d]\nSome string value is : %s\n" COMMA
					bool() COMMA
					char(67) COMMA
					int8(1) COMMA
					uint8() COMMA
					int16() COMMA
					uint16() COMMA
					int32() COMMA
					uint32() COMMA
					int64() COMMA
					uint64() COMMA
					float() COMMA
					float(8125.5432) COMMA
					double(2135.354684343565435) COMMA
					double(2135.354684343565435) COMMA
					ldouble() COMMA
					ldouble(156.698461) COMMA
					"nullptr" COMMA
					7 COMMA 8 COMMA 9 COMMA
					std::string("jejejejejejej").c_str()
				);
			}
		}
	);

	TEST_OPERATION("Testing FORMATTER using heap:\n",
		{
			for (uint32 i = 0; i < count; i++)
			{
				auto formatted = format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {}\n" COMMA
					bool() COMMA
					char(67) COMMA
					int8(1) COMMA
					uint8() COMMA
					int16() COMMA
					uint16() COMMA
					int32() COMMA
					uint32() COMMA
					int64() COMMA
					uint64() COMMA
					float() COMMA
					double(2135.354684343565435) COMMA
					ldouble() COMMA
					nullptr COMMA
					7 COMMA 8 COMMA 9 COMMA
					std::string("jejejejejejej")
				);

				delete[] formatted;
			}
		}
	);

	TEST_OPERATION("Testing FORMATTER using stack:\n",
		{
			for (uint32 i = 0; i < count; i++)
			{
				char buffer[450];
				unsigned int written = formatTo<450>(buffer COMMA "{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {}\n" COMMA
					bool() COMMA
					char(67) COMMA
					int8(1) COMMA
					uint8() COMMA
					int16() COMMA
					uint16() COMMA
					int32() COMMA
					uint32() COMMA
					int64() COMMA
					uint64() COMMA
					float() COMMA
					double(2135.354684343565435) COMMA
					ldouble() COMMA
					nullptr COMMA
					7 COMMA 8 COMMA 9 COMMA
					std::string("jejejejejejej")
				);
			}
		}
	);

	TEST_OPERATION("Testing SNPRINTF:\n",
		{
			for (uint32 i = 0; i < count; i++)
			{
				char* buffer = new char[1024];
				snprintf(buffer COMMA 1024 COMMA
				"%d %c %d %u %d %u %d %u %lld %llu %f %f %Lf nullptr [%d %d %d] %s" COMMA
					bool() COMMA
					char(67) COMMA
					int8(1) COMMA
					uint8() COMMA
					int16() COMMA
					uint16() COMMA
					int32() COMMA
					uint32() COMMA
					int64() COMMA
					uint64() COMMA
					float() COMMA
					double(2135.354684343565435) COMMA
					ldouble() COMMA
					7 COMMA 8 COMMA 9 COMMA
					std::string("jejejejejejej").c_str()
				);
				delete[] buffer;
			}
		}
	);

	TEST_OPERATION("Testing STRING STREAM:\n",
		{
			for (int i = 0; i < count; i++)
			{
				std::stringstream stream;
				stream << bool(0) << 
					char(67) <<
					int8(1) <<
					uint8(0) <<
					int16(0) <<
					uint16(0) <<
					int32(0) <<
					uint32(0) <<
					int64(0) <<
					uint64(0) <<
					float(0) <<
					double(2135.354684343565435) <<
					ldouble(0) << "nullptr" << '[' << 7 << ' ' << 8 << ' ' << 9 << ']' <<
					std::string("jejejejejejej") << '\n';
			}
		}
	);

	const unsigned int stressCount = 100000000u;

	TEST_OPERATION("Testing FORMATTER using heap:\n",
		{
			for (int i = 0; i < stressCount; i++)
			{
				char* formatted = format("{}" COMMA int(i));
				delete[] formatted;
			}
		}
	);

	TEST_OPERATION("Testing FORMATTER using stack:\n",
		{
			for (int i = 0; i < stressCount; i++)
			{
				char formatted[100];
				formatTo<100>(formatted, "{}", int(i));
			}
		}
	);

	TEST_OPERATION("Testing SNPRINTF:\n",
		{
			for (int i = 0; i < stressCount; i++)
			{
				char formatted[100];
				snprintf(formatted, 100, "%d", int(i));
			}
		}
	);

	return 0;
}
