#include <fstream>
#include <iostream>
using namespace std;

int strLen(char* arr) {
    int len = 0;
    while (arr[len] != '\0')
        len++;
    return len;
}

void strCopy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int intValidation() {
    int num;
    cin >> num;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number: ";
        cin >> num;
    }
    return num;
}


