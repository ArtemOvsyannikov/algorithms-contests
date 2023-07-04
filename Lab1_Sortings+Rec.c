/*
TASK 1. Qsort worst
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_elements;
    scanf("%d", &num_elements);

    int* pivot_values = (int*)malloc(num_elements * sizeof(int));
    for (int i = 0; i < num_elements; i++) scanf("%d", &pivot_values[i]);

    int* elements = (int*)malloc(num_elements * sizeof(int));
    for (int i = 0; i < num_elements; i++) elements[i] = i;

    int left_index = 0;
    int right_index = num_elements - 1;
    int* result = (int*)malloc(num_elements * sizeof(int));

    for (int i = 0; i < num_elements; i++) {
        if (pivot_values[i] == 0) {
            int index = elements[(left_index + right_index) / 2];
            result[index] = num_elements - i;
            for (int j = (left_index + right_index) / 2; j < num_elements - i - 1; j++) elements[j] = elements[j + 1];
            right_index--;
        }
        else if (pivot_values[i] == -1) {
            result[elements[right_index]] = num_elements - i;
            for (int j = right_index; j < num_elements - i - 1; j++) elements[j] = elements[j + 1];
            right_index--;
        }
        else {
            result[elements[left_index]] = num_elements - i;
            for (int j = left_index; j < num_elements - i - 1; j++) elements[j] = elements[j + 1];
            right_index--;
        }
    }

    for (int i = 0; i < num_elements; i++) printf("%d ", result[i]);

    return 0;
}

/*
TASK 2. M-recursion
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

void convertToBinary(long long num, int binaryArr[], int *index) {
    while (num > 0) {
        binaryArr[(*index)++] = num % 2;
        num /= 2;
    }
}

void printBinary(int binaryArr[], int size) {
    int skip = 0;
    printf("%d", binaryArr[size - 1]);
    for (int i = size - 2; i >= 0; i--) {
        if ((binaryArr[i] == binaryArr[i + 1]) && (skip == 0)) {
            skip = 1;
            continue;
        }
        printf("%d", binaryArr[i]);
        skip = 0;
    }
    printf("\n");
}

void printBinaryReverse(int binaryArr[], int size) {
    int skip = 0;
    printf("%d", binaryArr[0]);
    for (int i = 1; i < size; i++) {
        if ((binaryArr[i] == binaryArr[i - 1]) && (skip == 0)) {
            skip = 1;
            continue;
        }
        printf("%d", binaryArr[i]);
        skip = 0;
    }
}

int main() {
    long long n;
    scanf("%lld", &n);
    if (n == 0) {
        printf("0\n");
        printf("0\n");
        return 0;
    }

    int binaryArr[MAX_SIZE];
    int index = 0;

    convertToBinary(n, binaryArr, &index);
    printBinary(binaryArr, index);
    printBinaryReverse(binaryArr, index);

    return 0;
}

/*
TASK 3. Merge sort
*/

#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int left, int mid, int right) {
    printf("\n");
    int left_size = mid - left + 1;
    int right_size = right - mid;
    int* left_array = (int*)malloc(left_size * sizeof(int));
    int* right_array = (int*)malloc(right_size * sizeof(int));
    printf("Left part: ");
    for (int i = 0; i < left_size; i++) {
        left_array[i] = array[left + i];
        printf("%d ", array[left + i]);
    }
    printf("\nRight part: ");
    for (int j = 0; j < right_size; j++) {
        right_array[j] = array[mid + 1 +j];
        printf("%d ", array[mid + 1 + j]);
    }
    printf("\nMerged parts: ");
    int i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {
        if (left_array[i] <= right_array[j]) {
            array[k++] = left_array[i++];
            printf("%d ", left_array[i-1]);
        } else {
            array[k++] = right_array[j++];
            printf("%d ", right_array[j-1]);
        }
    }
    while (i < left_size) {
        array[k++] = left_array[i++];
        printf("%d ", left_array[i-1]);
    }
    while (j < right_size) {
        array[k++] = right_array[j++];
        printf("%d ", right_array[j-1]);
    }
    printf("\n");
}

void merge_sort(int* array, int left, int right) {
	if (left >= right) return;
	int mid = left + (right - left - 1) / 2;
	merge_sort(array, left, mid);
	merge_sort(array, mid+1, right);
	merge(array, left, mid, right);
}

int main() {
	int num_elements;
	scanf("%d", &num_elements);
	int* array = (int*)malloc(num_elements * sizeof(int));
	for (int i = 0; i < num_elements; i++) scanf("%d", &array[i]);
	printf("Initial array:\n");
	for (int i = 0; i < num_elements; i++) printf("%d ", array[i]);
	printf("\n");
	merge_sort(array, 0, num_elements-1);
	return 0;
}


/*
TASK 4. L-recursion
*/

#include <stdio.h>
#include <math.h>

int F(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    } else if (a > 20 || b > 20 || c > 20) {
        return 1048576;
    } else if (a < b && b < c) {
        return pow(2, a);
    } else if (a == b || a == c) {
        return pow(2, a);
    } else {
        return F(a - 1, b, c) + F(a - 1, b - 1, c) + F(a - 1, b, c - 1) - F(a - 1, b - 1, c - 1);
    }
}

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%d", F(a, b, c));
}

/*
TASK 5. Quick sort
*/

#include <stdio.h>
#include <stdlib.h>

int num_elements;

int partition(int* array, int low, int high) {
    int pivot_index = (low + high) / 2;
    int pivot = array[pivot_index];
    printf("Pivot index: %d , pivot element: %d\n", pivot_index, pivot);
    int less[10000];
    int greater[10000];
    int less_count = 0, greater_count = 0;

    for (int j = low; j <= high; j++) {
        if (j == pivot_index) continue;
        if (array[j] <= pivot) {
            less[less_count++] = array[j];
        } else {
            greater[greater_count++] = array[j];
        }
    }
    int cc = low;
    for (int l = 0; l < less_count; l++) {
        array[cc++] = less[l];
    }
    array[cc++] = pivot;
    for (int g = 0; g < greater_count; g++) {
        array[cc++] = greater[g];
    }
    return cc - greater_count - 1;
}

void quickSort(int* array, int low, int high) {
    if (low < high) {
        printf("\n");
        int pi = partition(array, low, high);
        printf("Array after partition: ");
        for (int i = 0; i < num_elements; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main() {
    scanf("%d", &num_elements);
    int* arr = malloc(num_elements * sizeof(int));
    for (int i = 0; i < num_elements; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Initial array:\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    quickSort(arr, 0, num_elements - 1);
    free(arr);
    return 0;
}
