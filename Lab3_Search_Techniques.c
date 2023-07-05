/*
TASK 1. Linear Search
*/

#include <stdio.h>
#include <stdlib.h>

#define ll long long

void linear_search() {
    ll num_elements = 0, target = 0;
    scanf("%lld%lld", &num_elements, &target);

    ll* arr = (ll*)malloc((num_elements + 1) * sizeof(ll));
    for (ll i = 0; i < num_elements; ++i) scanf("%lld", &arr[i]);

    printf("Initial array:\n");
    for (ll i = 0; i < num_elements; ++i) printf("%lld ", arr[i]);

    printf("\n");
    printf("Target element: %lld\n", target);

    ll* indices = (ll*)malloc((num_elements + 1) * sizeof(ll));
    ll index = 0;
    for (ll i = 0; i < num_elements; ++i) {
        if (arr[i] == target) {
            indices[index] = i;
            index++;
        }
    }

    if (index == 0) printf("No targets");
    else {
        printf("Target is found at:");
        for (ll i = 0; i < index; i++) printf(" %lld", indices[i]);
    }
}

int main() {
    linear_search();
}

/*
TASK 2. Binary Search
*/

#include <stdio.h>
#include <stdlib.h>

#define ll long long

void binary_search(ll* arr, ll num_elements, ll target) {
    printf("Search history: ");

    ll left = 0, right = num_elements - 1;
    int found = 1;

    while (left <= right) {
        ll mid = (left + right) / 2;
        printf("%lld(%lld) ", arr[mid], mid);
        if (arr[mid] == target) {
            printf("\nTarget is found at: %lld", mid);
            found = 0;
            break;
        }
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    printf("\n");
    if (found == 1) printf("No targets");
}

void prepare_search() {
    ll num_elements = 0, target = 0;
    scanf("%lld%lld", &num_elements, &target);

    ll* arr = (ll*)malloc((num_elements + 1) * sizeof(ll));
    for (ll i = 0; i < num_elements; ++i) scanf("%lld", &arr[i]);

    printf("Initial array:\n");
    for (ll i = 0; i < num_elements; ++i) printf("%lld ", arr[i]);

    printf("\n");
    printf("Target element: %lld\n", target);
    binary_search(arr, num_elements, target);
}

int main() {
    prepare_search();
}

/*
TASK 3. Doubling Search
*/

#define ll long long
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binary_search(ll* array, ll left, ll right, ll target, ll num_elements) {
    ll bound1 = left, bound2 = right;
    int found = 1;
    if ((left + right) / 2 == bound1 || (left + right) / 2 == bound2) {
        printf("No targets\n");
        return 0;
    }
    printf("Search history: ");
    while (left < right && ((left + right) / 2 != bound1 && (left + right) / 2 != bound2)) {
        ll center = (left + right) / 2;
        printf("%lld(%lld) ", array[center], center);
        if (array[center] == target) {
            printf("\nTarget is found at: %lld", center);
            found = 0;
            break;
        }
        if (array[center] < target) left = center+1;
        else right = center;
    }
    printf("\n");
    if (found == 1) printf("No targets");
    return 0;
}

int exponential_search(ll* array, ll num_elements, ll target) {
    printf("Bounds history: %lld(0)", array[0]);
    if (array[0] == target) {
        printf("\nTarget is found at: 0");
        return 0;
    }
    if (array[1] > target) {
        printf("\nNo targets\n");
        return 0;
    }
    ll index = 1;
    while (index < num_elements && array[index] <= target) {
        printf(" %lld(%lld)", array[index], index);
        if (array[index] == target) {
            printf("\nTarget is found at: %lld", index);
            return 0;
        }
        index *= 2;
    }
    if (index < num_elements)
        printf(" %lld(%lld)", array[index], index);
    
    printf("\n");
    binary_search(array, index/2, index < num_elements ? index : num_elements, target, num_elements);
    return 0;
}

void prepare_search() {
    ll num_elements = 0, target = 0;
    scanf("%lld%lld", &num_elements, &target);
    
    ll* array = (ll*)malloc((num_elements + 1) * sizeof(ll));
    for (ll i = 0; i < num_elements; ++i)
        scanf("%lld", &array[i]);
    
    printf("Initial array:\n");
    for (ll i = 0; i < num_elements; ++i)
        printf("%lld ", array[i]);
    
    printf("\nTarget element: %lld\n", target);
    exponential_search(array, num_elements, target);
}

int main() {
    prepare_search();
}


