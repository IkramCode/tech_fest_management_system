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

bool validateDate(char* date) {
    int day = 0, month = 0, year = 0;
    int i = 0, c = 0;
    int len = strLen(date);
    if (len < 8 || len > 10)
        return false;

    while (date[i] != '/' && date[i] != '\0') {
        if (date[i] < '0' || date[i] > '9')
            return false;
        day = day * 10 + (date[i] - '0');
        c++;
        i++;
    }
    if (date[i] != '/' || c == 0 || c > 2)
        return false;
    i++;
    c = 0;

    while (date[i] != '/' && date[i] != '\0') {
        if (date[i] < '0' || date[i] > '9')
            return false;
        month = month * 10 + (date[i] - '0');
        c++;
        i++;
    }
    if (date[i] != '/' || c == 0 || c > 2)
        return false;
    i++;
    c = 0;

    while (date[i] != '\0') {
        if (date[i] < '0' || date[i] > '9')
            return false;
        year = year * 10 + (date[i] - '0');
        c++;
        i++;
    }
    if (c != 4)
        return false;

    if (year < 2025 || year > 2035 || month < 1 || month > 12 || day < 1)
        return false;

    int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day > maxDays[month - 1])
        return false;

    return true;
}
