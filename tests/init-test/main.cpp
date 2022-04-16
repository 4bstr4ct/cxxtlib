// #define ENABLE_STD_FORMATTERS 1
#define ENABLE_STD_FORMATTERS 1
// #include <cxxtlib/format/format.hpp>
#include "format.hpp"

#include <stdio.h>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <map>
#include <utility>
#include <sstream>

struct Point
{
public:
	using Type = int;

public:
	Type x, y, z;
};

template<>
CUSTOM_TYPE_OF(Point);

template<typename Char>
CUSTOM_FORMATTER(Char COMMA Point)
{
public:
	template<typename ParserContext>
	static void parse(ParserContext& pContext)
	{
		for (; *pContext != '}'; pContext++);
		pContext++;
	}

	template<typename FormatterContext>
	static void format(FormatterContext& pContext, const Point& pValue)
	{
		Formatter<Char, Char>::template format<FormatterContext>(pContext, '[');
		Formatter<Char, Point::Type>::template format<FormatterContext>(pContext, pValue.x);
		Formatter<Char, Char>::template format<FormatterContext>(pContext, ' ');
		Formatter<Char, Point::Type>::template format<FormatterContext>(pContext, pValue.y);
		Formatter<Char, Char>::template format<FormatterContext>(pContext, ' ');
		Formatter<Char, Point::Type>::template format<FormatterContext>(pContext, pValue.z);
		Formatter<Char, Char>::template format<FormatterContext>(pContext, ']');
	}
};


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
	using namespace ::cxxtlib::format;
	
	for (details::uint32 i = 0; i < tCount; i++)
	{
		auto formatted = format<char>("{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {} {} {} {} {}\n",
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
			"jejejejejejej"
		);

		cleanup(formatted);
	}
}

template<int tCount>
void testFormatterWithStackWriter()
{
	using namespace ::cxxtlib::format;

	for (details::uint32 i = 0; i < tCount; i++)
	{
		char buffer[450];
		int written = format<char, 450>(buffer, "{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {} {} {} {} {}\n",
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
			"jejejejejejej"
			);

		// cleanup(formatted);
	}
}

template<int tCount>
void testPrintf()
{
	using namespace ::cxxtlib::format;

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
			"jejejejejejej");
		delete[] buffer;
	}
}

template<int tCount>
void tesSStream()
{
	using namespace ::cxxtlib::format;
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
	using namespace ::cxxtlib::format;

	for (int i = 0; i < 100; i++)
	{
		print<std::ostream, char>(std::cout, "{} {} {} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {} {} {} {} {}\n",
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
			"jejejejejejej"
		);
	}
}

void testCout()
{
	using namespace ::cxxtlib::format;
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
			"jejejejejejej" << '\n';
	}
}
#endif

int main(void)
{
	using namespace ::std;
	using namespace ::cxxtlib::format;

	stdprint(cout, "{} != {}", 5, Point{ 5, 8, 9 });

	/*
	std::vector<std::vector<int>> mat = { { 0, 1, 1, 0, 1 }, { 0, 1, 1, 1, 1 }, { 1, 0, 1, 1, 0}, { 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 1 } };
	print<std::ostream, char>(std::cout, "{} {} {b10} {} {} {} {} {} {} {} {} {} {} {} [{} {} {}] {} {} {} {} {} {\n}\n",
			bool(),
			char(67),
			details::int8(12),
			details::uint8(16),
			details::int16(),
			details::uint16(),
			details::int32(874525),
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
			"jejejejejejej",
			mat
	);
	*/

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
	
	cout << "\End!\n";
#endif

#define TEST_FORMATING 1
#if TEST_FORMATING == 1
	const int count = 1000000;

	cout << "\nTesting formatter!\n";

	for (int i = 0; i < 3; i++)
	{
		{
			Timer timer = Timer([](long double duration) { std::cout << "Formatter worked for " << duration << " ms.\n"; });
			testFormatterWithHeapWriter<count>();
		}
	}
	
	cout << "Testing sprintf!\n";

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
#endif

	/*
	std::initializer_list<int> ilt = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::array<Point, 3> arr = { Point{ 0, 1, 2 }, Point{ 4, 5, 6 }, Point{ 7, 8, 9 } };
	std::vector<float> vec = { -0, -1, -2, -3, -4 };
	std::list<double> lst = { 10, 12, 13, 14, 15 };
	std::vector<std::vector<int>> mat = { { 0, 1, 1, 0, 1 }, { 0, 1, 1, 1, 1 }, { 1, 0, 1, 1, 0}, { 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 1 } };
	std::pair<bool, int> par = { true, 59 };
	std::map<float, bool> pmp = { { 5.0f, true }, { -9.0f, true }, { 1.0f, false} };

	print<ostream, char>(cout, "Mat : \n{\n}\n{}\n{\n}\n\n",
		mat,
		par,
		pmp
	);

	print<ostream, char>(cout, "Pattern : {}\n          {}\n          {}\n          {}\n\n",
		ilt,
		arr,
		vec,
		lst
	);
	*/

	return 0;
}