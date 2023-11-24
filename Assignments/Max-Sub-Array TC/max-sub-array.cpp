#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include<chrono>
#include <limits>

using namespace std;


int generateRandomNum() {
    return rand() % 2001 - 1000;
}

void createFile(int n) {
    string filename = "file_" + to_string(n) + ".txt";

    ofstream file(filename);

    file << n << endl;

    for (int i = 0; i < n; ++i) {
        int num = generateRandomNum();
        if (num < 0)
        file << num << " ";
    }

    file.close();
}

int maxSubArrayBF(int nums[], int n) {
    int maxSum = 0;
    for (int i = 0; i < n; i++) {
        int currSum = 0;
        for (int j = i; j < n; j++) {
            currSum += nums[j];
            if (currSum > maxSum)
                maxSum = currSum;
        }
    }
    return maxSum;
}

int maxCrossing(int arr[], int low, int mid, int high) {
    int leftSum = std::numeric_limits<int>::min();
    int sum = 0;
    int i = mid;

    while (i >= low) {
        sum += arr[i];
        if (sum > leftSum)
            leftSum = sum;
        --i;
    }

    int rightSum = std::numeric_limits<int>::min();
    sum = 0;
    int j = mid + 1;

   
    while (j <= high) {
        sum += arr[j];
        if (sum > rightSum)
            rightSum = sum;
        ++j;
    }

    return leftSum + rightSum;
}


int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

int maxSubArrayDC(int A[], int low, int high)
{
    if (high == low)
        return A[high];

    int mid = (high + low) / 2;

    int left = maxSubArrayDC(A, low, mid);
    int right = maxSubArrayDC(A, mid + 1, high);
    int  crossings = maxCrossing(A, low, mid, high);

    return maximum(maximum(left, right), crossings);
}



int main() {

    srand(time(0));

    int sizes[] = { 10, 15, 20, 30, 40, 50, 60, 70, 80, 100, 100, 200, 250, 300, 350, 400, 450, 500, 750, 1000 };

    for (int size : sizes) {
        createFile(size);
    }

    for (int size : sizes) {
        string filename = "file_" + to_string(size) + ".txt";
        ifstream file(filename);
        int n;
        file >> n;

        int* nums = new int[n];
        for (int i = 0; i < n; ++i) {
            file >> nums[i];
        }

        file.close();

        auto start = chrono::high_resolution_clock::now();
        // Find maximum subarray using Brute Force approach
        int maxSumBF = maxSubArrayBF(nums, n);
        auto end = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::microseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        // Find maximum subarray using Divide and Conquer approach
        int maxSumDC = maxSubArrayDC(nums, 0, n - 1);
        end = chrono::high_resolution_clock::now();
        auto durationDC = chrono::duration_cast<chrono::microseconds>(end - start).count();

        delete[] nums; // Deallocate the dynamically allocated array

        cout << "File size: " << size << endl;
        cout << "Brute Force Max Sum: " << maxSumBF << " Execution Time: " << durationBF << " microseconds" << endl;
        cout << "Divide and Conquer Max Sum: " << maxSumDC << " Execution Time: " << durationDC << " microseconds" << endl;
    }

    return 0;
}