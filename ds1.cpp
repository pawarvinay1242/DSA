#include<iostream>
#include<algorithm>
#include<string>
#include<chrono> // Added for real-time performance measurement

using namespace std;

// Define the structure first
struct Student {
    int id;
    string name;
    float cgpa;
};

// Linear Search by Student ID
int linearSearch(Student s[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (s[i].id == key)
            return i;
    }
    return -1;
}

// Binary Search by Student ID (Requires array to be sorted by ID first)
int binarySearch(Student s[], int n, int key) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (s[mid].id == key)
            return mid;
        if (key < s[mid].id)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

// Bubble Sort to sort students alphabetically by Name
void bubbleSortName(Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j].name > s[j + 1].name) {
                swap(s[j], s[j + 1]);
            }
        }
    }
}

// Selection Sort to sort students by CGPA ascending
void selectionSortCGPA(Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (s[j].cgpa < s[min].cgpa)
                min = j;
        }
        swap(s[i], s[min]);
    }
}

int main() {
    int n;
    cout << "Enter Number of Students : ";
    cin >> n;

    Student *s = new Student[n];

    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << endl;
        cout << "ID : ";
        cin >> s[i].id;
        cout << "Name : ";
        cin >> s[i].name;
        cout << "CGPA : ";
        cin >> s[i].cgpa;
    }

    cout << "\nStudent Records\n";
    for (int i = 0; i < n; i++) {
        cout << s[i].id << " " << s[i].name << " " << s[i].cgpa << endl;
    }

    int key;
    cout << "\nEnter ID to Search : ";
    cin >> key;

    // =========================================================================
    // 1. Linear Search (Before ID Sorting)
    // =========================================================================
    auto startLinear = chrono::high_resolution_clock::now();
    int posLinear = linearSearch(s, n, key);
    auto stopLinear = chrono::high_resolution_clock::now();
    auto durationLinear = chrono::duration_cast<chrono::nanoseconds>(stopLinear - startLinear);

    if (posLinear != -1)
        cout << "Found using Linear Search at index " << posLinear << endl;
    else
        cout << "Not Found using Linear Search" << endl;

    // 2. Bubble Sort by Name
    bubbleSortName(s, n);
    cout << "\nSorted by Name\n";
    for (int i = 0; i < n; i++) {
        cout << s[i].id << " " << s[i].name << " " << s[i].cgpa << endl;
    }

    // 3. Selection Sort by CGPA
    selectionSortCGPA(s, n);
    cout << "\nSorted by CGPA\n";
    for (int i = 0; i < n; i++) {
        cout << s[i].id << " " << s[i].name << " " << s[i].cgpa << endl;
    }

    // =========================================================================
    // 4. Binary Search (After ID Sorting)
    // =========================================================================
    // We also track how long the sorting overhead itself takes
    auto startSort = chrono::high_resolution_clock::now();
    sort(s, s + n, [](Student a, Student b) {
        return a.id < b.id;
    });
    auto stopSort = chrono::high_resolution_clock::now();
    auto durationSort = chrono::duration_cast<chrono::nanoseconds>(stopSort - startSort);

    auto startBinary = chrono::high_resolution_clock::now();
    int posBinary = binarySearch(s, n, key);
    auto stopBinary = chrono::high_resolution_clock::now();
    auto durationBinary = chrono::duration_cast<chrono::nanoseconds>(stopBinary - startBinary);

    if (posBinary != -1)
        cout << "\nFound using Binary Search at index " << posBinary << endl;
    else
        cout << "\nNot Found using Binary Search" << endl;

    // =========================================================================
    // SEARCH PERFORMANCE COMPARISON ANALYSIS
    // =========================================================================
    cout << "\n=================================================================\n";
    cout << "          SEARCH PERFORMANCE COMPARISON REPORT                  \n";
    cout << "=================================================================\n";
    cout << "Search Type       | Setup Context | Time Complexity | Actual Runtime \n";
    cout << "------------------|---------------|-----------------|----------------\n";
    cout << "Linear Search     | Unsorted IDs  | O(n)            | " << durationLinear.count() << " ns\n";
    cout << "Binary Search     | Sorted IDs    | O(log n)        | " << durationBinary.count() << " ns\n";
    cout << "------------------|---------------|-----------------|----------------\n";
    cout << "Sorting Overhead  | std::sort     | O(n log n)      | " << durationSort.count() << " ns\n";
    cout << "=================================================================\n";
    cout << "ANALYSIS INSIGHTS:\n";
    cout << "1. For small inputs (N < 20), Linear Search can be faster because it\n";
    cout << "   avoids the " << durationSort.count() << " ns penalty required to sort the array.\n";
    cout << "2. For multiple searches or large datasets, sorting once to use \n";
    cout << "   Binary Search drops search lookups from linear scaling to logarithmic.\n";
    cout << "=================================================================\n";

    delete[] s;
    return 0;
}
