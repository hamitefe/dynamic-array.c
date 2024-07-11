#include "dynamic_array.c"
typedef struct {
	int x;
	double y;
	float z;
} TestStruct;

void print_struct(TestStruct data) {
	printf("x of the struct: %d\n", data.x);
	printf("y of the struct: %f\n", data.y);
	printf("z of the struct: %f\n", data.z);
}

int main() {
	DynamicArray arr = initializedarr();
	double double_ = 3.0;
	int integer = 5;
	float float_ = 10.0;
	TestStruct data = {
		15,
		35.0,
		99.0
	};
	pushdarr(&arr, &double_, sizeof(double));
	pushdarr(&arr, &integer, sizeof(int));
	pushdarr(&arr, &float_, sizeof(float));
	pushdarr(&arr, &data, sizeof(TestStruct));
	deletedarr(&arr, 2);
	double readed_double = 0.0;
	int readed_integer = 0;
	float readed_float = 0.0;
	TestStruct readed_struct;
	
	readdarr(&arr, &readed_double, 0);
	readdarr(&arr, &readed_integer, 1);
	readdarr(&arr, &readed_struct, 2);
	
	printf("readed double: %f \n", readed_double);
	printf("readed integer: %d \n", readed_integer);
	printf("readed struct: \n");
	print_struct(readed_struct);
	return 0;
}
