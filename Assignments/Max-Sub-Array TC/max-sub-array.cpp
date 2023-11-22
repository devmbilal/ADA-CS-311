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
