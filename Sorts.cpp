#include <iostream>
#include <vector>

//Метод простого включения
template<typename T>
void SimpleInclusionSort(T* arr, size_t size) {
	for (size_t i = 1; i < size; ++i) {
		for (size_t j = 0; j < i; ++j) {
			if (arr[i] < arr[j]) {
				std::swap(arr[i], arr[j]);
			}
		}
	}
}
//Метод бинарных вставок
template<typename T>
void BinarySort(T* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        int pos = -1;
        int start = 0;
        int end = i - 1;
        T num_to_insert = arr[i];

        while (start <= end) {
            int middle = (start + end) / 2;
            if (num_to_insert > arr[middle])
                start = middle + 1;
            else if (num_to_insert < arr[middle])
                end = middle - 1;
            else {
                pos = middle;
                break;
            }
        }

        if (pos == -1) {
            pos = start;
        }

        if (pos < i) {
            for (size_t j = i; j > pos; --j) {
                arr[j] = arr[j - 1];
            }

            arr[pos] = num_to_insert;
        }
    }
}
//Метод Шелла
template<typename T>
void ShellSort(T* arr, size_t size) {
    for (size_t R = size / 2; R > 0; R /= 2) {
        for (size_t i = R; i < size; ++i) {
            T tmp = arr[i];
            size_t j;
            for (j = i; j >= R && arr[j - R] > tmp; j -= R) {
                arr[j] = arr[j - R];
            }
            arr[j] = tmp;
        }
    }
}
//Сортировка простым выбором (извлечением)
template<typename T>
void SelectionSort(T* arr, size_t size) {
    for (size_t i = 0; i < size-1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[min_idx], arr[i]);
    }
}
//Простая обменная сортировка
template<typename T>
void BubbleSort(T* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = (size - 1); j > i; --j) {
            if (arr[j] < arr[j-1]) {
                std::swap(arr[j], arr[j-1]);
            }
        }
    }
}
//Шейкерная сортировка
template<typename T>
void ShekerSort(T* arr, size_t size) {
    size_t left = 0, right = size - 1;
    int flag = 1;
    while ((left < right) && flag > 0) {
        flag = 0;
        for (size_t i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                flag = 1;
            }
        }
        --right;
        for (size_t i = right; i > left; i--) {
            if (arr[i - 1] > arr[i]) {
                std::swap(arr[i], arr[i - 1]);
                flag = 1;
            }
        }
        ++left;
    }
}
//Быстрая сортировка
template <typename T>
int partition(T* arr, int low, int high) {
    T pivot = arr[low];  // Опорный элемент
    int left = low + 1;
    int right = high;

    while (true) {
        // Находим первый элемент с левой стороны, который больше опорного
        while (left <= right && arr[left] <= pivot) {
            left++;
        }
        // Находим первый элемент с правой стороны, который меньше опорного
        while (left <= right && arr[right] >= pivot) {
            right--;
        }

        if (left > right) {
            break;
        }
        else {
            std::swap(arr[left], arr[right]);
        }
    }
    std::swap(arr[low], arr[right]);
    return right;
}
template <typename T>
void quickSort(T* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high); // Индекс опорного элемента
        quickSort(arr, low, pivotIndex - 1);        // Сортировка левой части
        quickSort(arr, pivotIndex + 1, high);       // Сортировка правой части
    }
}
// Естественное двухпутевое слияние
template <typename T>
void merge(T* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1);
    std::vector<T> R(n2);

    // Копируем данные в временные массивы L[] и R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    // Сливаем временные массивы обратно в arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Копируем оставшиеся элементы L[], если есть
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Копируем оставшиеся элементы R[], если есть
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}
template <typename T>
void naturalMergeSort(T* arr, int n) {
    std::vector<std::pair<int, int>> runs;

    // Находим естественные подмассивы
    int start = 0;
    while (start < n) {
        int end = start;
        while (end < n - 1 && arr[end] <= arr[end + 1]) {
            ++end;
        }
        runs.emplace_back(start, end);
        start = end + 1;
    }

    while (runs.size() > 1) {
        std::vector<std::pair<int, int>> newRuns;
        for (size_t i = 0; i < runs.size(); i += 2) {
            if (i + 1 < runs.size()) {
                int left = runs[i].first;
                int mid = runs[i].second;
                int right = runs[i + 1].second;
                merge(arr, left, mid, right);
                newRuns.emplace_back(left, right);
            }
            else {
                newRuns.push_back(runs[i]);
            }
        }
        runs = newRuns;
    }
}
// Простое двухпутевое слияние
template <typename T>
void merge2(T* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1);
    std::vector<T> R(n2);

    // Копируем данные в временные массивы L[] и R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    // Сливаем временные массивы обратно в arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Копируем оставшиеся элементы L[], если есть
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Копируем оставшиеся элементы R[], если есть
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}
// Рекурсивная функция сортировки слиянием
template <typename T>
void mergeSort2(T* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Сортируем первую и вторую половины
        mergeSort2(arr, left, mid);
        mergeSort2(arr, mid + 1, right);

        // Сливаем отсортированные половины
        merge2(arr, left, mid, right);
    }
}