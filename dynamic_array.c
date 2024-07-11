#include <stdlib.h>
#include <stdio.h>

typedef struct {
	size_t* sizes;
	size_t total_size;
	size_t item_count;
	unsigned char* ptr;
} DynamicArray;

static DynamicArray initializedarr() {

	DynamicArray arr = {
		NULL,
		0,
		0,
		NULL
	};
	return arr;
}
//size is the size of the variable you are adding
//ptr is the pointer to the variable
//example usage:
//double d = 3.0;
//pushdarr(&arr, &d, sizeof(double))
static void pushdarr(DynamicArray *array, unsigned char * ptr, size_t size) {
	if (array->ptr == NULL) {
		array->ptr = malloc(size);
		for (int i = 0; i < size; i++) {
			array->ptr[i] = ptr[i];
		}
	}
	else {
		array->ptr = realloc(array->ptr, array->total_size + size);
		for (int i = 0; i < size; i++) {
			array->ptr[array->total_size + i] = ptr[i];
		}
	}
	if (array->sizes == NULL) {
		array->sizes = malloc(sizeof(size_t));
	}else {
		array->sizes =(unsigned char*) realloc(array->sizes, (array->item_count+1)* + sizeof(size_t));
	}
	array->sizes[array->item_count] = size;
	array->item_count++;
	array->total_size += size;
}
static void readdarr(DynamicArray* array, unsigned char* ptr, int index) {
	size_t until_item = 0;
	if (index > 0){
		for (int i = 0; i < index; i++) {
			until_item += array->sizes[i];
		}
	}
	for (int i = 0; i < array -> sizes[index]; i++){
		ptr[i] = array->ptr[until_item + i];
	}
}

static void deletedarr(DynamicArray* array, int index) {
	if (array->item_count <= index) return;
	if (index == array->item_count - 1) {
		array->ptr = realloc(array->ptr, array->total_size - array->sizes[index]);
		array->total_size = array->total_size - array->sizes[index];
		array->item_count--;
		array->sizes = realloc(array->sizes, array->item_count * sizeof(size_t));
		return;
	}
	size_t until_item = 0;
	for (int i = 0; i < index; i++) {
		until_item += array->sizes[i];
	}
	size_t size_of_removed_item = array->sizes[index];
	for (int i = until_item + size_of_removed_item; i < array->total_size; i++) {
		array->ptr[i - size_of_removed_item] = array->ptr[i];
	}
	array->total_size = array->total_size - array->sizes[index];

	for (int i = index; i < array->item_count; i++) {
		array->sizes[index] = array->sizes[index+1];
	}

	array->item_count--;
	array->ptr = realloc(array->ptr, array->total_size);

}
