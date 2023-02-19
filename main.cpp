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
#include "sort.h"

// shortened name for sorting function
using Func = std::function<void(std::vector<int>&, int&)>;

// files to output arrays (before and after)
const std::string INPUT_FILENAME = "input.txt";
const std::string OUTPUT_FILENAME = "output.txt";
// file to output sorts data
const std::string DATA_OUTPUT = "data.csv";

// for averaging time measurements
const int MEASUREMENTS_CNT = 10;
const int SORTS_CNT = 13;

// create a map to write sorts names in table
const std::map<int, std::string> sorts_names = {
        { 1, "select" },
        { 2, "bubble" }, { 3, "Aversion1" }, { 4, "Aversion2" },
        { 5, "insert" }, { 6, "binaryInsert" },
        { 7, "count" }, { 8, "radix" },
        { 9, "merge" }, { 10, "quick" }, { 11, "heap" },
        { 12, "shellCiura" }, { 13, "shell" },
};

// create an array of sorts implementing in task
const Func sorts[SORTS_CNT] = {
        Sort::selectionSort,
        Sort::bubbleSort, Sort::bubbleSortAversion1, Sort::bubbleSortAversion2,
        Sort::insertionSort, Sort::binaryInsertionSort,
        Sort::countingSort, Sort::radixSort,
        Sort::mergeSort, Sort::quickSort, Sort::heapSort,
        Sort::shellSortWithCiura, Sort::shellSort
};

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

// write array's content to files (.txt)
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

// write data's content to files (.csv)
void outputVecPair(const std::vector< std::vector< std::vector<
        std::pair< std::vector<int>, std::pair<std::vector<double>, std::vector<int>> >
                > > > &data, const std::string& filename) {
    int num = 0;
    for (int measure_type = 0; measure_type < 2; ++measure_type) {
        for (int range = 0; range < data.size(); ++range) {
            for (int type = 0; type < data[range].size(); ++type) {
                ++num;
                std::string file = "0" + std::to_string(num) + filename;
                std::ofstream outfile(file);
                switch (type) {
                    case 0:
                        outfile << "0-5\n";
                        break;
                    case 1:
                        outfile << "0-4000\n";
                        break;
                    case 2:
                        outfile << "almost-sorted\n";
                        break;
                    case 3:
                        outfile << "sorted-descend\n";
                        break;
                    default:
                        break;
                }
                outfile << " ;";
                for (int i = 0; i < SORTS_CNT; ++i) {
                    outfile << sorts_names.at(i + 1) << ";";
                }
                outfile << "\n";
                for (int v = 0; v < data[range][type].size(); ++v) {
                    int step = (range == 0) ? 50 : 100;
                    int arr_size = (v + 1) * step;
                    outfile << arr_size << ";";
                    auto pair = data[range][type][v];
                    for (int i = 0; i < SORTS_CNT; ++i) {
                        outfile << ( (measure_type == 0) ? pair.second.first[i] : pair.second.second[i] );
                        if (i < SORTS_CNT - 1) {
                            outfile << ";";
                        }
                    }
                    outfile << "\n";
                }
                outfile.close();
                std::cout << "Array written to file " << file << "\n";
            }
        }
    }
}

// calculates arrays-of-time-measurements and elemental-operations-count for sorts
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

// launching sort processes functions for current vector (changes values in data)
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
    // get data and change values for arrays
    auto data = getVecData();
    for (int range = 0; range < data.size(); ++range) {
        std::cout << ( (range == 0) ? "50-300-50" : "100-4100-100" ) << "\n\n";
        for (int type = 0; type < data[range].size(); ++type) {
            std::cout << "type #" << type + 1 << "\n\n";
            for (int v = 0; v < data[range][type].size(); ++v) {
                std::cout << "vector #" << v + 1 << "\n\n";
                launchSorts(data[range][type][v]);
            }
        }
    }
    outputVecPair(data, DATA_OUTPUT);
    return 0;
}
