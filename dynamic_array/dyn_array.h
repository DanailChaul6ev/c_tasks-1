#ifndef C_TASKS__DYNAMIC_ARRAY__DYN_ARRAY__H__
#define C_TASKS__DYNAMIC_ARRAY__DYN_ARRAY__H__

#include <stddef.h>

// dyn_array is an array of float numbers with dynamic size
// all access is done via functions to ensure the consistency of the data
// the reserved size is the number of elements for which memory is allocated 
// the size of the array refers to the number of actually added elements, only this elements are accessible by the user

struct dyn_array_type;

typedef struct dyn_array_type* dyn_array_handle;

#define DYN_ARRAY_HANDLE_INVALID NULL

// creates a dynamic array with size==zero and and reserved space==reserve
// if a negative size is given the invalid handle is returned
// in case of an error, the invalid handle is returned
dyn_array_handle dyn_array_create(size_t reserve);

// creates a deep copy of the given array
// in case of an error, the invalid handle is returned
dyn_array_handle dyn_array_copy(dyn_array_handle array);

// free all ressources related to the given array
void dyn_array_delete(dyn_array_handle handle);

// returns the reserved suize for this array
size_t dyn_array_reserved(dyn_array_handle array);

// returns the used size of the array
size_t dyn_array_size(dyn_array_handle array);

// allocate space for the array
// the existing content is copied to the new allocated memory
// if the given size is smaller than the used size, then the reserved size is the same as number of used elements
// returns the resulting reserved size
size_t dyn_array_reserve(dyn_array_handle array, size_t size);

// sets the number of used elements in the array
// if the new size is bigger than the old size, then the added elements are set to the given value
// the rules for reserved memory as described for add apply
// if the new size is smaller than the old size, then the last elements of the array are lost
// the reserved size does not change if the new size is smaller than the old size
// returns the resulting size
size_t dyn_array_resize(dyn_array_handle array, size_t size, float value);

// adds a value at the end of the array
// if size==reserved_size the reserved size is increased by 50%
// if successful the function returns the new size
// if not successful it returns 0
size_t dyn_array_add(dyn_array_handle array,float value);

// removes the element at the position index from the array
// the element order does not have to be preserved
// if successful the function returns the new size
// if not successful it returns 0
size_t dyn_array_remove(dyn_array_handle array,size_t index);

// copies the value of the element at the index into the memorypointed to by out_value
// triggers assert if the index is out of the range of used elements
void dyn_array_get(dyn_array_handle array,size_t index, float* out_value);

// sets the value of the element at index
// triggers assert if the index is out of the range of used elements
void dyn_array_set(dyn_array_handle array,size_t index, float value);


#endif // C_TASKS__DYNAMIC_ARRAY__DYN_ARRAY__H__
