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
