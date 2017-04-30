#include "dyn_array.h"
#include <stdlib.h>
#include <string.h>

struct dyn_array_type
{
	float* data;
	size_t reserved;
	size_t size;
};

#define GUARD_INVALID_HANDLE( handle,return_value) 	if((handle)==DYN_ARRAY_HANDLE_INVALID){return return_value;}
#define GUARD_INVALID_HANDLE_VOID( handle) 	if((handle)==DYN_ARRAY_HANDLE_INVALID){return;}

// helper functions

void allocate_memory(dyn_array_handle array, size_t reserve){
	array->data = (0 < reserve) ? malloc(sizeof(float) * reserve) : NULL;
	array->reserved = (array->data!=NULL)?reserve : 0;
}

void copy_data(dyn_array_handle destination, dyn_array_handle source)
{
	memcpy(destination->data, source->data, source->size);
	destination->size = source->size;
}

// creates a dynamic array with size==zero and and reserved space==reserve
// if a negative size is given the invalid handle is returned
// in case of an error, the invalid handle is returned
dyn_array_handle dyn_array_create(size_t reserve)
{
// TO BE IMPLEMENTED
}

// creates a deep copy of the given array
// in case of an error, the invalid handle is returned
dyn_array_handle dyn_array_copy(dyn_array_handle array)
{
	GUARD_INVALID_HANDLE(array, DYN_ARRAY_HANDLE_INVALID)

// TO BE IMPLEMENTED
}

// free all ressources related to the given array
void dyn_array_delete(dyn_array_handle array)
{
	GUARD_INVALID_HANDLE_VOID(array)

// TO BE IMPLEMENTED
}

// returns the reserved size for this array
size_t dyn_array_reserved(dyn_array_handle array)
{
// TO BE IMPLEMENTED
}

// returns the used size of the array
size_t dyn_array_size(dyn_array_handle array)
{
// TO BE IMPLEMENTED
}

// allocate space for the array
// the existing content is copied to the new allocated memory
// if the given size is smaller than the used size, then the reserved size is the same as number of used elements
// returns the resulting reserved size
size_t dyn_array_reserve(dyn_array_handle array, size_t reserved)
{
	GUARD_INVALID_HANDLE(array, 0)
// TO BE IMPLEMENTED
}

// sets the number of used elements in the array
// if the new size is bigger than the old size, then the added elements are set to the given value
// the rules for reserved memory as described for add apply
// if the new size is smaller than the old size, then the last elements of the array are lost
// returns the resulting reserved size
size_t dyn_array_resize(dyn_array_handle array, size_t size, float value)
{
	GUARD_INVALID_HANDLE(array, 0)
	
// TO BE IMPLEMENTED
}

// adds a value at the end of the array
// if size==reserved_size the reserved size is increased by 50%
// if successful the function returns the new size
// if not successful it returns 0
size_t dyn_array_add(dyn_array_handle array,float value)
{
	GUARD_INVALID_HANDLE(array, 0)
// TO BE IMPLEMENTED
}

// removes the element at the position index from the array
// the element order does not have to be preserved
// if successful the function returns the new size
// if not successful it returns 0
size_t dyn_array_remove(dyn_array_handle array,size_t index)
{
	GUARD_INVALID_HANDLE(array, 0)
	
// TO BE IMPLEMENTED
}

// copies the value of the element at the index into the memorypointed to by out_value
// triggers assert if the index is out of the range of used elements
void dyn_array_get(dyn_array_handle array,size_t index, float* out_value)
{
	GUARD_INVALID_HANDLE_VOID(array)
	
// TO BE IMPLEMENTED
}

// sets the value of the element at index
// triggers assert if the index is out of the range of used elements
void dyn_array_set(dyn_array_handle array,size_t index, float value)
{
	GUARD_INVALID_HANDLE_VOID(array)

// TO BE IMPLEMENTED
}


