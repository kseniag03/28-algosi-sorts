/*
1) АиСД-2, 2023, задание 1
2) Ганина Ксения Андреевна 212
3) CLion
4) 28 удар... 13 сортировок, замеры времени
   функция проверки упорядоченности элементов массива
   генерация массивов
   вывод исходного массива в input.txt, полученного в output.txt
   сохранение результатов замеров в файл .cvs
   счётчик эл-х операций
5) графики
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// shortened name for sorting function
using Func = std::function<void(std::vector<int>&, int&)>;

const std::string INPUT_FILENAME = "input.txt";
const std::string OUTPUT_FILENAME = "output.txt";
const std::string DATA_OUTPUT = "data.csv";

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

void selectionSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 2 + 2 * (n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        ++cnt;
        cnt += 2 + 2 * (n - i - 1);
        for (int j = i + 1; j < n; ++j) {
            ++cnt;
            if (a[j] < a[min]) {
                min = j;
                ++cnt;
            }
        }
        std::swap(a[i], a[min]);
        cnt += 3;
    }
}

// #2 bubble sort

void bubbleSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 2 + 2 * (n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cnt += 3 + 2 * (n - i - 1);
        for (int j = 0; j < n - i - 1; ++j) {
            cnt += 2;
            if (a[j] > a[j + 1]) {
                ++cnt;
                std::swap(a[j], a[j + 1]);
                cnt += 3;
            }
        }
    }
}

// #3 bubble sort with Aversion modification 1

void bubbleSortAversion1(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 2 + 2 * (n - 1);
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        ++cnt;
        cnt += 3 + 2 * (n - i - 1);
        for (int j = 0; j < n - i - 1; ++j) {
            cnt += 2;
            if (a[j] > a[j + 1]) {
                ++cnt;
                std::swap(a[j], a[j + 1]);
                cnt += 3;
                swapped = true;
                ++cnt;
            }
        }
        ++cnt;
        if (!swapped) {
            break;
        }
    }
}

// #4 bubble sort with Aversion modification 1 + 2

void bubbleSortAversion2(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    int new_n;
    cnt += 1;
    do {
        new_n = 0;
        ++cnt;
        cnt += 1 + 2 * (n - 1);
        for (int i = 1; i < n; ++i) {
            cnt += 2;
            if (a[i - 1] > a[i]) {
                ++cnt;
                std::swap(a[i - 1], a[i]);
                cnt += 3;
                new_n = i;
                ++cnt;
            }
        }
        n = new_n;
        cnt += 2;
    } while (new_n > 1);
}

// #5 insertion sort

void insertionSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 1 + 2 * (n - 1);
    for (int i = 1; i < n; ++i) {
        int j = i;
        ++cnt;
        while (j > 0 && a[j - 1] > a[j]) {
            cnt += 3;
            std::swap(a[j - 1], a[j]);
            cnt += 3;
            --j;
            ++cnt;
        }
    }
}

// #6 binary insertion sort

void binaryInsertionSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 1 + 2 * (n - 1);
    for (int i = 1; i < n; ++i) {
        int left = 0;
        int right = i;
        int middle = (left + right) / 2;
        int key = a[i];
        cnt += 6;
        while (left < right) {
            cnt += 2;
            if (key < a[middle]) {
                right = middle;
                ++cnt;
            } else {
                left = middle + 1;
                cnt += 2;
            }
            middle = (left + right) / 2;
            cnt += 3;
        }
        cnt += 1 + 2 * (i - left);
        for (int j = i; j > left; --j) {
            a[j] = a[j - 1];
            cnt += 2;
        }
        a[left] = key;
        ++cnt;
    }
}

// #7 counting sort stable
// does not deal with negative nums as task works with nums >= 0

void countingSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    int max = 0;
    cnt += 2 + 2 * n;
    for (int i = 0; i < n; ++i) {
        ++cnt;
        if (a[i] > max) {
            max = a[i];
            ++cnt;
        }
    }
    int k = max + 1;
    ++cnt;
    std::vector<int> b(n);
    std::vector<int> c(k);
    cnt += 2;
    cnt += 1 + 2 * n;
    for (int i = 0; i < n; ++i) {
        c[a[i]] += 1;
        cnt += 2;
    }
    cnt += 1 + 2 * (k - 1);
    for (int i = 1; i < k; ++i) {
        c[i] += c[i - 1];
        cnt += 2;
    }
    cnt += 2 + 2 * n;
    for (int i = n - 1; i >= 0; --i) {
        c[a[i]] -= 1;
        b[c[a[i]]] = a[i];
        cnt += 5;
    }
    cnt += 1 + 2 * n;
    for (int i = 0; i < n; ++i) {
        a[i] = b[i];
        ++cnt;
    }
}

// #8 radix sort by base 256
// does not deal with negative nums as task works with nums >= 0

void radixSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    std::vector<int> b(n);
    const int integer_bites = 4;
    const int base = 256;
    cnt += 2 + 2 * integer_bites;
    for (int i = 0; i < integer_bites; ++i) {
        std::vector<int> c(base, 0);
        ++cnt;
        const int mask = base - 1;
        cnt += 1 + 2 * n;
        for (int j = 0; j < n; ++j) {
            ++c[((a[j]) >> (i * 8)) & mask];
            cnt += 4;
        }
        cnt += 1 + 2 * (base - 1);
        for (int j = 1; j < base; ++j) {
            c[j] += c[j - 1];
            cnt += 2;
        }
        cnt += 2 + 2 * n;
        for (int j = n - 1; j >= 0; --j) {
            b[--c[((a[j]) >> (i * 8)) & mask]] = a[j];
            cnt += 5;
        }
        cnt += 1 + 2 * n;
        for (int j = 0; j < n; ++j) {
            a[j] = b[j];
            ++cnt;
        }
    }
}

// #9 merge sort

std::vector<int> merge(std::vector<int> &a, std::vector<int> &b, int &cnt) {
    int n = static_cast<int>(a.size());
    int m = static_cast<int>(b.size());
    int i = 0, j = 0;
    std::vector<int> c;
    cnt += 2;
    while (i < n && j < m) {
        cnt += 3;
        if (a[i] < b[j]) {
            c.push_back(a[i]);
            ++i;
            cnt += 2;
        } else {
            c.push_back(b[j]);
            ++j;
            cnt += 2;
        }
    }
    while (i < n) {
        c.push_back(a[i]);
        ++i;
        cnt += 3;
    }
    while (j < m) {
        c.push_back(b[j]);
        ++j;
        cnt += 3;
    }
    return c;
}

void mergeSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 1;
    if (n > 1) {
        int m = n / 2;
        std::vector<int> b(a.begin(), a.begin() + m);
        std::vector<int> c(a.begin() + m, a.end());
        cnt += 4;
        mergeSort(b, cnt);
        mergeSort(c, cnt);
        a = merge(b, c, cnt);
        ++cnt;
    }
}

// #10 quick sort (first element)

void quickSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    ++cnt;
    if (n <= 1) {
        return;
    }
    // choose first element as pivot
    int pivot = a[0];
    std::vector<int> left, right;
    cnt += 3 + 2 * (n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cnt += 2;
        if (a[i] < pivot) {
            left.push_back(a[i]);
        } else {
            right.push_back(a[i]);
        }
    }
    // recursively sort left and right subarrays
    quickSort(left, cnt);
    quickSort(right, cnt);
    a.clear();
    a.reserve(left.size() + right.size() + 1);
    a.insert(a.end(), left.begin(), left.end());
    a.push_back(pivot);
    a.insert(a.end(), right.begin(), right.end());
    cnt += n + static_cast<int>(left.size()) + 1 + static_cast<int>(right.size());
}

// #11 heap sort

void heapify(std::vector<int> &vec, int n, int i, int &cnt) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    cnt += 9;
    if (left < n && vec[largest] < vec[left]) {
        largest = left;
        ++cnt;
    }
    cnt += 2;
    if (right < n && vec[largest] < vec[right]) {
        largest = right;
        ++cnt;
    }
    ++cnt;
    if (largest != i) {
        int replace = vec[i];
        vec[i] = vec[largest];
        vec[largest] = replace;
        cnt += 3;
        heapify(vec, n, largest, cnt);
    }
}

void heapSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 3 + n;
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(a, n, i, cnt);
    }
    cnt += 1 + 2 * n;
    for (int i = n - 1; i >= 0; --i) {
        int replace = a[0];
        a[0] = a[i];
        a[i] = replace;
        cnt += 3;
        heapify(a, i, 0, cnt);
    }
}

// #12 shell sort (Ciura sequence)

const int ciuraSeq[20] = { 0, 1, 4, 10, 23, 57, 132, 301, 701, 1750, 4001,
                        10001, 20001, 50001, 100001, 200001, 500001, 1000001, 2000001 };

void shellSortWithCiura(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    int i, j, d, temp;
    cnt += 1;
    for (i = 19; ciuraSeq[i] > n; --i) {
        cnt += 2;
    }
    for (; i >= 0; --i) {
        cnt += 2;
        d = ciuraSeq[i];
        cnt += 2;
        for (j = d; j < n; ++j) {
            cnt += 2;
            temp = a[j];
            int k;
            cnt += 3;
            for (k = j; k >= d && temp < a[k - d]; k -= d) {
                cnt += 5;
                a[k] = a[k - d];
            }
            a[k] = temp;
            ++cnt;
        }
    }
}

// #13 shell sort (Shell sequence)

void shellSort(std::vector<int> &a, int &cnt) {
    int n = static_cast<int>(a.size());
    cnt += 2;
    for (int d = n / 2; d > 0; d /= 2) {
        cnt += 3 + 2 * (n - d);
        for (int i = d; i < n; ++i) {
            int temp = a[i];
            int j;
            cnt += 3;
            for (j = i; j >= d && a[j - d] > temp; j -= d) {
                cnt += 5;
                a[j] = a[j - d];
            }
            a[j] = temp;
            ++cnt;
        }
    }
}

// generate arrays

std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> > generateVec(int n, int type) {
    std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> > vec_with_list;
    std::vector<int> vec(n);
    int start = 0;
    int end = 5;
    if (type == 4) {
        start = 1;
        end = 4100;
    } else if (type == 2 || type == 3) {
        end = 4000;
    }
    srand(time(nullptr));
    for (int & i : vec) {
        i = rand() % end + start;
    }
    if (type == 3) {
        // after sorting do the "sueta"...
        std::sort(vec.begin(), vec.end());
        int swaps_cnt = n / 10;
        srand(time(nullptr));
        for (int i = 0; i < swaps_cnt; ++i) {
            int x = rand() % n;
            int y = rand() % n;
            std::swap(vec[x], vec[y]);
        }
    } else if (type == 4) {
        std::sort(vec.begin(), vec.end());
        std::reverse(vec.begin(), vec.end());
    }
    vec_with_list.first = vec;
    std::vector<int> cnt(SORTS_CNT);
    vec_with_list.second.second = cnt;
    return vec_with_list;
}

std::vector< std::vector< std::vector< std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> > > > > getVecData() {
    std::vector< std::vector< std::vector<
            std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> >
            > > > vec_data;
    for (int range = 1; range <= 2; ++range) {
        int size_begin = 50;
        int size_end = 300;
        int step = 50;
        if (range > 1) {
            size_begin = 100;
            size_end = 4100;
            step = 100;
        }
        std::vector< std::vector< std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> > > > vec_list;
        for (int type = 1; type <= 4; ++type) {
            std::vector< std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> > > vec_list_type;
            for (int size = size_begin; size <= size_end; size += step) {
                auto vec = generateVec(size, type);
                vec_list_type.push_back(vec);
            }
            vec_list.push_back(vec_list_type);
        }
        vec_data.push_back(vec_list);
    }
    return vec_data;
}

// write array's content to files (.txt or .cvs)

void outputVec(const std::vector<int>& vec, const std::string& filename) {
    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        for (int i : vec) {
            outfile << i << " ";
        }
        outfile << "\n\n";
        outfile.close();
    }
}

// create a map to write sorts names in table

const std::map<int, std::string> sorts_names = {
        { 1, "select" },
        { 2, "bubble" }, { 3, "Aversion1" }, { 4, "Aversion2" },
        { 5, "insert" }, { 6, "binaryInsert" },
        { 7, "count" }, { 8, "radix" },
        { 9, "merge" }, { 10, "quick" }, { 11, "heap" },
        { 12, "shellCiura" }, { 13, "shell" },
};

void outputVecPair(const std::vector< std::vector< std::vector<
        std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> >
                > > > &data, const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        for (int measure_type = 0; measure_type < 2; ++measure_type) {
            outfile << " ;";
            for (int i = 0; i < SORTS_CNT; ++i) {
                outfile << sorts_names.at(i + 1) << ";";
            }
            outfile << "\n";
            for (int range = 0; range < data.size(); ++range) {
                for (int type = 0; type < data[range].size(); ++type) {
                    for (int v = 0; v < data[range][type].size(); ++v) {
                        outfile << v + 1 << ";";
                        auto pair = data[range][type][v];
                        for (int i = 0; i < SORTS_CNT; ++i) {
                            outfile << ( (measure_type == 0) ? pair.second.first[i] : pair.second.second[i] );
                            if (i < SORTS_CNT - 1) {
                                outfile << ";";
                            }
                        }
                        outfile << "\n";
                    }
                    outfile << "\n";
                }
                outfile << "\n";
            }
            outfile << "\n\n";
        }
        outfile.close();
        std::cout << "Array written to file " << filename << std::endl;
    } else {
        std::cerr << "Error: unable to open file " << filename << std::endl;
    }
}

// launching sort processes functions

const Func sorts[SORTS_CNT] = {
        selectionSort,
        bubbleSort, bubbleSortAversion1, bubbleSortAversion2,
        insertionSort, binaryInsertionSort,
        countingSort, radixSort,
        mergeSort, quickSort, heapSort,
        shellSortWithCiura, shellSort
};

void getSortsTime(const std::vector<int> &a, std::vector<std::vector<int64_t>> &sorts_ns, std::vector<int> &cnt) {
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
            cnt[i] = 0;
            clock_gettime(CLOCK_MONOTONIC, &start);
            sort(copy_vec, cnt[i]);
            clock_gettime(CLOCK_MONOTONIC, &end);
            elapsed_ns = timespecDifference(end, start);
            sorts_ns[i][j] = elapsed_ns;
            if (j == 0) {
                outputVec(copy_vec, OUTPUT_FILENAME);
            }
        }
    }
}

void launchSorts(std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> > &vec) {
    outputVec(vec.first, INPUT_FILENAME);
    std::vector<std::vector<int64_t>> sorts_ns(SORTS_CNT, std::vector<int64_t>(MEASUREMENTS_CNT));
    getSortsTime(vec.first, sorts_ns, vec.second.second);
    std::vector<double> average_sorts_ns(SORTS_CNT);
    for (int i = 0; i < sorts_ns.size(); ++i) {
        int64_t sum = 0;
        for (auto x : sorts_ns[i]) {
            sum += x;
        }
        average_sorts_ns[i] = static_cast<double>(sum) / MEASUREMENTS_CNT;
    }
    vec.second.first = average_sorts_ns;
    for (int i = 0; i < SORTS_CNT; ++i) {
        std::cout << "#" << i + 1 << ": " << average_sorts_ns[i] << "\n";
    }
}

// main

int main() {
    // clear files
    std::ofstream infile(INPUT_FILENAME, std::ios_base::trunc);
    infile.close();
    std::ofstream outfile(OUTPUT_FILENAME, std::ios_base::trunc);
    outfile.close();

    std::ofstream datafile(DATA_OUTPUT, std::ios_base::trunc);
    datafile.close();

    auto data = getVecData();
    for (int range = 0; range < data.size(); ++range) {
        std::cout << ( (range == 0) ? "50-300-50" : "100-4100-100" ) << "\n\n";
        for (int type = 0; type < data[range].size(); ++type) {
            switch (type) {
                case 0:
                    std::cout << "0-5 range array\n";
                    break;
                case 1:
                    std::cout << "0-4000 range array\n";
                    break;
                case 2:
                    std::cout << "almost sorted array\n";
                    break;
                case 3:
                    std::cout << "array sorted in descending order\n";
                    break;
                default:
                    break;
            }
            for (int v = 0; v < data[range][type].size(); ++v) {
                std::cout << "vector #" << v + 1 << "\n\n";
                launchSorts(data[range][type][v]);
            }
        }
    }
    outputVecPair(data, DATA_OUTPUT);
    return 0;
}
