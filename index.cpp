#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

struct GymRecord {
    int memberId;
    string memberName;
    int age;
    float weight;
};
void addnewRecord(const GymRecord& record);
void updateRecord(int memberId);
void deleteRecord(int memberId);
void searchRecord(int memberId);
void existingmember();
void clearScreen();
void displayMenu();
void validateInput(string& variable, const string& prompt, int width);
bool IsAllDigits(const string& str); 
int GetValidInput();

int main() 
{
    cout << "\n\t\t\t\t\t Welcome to Fitness First Gym\n\n";
    int choice;
    bool invalidInput;

    do {
        displayMenu();
        cout << "Enter your choice: ";
 
        invalidInput = false;
        if (!(cin >> choice) || cin.peek() != '\n') {
            invalidInput = true;
            cout << "Invalid input. Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (!invalidInput) {
            switch (choice) {
                case 1: {
                    GymRecord newRecord;
                    cout << "Enter Member ID: ";
                    while (!(cin >> newRecord.memberId) || newRecord.memberId < 1 || cin.peek() != '\n') {
                        cout << "Invalid input. Enter a positive integer for Member ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    ifstream inFile("gym_records.txt");
                    GymRecord record;
                    bool idExists = false;
                    while (inFile >> record.memberId >> record.memberName >> record.age >> record.weight ) {
                        if (record.memberId == newRecord.memberId) {
                            idExists = true;
                            break;
                        }
                    }
                    inFile.close();

                    if (idExists) {
                        cout << "Member ID already exists. Please choose a different ID.\n";
                        existingmember();
                        cout<<"These are the existing record Make different id from them.\n ";
                        break;
                    }

                    cin.ignore();
                    validateInput(newRecord.memberName, "(Note: Enter name without whitespace use '_' instead of whitespace) \nEnter Member Name : ", 10);

                    cout << "Enter Age: ";
                    while (!(cin >> newRecord.age) || newRecord.age < 1 || cin.peek() != '\n') {
                        cout << "Invalid input. Enter a positive integer for Age: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    cout << "Enter Weight: ";
                    while (!(cin >> newRecord.weight) || newRecord.weight < 1 || cin.peek() != '\n') {
                        cout << "Invalid input. Enter a positive number for Weight: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    addnewRecord(newRecord);
                    break;
                }
                case 2: {
                    int memberId;
                    cout << "Enter Member ID to update: ";
                    while (!(cin >> memberId) || memberId < 1 || cin.peek() != '\n') {
                        cout << "Invalid input. Enter a positive integer for Member ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    updateRecord(memberId);
                    break;
                }
                case 3: {
                    int memberId;
                    cout << "Enter Member ID to delete: ";
                    while (!(cin >> memberId) || memberId < 1 || cin.peek() != '\n') {
                        cout << "Invalid input. Enter a positive integer for Member ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    deleteRecord(memberId);
                    break;
                }
                case 4: {
                    int memberId;
                    cout << "Enter Member ID to search: ";
                    while (!(cin >> memberId) || memberId < 1 || cin.peek() != '\n') {
                        cout << "Invalid input. Enter a positive integer for Member ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    searchRecord(memberId);
                    break;
                }
                case 5:
                    existingmember(); 
                    break;
                case 6:
                    clearScreen();
                    break;
                case 7:
                    cout << "Exiting the program.\n";
                    break;
                default: {
                    cout << "Invalid choice. Please try again.\n";
                    invalidInput = true;
                    break;
                }
            }
        }
    } while (choice != 7 || invalidInput);

    return 0;
}

void displayMenu() {
    cout << "    Menu:\n";
    cout << "1. New Record\n";
    cout << "2. Update Record\n";
    cout << "3. Delete Record\n";
    cout << "4. Search Record\n";
    cout << "5. Existing Members\n";
    cout << "6. Clear screen\n";
    cout << "7. Exit\n";
}

void addnewRecord(const GymRecord& record) {
    ofstream outFile("gym_records.txt", ios::app);
    if (outFile.is_open()) {
        outFile <<"  "<<record.memberId << "   " << record.memberName << "   " << record.age << "    " << record.weight << "\n";
        cout << "Record saved successfully.\n";
        outFile.close();
    } else {
        cout << "Error opening file for saving record.\n";
    }
}

void updateRecord(int memberId) {

    ifstream inFile("gym_records.txt");
    ofstream outFile("temp.txt");

    if (inFile.is_open() && outFile.is_open()) {
        GymRecord record;
        bool found = false;

        while (inFile >> record.memberId >> record.memberName >> record.age >> record.weight) {
            if (record.memberId == memberId) {
                found = true;

                cout << "Enter updated Member Name: ";
                cin.ignore(); 
                getline(cin, record.memberName);

                cout << "Enter updated Age: ";
                while (!(cin >> record.age) || record.age < 1 || cin.peek() != '\n') {
                    cout << "Invalid input. Enter a positive integer for Age: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Enter updated Weight: ";
                while (!(cin >> record.weight) || record.weight < 1 || cin.peek() != '\n') {
                    cout << "Invalid input. Enter a positive number for Weight: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Record updated successfully.\n";
            }

            outFile << record.memberId << "   " << record.memberName << "   " << record.age << "    " << record.weight << "\n";
        }

        if (!found) {
            cout << "Record not found.\n";
        }

        inFile.close();
        outFile.close();

        remove("gym_records.txt");
        rename("temp.txt", "gym_records.txt");
    } else {
        cout << "Error opening files for updating record.\n";
    }
}

void deleteRecord(int memberId) {

    ifstream inFile("gym_records.txt");
    ofstream outFile("temp.txt");

    if (inFile.is_open() && outFile.is_open()) {
        GymRecord record;
        bool found = false;

        while (inFile >> record.memberId >> record.memberName >> record.age >> record.weight) {
            if (record.memberId == memberId) {
                found = true;
                cout << "Record deleted successfully.\n";
            }
            else {
                outFile << record.memberId << "   " << record.memberName << "   " << record.age << "   " << record.weight << "\n";
            }
        }

        if (!found) {
            cout << "Record not found.\n";
        }

        inFile.close();
        outFile.close();

        remove("gym_records.txt");
        rename("temp.txt", "gym_records.txt");
    } else {
        cout << "Error opening files for deleting record.\n";
    }
}

void searchRecord(int memberId) {
    ifstream inFile("gym_records.txt");
    if (inFile.is_open()) {
        GymRecord record;
        bool found = false;

        while (inFile >> record.memberId >> record.memberName >> record.age >> record.weight) {
            if (record.memberId == memberId) {
                found = true;
                cout << "Record found:\n";
                cout << "Member ID: " << record.memberId << "\n";
                cout << "Member Name: " << record.memberName << "\n";
                cout << "Age: " << record.age << "\n";
                cout << "Weight: " << record.weight << "\n";
                break;
            }
        }

        if (!found) {
            cout << "Record not found.\n";
        }

        inFile.close();
    } else {
        cout << "Error opening file for searching record.\n";
    }
}

void existingmember() {
    ifstream inFile("gym_records.txt");
    if (inFile.is_open()) {
        GymRecord record;

        cout << "\nReport of all records:\n";
        cout << "--------------------------------------------------------------\n";
        cout << "Member ID\tMember Name\t\tAge\tWeight\n";
        cout << "--------------------------------------------------------------\n";

        while (inFile >> record.memberId >> record.memberName >> record.age >> record.weight) {
            cout <<setw(16)<<left<<setfill(' ')<<record.memberId
                 <<setw(24)<<left<<setfill(' ') <<record.memberName 
                 <<setw(9)<<left<<setfill(' ')<< record.age 
                 <<setw(4)<<left<<setfill(' ')<<record.weight << "\n";
        }

        cout << "--------------------------------------------------------------\n";

        inFile.close();
    } else {
        cout << "Error opening file for displaying report.\n";
    }
}

void clearScreen() {
    system("cls");
    cout<<"\n\t\t\t\t\t Wellcome to Fitness First Gym\n\n";
}

void validateInput(string& variable, const string& prompt , int width) {
    cout << prompt;
    cout<< setfill(' ') << left << setw(width) ;
    cin >> variable;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}