#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// --- Data Structures ---
struct Course {
    string code;
    int units;
    string lecturer;
};

struct Student {
    string name;
    string password;
    vector<Course> courses;
};

// --- Database Manager ---
class Database {
private:
    string filename = "db.txt";

public:
    vector<Student> students;

    // Load data from file (Format: Name|Password|CourseCode,Units,Lecturer;CourseCode,Units,Lecturer)
    void load() {
        students.clear();
        ifstream file(filename);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            Student s;
            stringstream ss(line);
            string segment;
            
            // 1. Name
            getline(ss, s.name, '|');
            // 2. Password
            getline(ss, s.password, '|');
            
            // 3. Courses (separated by ';')
            string coursesStr;
            getline(ss, coursesStr);
            
            stringstream ssCourses(coursesStr);
            string courseData;
            while(getline(ssCourses, courseData, ';')) {
                if(courseData.empty()) continue;
                stringstream ssC(courseData);
                string code, unitStr, lect;
                
                getline(ssC, code, ',');
                getline(ssC, unitStr, ',');
                getline(ssC, lect, ',');
                
                Course c;
                c.code = code;
                c.units = stoi(unitStr);
                c.lecturer = lect;
                s.courses.push_back(c);
            }
            students.push_back(s);
        }
        file.close();
    }

    // Save data to file
    void save() {
        ofstream file(filename);
        for (const auto& s : students) {
            file << s.name << "|" << s.password << "|";
            for (const auto& c : s.courses) {
                file << c.code << "," << c.units << "," << c.lecturer << ";";
            }
            file << endl;
        }
        file.close();
    }

    Student* findStudent(string name) {
        for (auto& s : students) {
            if (s.name == name) return &s;
        }
        return nullptr;
    }
};

// --- Application Logic ---
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader(string title) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "   COURSE MANAGEMENT SYSTEM (C++)" << endl;
    cout << "========================================" << endl;
    cout << "   " << title << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    Database db;
    db.load();
    
    while (true) {
        printHeader("MAIN MENU");
        cout << "1. Register / Add Course" << endl;
        cout << "2. Student Login (View Dashboard)" << endl;
        cout << "3. Exit" << endl;
        cout << "\nChoice: ";
        
        int choice;
        cin >> choice;
        cin.ignore(); // consume newline

        if (choice == 1) {
            printHeader("REGISTRATION");
            string name, pass, code, lect;
            int units;

            cout << "Enter Full Name: ";
            getline(cin, name);
            cout << "Enter Password: ";
            getline(cin, pass);

            Student* s = db.findStudent(name);
            
            // Validate user if exists
            if (s != nullptr) {
                if (s->password != pass) {
                    cout << "\n[ERROR] Incorrect Password!" << endl;
                    cout << "Press Enter to continue...";
                    cin.get();
                    continue;
                }
                cout << "\n[INFO] Welcome back, " << name << "!" << endl;
            } else {
                // Create new user
                Student newStudent;
                newStudent.name = name;
                newStudent.password = pass;
                db.students.push_back(newStudent);
                s = db.findStudent(name); // Point to the new student in vector
                cout << "\n[INFO] New profile created." << endl;
            }

            // Add Course
            cout << "\n--- Course Details ---" << endl;
            cout << "Course Code (e.g., CSC201): ";
            getline(cin, code);
            
            // Check Duplicate
            bool exists = false;
            for(const auto& c : s->courses) {
                if(c.code == code) exists = true;
            }

            if(exists) {
                cout << "\n[WARNING] You have already registered for " << code << endl;
            } else {
                cout << "Units: ";
                cin >> units;
                cin.ignore();
                cout << "Lecturer: ";
                getline(cin, lect);

                Course c = {code, units, lect};
                s->courses.push_back(c);
                db.save();
                cout << "\n[SUCCESS] Course Registered Successfully!" << endl;
            }
            cout << "Press Enter to continue...";
            cin.get();
        } 
        else if (choice == 2) {
            printHeader("LOGIN");
            string name, pass;
            cout << "Username: ";
            getline(cin, name);
            cout << "Password: ";
            getline(cin, pass);

            Student* s = db.findStudent(name);

            if (s != nullptr && s->password == pass) {
                // DASHBOARD
                while(true) {
                    printHeader("DASHBOARD - " + s->name);
                    cout << "Total Courses: " << s->courses.size() << endl;
                    
                    int totalUnits = 0;
                    cout << "\n%-10s %-10s %-20s\n", "CODE", "UNITS", "LECTURER";
                    cout << "----------------------------------------" << endl;
                    
                    if(s->courses.empty()) {
                        cout << "No courses found." << endl;
                    }

                    for(const auto& c : s->courses) {
                        cout << c.code << "\t   " << c.units << "\t      " << c.lecturer << endl;
                        totalUnits += c.units;
                    }
                    cout << "----------------------------------------" << endl;
                    cout << "Total Units: " << totalUnits << endl;

                    cout << "\n1. Logout" << endl;
                    cout << "Choice: ";
                    int dChoice;
                    cin >> dChoice;
                    cin.ignore();
                    if(dChoice == 1) break;
                }
            } else {
                cout << "\n[ERROR] Invalid Credentials." << endl;
                cout << "Press Enter to continue...";
                cin.get();
            }
        } 
        else if (choice == 3) {
            break;
        }
    }

    return 0;
}
