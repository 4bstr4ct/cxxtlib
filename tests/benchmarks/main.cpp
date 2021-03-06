#include <cformat/format.hpp>

#include <iostream>
#include <sstream>

#include <chrono>
#include <functional>

class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;

public:
	Timer()
		: startTimePoint(std::chrono::high_resolution_clock::now()) { }

	~Timer()
	{
	}

public:
	long double stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(this->startTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

		return (long double)(end - start) * 0.001;
	}
};

#define TEST_OPERATION(title, Operation) \
{ \
	cprint(stdout COMMA title); \
	double time = 0.0; \
	int iterations = 100; \
	for (int it = 0; it < iterations; it++) \
	{ \
		Timer timer; \
		Operation \
		time += timer.stop(); \
	} \
	time /= (double)iterations; \
	std::cout << SET_GREEN << "Operation worked for " << time << " s (in average)." << SET_RESET << "\n\n"; \
}

#if _WIN32
#	define CLEAR "cls"
#else
#	define CLEAR "clear"
#endif

#define TO_NEXT(label) \
{ \
	cprint(stdout, SET_RESET"+----------------------------------+\n{}\n", label); \
}

#define SET_RESET "\u001b[0m"
#define SET_BLACK "\u001b[30m"
#define SET_WHITE "\u001b[37m"
#define SET_GREEN "\u001b[32m"
#define SET_YELLOW "\u001b[33m"
#define SET_RED "\u001b[31m"

int main(void)
{
	using namespace ::std;
	using namespace ::cformat;
	using namespace ::cformat::details;

	// Ten million
	#define ITERATIONS_COUNT 10000000
	auto result = system(CLEAR);

	TO_NEXT("Starting libc tests:\n")
	{
		TEST_OPERATION("Testing snprintf:\n",
			for (int i = 0; i < ITERATIONS_COUNT; i++)
			{
				char buffer[33] = { };
				snprintf(buffer COMMA 33 COMMA "%d\n" COMMA int(100));
			}
		);

		TEST_OPERATION("Testing sprintf:\n",
			for (int i = 0; i < ITERATIONS_COUNT; i++)
			{
				char* buffer = new char[33];
				sprintf(buffer COMMA "%d\n" COMMA int(100));
				delete[] buffer;
			}
		);
	}

	TO_NEXT("Starting cformat tests:\n")
	{
		TEST_OPERATION("Testing format:\n",
			for (int i = 0; i < ITERATIONS_COUNT; i++)
			{
				char* buffer = format("{}\n" COMMA int(100));
				delete[] buffer;
			}
		);

		TEST_OPERATION("Testing formatTo:\n",
			for (int i = 0; i < ITERATIONS_COUNT; i++)
			{
				char buffer[33] = { };
				formatTo(buffer COMMA 33 COMMA "{}\n" COMMA int(100));
			}
		);

		TEST_OPERATION("Testing sformat:\n",
			for (int i = 0; i < ITERATIONS_COUNT; i++)
			{
				string formatted = sformat<string>("{}\n" COMMA int(100));
			}
		);
	}

	TO_NEXT("Starting libc++ tests:\n")
	{
		TEST_OPERATION("Testing stringstream:\n",
			for (int i = 0; i < ITERATIONS_COUNT; i++)
			{
				stringstream stream;
				stream << int(100) << '\n';
			}
		);
	}

	return 0;
}
