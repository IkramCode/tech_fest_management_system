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

void getValidDate(char* date) {
    while (true) {
        cout << "Date (DD/MM/YYYY): ";
        cin.ignore();
        cin.getline(date, 100);
        if (validateDate(date))
            break;
        cout << "Invalid date format. Try again." << endl;
    }
}

int timeSelect(int* timeSlots) {
    int op;
    cout << "Available Time Slots:" << endl;
    cout << "1. 09:00AM" << endl;
    cout << "2. 10:00AM" << endl;
    cout << "3. 12:00PM" << endl;
    cout << "4. 02:00PM" << endl;
    cout << "5. 03:00PM" << endl;
    cout << "Choose time slot: ";
    op = intValidation();
    while (op < 1 || op > 5) {
        cout << "Invalid choice, try again: ";
        op = intValidation();
    }
    return timeSlots[op - 1];
}

void getTime(int eventTime, char* timeStr) {
    switch (eventTime) {
    case 1:
        strCopy(timeStr, "09:00AM");
        break;
    case 2:
        strCopy(timeStr, "10:00AM");
        break;
    case 3:
        strCopy(timeStr, "12:00PM");
        break;
    case 4:
        strCopy(timeStr, "02:00PM");
        break;
    case 5:
        strCopy(timeStr, "03:00PM");
        break;
    default:
        strCopy(timeStr, "Invalid Slot");
        break;
    }
}

