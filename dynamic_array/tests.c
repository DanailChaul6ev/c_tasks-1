#include <stdio.h>
#include "dyn_array.h"
#include "tests.h"

const size_t initial_reserved = 105;
const float init_value = 42.f;
const float invalid_value = 2165.f;

void check_int(const int expected_value, const int value,const char* error_msg, const char* file, int line);
void check_float(const float expected_value, const float value,const char* error_msg, const char* file, int line);
void print(dyn_array_handle array);


#define CHECK_INT(expected, value, msg) check_int(expected, value, msg, __FILE__, __LINE__)
#define CHECK_FLOAT(expected, value, msg) check_float(expected, value, msg, __FILE__, __LINE__)

int current_test=0;
int failed_tests=0;

void run_tests_dyn_array()
{
	current_test=0;
	failed_tests=0;
	
	size_t ret =0;
	
	float value = invalid_value;
	float expected_value = invalid_value;
	int i =0;
	size_t size = 0;
	
	dyn_array_handle array = dyn_array_create(initial_reserved);
	CHECK_INT(initial_reserved, dyn_array_reserved(array),"initial reserved size is not correct");
	CHECK_INT(0, dyn_array_size(array),"initial size is not zero");

	size = initial_reserved/2;
	ret = dyn_array_resize(array,size,init_value);
	CHECK_INT(initial_reserved, dyn_array_reserved(array),"reserved size changed after resize");
	CHECK_INT(size, dyn_array_size(array),"resize resulted in wrong size");
	CHECK_INT(initial_reserved, ret, "return value for dyn_array_resize is not as expected");
	for(i=0; size > i; ++i)
	{
		value = invalid_value;
		dyn_array_get(array, i, &value);
		CHECK_FLOAT(init_value, value,"wrong element value after resize");
		dyn_array_set(array, i, (float)i);
		dyn_array_get(array, i, &value);
		CHECK_FLOAT((float)i, value,"wrong element value after setting the element value");
	}
	
	int diff = initial_reserved - dyn_array_size(array);
	for(i=0; diff>i; ++i)
	{
		value = (float)(size+i);
		ret = dyn_array_add(array, value);
		CHECK_INT(initial_reserved, dyn_array_reserved(array),"reserved size changed after an element was added");
		CHECK_INT(size+i+1, dyn_array_size(array), "size is not correct");
		CHECK_INT(ret, dyn_array_size(array), "return value for dyn_array_add is not as expected");
	}
	CHECK_INT(dyn_array_size(array), dyn_array_reserved(array), "reserved size or size is not as expected");
	
	ret = dyn_array_add(array,init_value);
	CHECK_INT(initial_reserved+1, dyn_array_size(array), "size is not as expected");
	CHECK_INT(initial_reserved *1.5f, dyn_array_reserved(array), "reserved size is not as expected");
	CHECK_INT(dyn_array_size(array), ret, "return value for dyn_array_add is not as expected");
	size = dyn_array_size(array);
	for(i=0; size-1>i;++i)
	{
		expected_value = (float)i;
		value = invalid_value;
		dyn_array_get(array, i, &value);
		CHECK_FLOAT(expected_value, value,"element value is not as expected");
	}

	value = invalid_value;
	dyn_array_get(array, size-1, &value);
	CHECK_FLOAT(init_value, value,"last element value is not as expected");
	dyn_array_set(array, size-1, (float)size-1);
	
	ret = dyn_array_reserve(array,initial_reserved *2);
	CHECK_INT(size, dyn_array_size(array), "size changed after reserve");
	CHECK_INT(initial_reserved *2, dyn_array_reserved(array), "reserved size is not as expected after increasing the reserved size");
	CHECK_INT(dyn_array_reserved(array), ret, "return value for dyn_array_reserve is not as expected");
	
	for(i=0; size>i;++i)
	{
		expected_value = (float)i;
		value = invalid_value;
		dyn_array_get(array, i, &value);
		CHECK_FLOAT(expected_value, value,"element value changed after reserve");
	}
	
	ret = dyn_array_reserve(array, size/2);
	CHECK_INT(size, dyn_array_size(array), "size changed after reserve");
	CHECK_INT(size, dyn_array_reserved(array), "reserved size is not as expected after decreasing the reserved size");
	CHECK_INT(dyn_array_reserved(array), ret, "return value for dyn_array_reserve is not as expected");
	
	ret = dyn_array_resize(array, size/2, init_value);
	CHECK_INT(size/2, dyn_array_size(array), "size changed after reserve");
	CHECK_INT(size, dyn_array_reserved(array), "reserved size is not as expected after reducing used size");
	CHECK_INT(dyn_array_reserved(array), ret, "return value for dyn_array_resize is not as expected");
	
	for(i=0; dyn_array_size(array)>i;++i)
	{
		expected_value = (float)i;
		value = invalid_value;
		dyn_array_get(array, i, &value);
		CHECK_FLOAT(expected_value, value,"element value changed after reserve");
	}
	
	size = dyn_array_size(array);
	ret = dyn_array_remove(array,0);
	CHECK_INT(size-1, dyn_array_size(array),"size is not correct after removing the first element");
	CHECK_INT(dyn_array_size(array), ret, "return value for dyn_array_remove is not as expected");
	float sum = 0.f;
	for(i=0; dyn_array_size(array)>i;++i)
	{
		dyn_array_get(array, i, &value);
		sum += value;
	}
	expected_value = (float)((size+1)*size) / 2 -size;
	CHECK_FLOAT(expected_value, sum, "array content is not as expected after removing first element");
	
	ret = dyn_array_remove(array,size/2);
	CHECK_INT(size-2, dyn_array_size(array), "size is not correct after removing middle element");
	CHECK_INT(dyn_array_size(array), ret, "return value for dyn_array_remove is not as expected");
	sum = 0.f;
	for(i=0; dyn_array_size(array)>i;++i)
	{
		dyn_array_get(array, i, &value);
		sum += value;
	}
	expected_value -= (size/2);
	CHECK_FLOAT(expected_value, sum,"array content is not as expected after removing middle element");
	
	dyn_array_get(array,dyn_array_size(array)-1,&value);
	expected_value-= value;
	ret = dyn_array_remove(array,dyn_array_size(array)-1);
	CHECK_INT(size-3, dyn_array_size(array), "size is not correct after removing last element");
	CHECK_INT(dyn_array_size(array), ret, "return value for dyn_array_remove is not as expected");
	sum = 0.f;
	for(i=0; dyn_array_size(array)>i;++i)
	{
		dyn_array_get(array, i, &value);
		sum += value;
	}
	CHECK_FLOAT(expected_value, sum,"array content is not as expected after removing last element");
	
	dyn_array_delete(array);
	printf("number of failed tests: %i\n",failed_tests);
}

void print(dyn_array_handle array)
{
	int i=0;
	const int reserved = dyn_array_reserved(array);
	const int size = dyn_array_size(array);
	float value = 0.f;
	printf("reserved/size\t%i/%i\n", reserved, size);
	for(i=0; size>i;++i)
	{
		dyn_array_get(array, i, &value);
		printf("%i\t%f\n",i,value);
	}
}

void check_int(const int expected_value,const int value, const char* error_msg, const char* file, int line)
{
	++current_test;
	if(expected_value != value)
	{
		++failed_tests;
		fprintf(stderr,"%s:%i\t%s\texpected='%i'\tgot='%i'\n", file, line, error_msg, expected_value, value);
	}

}
void check_float(const float expected_value,const float value, const char* error_msg, const char* file, int line)
{
	++current_test;
	if(expected_value != value)
		fprintf(stderr,"%s:%i\t%s\texpected='%f'\tgot='%f'\n", file, line, error_msg, expected_value, value);

}

