// 2021/02/22: SHAUN08 --> Generic C program to check and convert endianness of unisgned integers
//                         irrespective of native endianness of the machine running this program

#include <stdio.h>
#include <stdint.h>

void convert_endianness(void *num, size_t numsize)
{
	int i = 0;

	printf("Size of datatype passed: %d\n",numsize);

	for(i=0; i<numsize/2; i++)
	{
		// Get the highest and lowest significant byte at each iteration
		uint8_t* msb = (uint8_t*)num + (numsize-1-i);
		uint8_t* lsb = (uint8_t*)num + i;

		// Swap the highest and lowest bytes
		*msb ^= *lsb;
		*lsb ^= *msb;
		*msb ^= *lsb;
	}
}

int main()
{
	uint32_t a = 0x01020304;
	uint64_t a2 = 0x0102030405060708;

	printf("\nNumber1= 0x%x\n",a);

	// Check and convert endianness of a
	char b = (char)a;

	if((uint32_t)b == 0x04)
		printf("Machine is little endian\n");
	else
		printf("Machine is big endian\n");

	convert_endianness( (void *)&a, sizeof(a));

	printf("Number1 post endian coversion= 0x%x\n\n\n",a);

	printf("Number2= %llu\n",a2);

	// Check and convert endianness of a2
	b = (char)a2;

	if((uint64_t)b == 0x08)
		printf("Machine is little endian\n");
	else
		printf("Machine is big endian\n");

	convert_endianness( (void *)&a2, sizeof(a2));

	printf("Number2 post endian coversion= %llu\n\n\n",a2);

	printf("Number3= 0x%x\n",a);

	// Check and convert endianness of a excluding the most significant byte
	// At this point a will have been converted to 0x04030201
	b = (char)a;

	if((uint32_t)b == 0x01)
		printf("Machine is little endian\n");
	else
		printf("Machine is big endian\n");

	convert_endianness( (void *)&a, sizeof(a)-1);

	printf("Number3 post endian coversion= 0x%x\n\n",a);

	return 0;
}

