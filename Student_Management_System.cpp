#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
using namespace std;

class Student {
    int roll;
    string name;
    float marks1, marks2, marks3; 
    char grade;

public:
    void input();
    void display() const;
    int getRoll() const { return roll; }
    void calculateGrade();

    // Encryption/Decryption
    string encrypt(const string &text, int key = 3);
    string decrypt(const string &text, int key = 3);

    void saveToFile();
    bool loadFromFile(const string &line);
    string toLine();
};

void Student::input() {
    cout << "Enter Roll No: ";
    while (!(cin >> roll) || roll <= 0) {
        cout << "Invalid Roll No. Enter positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Marks for 3 subjects (0-100): ";
    while (!(cin >> marks1 >> marks2 >> marks3) ||
           marks1 < 0 || marks1 > 100 ||
           marks2 < 0 || marks2 > 100 ||
           marks3 < 0 || marks3 > 100) {
        cout << "Invalid input. Enter marks between 0-100: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    calculateGrade();
}

void Student::calculateGrade() {
    float avg = (marks1 + marks2 + marks3) / 3.0;
    if (avg >= 90) grade = 'A';
    else if (avg >= 75) grade = 'B';
    else if (avg >= 50) grade = 'C';
    else grade = 'F';
}

void Student::display() const {
    cout << left << setw(10) << roll
         << setw(20) << name
         << setw(10) << marks1
         << setw(10) << marks2
         << setw(10) << marks3
         << setw(10) << grade << endl;
}

string Student::encrypt(const string &text, int key) {
    string result = text;
    for (char &c : result) {
        c = c + key;
    }
    return result;
}

string Student::decrypt(const string &text, int key) {
    string result = text;
    for (char &c : result) {
        c = c - key;
    }
    return result;
}

string Student::toLine() {
    return to_string(roll) + "|" + name + "|" +
           to_string(marks1) + "|" + to_string(marks2) + "|" +
           to_string(marks3) + "|" + grade;
}

void Student::saveToFile() {
    ofstream fout("students.txt", ios::app);
    if (!fout) {
        cout << "Error opening file!" << endl;
        return;
    }
    fout << encrypt(toLine()) << endl;
    fout.close();
}

bool Student::loadFromFile(const string &line) {
    string decrypted = decrypt(line);
    if (decrypted.empty()) return false;

    size_t pos = 0;
    vector<string> fields;
    string temp = decrypted;
    while ((pos = temp.find("|")) != string::npos) {
        fields.push_back(temp.substr(0, pos));
        temp.erase(0, pos + 1);
    }
    if (!temp.empty()) fields.push_back(temp);

    if (fields.size() != 6) return false;

    roll = stoi(fields[0]);
    name = fields[1];
    marks1 = stof(fields[2]);
    marks2 = stof(fields[3]);
    marks3 = stof(fields[4]);
    grade = fields[5][0];

    return true;
}

// ======= HELPER FUNCTIONS =======
void displayAll() {
    ifstream fin("students.txt");
    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    cout << left << setw(10) << "Roll"
         << setw(20) << "Name"
         << setw(10) << "Marks1"
         << setw(10) << "Marks2"
         << setw(10) << "Marks3"
         << setw(10) << "Grade" << endl;
    cout << string(70, '-') << endl;

    string line;
    Student s;
    while (getline(fin, line)) {
        if (s.loadFromFile(line)) s.display();
    }
    fin.close();
}

void searchStudent(int rollNo) {
    ifstream fin("students.txt");
    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    bool found = false;
    string line;
    Student s;
    while (getline(fin, line)) {
        if (s.loadFromFile(line) && s.getRoll() == rollNo) {
            cout << "Student found:\n";
            cout << left << setw(10) << "Roll"
                 << setw(20) << "Name"
                 << setw(10) << "Marks1"
                 << setw(10) << "Marks2"
                 << setw(10) << "Marks3"
                 << setw(10) << "Grade" << endl;
            cout << string(70, '-') << endl;
            s.display();
            found = true;
            break;
        }
    }
    fin.close();

    if (!found) cout << "Student not found!\n";
}

void updateStudent(int rollNo) {
    ifstream fin("students.txt");
    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    vector<string> lines;
    string line;
    Student s;
    bool updated = false;

    while (getline(fin, line)) {
        if (s.loadFromFile(line) && s.getRoll() == rollNo) {
            cout << "Enter new details:\n";
            s.input();
            lines.push_back(s.encrypt(s.toLine()));
            updated = true;
        } else {
            lines.push_back(line);
        }
    }
    fin.close();

    ofstream fout("students.txt");
    for (auto &l : lines) fout << l << endl;
    fout.close();

    if (updated) cout << "Record updated successfully!\n";
    else cout << "Student not found!\n";
}

void deleteStudent(int rollNo) {
    ifstream fin("students.txt");
    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    vector<string> lines;
    string line;
    Student s;
    bool deleted = false;

    while (getline(fin, line)) {
        if (s.loadFromFile(line) && s.getRoll() == rollNo) {
            deleted = true;
            continue; 
        }
        lines.push_back(line);
    }
    fin.close();

    ofstream fout("students.txt");
    for (auto &l : lines) fout << l << endl;
    fout.close();

    if (deleted) cout << "Record deleted successfully!\n";
    else cout << "Student not found!\n";
}

// ======= MAIN MENU =======
void menu() {
    int choice;
    do {
        system("cls"); // clear screen (Windows)
        cout << "===== Student Management System =====" << endl;
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            s.input();
            s.saveToFile();
            cout << "Student added successfully!\n";
            system("pause");
        }
        else if (choice == 2) {
            displayAll();
            system("pause");
        }
        else if (choice == 3) {
            int r; cout << "Enter Roll No to search: "; cin >> r;
            searchStudent(r);
            system("pause");
        }
        else if (choice == 4) {
            int r; cout << "Enter Roll No to update: "; cin >> r;
            updateStudent(r);
            system("pause");
        }
        else if (choice == 5) {
            int r; cout << "Enter Roll No to delete: "; cin >> r;
            deleteStudent(r);
            system("pause");
        }

    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
