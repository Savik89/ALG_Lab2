#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// поиск minrun
static int getMinRun(int n){
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n = n / 2;
    }
    return n + r;
}

static void insertSort(vector<int>& arr, int start, int end) {
    for (int i = start; i < end; i++){
        int k = arr[i];
        int j = i - 1;
        while (j >= start and arr[j] > k){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = k;
    }
}

static void mergeSort(vector<int>& arr, int left, int mid, int right) {
    int sizeL = mid - left + 1;
    int sizeR = right - mid;
    vector<int> Left(sizeL), Right(sizeR);

    for (int i = 0; i < sizeL; i++) {
        Left[i] = arr[left + i];
    }
    for (int j = 0; j < sizeR; j++) {
        Right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0;
    int curr = left;
    int gallopCountLeft = 0, gallopCountRight = 0;
    const int gallopLimit = 7;

    while (i < sizeL && j < sizeR) {
        if (Left[i] <= Right[j]) {
            arr[curr++] = Left[i++];
            gallopCountLeft++;
            gallopCountRight = 0;
        }
        else {
            arr[curr++] = Right[j++];
            gallopCountRight++;
            gallopCountLeft = 0;
        }

        if (gallopCountLeft >= gallopLimit) {
            while (i < sizeL && (j >= sizeR || Left[i] <= Right[j])) {
                arr[curr++] = Left[i++];
            }
            gallopCountLeft = 0;
        }

        if (gallopCountRight >= gallopLimit) {
            while (j < sizeR && (i >= sizeL || Right[j] < Left[i])) {
                arr[curr++] = Right[j++];
            }
            gallopCountRight = 0;
        }
    }

    while (i < sizeL) {
        arr[curr++] = Left[i++];
    }
    while (j < sizeR) {
        arr[curr++] = Right[j++];
    }
}

static void timSort(vector<int>& arr) {
    int n = arr.size();
    int minRun = getMinRun(n);

    for (int i = 0; i < n; i += minRun) {
        int end = min(i + minRun, n);
        insertSort(arr, i, end);
    }

    for (int size = minRun; size < n; size *= 2) {
        for (int start = 0; start < n; start += 2 * size) {
            int mid = min(start + size - 1, n - 1);
            int end = min(start + 2 * size - 1, n - 1);

            if (mid < end) {
                mergeSort(arr, start, mid, end);
            }
        }
    }
}

static void printArray(const vector<int>& arr) {
    for (auto& element: arr)
        cout << element << " ";
    cout << endl;
}

int main() {
    vector<int> arr;
    int length;
    int choice;
    cout << "Что будем делать?\n";
    cout << "1. Ввести вручную длины n\n";
    cout << "2. Заполнить массив длины n рандомными числами\n\n";
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "Введите длину массива: ";
        cin >> length;
        for (int i = 0; i < length; i++) {
            int a;
            cin >> a;
            arr.push_back(a);
        }
        break;
    case 2:
        cout << "Введите длину массива: ";
        cin >> length;
        for (int i = 0; i < length; i++) {
            arr.push_back(rand() % 1000);
        }
        break;
    }
    cout << "\nИсходный массив:\n";
    printArray(arr);
    cout << endl;
    timSort(arr);
    cout << "Отсортированный массив:\n";
    printArray(arr);
    return 0;
}