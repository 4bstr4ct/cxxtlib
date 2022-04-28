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

#if 1
std::vector<float> vec = { -0, -1, -2, -3, -4 };
std::list<double> lst = { 10, 12, 13, 14, 15 };
std::map<float, bool> mp = { { 5.0f, true }, { -9.0f, true }, { 1.0f, false} };

template<int tCount>
void testFormatterWithHeapWriter()
{
	using namespace ::cformat;
	
	for (details::uint32 i = 0; i < tCount; i++)
	{
		auto formatted = format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {} {} {} {} {}\n",
			bool(),
			char(67),
			details::int8(1),
			details::uint8(),
			details::int16(),
			details::uint16(),
			details::int32(),
			details::uint32(),
			details::int64(),
			details::uint64(),
			float(),
			double(2135.354684343565435),
			details::ldouble(),
			nullptr,
			7, 8, 9,
			&vec,
			&vec,
			&lst,
			&mp,
			std::string("jejejejejejej")
		);

		cleanup(formatted);
	}
}

template<int tCount>
void testFormatterWithStackWriter()
{
	using namespace ::cformat;

	for (details::uint32 i = 0; i < tCount; i++)
	{
		char buffer[450];
		unsigned int written = format<450>(buffer, "{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {} {} {} {} {}\n",
			bool(),
			char(67),
			details::int8(1),
			details::uint8(),
			details::int16(),
			details::uint16(),
			details::int32(),
			details::uint32(),
			details::int64(),
			details::uint64(),
			float(),
			double(2135.354684343565435),
			details::ldouble(),
			nullptr,
			7, 8, 9,
			&vec,
			&vec,
			&lst,
			&mp,
			std::string("jejejejejejej")
			);
	}
}

template<int tCount>
void testPrintf()
{
	using namespace ::cformat;

	for (details::uint32 i = 0; i < tCount; i++)
	{
		char* buffer = new char[1024];
		sprintf(buffer,
		"%d %c %d %u %d %u %d %u %lld %llu %f %f %Lf nullptr [%d %d %d] %p %p %p %p %s",
			bool(),
			char(67),
			details::int8(1),
			details::uint8(),
			details::int16(),
			details::uint16(),
			details::int32(),
			details::uint32(),
			details::int64(),
			details::uint64(),
			float(),
			double(2135.354684343565435),
			details::ldouble(),
			7, 8, 9,
			&vec,
			&vec,
			&lst,
			&mp,
			std::string("jejejejejejej").c_str()
			);
		delete[] buffer;
	}
}

template<int tCount>
void tesSStream()
{
	using namespace ::cformat;
	using namespace ::std;
	
	Point point = Point{ 7, 8, 9 };

	for (int i = 0; i < tCount; i++)
	{
		std::stringstream stream;
		stream << bool(0) << 
			char(67) <<
			details::int8(1) <<
			details::uint8(0) <<
			details::int16(0) <<
			details::uint16(0) <<
			details::int32(0) <<
			details::uint32(0) <<
			details::int64(0) <<
			details::uint64(0) <<
			float(0) <<
			double(2135.354684343565435) <<
			details::ldouble(0) << "nullptr" << '[' << point.x << ' ' << point.y << ' ' << point.z << ']' <<
			&vec <<
			&vec <<
			&lst <<
			&mp <<
			std::string("jejejejejejej") << '\n';
	}
}

void testPrint()
{
	using namespace ::cformat;

	for (int i = 0; i < 100; i++)
	{
		print<std::ostream>(std::cout, "{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {} {} {} {} {}\n",
			bool(),
			char(67),
			details::int8(1),
			details::uint8(),
			details::int16(),
			details::uint16(),
			details::int32(),
			details::uint32(),
			details::int64(),
			details::uint64(),
			float(),
			double(2135.354684343565435),
			details::ldouble(),
			nullptr,
			7, 8, 9,
			&vec,
			&vec,
			&lst,
			&mp,
			std::string("jejejejejejej")
		);
	}
}

void testCout()
{
	using namespace ::cformat;
	using namespace ::std;

	for (int i = 0; i < 100; i++)
	{
		cout << bool() <<
			char(67) <<
			details::int8(1) <<
			details::uint8() <<
			details::int16() <<
			details::uint16() <<
			details::int32() <<
			details::uint32() <<
			details::int64() <<
			details::uint64() <<
			float() <<
			double(2135.354684343565435) <<
			details::ldouble() <<
			"nullptr" <<
			'[' << 7 << ' ' << 8 << ' ' << 9 << ']' <<
			&vec <<
			&vec <<
			&lst <<
			&mp <<
			std::string("jejejejejejej") << '\n';
	}
}
#endif

template<unsigned int tCount>
static constexpr void stressTestForFormatterWithHeap()
{
	using namespace ::cformat;

	for (details::uint32 i = 0; i < tCount; i++)
	{
		auto formatted = format("Boolean value is : {}\nChar value is : {}\nInt8 value is : {}\nUInt8 value is : {}\nInt16 value is : {}\nUInt16 value is : {}\nInt32 value is : {}\nUInt32 value is : {}\nLongLong value is : {}\nULongLong value is : {}\nFloat value is : {}\nFloat value with precision is : {p:3.5}\nDouble value is : {}\nDouble value with precision is : {p:3.5}\nLongDouble value is : {}\nLongDouble value with precision is : {p:3.5}\nNullptr stringified is : {}\nPoint here goes brrr : [{} {} {}]\nAddressOne value is : {}\nAddressTwo value is : {}\nAddressThree value is : {}\nAddressFour value is : {}\nSome string value is : {}\n",
			bool(),
			char(67),
			details::int8(1),
			details::uint8(),
			details::int16(),
			details::uint16(),
			details::int32(),
			details::uint32(),
			details::int64(),
			details::uint64(),
			float(),
			float(8125.5432),
			double(2135.354684343565435),
			double(2135.354684343565435),
			details::ldouble(),
			details::ldouble(156.698461),
			nullptr,
			7, 8, 9,
			&vec,
			&vec,
			&lst,
			&mp,
			std::string("jejejejejejej")
			);

		cleanup(formatted);
	}
}

template<unsigned int tCount>
static constexpr void stressTestForFormatterWithStack()
{
	using namespace ::cformat;

	for (details::uint32 i = 0; i < tCount; i++)
	{
		char buffer[2048];
		details::uint32 written = format<2048>(buffer, "Boolean value is : {}\nChar value is : {}\nInt8 value is : {}\nUInt8 value is : {}\nInt16 value is : {}\nUInt16 value is : {}\nInt32 value is : {}\nUInt32 value is : {}\nLongLong value is : {}\nULongLong value is : {}\nFloat value is : {}\nFloat value with precision is : {p:3.5}\nDouble value is : {}\nDouble value with precision is : {p:3.5}\nLongDouble value is : {}\nLongDouble value with precision is : {p:3.5}\nNullptr stringified is : {}\nPoint here goes brrr : [{} {} {}]\nAddressOne value is : {}\nAddressTwo value is : {}\nAddressThree value is : {}\nAddressFour value is : {}\nSome string value is : {}\n",
			bool(),
			char(67),
			details::int8(1),
			details::uint8(),
			details::int16(),
			details::uint16(),
			details::int32(),
			details::uint32(),
			details::int64(),
			details::uint64(),
			float(),
			float(8125.5432),
			double(2135.354684343565435),
			double(2135.354684343565435),
			details::ldouble(),
			details::ldouble(156.698461),
			nullptr,
			7, 8, 9,
			&vec,
			&vec,
			&lst,
			&mp,
			std::string("jejejejejejej")
			);
	}
}

template<unsigned int tCount>
static constexpr void stressTestForSPRINTF()
{
	using namespace ::cformat;

	for (details::uint32 i = 0; i < tCount; i++)
	{
		char buffer[2048];
		snprintf(buffer, 2048, "Boolean value is : %d\nChar value is : %c\nInt8 value is : %d\nUInt8 value is : %u\nInt16 value is : %d\nUInt16 value is : %u\nInt32 value is : %d\nUInt32 value is : %u\nLongLong value is : %lld\nULongLong value is : %llu\nFloat value is : %f\nFloat value with precision is : %3.5f\nDouble value is : %f\nDouble value with precision is : %3.5f\nLongDouble value is : %Lf\nLongDouble value with precision is : %3.5Lf\nNullptr stringified is : %s\nPoint here goes brrr : [%d %d %d]\nAddressOne value is : %p\nAddressTwo value is : %p\nAddressThree value is : %p\nAddressFour value is : %p\nSome string value is : %s\n",
			bool(),
			char(67),
			details::int8(1),
			details::uint8(),
			details::int16(),
			details::uint16(),
			details::int32(),
			details::uint32(),
			details::int64(),
			details::uint64(),
			float(),
			float(8125.5432),
			double(2135.354684343565435),
			double(2135.354684343565435),
			details::ldouble(),
			details::ldouble(156.698461),
			"nullptr",
			7, 8, 9,
			&vec,
			&vec,
			&lst,
			&mp,
			std::string("jejejejejejej").c_str()
			);
	}
}

int main(void)
{
	using namespace ::std;
	using namespace ::cformat;

	print<ostream>(cout, "Press any key to start tests...\n");
	cin.get();

#define STRESS_TEST 0
#if STRESS_TEST == 1
	const int count = 1000000;

	cout << "\nTesting formatter with heap!\n";

	for (int i = 0; i < 3; i++)
	{
		{
			Timer timer = Timer([](long double duration) { std::cout << "Formatter with heap worked for " << duration << " ms.\n"; });
			stressTestForFormatterWithHeap<count>();
		}
	}

	cout << "\nTesting SPRINTF!\n";

	for (int i = 0; i < 3; i++)
	{
		{
			Timer timer = Timer([](long double duration) { std::cout << "SPRINTF worked for " << duration << " ms.\n"; });
			stressTestForSPRINTF<count>();
		}
	}

	cout << "\nTesting formatter with stack!\n";

	for (int i = 0; i < 3; i++)
	{
		{
			Timer timer = Timer([](long double duration) { std::cout << "Formatter with stack worked for " << duration << " ms.\n"; });
			stressTestForFormatterWithStack<count>();
		}
	}
#endif

#define TEST_PRINTING 0
#if TEST_PRINTING == 1
	cout << "\nTesting print!\n";

	for (int i = 0; i < 10; i++)
	{
		{
			Timer timer = Timer([](long double duration) { std::cout << "Print worked for " << duration << " ms.\n"; });
			testPrint();
		}
	}

	cout << "\nTesting cout!\n";

	for (int i = 0; i < 10; i++)
	{
		{
			Timer timer = Timer([](long double duration) { std::cout << "Cout worked for " << duration << " ms.\n"; });
			testCout();
		}
	}
	
	cout << "\nEnd!\n\n\n";
#endif

#define TEST_FORMATING 0
#if TEST_FORMATING == 1
	{
		const int count = 1000000;

		cout << "\n+--------------------------------------+\nTesting formatter!\n";

		for (int i = 0; i < 3; i++)
		{
			{
				Timer timer = Timer([](long double duration) { std::cout << "Formatter worked for " << duration << " ms.\n"; });
				testFormatterWithHeapWriter<count>();
			}
		}
		
		cout << "\nTesting sprintf!\n";

		for (int i = 0; i < 3; i++)
		{
			{
				Timer timer = Timer([](long double duration) { std::cout << "Sprintf worked for " << duration << " ms.\n"; });
				testPrintf<count>();
			}
		}
		
		cout << "\nTesting formatter!\n";
		
		for (int i = 0; i < 3; i++)
		{
			{
				Timer timer = Timer([](long double duration) { std::cout << "Formatter worked for " << duration << " ms.\n"; });
				testFormatterWithStackWriter<count>();
			}
		}

		cout << "\nTesting string stream!\n";

		for (int i = 0; i < 3; i++)
		{
			{
				Timer timer = Timer([](long double duration) { std::cout << "SStream worked for " << duration << " ms.\n"; });
				tesSStream<count>();
			}
		}

		cout << "+--------------------------------------+\n";
	}
#endif

#define COMPARE 1
#if COMPARE == 1
	{
		cout << "+-------------------+\n";
		
		{
			Timer timer = Timer([](long double duration) { std::cout << "Formatter (heap) worked for " << duration << " ms.\n"; });
			{
				for (int i = 0; i < 100000000; i++)
				{
					char* formatted = format("{}", int(i));
					cleanup(formatted);
				}
			}
		}

		cout << "+-------------------+\n";

		{
			Timer timer = Timer([](long double duration) { std::cout << "Formatter (stack) worked for " << duration << " ms.\n"; });
			{
				for (int i = 0; i < 100000000; i++)
				{
					char formatted[100];
					format<100>(formatted, "{}", int(i));
				}
			}
		}

		cout << "+-------------------+\n";

		{
			Timer timer = Timer([](long double duration) { std::cout << "Snprintf worked for " << duration << " ms.\n"; });
			{
				for (int i = 0; i < 100000000; i++)
				{
					char formatted[100];
					snprintf(formatted, 100, "%d", int(i));
				}
			}
		}

		cout << "+-------------------+\n";
	}
#endif

	return 0;
}
