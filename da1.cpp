#include <iostream>
//#include <fstream>

const unsigned short MAX_KEY = 65535;

void Resize(unsigned short*& arrayKey, unsigned long long*& arrayValue, size_t& size) {
    size_t newSize = size * 2;
    unsigned short* newArrayKey = new unsigned short[newSize];
    unsigned long long* newArrayValue = new unsigned long long[newSize];
    for (size_t i = 0; i < size; i++) {
        newArrayKey[i] = arrayKey[i];
        newArrayValue[i] = arrayValue[i];
    }
    delete[] arrayKey;
    delete[] arrayValue;
    arrayKey = newArrayKey;
    arrayValue = newArrayValue;
    size = newSize;
}

void CountingSort(unsigned short*& arrayKey, unsigned long long*& arrayValue,
    size_t size, unsigned short min, unsigned short max,
    unsigned short*& newArrayKey, unsigned long long*& newArrayValue, size_t*& count)
{
    for (size_t i = 0; i <= max; i++) {
        count[i] = 0;
    }
    for (size_t i = 0; i < size; i++) {
        count[arrayKey[i]]++;
    }
    for (size_t i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    for (size_t i = size - 1 + 1; i > 0; i--) {
        newArrayKey[count[arrayKey[i - 1]] - 1] = arrayKey[i - 1];
        newArrayValue[count[arrayKey[i - 1]] - 1] = arrayValue[i - 1];
        count[arrayKey[i - 1]]--;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    //std::ifstream fin("input.txt");
    //std::ofstream fout("output.txt");
    size_t size = 1000000;
    unsigned short* arrayKey = new unsigned short[size];
    unsigned long long* arrayValue = new unsigned long long[size];
    unsigned short key = 0;
    unsigned long long value = 0;
    unsigned short max = 0;
    unsigned short min = MAX_KEY;
    size_t iter = 0;
    bool isExist = false;
    while (std::cin >> key >> value) {
    //while (fin >> key >> value) {
        isExist = true;
        if (max < key) {
            max = key;
        }
        if (min >= key) {
            min = key;
        }
        if (iter >= size) {
            Resize(arrayKey, arrayValue, size);
        }
        arrayKey[iter] = key;
        arrayValue[iter] = value;
        iter++;
    }
    if (!isExist) {
        return 0;
    }
    unsigned short* newArrayKey = new unsigned short[size];
    unsigned long long* newArrayValue = new unsigned long long[size];
    size_t* count = new size_t[max + 1];
    CountingSort(arrayKey, arrayValue, iter, min, max, newArrayKey, newArrayValue, count);
    for (size_t i = 0; i < iter; i++) {
        std::cout << newArrayKey[i] << "\t" << newArrayValue[i] << "\n";
        //fout << newArrayKey[i] << "\t" << newArrayValue[i] << "\n";
    }
    delete[] arrayKey;
    delete[] arrayValue;
    delete[] newArrayKey;
    delete[] newArrayValue;
    delete[] count;
    //fin.close();
    //fout.close();
}
