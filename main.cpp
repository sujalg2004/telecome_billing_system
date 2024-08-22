
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

class Subscriber {
public:
    string phoneNumber;
    string name;
    int planAmount;
    int amount;
    string status;
    string recordDate;
    string paymentDate;

    void addRecord();
    void displayRecord();
    void deleteRecord();
    void searchRecord();
    void modifyRecord();
    void makePayment();
    void writeToFile();
    void generateReport();
};
bool isAdminLogin() {     string adminId;     string password;      cout << "Enter Admin ID: ";     cin >> adminId;          while (adminId != "admin") {         cout << "Invalid Admin ID. Please enter the correct Admin ID: ";         cin >> adminId;     }      cout << "Enter Password: ";     cin >> password;      while (password != "1234") {         cout << "Invalid Password. Please enter the correct Password: ";         cin >> password;     }          return true; }
void Subscriber::addRecord() {
    while (true) {
        cout << "Enter Phone Number (10 digits): ";
        cin >> phoneNumber;

        if (phoneNumber.length() == 10 && all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {
            break;
        } else {
            cout << "Invalid phone number. Please enter a 10-digit number.\n";
        }
    }

    while (true) {
        cout << "Enter Name (up to 15 characters): ";
        cin >> name;

        if (name.length() <= 15 && std::all_of(name.begin(), name.end(), ::isalpha)) {
            break;
        } else {
            cout << "Invalid name. Please enter a name with up to 15 alphabetical characters.\n";
        }
    }

    cout << "Choose Subscription Duration:\n"
         "1. Monthly (Rs 199)\n"
         "2. Quarterly (Rs 499)\n"
         "3. Yearly (Rs 1199)\n";
    int durationChoice;
    cin >> durationChoice;

    switch (durationChoice) {
    case 1:
        planAmount = 199;
        break;
    case 2:
        planAmount = 499;
        break;
    case 3:
        planAmount = 1199;
        break;
    default:
        cout << "Invalid choice. Setting plan amount to 0\n";
        planAmount = 0;
    }

    amount = planAmount;
    status = "PENDING";

    time_t now = time(0);
    tm* ltm = localtime(&now);
    recordDate = to_string(1 + ltm->tm_mon) + '/' + to_string(ltm->tm_mday) + '/' + to_string(1900 + ltm->tm_year);
    paymentDate = "N/A"; 

    cout << "Record Added Successfully!\n";
}

void Subscriber::displayRecord() {
    cout << "----------------------------------------\n";
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Name: " << name << endl;
    cout << "Plan Amount: " << planAmount << endl;
    cout << "Due Amount: " << amount << endl;
    cout << "Payment Status: " << status << endl;
    cout << "Record Date: " << recordDate << endl;
    cout << "Payment Date: " << paymentDate << endl; 
    cout << "----------------------------------------\n";
}

void Subscriber::deleteRecord() {
    cout << "Enter Phone Number to Delete: ";
    string deletePhoneNumber;
    cin >> deletePhoneNumber;

    ifstream infile("records12.txt");
    ofstream temp("temp.txt");

    if (!infile) {
        cout << "Error opening the file!\n";
        return;
    }

    bool recordFound = false;
    while (infile >> phoneNumber >> name >> planAmount >> amount >> status >> recordDate >> paymentDate) {
        if (deletePhoneNumber == phoneNumber) {
            recordFound = true;
            char confirm;
            cout << "Are you sure you want to delete this record? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                cout << "Record Deleted Successfully!\n";
                continue;
            } else {
                cout << "Deletion cancelled.\n";
            }
        }
        temp << phoneNumber << " " << name << " " << planAmount << " " << amount << " " << status << " "
             << recordDate << " " << paymentDate << endl;
    }

    infile.close();
    temp.close();
    remove("records12.txt");
    rename("temp.txt", "records12.txt");

    if (!recordFound) {
        cout << "Record not found. Unable to delete.\n";
    }
}

void Subscriber::searchRecord() {
    string searchPhoneNumber;
    cout << "Enter Phone Number to Search: ";
    cin >> searchPhoneNumber;

    ifstream infile("records12.txt");

    if (!infile) {
        cout << "Error opening the file!\n";
        return;
    }

    bool recordFound = false;
    while (infile >> phoneNumber >> name >> planAmount >> amount >> status >> recordDate >> paymentDate) {
        if (searchPhoneNumber == phoneNumber) {
            recordFound = true;
            cout << "Search Results:\n";
            displayRecord();
        }
    }

    infile.close();

    if (!recordFound) {
        cout << "Record not found.\n";
    }
}

void Subscriber::modifyRecord() {
    cout << "Enter Phone Number to Modify: ";
    string modifyPhoneNumber;
    cin >> modifyPhoneNumber;

    ifstream infile("records12.txt");
    ofstream temp("temp.txt");

    if (!infile) {
        cout << "Error opening the file!\n";
        return;
    }

    bool recordFound = false;
    while (infile >> phoneNumber >> name >> planAmount >> amount >> status >> recordDate >> paymentDate) {
        if (modifyPhoneNumber == phoneNumber) {
            recordFound = true;
            cout << "Enter New Name: ";
            cin >> name;
            cout << "Enter New Plan Amount: ";
            cin >> planAmount;
            amount = planAmount;
            cout << "Record Modified Successfully!\n";
        }
        temp << phoneNumber << " " << name << " " << planAmount << " " << amount << " " << status << " "
             << recordDate << " " << paymentDate << endl;
    }

    infile.close();
    temp.close();
    remove("records12.txt");
    rename("temp.txt", "records12.txt");

    if (!recordFound) {
        cout << "Record not found. Unable to modify.\n";
    }
}

void Subscriber::makePayment() {
    cout << "Enter Phone Number to Make Payment: ";
    string paymentPhoneNumber;
    cin >> paymentPhoneNumber;

    ifstream infile("records12.txt");
    ofstream temp("temp.txt");

    if (!infile) {
        cout << "Error opening the file!\n";
        return;
    }

    bool recordFound = false;
    while (infile >> phoneNumber >> name >> planAmount >> amount >> status >> recordDate >> paymentDate) {
        if (paymentPhoneNumber == phoneNumber) {
            recordFound = true;
            int paymentAmount;
            cout << "Enter Payment Amount: ";
            cin >> paymentAmount;

            if (paymentAmount > 0 && paymentAmount <= amount) {
                amount -= paymentAmount;

                if (amount <= 0) {
                    amount = 0;
                    status = "PAID";
                }

                
                time_t now = time(0);
                tm* ltm = localtime(&now);
                paymentDate = to_string(1 + ltm->tm_mon) + '/' + to_string(ltm->tm_mday) + '/' + to_string(1900 + ltm->tm_year);

                cout << "Payment Successful!\n";
            } else {
                cout << "Invalid payment amount or exceeds due amount. Payment not processed.\n";
            }
        }
        temp << phoneNumber << " " << name << " " << planAmount << " " << amount << " " << status << " "
             << recordDate << " " << paymentDate << endl;
    }

    infile.close();
    temp.close();
    remove("records12.txt");
    rename("temp.txt", "records12.txt");

    if (!recordFound) {
        cout << "Record not found. Unable to make payment.\n";
    }
}



void Subscriber::writeToFile() {
    ofstream outfile("records12.txt", ios::app);
    outfile << phoneNumber << " " << name << " " << planAmount << " " << amount << " " << status << " "
            << recordDate << " " << paymentDate << endl;
    outfile.close();
}

void Subscriber::generateReport() {
    ifstream infile("records12.txt");
    if (!infile) {
        cout << "Error opening the file!\n";
        return;
    }

    cout << "----------------------------------------\n";
    cout << setw(15) << "Phone Number" << setw(15) << "Name" << setw(15) << "Plan Amount"
         << setw(15) << "Due Amount" << setw(15) << "Status" << setw(15) << "Record Date"
         << setw(15) << "Payment Date\n";
    cout << "----------------------------------------\n";

    while (infile >> phoneNumber >> name >> planAmount >> amount >> status >> recordDate >> paymentDate) {
        cout << setw(15) << phoneNumber << setw(15) << name << setw(15) << planAmount
             << setw(15) << amount << setw(15) << status << setw(15) << recordDate
             << setw(15) << paymentDate << endl;
    }

    infile.close();
}


int main() {
    cout << "WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM\n";
if (!isAdminLogin()) {         cout << "Invalid admin credentials. Exiting...\n";         return 0;     }
    int choice;

    Subscriber subscriber;

    while (true) {
        cout << "1. Add Record\n";
        cout << "2. Display Record\n";
        cout << "3. Delete Record\n";
        cout << "4. Search Record\n";
        cout << "5. Modify Record\n";
        cout << "6. Make Payment\n";
        cout << "7. Generate Report\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            subscriber.addRecord();
            subscriber.writeToFile();
            break;
        case 2:
            subscriber.displayRecord();
            break;
        case 3:
            subscriber.deleteRecord();
            break;
        case 4:
            subscriber.searchRecord();
            break;
        case 5:
            subscriber.modifyRecord();
            break;
        case 6:
            subscriber.makePayment();
            break;
        case 7:
            subscriber.generateReport();
            break;
        case 8:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}                                 
