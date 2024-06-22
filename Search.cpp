#include <iostream>

int LinearSearch(int* arr, int target, int size) {
	for (size_t i = 0; i < size; ++i) {
		if (arr[i] == target)
			return i;
	}

	return -1;
}

int BinarySearch(int* arr, int target, int size) {
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (arr[mid] == target) return mid;

		if (arr[mid] < target) left = mid + 1;

		else right = mid - 1;
	}

	return -1;
}

int InterpolationSearch(int* arr, int target, int size) {
	int low = 0;
	int high = size - 1;

	while (low <= high && target >= arr[low] && target <= arr[high]) {
		if (low == high) {
			if (arr[low] == target)
				return low;
			return -1;
		}

		int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));

		if (arr[pos] == target) return pos;

		if (arr[pos] < target) low = pos + 1;

		else high = pos - 1;
	}
	return -1;
}