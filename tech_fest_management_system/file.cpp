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

void writeEventToFile(char* name, char* date, char* timeStr) {
    ofstream fout("events.txt", ios::app);
    if (fout.is_open()) {
        fout << "Event Name: " << name << endl;
        fout << "Date: " << date << endl;
        fout << "Time: " << timeStr << endl;
        fout << "--------------------------" << endl;
        fout.close();
        cout << "Event saved to events.txt" << endl;
    }
    else {
        cout << "Error: Could not open events.txt for writing!" << endl;
    }
}

void writeParticipantToFile(char* name, char* roll, char* dept, char* contact,
    char* eventName, char* id) {
    ofstream fout("participants.txt", ios::app);
    if (fout.is_open()) {
        fout << "Name: " << name << endl;
        fout << "Roll Number: " << roll << endl;
        fout << "Department: " << dept << endl;
        fout << "Contact: " << contact << endl;
        fout << "Event: " << eventName << endl;
        fout << "Participation ID: " << id << endl;
        fout << "--------------------------" << endl;
        fout.close();
        cout << "Participant data saved to participants.txt" << endl;
    }
    else {
        cout << "Error: Could not open participants.txt for writing!" << endl;
    }
}

void intToStr(int num, char* str) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int temp = num;
    int digits = 0;
    while (temp > 0) {
        temp /= 10;
        digits++;
    }

    str[digits] = '\0';
    for (int i = digits - 1; i >= 0; i--) {
        str[i] = '0' + (num % 10);
        num /= 10;
    }
}

void writeScoresToFile(char* eventName, char** rolls, int* scores, int count) {
    ofstream fout("scores.txt", ios::app);
    if (fout.is_open()) {
        fout << "Scores for Event: " << eventName << endl;
        for (int i = 0; i < count; i++) {
            fout << rolls[i] << " : " << scores[i] << endl;
        }
        fout << "--------------------------" << endl;
        fout.close();
        cout << "Scores saved to scores.txt" << endl;
    }
    else {
        cout << "Error: Could not open scores.txt for writing!" << endl;
    }
}

void writeResultsToFile(char* eventName, char** rolls, int* scores, int* top) {
    ofstream fout("results.txt", ios::app);
    if (fout.is_open()) {
        fout << "Winners for " << eventName << endl;
        for (int i = 0; i < 3 && top[i] != -1; i++) {
            fout << i + 1 << ". " << rolls[top[i]] << " - " << scores[top[i]] << endl;
        }
        fout << "--------------------------" << endl;
        fout.close();
        cout << "Results saved to results.txt" << endl;
    }
    else {
        cout << "Error: Could not open results.txt for writing!" << endl;
    }
}

void generateCertificate(char* name, char* eventName, int position) {
    ofstream fout("certificates.txt", ios::app);
    if (fout.is_open()) {
        fout << "========================================" << endl;
        fout << "           CERTIFICATE OF ACHIEVEMENT" << endl;
        fout << "========================================" << endl;
        fout << endl;
        fout << "This is to certify that" << endl;
        fout << "        " << name << endl;
        fout << "has secured ";
        if (position == 1)
            fout << "1st Position";
        else if (position == 2)
            fout << "2nd Position";
        else if (position == 3)
            fout << "3rd Position";
        fout << " in" << endl;
        fout << "        " << eventName << endl;
        fout << endl;
        fout << "Congratulations on this achievement!" << endl;
        fout << endl;
        fout << "TechFest 2025" << endl;
        fout << "========================================" << endl;
        fout << endl;
        fout.close();
    }
    else {
        cout << "Error: Could not open certificates.txt for writing!" << endl;
    }
}

bool strComp(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    return *str1 == *str2; // Both should reach null terminator
}

bool uniqueRollNumber(char** rollNumbers, int count, const char* roll) {
    for (int i = 0; i < count; i++) {
        if (strComp(rollNumbers[i], roll)) {
            return false; // Roll number already exists
        }
    }
    return true; // Unique roll number
}

bool uniqueContact(char** contacts, int count, const char* contact) {
    for (int i = 0; i < count; i++) {
        if (strComp(contacts[i], contact)) {
            return false; // Contact already exists
        }
    }
    return true; // Unique contact
}

void getUniqueRollNumber(char** rollNumbers, int count, char* roll) {
    while (true) {
        cout << "Enter Roll Number: ";
        cin.getline(roll, 100);
        if (uniqueRollNumber(rollNumbers, count, roll)) {
            return; // Unique roll number found
        }
        cout << "Roll number already exists. Please enter a unique roll number." << endl;
    }
}

void getUniqueContact(char** contacts, int count, char* contact) {
    while (true) {
        cout << "Enter Contact: ";
        cin.getline(contact, 100);
        if (uniqueContact(contacts, count, contact)) {
            return; // Unique contact found
        }
        cout << "Contact already exists. Please enter a unique contact." << endl;
    }
}

void addEvent(const int maxEvents, int& eventCounter, char** eventNames, char** eventDates, int* timeSlots, int* eventTimes) {
    if (eventCounter < maxEvents) {
        cout << "Enter Event Name: ";
        cin.ignore();
        cin.getline(eventNames[eventCounter], 100);
        getValidDate(eventDates[eventCounter]);
        eventTimes[eventCounter] = timeSelect(timeSlots);
        char timeStr[20];
        getTime(eventTimes[eventCounter], timeStr);
        writeEventToFile(eventNames[eventCounter], eventDates[eventCounter], timeStr);
        cout << "Event Added Successfully." << endl;
        eventCounter++;
    }
    else {
        cout << "Maximum events reached." << endl;
    }
}

void registerParticipant(const int maxEvents, const int maxParticipants, int eventCounter, int& participantIDCounter,
    char** eventNames, char** names, char** rollNumbers, char** departments, char** contacts,
    int* participantCount) {
    if (eventCounter == 0) {
        cout << "Add at least one event first." << endl;
        return;
    }

    cout << "Select Event to Register In:" << endl;
    for (int i = 0; i < eventCounter; i++) {
        cout << i + 1 << ". " << eventNames[i] << endl;
    }
    cout << "Enter choice: ";
    int ev = intValidation();
    while (ev < 1 || ev > eventCounter) {
        cout << "Invalid event. Try again: ";
        ev = intValidation();
    }
    ev--;

    if (participantCount[ev] >= maxParticipants) {
        cout << "Event is full." << endl;
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(names[ev * maxParticipants + participantCount[ev]], 100);
    getUniqueRollNumber(rollNumbers + ev * maxParticipants, participantCount[ev],
        rollNumbers[ev * maxParticipants + participantCount[ev]]);
    cout << "Enter Department: ";
    cin.getline(departments[ev * maxParticipants + participantCount[ev]], 100);
    getUniqueContact(contacts + ev * maxParticipants, participantCount[ev],
        contacts[ev * maxParticipants + participantCount[ev]]);

    char id[100] = "TECHFEST-2025-";
    char buffer[10];
    intToStr(++participantIDCounter, buffer);
    strCopy(id + strLen(id), buffer);

    cout << "Participant Registered with ID: " << id << endl;
    writeParticipantToFile(
        names[ev * maxParticipants + participantCount[ev]],
        rollNumbers[ev * maxParticipants + participantCount[ev]],
        departments[ev * maxParticipants + participantCount[ev]],
        contacts[ev * maxParticipants + participantCount[ev]],
        eventNames[ev], id);
    participantCount[ev]++;
}

void submitScores(const int maxParticipants, int eventCounter, char** eventNames, char** names,
    char** rollNumbers, int* participantCount, int** scores) {
    if (eventCounter == 0) {
        cout << "No events available. Add events first." << endl;
        return;
    }

    for (int e = 0; e < eventCounter; e++) {
        if (participantCount[e] == 0) {
            cout << "No participants in " << eventNames[e] << ". Skipping..." << endl;
            continue;
        }

        cout << "\nEnter scores for " << eventNames[e] << ":" << endl;
        for (int p = 0; p < participantCount[e]; p++) {
            cout << "Participant " << names[e * maxParticipants + p] << " ("
                << rollNumbers[e * maxParticipants + p] << ") score (0-100): ";
            int s = intValidation();
            while (s < 0 || s > 100) {
                cout << "Invalid score. Try again (0-100): ";
                s = intValidation();
            }
            scores[e][p] = s;
        }
        writeScoresToFile(eventNames[e], &rollNumbers[e * maxParticipants],
            scores[e], participantCount[e]);
    }
    cout << "All scores submitted successfully." << endl;
}

void showWinnersAndGenerateCertificates(const int maxParticipants, int eventCounter, char** eventNames,
    char** names, char** rollNumbers, int* participantCount, int** scores) {
    if (eventCounter == 0) {
        cout << "No events available." << endl;
        return;
    }

    for (int e = 0; e < eventCounter; e++) {
        if (participantCount[e] == 0) {
            cout << "No participants in " << eventNames[e] << endl;
            continue;
        }

        cout << "\nTop 3 winners for " << eventNames[e] << ":" << endl;
        int top[3] = { -1, -1, -1 }, topScores[3] = { -1, -1, -1 };

        for (int p = 0; p < participantCount[e]; p++) {
            int score = scores[e][p];
            if (score > topScores[0]) {
                topScores[2] = topScores[1];
                top[2] = top[1];
                topScores[1] = topScores[0];
                top[1] = top[0];
                topScores[0] = score;
                top[0] = p;
            }
            else if (score > topScores[1]) {
                topScores[2] = topScores[1];
                top[2] = top[1];
                topScores[1] = score;
                top[1] = p;
            }
            else if (score > topScores[2]) {
                topScores[2] = score;
                top[2] = p;
            }
        }

        for (int i = 0; i < 3 && top[i] != -1; i++) {
            cout << i + 1 << ". " << names[e * maxParticipants + top[i]] << " ("
                << rollNumbers[e * maxParticipants + top[i]] << ") - "
                << topScores[i] << " points" << endl;

            generateCertificate(names[e * maxParticipants + top[i]],
                eventNames[e], i + 1);
        }

        writeResultsToFile(eventNames[e], &rollNumbers[e * maxParticipants],
            scores[e], top);
    }
    cout << "\nCertificates generated for all winners!" << endl;
}

int main() {
    const int maxEvents = 5;
    const int maxParticipants = 30;
    char** eventNames = new char* [maxEvents];
    char** eventDates = new char* [maxEvents];
    int* eventTimes = new int[maxEvents];
    int* participantCount = new int[maxEvents];
    int** scores = new int* [maxEvents];

    for (int i = 0; i < maxEvents; i++) {
        eventNames[i] = new char[100];
        eventDates[i] = new char[100];
        participantCount[i] = 0;
        scores[i] = new int[maxParticipants];
        for (int j = 0; j < maxParticipants; j++) {
            scores[i][j] = 0;
        }
    }

    char** rollNumbers = new char* [maxEvents * maxParticipants];
    char** names = new char* [maxEvents * maxParticipants];
    char** departments = new char* [maxEvents * maxParticipants];
    char** contacts = new char* [maxEvents * maxParticipants];

    for (int i = 0; i < maxEvents * maxParticipants; i++) {
        rollNumbers[i] = new char[100];
        names[i] = new char[100];
        departments[i] = new char[100];
        contacts[i] = new char[100];
    }

    int timeSlots[5] = { 1, 2, 3, 4, 5 };
    int eventCounter = 0, participantIDCounter = 0;

    while (true) {
        cout << endl;
        cout << "--- TechFest Management System ---" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. Register Participant" << endl;
        cout << "3. Submit Scores" << endl;
        cout << "4. Show Winners & Generate Certificates" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice = intValidation();

        if (choice == 1) {
            addEvent(maxEvents, eventCounter, eventNames, eventDates, timeSlots, eventTimes);
        }
        else if (choice == 2) {
            registerParticipant(maxEvents, maxParticipants, eventCounter, participantIDCounter,
                eventNames, names, rollNumbers, departments, contacts, participantCount);
        }
        else if (choice == 3) {
            submitScores(maxParticipants, eventCounter, eventNames, names, rollNumbers,
                participantCount, scores);
        }
        else if (choice == 4) {
            showWinnersAndGenerateCertificates(maxParticipants, eventCounter, eventNames, names,
                rollNumbers, participantCount, scores);
        }
        else if (choice == 5) {
            cout << "Thank you for using TechFest Management System!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Cleanup memory
    for (int i = 0; i < maxEvents; i++) {
        delete[] eventNames[i];
        delete[] eventDates[i];
        delete[] scores[i];
    }
    delete[] eventNames;
    delete[] eventDates;
    delete[] eventTimes;
    delete[] participantCount;
    delete[] scores;

    for (int i = 0; i < maxEvents * maxParticipants; i++) {
        delete[] rollNumbers[i];
        delete[] names[i];
        delete[] departments[i];
        delete[] contacts[i];
    }
    delete[] rollNumbers;
    delete[] names;
    delete[] departments;
    delete[] contacts;

    return 0;
}