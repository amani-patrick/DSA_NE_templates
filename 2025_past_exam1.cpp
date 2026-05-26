// ================================================================
//  RWANDA MINISTRY OF INFRASTRUCTURE
//  Cities & Roads Management System
//  Compile: g++ -std=c++17 -o program program.cpp
// ================================================================

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

// ---------- GLOBAL DATA STRUCTURES ----------
vector<string> cities;                  // 0-based internally; displayed as 1-based
vector<vector<int>> roadMatrix;         // adjacency matrix: 0 = no road, 1 = road exists
vector<vector<double>> budgetMatrix;    // adjacency matrix: budget in Billion RWF

// ---------- FORMATTING CONSTANTS ----------
const int CITY_NAME_WIDTH = 12;
const int MATRIX_CELL_WIDTH = 8;
const int BUDGET_PRECISION = 1;

// ================================================================
//  HELPER FUNCTIONS
// ================================================================

// Clear cin fail state and discard invalid input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Trim leading and trailing whitespace from a string
string trim(const string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(static_cast<unsigned char>(str[start]))) {
        ++start;
    }
    size_t end = str.length();
    while (end > start && isspace(static_cast<unsigned char>(str[end - 1]))) {
        --end;
    }
    return str.substr(start, end - start);
}
// Get a validated integer within [min, max]
int getValidInteger(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cout << "Invalid input. Please enter an integer between "
                 << min << " and " << max << "." << endl;
            clearInputBuffer();
        } else {
            clearInputBuffer(); // consume trailing newline for getline safety
            return value;
        }
    }
}

// Get a validated positive double
double getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0.0) {
            cout << "Invalid input. Budget must be a positive number." << endl;
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

// Validate city name: non-empty, only letters and hyphens
bool isValidCityName(const string& name) {
    if (name.empty()) return false;
    for (char ch : name) {
        if (!isalpha(static_cast<unsigned char>(ch)) && ch != '-') {
            return false;
        }
    }
    return true;
}

// Convert string to lowercase (for case-insensitive comparison)
string toLowercase(const string& str) {
    string lower = str;
    for (char& ch : lower) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return lower;
}

// Check if a city name already exists (case-insensitive)
bool cityExists(const string& name) {
    string lowerName = toLowercase(name);
    for (const string& city : cities) {
        if (toLowercase(city) == lowerName) {
            return true;
        }
    }
    return false;
}

// Get a valid NEW city name (format + uniqueness check)
string getValidNewCityName(const string& prompt) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);
        name = trim(name); 
        if (!isValidCityName(name)) {
            cout << "Error: City name must contain only letters and hyphens, "
                 << "and cannot be empty." << endl;
        } else if (cityExists(name)) {
            cout << "Error: City '" << name << "' already exists. "
                 << "Duplicate cities are not allowed." << endl;
        } else {
            return name;
        }
    }
}

// Get index of existing city (case-insensitive), returns -1 if not found
int getCityIndex(const string& name) {
    string lowerName = toLowercase(name);
    for (size_t i = 0; i < cities.size(); ++i) {
        if (toLowercase(cities[i]) == lowerName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Get a validated EXISTING city name from user
string getValidExistingCityName(const string& prompt) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);
        name=trim(name);
        int idx = getCityIndex(name);
        if (idx == -1) {
            cout << "Error: City '" << name << "' not found. "
                 << "Please enter a valid city name." << endl;
        } else {
            return cities[idx]; // return with original casing
        }
    }
}

// Resize matrices when a new city is added
void resizeMatrices() {
    size_t n = cities.size();
    roadMatrix.resize(n);
    for (size_t i = 0; i < n; ++i) {
        roadMatrix[i].resize(n, 0);
    }
    budgetMatrix.resize(n);
    for (size_t i = 0; i < n; ++i) {
        budgetMatrix[i].resize(n, 0.0);
    }
}

// ================================================================
//  MENU FUNCTIONS
// ================================================================

// Choice 1: Add new city(ies)
void addCities() {
    int count = getValidInteger("Enter number of cities to add: ", 1, 999);
    int added = 0;
    for (int c = 0; c < count; ++c) {
        cout << "\n--- City " << (c + 1) << " of " << count << " ---" << endl;
        string name = getValidNewCityName("Enter city name: ");
        cities.push_back(name);
        resizeMatrices();
        ++added;
    }
    cout << "\n>> " << added << " city/cities added successfully.\n" << endl;
}

// Choice 2: Add road between two cities
void addRoad() {
    if (cities.size() < 2) {
        cout << "Error: At least 2 cities are required to add a road." << endl;
        return;
    }
    cout << "\n--- Add Road Between Cities ---" << endl;
    string city1 = getValidExistingCityName("Enter first city name: ");
    string city2 = getValidExistingCityName("Enter second city name: ");
    if (city1 == city2) {
        cout << "Error: Cannot add a road between the same city." << endl;
        return;
    }
    int i = getCityIndex(city1);
    int j = getCityIndex(city2);
    if (roadMatrix[i][j] == 1) {
        cout << "Error: A road already exists between " << city1
             << " and " << city2 << "." << endl;
        return;
    }
    roadMatrix[i][j] = 1;
    roadMatrix[j][i] = 1;
    cout << ">> Road added successfully between " << city1
         << " and " << city2 << "." << endl;
}

// Choice 3: Add budget for a road
void addBudget() {
    if (cities.size() < 2) {
        cout << "Error: At least 2 cities are required to add a budget." << endl;
        return;
    }
    cout << "\n--- Add Budget for Road ---" << endl;
    string city1 = getValidExistingCityName("Enter first city name: ");
    string city2 = getValidExistingCityName("Enter second city name: ");
    if (city1 == city2) {
        cout << "Error: Cannot add a budget for the same city." << endl;
        return;
    }
    int i = getCityIndex(city1);
    int j = getCityIndex(city2);
    if (roadMatrix[i][j] == 0) {
        cout << "Error: No road exists between " << city1 << " and " << city2
             << ". Add a road first (Choice 2)." << endl;
        return;
    }
    if (budgetMatrix[i][j] > 0.0) {
        cout << "A budget of " << budgetMatrix[i][j]
             << " Billion RWF already exists. Overwriting..." << endl;
    }
    double budget = getValidDouble("Enter budget (in Billion RWF): ");
    budgetMatrix[i][j] = budget;
    budgetMatrix[j][i] = budget;
    cout << ">> Budget added successfully for " << city1 << "-" << city2
         << ": " << budget << " Billion RWF." << endl;
}

// Choice 6: Display list of cities
void displayCities() {
    cout << "\n--- List of Cities ---" << endl;
    if (cities.empty()) {
        cout << "No cities recorded." << endl;
        return;
    }
    cout << left << setw(8) << "Index" << "City_Name" << endl;
    cout << string(8 + CITY_NAME_WIDTH, '-') << endl;
    for (size_t i = 0; i < cities.size(); ++i) {
        cout << left << setw(8) << (i + 1) << cities[i] << endl;
    }
    cout << endl;
}


// Choice 4: Edit city name by index
void editCity() {
    if (cities.empty()) {
        cout << "Error: No cities recorded. Add cities first (Choice 1)." << endl;
        return;
    }
    cout << "\n--- Edit City ---" << endl;
    displayCities();
    int index = getValidInteger("Enter city index to edit: ", 1,
                                static_cast<int>(cities.size()));
    cout << "Current name: " << cities[index - 1] << endl;
    string newName = getValidNewCityName("Enter new city name: ");
    cities[index - 1] = newName;
    cout << ">> City updated successfully at index " << index << "." << endl;
}

// Choice 5: Search city by index
void searchCity() {
    if (cities.empty()) {
        cout << "Error: No cities recorded. Add cities first (Choice 1)." << endl;
        return;
    }
    cout << "\n--- Search City by Index ---" << endl;
    int index = getValidInteger("Enter city index to search: ", 1,
                                static_cast<int>(cities.size()));
    cout << "\n>> Search Result:" << endl;
    cout << "   Index: " << index << endl;
    cout << "   City:  " << cities[index - 1] << endl;
}



// Choice 7: Display roads adjacency matrix
void displayRoads() {
    if (cities.empty()) {
        cout << "Error: No cities recorded. Add cities first (Choice 1)." << endl;
        return;
    }
    cout << "\n==================== ROADS ADJACENCY MATRIX ====================" << endl;
    displayCities();

    size_t n = cities.size();
    int colWidth = max(CITY_NAME_WIDTH, MATRIX_CELL_WIDTH);

    // Column headers
    cout << setw(colWidth) << " ";
    for (size_t j = 0; j < n; ++j) {
        cout << setw(colWidth) << cities[j].substr(0, colWidth - 2);
    }
    cout << endl;

    // Matrix rows
    for (size_t i = 0; i < n; ++i) {
        cout << setw(colWidth) << cities[i].substr(0, colWidth - 2);
        for (size_t j = 0; j < n; ++j) {
            cout << setw(colWidth) << roadMatrix[i][j];
        }
        cout << endl;
    }
    cout << "\n(1 = Road exists, 0 = No road)" << endl;
}

// Save cities to cities.txt and roads to roads.txt
void saveToFiles() {
    // --- Save cities.txt ---
    ofstream cityFile("cities.txt");
    if (!cityFile) {
        cerr << "Error: Unable to create cities.txt" << endl;
        return;
    }
    cityFile << left << setw(8) << "Index" << "City_Name" << endl;
    cityFile << string(20, '-') << endl;
    for (size_t i = 0; i < cities.size(); ++i) {
        cityFile << left << setw(8) << (i + 1) << cities[i] << endl;
    }
    cityFile.close();

    // --- Save roads.txt ---
    ofstream roadFile("roads.txt");
    if (!roadFile) {
        cerr << "Error: Unable to create roads.txt" << endl;
        return;
    }
    roadFile << left << setw(6) << "Nbr" << setw(22) << "Road" << "Budget" << endl;
    roadFile << string(40, '-') << endl;

    int counter = 1;
    size_t n = cities.size();
    roadFile << fixed << setprecision(BUDGET_PRECISION);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {  // upper triangle only (undirected)
            if (roadMatrix[i][j] == 1) {
                string roadName = cities[i] + "-" + cities[j];
                roadFile << left << setw(6) << (to_string(counter) + ".")
                         << setw(22) << roadName
                         << budgetMatrix[i][j] << endl;
                ++counter;
            }
        }
    }
    roadFile.close();

    cout << "\n>> Data saved to cities.txt and roads.txt." << endl;
}

// Choice 8: Display all data (cities + roads matrix + budget matrix) and save to files
void displayAllData() {
    if (cities.empty()) {
        cout << "Error: No data recorded. Add cities first (Choice 1)." << endl;
        return;
    }
    size_t n = cities.size();
    int colWidth = max(CITY_NAME_WIDTH, MATRIX_CELL_WIDTH);

    cout << "\n==================== ALL RECORDED DATA ====================" << endl;

    // Cities
    displayCities();

    // Roads adjacency matrix
    cout << "\n--- Roads Adjacency Matrix ---" << endl;
    cout << setw(colWidth) << " ";
    for (size_t j = 0; j < n; ++j)
        cout << setw(colWidth) << cities[j].substr(0, colWidth - 2);
    cout << endl;
    for (size_t i = 0; i < n; ++i) {
        cout << setw(colWidth) << cities[i].substr(0, colWidth - 2);
        for (size_t j = 0; j < n; ++j)
            cout << setw(colWidth) << roadMatrix[i][j];
        cout << endl;
    }

    // Budget adjacency matrix
    cout << "\n--- Budget Adjacency Matrix (Billion RWF) ---" << endl;
    cout << fixed << setprecision(BUDGET_PRECISION);
    cout << setw(colWidth) << " ";
    for (size_t j = 0; j < n; ++j)
        cout << setw(colWidth) << cities[j].substr(0, colWidth - 2);
    cout << endl;
    for (size_t i = 0; i < n; ++i) {
        cout << setw(colWidth) << cities[i].substr(0, colWidth - 2);
        for (size_t j = 0; j < n; ++j)
            cout << setw(colWidth) << budgetMatrix[i][j];
        cout << endl;
    }
    cout << defaultfloat; // reset format

    // Save to files
    saveToFiles();
}

// ================================================================
//  FILE I/O FUNCTION
// ================================================================



// ================================================================
//  MAIN FUNCTION
// ================================================================

int main() {
    cout << "============================================================" << endl;
    cout << "  RWANDA MINISTRY OF INFRASTRUCTURE" << endl;
    cout << "  Cities & Roads Management System" << endl;
    cout << "============================================================" << endl;
    cout << "  Manage secondary cities connected to Kigali." << endl;
    cout << "  Budgets in Billion RWF." << endl;
    cout << "============================================================\n" << endl;

    int choice;
    do {
        cout << "\n==================== MAIN MENU ====================" << endl;
        cout << "  1. Add new city(ies)" << endl;
        cout << "  2. Add roads between cities" << endl;
        cout << "  3. Add the budget for roads" << endl;
        cout << "  4. Edit city" << endl;
        cout << "  5. Search for a city using its index" << endl;
        cout << "  6. Display cities" << endl;
        cout << "  7. Display roads" << endl;
        cout << "  8. Display recorded data on console" << endl;
        cout << "  9. Exit" << endl;
        cout << "====================================================" << endl;

        choice = getValidInteger("Enter your choice (1-9): ", 1, 9);

        switch (choice) {
            case 1: addCities(); break;
            case 2: addRoad(); break;
            case 3: addBudget(); break;
            case 4: editCity(); break;
            case 5: searchCity(); break;
            case 6: displayCities(); break;
            case 7: displayRoads(); break;
            case 8: displayAllData(); break;
            case 9:
                saveToFiles();
                cout << "\n>> Exiting program. Thank you for using the system!" << endl;
                cout << ">> Data saved to cities.txt and roads.txt." << endl;
                break;
        }
    } while (choice != 9);

    return 0;
}
