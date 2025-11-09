
 

#include <iostream>
#include <cstring>   // for strcmp
#include <cstdlib>   // for malloc, realloc, free
using namespace std;

struct Student {
    int id;
    char name[50];
    float cgpa;
};

Student* students = NULL;
int sizeDB = 0;

void addStudent() {
    students = (Student*) realloc(students, (sizeDB + 1) * sizeof(Student));
    if (students == NULL) {
        cout << "Memory allocation failed!" << endl;
        exit(1);
    }
    cout << "\nEnter Student ID: ";
    cin >> students[sizeDB].id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(students[sizeDB].name, 50);
    cout << "Enter CGPA: ";
    cin >> students[sizeDB].cgpa;
    sizeDB++;
}

// Display all students
void displayStudents() {
    cout << "\n----------------------------------------\n";
    cout << "ID\tName\t\tCGPA\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < sizeDB; i++) {
        cout << students[i].id << "\t" << students[i].name << "\t\t" << students[i].cgpa << endl;
    }
    cout << "----------------------------------------\n";
}

// Linear Search by ID
int linearSearch(int key, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < sizeDB; i++) {
        comparisons++;
        if (students[i].id == key) return i;
    }
    return -1;
}

// Binary Search (array must be sorted by ID first)
int binarySearch(int key, int& comparisons) {
    int low = 0, high = sizeDB - 1, mid;
    comparisons = 0;
    while (low <= high) {
        mid = (low + high) / 2;
        comparisons++;
        if (students[mid].id == key) return mid;
        else if (students[mid].id < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Bubble Sort by Name (Alphabetical)
void bubbleSortByName() {
    for (int i = 0; i < sizeDB - 1; i++) {
        for (int j = 0; j < sizeDB - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    cout << "\nStudents sorted by Name (Alphabetical).\n";
}

// Selection Sort by CGPA
void selectionSortByCGPA(bool ascending) {
    for (int i = 0; i < sizeDB - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < sizeDB; j++) {
            if ((ascending && students[j].cgpa < students[idx].cgpa) ||
                (!ascending && students[j].cgpa > students[idx].cgpa)) {
                idx = j;
            }
        }
        if (idx != i) {
            Student temp = students[i];
            students[i] = students[idx];
            students[idx] = temp;
        }
    }
    cout << "\nStudents sorted by CGPA (" << (ascending ? "Ascending" : "Descending") << ").\n";
}

// Bubble Sort by ID (for binary search)
void sortByID() {
    for (int i = 0; i < sizeDB - 1; i++) {
        for (int j = 0; j < sizeDB - i - 1; j++) {
            if (students[j].id > students[j + 1].id) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    int choice, id, pos, comparisons;

    do {
        cout << "\n====== Student Database Menu ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Linear Search by ID\n";
        cout << "4. Binary Search by ID\n";
        cout << "5. Sort by Name (Bubble Sort)\n";
        cout << "6. Sort by CGPA (Selection Sort)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3:
                cout << "Enter ID to search: ";
                cin >> id;
                pos = linearSearch(id, comparisons);
                if (pos != -1)
                    cout << "Found: " << students[pos].name << " (CGPA: " << students[pos].cgpa << ") | Comparisons: " << comparisons << endl;
                else
                    cout << "ID not found | Comparisons: " << comparisons << endl;
                break;
            case 4:
                sortByID(); // must be sorted before binary search
                cout << "Enter ID to search: ";
                cin >> id;
                pos = binarySearch(id, comparisons);
                if (pos != -1)
                    cout << "Found: " << students[pos].name << " (CGPA: " << students[pos].cgpa << ") | Comparisons: " << comparisons << endl;
                else
                    cout << "ID not found | Comparisons: " << comparisons << endl;
                break;
            case 5: bubbleSortByName(); displayStudents(); break;
            case 6:
                cout << "1. Ascending\n2. Descending\nEnter option: ";
                cin >> id;
                selectionSortByCGPA(id == 1);
                displayStudents();
                break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 7);

    free(students);
    return 0;
}













Output:











 
