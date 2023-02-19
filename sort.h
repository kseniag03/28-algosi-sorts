#include <vector>

class Sort {
public:
    // checks if an array is sorted in ascending order
    static bool isAscending(std::vector<int>& a) {
        int n = static_cast<int>(a.size());
        for (int i = 1; i < n; ++i) {
            if (a[i] < a[i - 1]) {
                return false;
            }
        }
        return true;
    }

    // #1 selection sort
    static void selectionSort(std::vector<int> &a, int &cnt) {
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
    static void bubbleSort(std::vector<int> &a, int &cnt) {
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
    static void bubbleSortAversion1(std::vector<int> &a, int &cnt) {
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
    static void bubbleSortAversion2(std::vector<int> &a, int &cnt) {
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
    static void insertionSort(std::vector<int> &a, int &cnt) {
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
    static void binaryInsertionSort(std::vector<int> &a, int &cnt) {
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
    static void countingSort(std::vector<int> &a, int &cnt) {
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
    static void radixSort(std::vector<int> &a, int &cnt) {
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
    static void mergeSort(std::vector<int> &a, int &cnt) {
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
    static void quickSort(std::vector<int> &a, int &cnt) {
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
    static void heapSort(std::vector<int> &a, int &cnt) {
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
    static void shellSortWithCiura(std::vector<int> &a, int &cnt) {
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
    static void shellSort(std::vector<int> &a, int &cnt) {
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

private:
    // private constructor
    Sort() = default;

    constexpr const static int ciuraSeq[20] = { 0, 1, 4, 10, 23, 57, 132, 301, 701, 1750, 4001,
                                                10001, 20001, 50001, 100001, 200001, 500001, 1000001, 2000001 };

    static std::vector<int> merge(std::vector<int> &a, std::vector<int> &b, int &cnt) {
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

    static void heapify(std::vector<int> &vec, int n, int i, int &cnt) {
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
};
