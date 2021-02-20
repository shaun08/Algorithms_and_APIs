// 2021-02-20: SHAUN08 --> C++ program to add 2 uint36_t's using only uint4_t and uint5_t
//                         (replication on 64 bit machine)


/* Header includes */
#include <iostream>
#include <stdint.h>
#include <stdlib.h>


/* Macros */
#define BITSIZE4 4
#define BITSIZE5 5
#define BITSIZE36 36
#define MAX_4BIT_UINT 0xF
#define MAX_5BIT_UINT 0x1F
#define MAX_36BIT_UINT 0xFFFFFFFFF
#define ARRAY_SIZE 4

#define CONVERT_TO_UINT4_T(x) ((x) & MAX_4BIT_UINT)
#define CONVERT_TO_UINT5_T(x) ((x) & MAX_5BIT_UINT)
#define CONVERT_TO_UINT36_T(x) ((x) & MAX_36BIT_UINT)


/* Data types */
#define uint4_t uint8_t
#define uint5_t uint8_t

struct uint36_t
{
	uint5_t five_bit_nrs[ARRAY_SIZE];
	uint4_t four_bit_nrs[ARRAY_SIZE];
	size_t  nr_of_four_bit_elements;
	size_t  nr_of_five_bit_elements;
};


/* Functions */
uint36_t map_uint64_to_uint36_struct(uint64_t& x)
{
	uint36_t value = {};
	size_t five_bit_arr_index = 0;
	size_t four_bit_arr_index = 0;

	if (x > MAX_36BIT_UINT)
	{
		std::cout << "Number passed greater than '" << MAX_36BIT_UINT <<
			"', so will be truncating to least " << BITSIZE36 << " bits" << std::endl;
		
		x = CONVERT_TO_UINT36_T(x);
	}
	
	while (x && (five_bit_arr_index < ARRAY_SIZE))
	{
		value.five_bit_nrs[five_bit_arr_index] = CONVERT_TO_UINT5_T(x);
		value.nr_of_five_bit_elements++;
		x >>= BITSIZE5;
		five_bit_arr_index++;
	}

	while (x && (four_bit_arr_index < ARRAY_SIZE))
	{
		value.four_bit_nrs[four_bit_arr_index] = CONVERT_TO_UINT4_T(x);
		value.nr_of_four_bit_elements++;
		x >>= BITSIZE4;
		four_bit_arr_index++;
	}

	return value;
}

uint64_t map_uint36_to_uint64_struct(uint36_t& x)
{
	uint64_t value = 0;
	uint64_t temp_val = 0;
	size_t five_bit_arr_index = 0;
	size_t four_bit_arr_index = 0;

	while (five_bit_arr_index < ARRAY_SIZE)
	{
		temp_val = x.five_bit_nrs[five_bit_arr_index];
		temp_val <<= (BITSIZE5 * five_bit_arr_index);
		five_bit_arr_index++;
		value |= temp_val;
	}

	while (four_bit_arr_index < ARRAY_SIZE)
	{
		temp_val = x.four_bit_nrs[four_bit_arr_index];
		temp_val <<= ((BITSIZE5 * ARRAY_SIZE) + BITSIZE4 * four_bit_arr_index);
		four_bit_arr_index++;
		value |= temp_val;
	}

	return value;
}

void print_uint36_t_struct(uint36_t& value)
{
	std::cout << "{ { ";

	for (int i = ARRAY_SIZE-1; i >= 0; i--)
	{
		std::cout << static_cast<int>(value.four_bit_nrs[i]) << " ";
	}

	std::cout << "}, { ";

	for (int i = ARRAY_SIZE-1; i >= 0; i--)
	{
		std::cout << static_cast<int>(value.five_bit_nrs[i]) << " ";
	}

	std::cout << "}, " << value.nr_of_four_bit_elements << ", "
		<< value.nr_of_five_bit_elements << " }" << std::endl;
}

uint36_t add_36bit_numbers(uint36_t& a, uint36_t& b, bool& overflow)
{
	uint36_t sum = {};
	int carry = 0;
	
	std::cout << "36bit numbers passed:" << std::endl;
	std::cout << "1st number ";
	print_uint36_t_struct(a);
	std::cout << "2st number ";
	print_uint36_t_struct(b);

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		sum.five_bit_nrs[i] = a.five_bit_nrs[i] + b.five_bit_nrs[i] + carry;
		
		// This check for overflow is done such that it works on 64-bit machine
		carry = (sum.five_bit_nrs[i] > MAX_5BIT_UINT) ? 1 : 0;

		// This wont be necessary if machine support was just 4/5 bit
		sum.five_bit_nrs[i] = CONVERT_TO_UINT5_T(sum.five_bit_nrs[i]);
	}

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		sum.four_bit_nrs[i] = a.four_bit_nrs[i] + b.four_bit_nrs[i] + carry;

		// This check for overflow is done such that it works on 64-bit machine
		carry = (sum.four_bit_nrs[i] > MAX_4BIT_UINT) ? 1 : 0;

		// This wont be necessary if machine support was just 4/5 bit
		sum.four_bit_nrs[i] = CONVERT_TO_UINT4_T(sum.four_bit_nrs[i]);
	}

	overflow = (carry == 0) ? false : true;
	
	return sum;
}

#if 1
int main()
{
	bool overflow = false;

	// Test addition with overflow
	uint64_t a = 0xFFFFFFFFF;
	uint64_t b = 0x01;
	
	uint36_t num1 = map_uint64_to_uint36_struct(a);
	uint36_t num2 = map_uint64_to_uint36_struct(b);

	uint36_t temp_sum = add_36bit_numbers(num1, num2, overflow);
	uint64_t sum = map_uint36_to_uint64_struct(temp_sum);

	std::cout << "Sum1 = " << sum << ", Overflow = " << overflow << std::endl << std::endl;

	// Test normal addition
	uint64_t c = 295;
	uint64_t d = 205;

	num1 = map_uint64_to_uint36_struct(c);
	num2 = map_uint64_to_uint36_struct(d);

	temp_sum = add_36bit_numbers(num1, num2, overflow);
	sum = map_uint36_to_uint64_struct(temp_sum);
	
	std::cout << "Sum2 = " << sum << ", Overflow = " << overflow << std::endl << std::endl;

	return 0;
}
#endif