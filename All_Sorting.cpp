//
// Created by prince on 13-11-2024.
//
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void bubbleSort(int arr[], int n, int &swapCount) {
    int comp = 0;
    int swap = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comp++;
            if (arr[j] > arr[j + 1]) {
                swap++;
                swapCount++;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    cout << "Array sorted with Bubble Sort: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // cout << "Number of swap in Bubble Sort: " <<swap<<endl;
    // cout << "Number of comparisons in Bubble Sort: " << comp << endl;
}

void selectionSort(int arr[], int size, int &swapCount) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            swapCount++;
        }
    }
    cout << "Time Complexity: O(n^2)" << endl;
}

void insertionSort(int arr[], int size, int &swapCount) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            swapCount++;
        }
        arr[j + 1] = key; // This is not a swap, just an assignment, so we don't count it
    }
    cout << "Time Complexity: O(n^2)" << endl;
}

void merge(int arr[], int left, int mid, int right, int &swapCount) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = new int[n1];
    int *R = new int[n2];
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
            swapCount++;
        } else {
            arr[k++] = R[j++];
            swapCount++;
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right,int &swapCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid,swapCount);
        mergeSort(arr, mid + 1, right,swapCount);
        merge(arr, left, mid, right,swapCount);
    }
}

int partition(int arr[], int low, int high, int &swapCount) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swapCount++;
        }
    }
    swap(arr[i + 1], arr[high]);
    swapCount++;
    return i + 1;
}

void quickSort(int arr[], int low, int high, int &swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

void generateRandomArray(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    if (size <= 0) {
        cout << "Invalid size. Size must be greater than 0." << endl;
        return 1;
    }

    int *arr = new int[size];
    int *originalArr = new int[size];
    generateRandomArray(arr, size);

    for (int i = 0; i < size; ++i) {
        originalArr[i] = arr[i];
    }

    int choice;
    printArray(arr, size);
    do {
        cout << "\n1. Sorting By BubbleSort\n";
        cout << "2. Sorting By SelectionSort\n";
        cout << "3. Sorting By InsertionSort\n";
        cout << "4. Sorting By MergeSort\n";
        cout << "5. Sorting By QuickSort\n";
        cout << "6. Exit\n";
        cout << "Enter your choice for sorting the array: ";
        cin >> choice;

        for (int i = 0; i < size; ++i) {
            arr[i] = originalArr[i];
        }

        int swapCount = 0;
        auto start = chrono::high_resolution_clock::now();

        switch (choice) {
            case 1:
                bubbleSort(arr, size, swapCount);
                // printArray(arr, size);
                cout<<"bubble sorting\t";
                break;
            case 2:
                selectionSort(arr, size, swapCount);
                printArray(arr, size);
                cout<<"selection sorting\t";
                break;
            case 3:
                insertionSort(arr, size, swapCount);
                printArray(arr, size);
                cout<<"insertion sorting\t";
                break;
            case 4:
                mergeSort(arr, 0, size - 1 - swapCount, swapCount);
                printArray(arr, size);
             cout<<"merge sorting\t";
                cout << "Time Complexity: O(n log n)" << endl;
                break;
            case 5:
                quickSort(arr, 0, size -1, swapCount);
                printArray(arr, size);
                cout << "Quick Sort swaps: " << swapCount << endl;
                cout << "Time Complexity : O(n log n) on average" << endl;
                break;
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Total swaps: " << swapCount << endl;
        cout << "Sorting Time: " << duration.count() << " seconds" << endl;

    } while (choice != 8);

    delete[] arr;
    delete[] originalArr;
    return 0;
}