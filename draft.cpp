/*
1) АиСД-2, 2023, задание 1
2) Ганина Ксения Андреевна 212
3) CLion
4) 28 удар... 13 сортировок, замеры времени, сохранение результатов замеров в файл .cvs
   функция проверки упорядоченности элементов массива
5) генерация массивов, счётчик эл-х операций, графики,
   вывод исходного массива в input.txt, полученного в output.txt
*/

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
// #include <chrono> // ?

// shortened name for sorting function
using Func = std::function<void(std::vector<int>&)>;

const std::string INPUT_FILENAME = "input.txt";
const std::string OUTPUT_FILENAME = "output.txt";

const int MAX_VALUE = 4100;
const int SORTS_CNT = 13;
const int MEASUREMENTS_CNT = 10;

int64_t timespecDifference(struct timespec a, struct timespec b) {
    int64_t timeA, timeB;
    timeA = a.tv_sec;
    timeA *= 1000000000;
    timeA += a.tv_nsec;
    timeB = b.tv_sec;
    timeB *= 1000000000;
    timeB += b.tv_nsec;
    return timeA - timeB;
}

// checks if an array is sorted in ascending order
bool isAscending(std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i - 1]) {
            return false;
        }
    }
    return true;
}

// #1 selection sort

void selectionSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        std::swap(a[i], a[min]);
    }
}

// #2 bubble sort

void bubbleSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}

// #3 bubble sort with Aversion modification 1 // ?

void bubbleSortAversion1(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// #4 bubble sort with Aversion modification 1 + 2 // ?

void bubbleSortAversion2(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    int new_n;
    do {
        new_n = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i - 1] > a[i]) {
                std::swap(a[i - 1], a[i]);
                new_n = i;
            }
        }
        n = new_n;
    } while (new_n > 1);
}

// #5 insertion sort // ?

void insertionSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j > 0 && a[j - 1] > a[j]) {
            std::swap(a[j - 1], a[j]);
            --j;
        }
    }
}

// #6 binary insertion sort // ?

void binaryInsertionSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = 1; i < n; ++i) {
        int left = 0;
        int right = i;
        int middle = (left + right) / 2;
        int key = a[i];
        while (left < right) {
            if (key < a[middle]) {
                right = middle;
            } else {
                left = middle + 1;
            }
            middle = (left + right) / 2;
        }
        for (int j = i; j > left; --j) {
            a[j] = a[j - 1];
        }
        a[left] = key;
    }
}

// #7 counting sort stable // ? what to do with k...

void countingSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    int k = MAX_VALUE;
    int min = 1e9;
    for (int i = 0; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    std::vector<int> b(n, 0);
    std::vector<int> c(k, 0);
    for (int i = 0; i < n; ++i) {
        c[a[i] + abs(min)] = c[a[i] + abs(min)] + 1;
    }
    for (int i = 1; i < k; ++i) {
        c[i] = c[i] + c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        c[a[i] + abs(min)] = c[a[i] + abs(min)] - 1;
        b[c[a[i] + abs(min)]] = a[i];
    }
    for (int i = 0; i < n; ++i) {
        a[i] = b[i];
    }
}

// #8 radix sort by base 256

void radixSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    int min = 1e9;
    for (int i = 0; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    std::vector<int> b(n);
    const int integer_bites = 4;
    const int base = 256;
    for (int i = 0; i < integer_bites; ++i) {
        std::vector<int> c(base, 0);
        const int mask = base - 1;
        for (int j = 0; j < n; ++j) {
            ++c[((a[j] + abs(min)) >> (i * 8)) & mask];
        }
        for (int j = 1; j < base; ++j) {
            c[j] += c[j - 1];
        }
        for (int j = n - 1; j >= 0; --j) {
            b[--c[((a[j] + abs(min)) >> (i * 8)) & mask]] = a[j];
        }
        for (int j = 0; j < n; ++j) {
            a[j] = b[j];
        }
    }
}

// #9 merge sort

std::vector<int> merge(std::vector<int> &a, std::vector<int> &b) {
    int n = static_cast<int>(a.size());
    int m = static_cast<int>(b.size());
    int i = 0, j = 0;
    std::vector<int> c;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            c.push_back(a[i]);
            ++i;
        } else {
            c.push_back(b[j]);
            ++j;
        }
    }
    while (i < n) {
        c.push_back(a[i]);
        ++i;
    }
    while (j < m) {
        c.push_back(b[j]);
        ++j;
    }
    return c;
}

void mergeSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    if (n > 1) {
        int m = n / 2;
        std::vector<int> b(a.begin(), a.begin() + m);
        std::vector<int> c(a.begin() + m, a.end());
        mergeSort(b);
        mergeSort(c);
        a = merge(b, c);
    }
}

// #10 quick sort (first element)

void quickSort(std::vector<int> &a) {
    if (a.size() <= 1) {
        return;  // already sorted
    }
    int pivot = a[0];  // choose first element as pivot
    std::vector<int> left, right;
    for (int i = 0; i < a.size() - 1; ++i) {
        if (a[i] < pivot) {
            left.push_back(a[i]);
        } else {
            right.push_back(a[i]);
        }
    }
    quickSort(left);   // recursively sort left and right subarrays
    quickSort(right);
    a.clear();
    a.reserve(left.size() + right.size() + 1);
    a.insert(a.end(), left.begin(), left.end());
    a.push_back(pivot);
    a.insert(a.end(), right.begin(), right.end());
}

// #11 heap sort

void heapify(std::vector<int> &vec, int n, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < n && vec[largest] < vec[left]) {
        largest = left;
    }
    if (right < n && vec[largest] < vec[right]) {
        largest = right;
    }
    if (largest != i) {
        int replace = vec[i];
        vec[i] = vec[largest];
        vec[largest] = replace;
        heapify(vec, n, largest);
    }
}

void heapSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(a, n, i);
    }
    for (int i = n - 1; i >= 0; --i) {
        int replace = a[0];
        a[0] = a[i];
        a[i] = replace;
        heapify(a, i, 0);
    }
}

// #12 shell sort (Ciura sequence) // ???

const int ciuraSeq[20] = { 0, 1, 4, 10, 23, 57, 132, 301, 701, 1750, 4001,
                        10001, 20001, 50001, 100001, 200001, 500001, 1000001, 2000001 };

void shellSortWithCiura(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    int i, j, d, temp;
    for (i = 19; ciuraSeq[i] > n; --i);
    for (; i >= 0; --i) {
        d = ciuraSeq[i];
        for (j = d; j < n; ++j) {
            temp = a[j];
            int k;
            for (k = j; k >= d && temp < a[k - d]; k -= d)
                a[k] = a[k - d];
            a[k] = temp;
        }
    }
}

// #13 shell sort (Shell sequence) // ???

void shellSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int d = n / 2; d > 0; d /= 2) {
        for (int i = d; i < n; ++i) {
            int temp = a[i];
            int j;
            for (j = i; j >= d && a[j - d] > temp; j -= d) {
                a[j] = a[j - d];
            }
            a[j] = temp;
        }
    }
}

// generate array

// launching sort processes functions

const Func sorts[SORTS_CNT] = { selectionSort,
                                 bubbleSort, bubbleSortAversion1, bubbleSortAversion2,
                                 insertionSort, binaryInsertionSort,
                                 countingSort, radixSort,
                                 mergeSort, quickSort, heapSort,
                                 shellSortWithCiura, shellSort };

void getSortsTime(const std::vector<int> &a, std::vector<std::vector<int64_t>> &sorts_ns) {
    std::map<int, Func> s;
    for (int i = 0; i < SORTS_CNT; ++i) {
        s[i] = sorts[i];
    }
    for (int i = 0; i < sorts_ns.size(); ++i) {
        for (int j = 0; j < sorts_ns[i].size(); ++j) {
            struct timespec start{}, end{};
            int64_t elapsed_ns;
            auto copy_vec = a;
            auto sort = s[i];
            clock_gettime(CLOCK_MONOTONIC, &start);
            sort(copy_vec);
            clock_gettime(CLOCK_MONOTONIC, &end);
            elapsed_ns = timespecDifference(end, start);
            sorts_ns[i][j] = elapsed_ns;
            std::cout << "#" << i + 1 << " Sort: ";
            for (int x : copy_vec) {
                std::cout << x << " ";
            }
            std::cout << "\nSort time: " << elapsed_ns << " ns\n\n";
        }
    }
}

void launchSorts(const std::vector<int> &vec) {
    std::vector<std::vector<int64_t>> sorts_ns(SORTS_CNT, std::vector<int64_t>(MEASUREMENTS_CNT));
    getSortsTime(vec, sorts_ns);
    std::vector<double> average_sorts_ns(SORTS_CNT);
    for (int i = 0; i < sorts_ns.size(); ++i) {
        int64_t sum = 0;
        for (auto x : sorts_ns[i]) {
            sum += x;
        }
        average_sorts_ns[i] = static_cast<double>(sum) / MEASUREMENTS_CNT;
    }
    for (int i = 0; i < SORTS_CNT; ++i) {
        std::cout << "#" << i + 1 << ": " << average_sorts_ns[i] << "\n";
    }
    // return average_sorts_ns;
}

// write array's content to files (.txt or .cvs)

void outputVec(const std::vector<int>& vec, const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        for (int i = 0; i < vec.size(); i++) {
            outfile << vec[i] << " ";
        }
        outfile.close();
        std::cout << "Array written to file " << filename << std::endl;
    }
    else {
        std::cerr << "Error: unable to open file " << filename << std::endl;
    }
}

void writeSortsTime(std::vector<double> &ns) {
    // write values to file .cvs
}

// main

int main() {
    std::cout << "Sorting int array\n";
    std::vector<int> vec = { 1, 3, 2, 5, 4, -10, 0, 100, 99, 101, -27, -41, 4, 2 };
    std::cout << "\nBefore: \n";
    for (int i : vec) {
        std::cout << i << " ";
    }
    //outputVec(vec, INPUT_FILENAME);
    std::cout << "\n\nAfter: \n";
    launchSorts(vec);
    return 0;
}
