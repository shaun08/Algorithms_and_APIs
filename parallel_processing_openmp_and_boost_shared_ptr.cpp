// 2021-02-20: SHAUN08 --> C++ program to test parallel processing using OpenMP and
//                         verify boost shared_ptr library in Visual Studio

#include <chrono>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <boost\make_shared.hpp>
#include <boost\shared_ptr.hpp>
#include <omp.h>
#include <thread>

using namespace std;

const double M_PI = 3.14;
const int SIZE = 10000;
const int THREAD_NUM = 4;
int ACTUAL_THREADS[] = { 0 };
chrono::milliseconds SLEEP(2000);

namespace test_for
{
	void without_openmp(void* arg)
	{
		//cout << "without openmp begin:" << endl;
		double* sinTable = (double*)arg;
		for (int a = 0; a < SIZE; ++a)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				sinTable[i] = 44444 * sin(i* M_PI / SIZE);
			}
		}
		//cout << "without openmp end" << endl;
	}

	void with_openmp(void* arg)
	{
		//cout << "with openmp begin:" << endl;
		double* sinTable = (double*)arg;
		omp_set_num_threads(THREAD_NUM);
#pragma omp parallel for //schedule(runtime)
		for (int a = 0; a < SIZE; ++a)
		{
			if (omp_get_thread_num() == 0)
				ACTUAL_THREADS[0] = omp_get_num_threads();
			for (int i = 0; i < SIZE; ++i)
			{
				sinTable[i] = 44444 * sin(i* M_PI / SIZE);
			}
		}
		//cout << "with openmp end" << endl;
	}
} // namespace test_for

namespace test_for_schedule
{
	const int LEVEL1_MAX = 2;
	const int LEVEL2_MAX = 1200;
	const int LEVEL3_MAX = 2;
	const int LEVEL4_MAX = 10;


	struct test_level4_struct
	{
		double x;
	};

	struct test_level3_struct
	{
		test_level4_struct l4_array[LEVEL4_MAX];
	};

	struct test_level2_struct
	{
		test_level3_struct l3_array[LEVEL3_MAX];
	};

	struct test_level1_struct
	{
		test_level2_struct l2_array[LEVEL2_MAX];
	};

	struct test_struct
	{
		test_level1_struct l1_array[LEVEL1_MAX];
	};

	void without_openmp(void* test_p)
	{
		//cout << "without openmp begin:" << endl;
		test_struct* test_data_p = ((test_struct*)test_p);
		int l1, l2, l3, l4;
		for (int i = 0; i < SIZE; ++i)
		{
			for (l1 = 0; l1 < LEVEL1_MAX; ++l1)
			{
				for (l2 = 0; l2 < LEVEL2_MAX; ++l2)
				{
					for (l3 = 0; l3 < LEVEL3_MAX; ++l3)
					{
						for (l4 = 0; l4 < LEVEL4_MAX; ++l4)
						{
							test_data_p->l1_array[l1].l2_array[l2].l3_array[l3].l4_array[l4].x =
								44444 * (sin(l1*l2*l3*l4) + tan(l1*l2*l3*l4) + cos(l1*l2*l3*l4));
						}
					}
				}
			}
		}
		//cout << "without openmp end" << endl;
	}

	void with_openmp(void* test_p)
	{
		//cout << "with openmp begin:" << endl;
		test_struct* test_data_p = ((test_struct*)test_p);
		int i, l1, l2, l3, l4;
		omp_set_num_threads(THREAD_NUM);
#pragma omp parallel for private(i, l1, l2, l3, l4) // schedule(runtime)
		for (i = 0; i < SIZE; ++i)
		{
			if (omp_get_thread_num() == 0)
				ACTUAL_THREADS[1] = omp_get_num_threads();
			for (l1 = 0; l1 < LEVEL1_MAX; ++l1)
			{
				for (l2 = 0; l2 < LEVEL2_MAX; ++l2)
				{
					for (l3 = 0; l3 < LEVEL3_MAX; ++l3)
					{
						for (l4 = 0; l4 < LEVEL4_MAX; ++l4)
						{
							test_data_p->l1_array[l1].l2_array[l2].l3_array[l3].l4_array[l4].x =
								44444 * (sin(l1*l2*l3*l4) + tan(l1*l2*l3*l4) + cos(l1*l2*l3*l4));
						}
					}
				}
			}
		}
		//cout << "with openmp end" << endl;
	}

	void with_openmp_schedule(void* test_p)
	{
		//cout << "with openmp collapse begin:" << endl;
		test_struct* test_data_p = ((test_struct*)test_p);
		int i, l1, l2, l3, l4;
		omp_set_num_threads(THREAD_NUM);
		//omp_set_schedule(['runtime']);
#pragma omp  parallel

#pragma omp	for /*collapse(5)*/ schedule(runtime)
		for (i = 0; i < SIZE; ++i)
		{
			if (omp_get_thread_num() == 0)
				//#pragma omp master
				//#pragma omp single
				//#pragma section(s)
				ACTUAL_THREADS[2] = omp_get_num_threads();
			for (l1 = 0; l1 < LEVEL1_MAX; ++l1)
			{
				for (l2 = 0; l2 < LEVEL2_MAX; ++l2)
				{
					for (l3 = 0; l3 < LEVEL3_MAX; ++l3)
					{
						for (l4 = 0; l4 < LEVEL4_MAX; ++l4)
						{
							test_data_p->l1_array[l1].l2_array[l2].l3_array[l3].l4_array[l4].x =
								44444 * (sin(l1*l2*l3*l4) + tan(l1*l2*l3*l4) + cos(l1*l2*l3*l4));
						}
					}
				}
			}
		}
		//cout << "with openmp schedule end" << endl;
	}
} //namespace test_for_schedule

#define CALC_TIME(func, arg) \
do{ \
   ostringstream output_pre; \
   output_pre << ">> Time in secs for " << SIZE << " iterations of "; \
   cout << setw(35) << output_pre.str() << setw(45) << #func " = " << \
   fixed << setprecision(7) << double(util::time_function(func, arg)/1000000000.0); \
}while(false)

namespace util
{

	int64_t time_function(void(*f)(void*), void* arg)
	{
		auto t1 = chrono::high_resolution_clock::now();
		f(arg);
		auto t2 = chrono::high_resolution_clock::now();

		auto duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
		return duration;
	}

} //namespace util

class boost_test
{
public:
	boost_test() :x(0), str("") {}

	boost_test(int a, string s) :x(a), str(s) {}

	void print()
	{
		cout << endl << "X: " << x << ", String: " << str << endl;
	}

public:
	int x;
	string str;
}; // class boost_test

int main()
{
	omp_set_dynamic(0); // Turn off dynamic
	cout << "Num of processors in current system: " << omp_get_num_procs() << endl;
	cout << "Max threads supported by OMP on current system: " << omp_get_max_threads() << endl << endl;

	omp_lock_t thread_lock;
	omp_init_lock(&thread_lock);

#pragma omp parallel
	{
		int thread_num = omp_get_thread_num();
		int num_threads = omp_get_num_threads();

		omp_set_lock(&thread_lock);
		//#pragma omp critical //atomic is used for things like incrementing a variable
				//{
		cout << "Running OMP test thread " << thread_num + 1 << " out of " << num_threads << endl;
		//}
		omp_unset_lock(&thread_lock);
	}

	omp_destroy_lock(&thread_lock);
	cout << endl;

	double sinTable[SIZE];
	cout << "Test Array of " << SIZE << " with sin/tan/cos operations in loop" << endl;
	CALC_TIME(test_for::without_openmp, sinTable);
	cout << endl;
	CALC_TIME(test_for::with_openmp, sinTable);
	cout << setw(16) << "; Threads used: " << ACTUAL_THREADS[0];
	cout << endl << endl;

	test_for_schedule::test_struct test_struct;
	cout << "Test nested for loop with schedule pragma" << endl;
	CALC_TIME(test_for_schedule::without_openmp, &test_struct);
	cout << endl;
	CALC_TIME(test_for_schedule::with_openmp, &test_struct);
	cout << setw(16) << "; Threads used: " << ACTUAL_THREADS[1] << endl;
	CALC_TIME(test_for_schedule::with_openmp_schedule, &test_struct);
	cout << setw(16) << "; Threads used: " << ACTUAL_THREADS[2] << endl;

	auto shptr1 = boost::make_shared<boost_test>(1, "Hello World");
	shptr1->print();

	auto shptr2 = std::make_shared<boost_test>(2, "Bye World");
	shptr2->print();

	cin.get();
}