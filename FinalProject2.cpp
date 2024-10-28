// Name:  Jesse James Aranda
// Title: Project 2
// Date:  10/21/2024
// Class: CS-300 Analysis and Design

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Define the structure for a Course
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Define a Node for the BST
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Define the BST
class BST {
public:
    BST() : root(nullptr) {}

    void insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            insert(root, course);
        }
    }

    void inOrderTraversal() {
        inOrderTraversal(root);
    }

    Course* search(string courseNumber) {
        return search(root, courseNumber);
    }

private:
    Node* root;

    void insert(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                insert(node->left, course);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                insert(node->right, course);
            }
        }
    }

    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->course.courseNumber << ", " << node->course.courseName << endl;
            inOrderTraversal(node->right);
        }
    }

    Course* search(Node* node, string courseNumber) {
        if (node == nullptr) {
            return nullptr;
        }
        else if (node->course.courseNumber == courseNumber) {
            return &node->course;
        }
        else if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }
        else {
            return search(node->right, courseNumber);
        }
    }
};

// Function to load courses from a file into the BST
void loadCoursesFromFile(string filename, BST& bst) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseName, prereq;
        vector<string> prerequisites;

        getline(ss, courseNumber, ',');
        getline(ss, courseName, ',');

        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        Course course = { courseNumber, courseName, prerequisites };
        bst.insert(course);
    }

    file.close();
}

// Function to print course details
void printCourseInfo(BST& bst, string courseNumber) {
    Course* course = bst.search(courseNumber);
    if (course == nullptr) {
        cout << "Error: Course " << courseNumber << " not found" << endl;
    }
    else {
        cout << "Course Number: " << course->courseNumber << endl;
        cout << "Course Name: " << course->courseName << endl;
        cout << "Prerequisites: ";
        if (course->prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (string prereq : course->prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
}

// Function to display the menu
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Load Data" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
}

int main() {
    BST bst;
    int choice;
    string filename, courseNumber;

    while (true) {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename: ";
            cin >> filename;
            loadCoursesFromFile(filename, bst);
            break;
        case 2:
            bst.inOrderTraversal();
            break;
        case 3:
            cout << "Enter course number: ";
            cin >> courseNumber;
            printCourseInfo(bst, courseNumber);
            break;
        case 9:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Error: Invalid choice" << endl;
            break;
        }
    }

    return 0;
}
