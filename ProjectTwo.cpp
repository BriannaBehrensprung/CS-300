//Author: Brianna Behrensprung 
//Date: October 10th, 2025 
//CS-300 Module Seven Project Two 
//Hash Table for Course Information/ Planner
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// Structure to hold course data
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Hash Table implementation using separate chaining
class HashTable {
private:
    vector<list<Course>> table;
    int size;

    // Simple ASCII hash function
    int HashFunction(const string& key) const {
        int sum = 0;
        for (char ch : key) {
            sum += static_cast<int>(ch);
        }
        return sum % size;
    }

public:
    // Constructor
    HashTable(int capacity = 40) {
        size = capacity;
        table.resize(size);
    }

    // Insert a course
    void Insert(const Course& course) {
        int index = HashFunction(course.courseNumber);
        table[index].push_back(course);
    }

    // Search for a course
    Course* Search(const string& courseNumber) {
        int index = HashFunction(courseNumber);
        for (auto& course : table[index]) {
            if (course.courseNumber == courseNumber) {
                return &course;
            }
        }
        return nullptr;
    }

    // Retrieve all courses
    vector<Course> GetAllCourses() const {
        vector<Course> allCourses;
        for (const auto& bucket : table) {
            for (const auto& course : bucket) {
                allCourses.push_back(course);
            }
        }
        return allCourses;
    }
};

// Function to load courses from a CSV file
HashTable LoadCoursesFromFile(const string& fileName) {
    ifstream file(fileName);
    HashTable ht(40);

    if (!file.is_open()) {
        cout << "Error: Could not open file '" << fileName << "'." << endl;
        return ht;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string item;
        vector<string> tokens;

        while (getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() < 2) {
            cout << "Skipping invalid line: " << line << endl;
            continue;
        }

        Course c;
        c.courseNumber = tokens[0];
        c.courseTitle = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            c.prerequisites.push_back(tokens[i]);
        }

        ht.Insert(c);
    }

    file.close();
    cout << "Courses successfully loaded from '" << fileName << "'." << endl;
    return ht;
}

// Print all courses in alphanumeric order
void PrintAllCourses(HashTable& ht) {
    vector<Course> allCourses = ht.GetAllCourses();
    sort(allCourses.begin(), allCourses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    cout << "\nCourse List (Alphanumeric Order):\n";
    for (const auto& course : allCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Print a single course’s details
void PrintCourseInfo(HashTable& ht, const string& courseNumber) {
    Course* course = ht.Search(courseNumber);

    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << "\n" << course->courseNumber << ", " << course->courseTitle << endl;
    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Display the program menu
void DisplayMenu() {
    cout << "\nWelcome to the Course Planner." << endl;
    cout << "1. Load course data" << endl;
    cout << "2. Print course list" << endl;
    cout << "3. Print course information" << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    HashTable courses;
    bool dataLoaded = false;

    while (true) {
        DisplayMenu();
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            // Automatically load from Courses.csv
            string defaultFile = "Courses.csv";
            courses = LoadCoursesFromFile(defaultFile);
            dataLoaded = true;
        }
        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Please load course data first." << endl;
            }
            else {
                PrintAllCourses(courses);
            }
        }
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Please load course data first." << endl;
            }
            else {
                cout << "Enter course number (e.g., CSCI200): ";
                string courseNumber;
                cin >> courseNumber;
                PrintCourseInfo(courses, courseNumber);
            }
        }
        else if (choice == 9) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid option. Try again." << endl;
        }
    }

    return 0;
}
