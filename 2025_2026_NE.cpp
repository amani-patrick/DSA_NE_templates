#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX = 100;

vector<string> cities;

int roadMatrix[MAX][MAX] = {0};
float budgetMatrix[MAX][MAX] = {0.0};

string trim(string str)
{
    while(!str.empty() && str.front() == ' ')
    {
        str.erase(str.begin());
    }

    while(!str.empty() && str.back() == ' ')
    {
        str.pop_back();
    }

    return str;
}

// Check the array index of cities to get the index
int getCityIndex(string cityName)
{
    for(int i = 0; i < cities.size(); i++)
    {
        if(cities[i] == cityName)
        {
            return i;
        }
    }

    return -1;
}

// TASK 1
void addCities()
{
    int n;

    cout << "Enter the number of cities to add: ";
    cin >> n;
    cin.ignore();

    for(int i = 0; i < n; i++)
    {
        string city;

        cout << "Enter the name for city "
             << cities.size() + 1 << ": ";

        getline(cin, city);
        city=trim(city);

        if(getCityIndex(city) == -1)
        {
            cities.push_back(city);
            cout << city << " added successfully.\n";
        }
        else
        {
            cout << "City already exists.\n";
        }
    }
}

// TASK 2A
void addRoad()
{
    string city1, city2;

    cin.ignore();

    cout << "Enter the name of the first city: ";
    getline(cin, city1);
    city1=trim(city1);

    cout << "Enter the name of the second city: ";
    getline(cin, city2);
    city2=trim(city2);

    int i = getCityIndex(city1);
    int j = getCityIndex(city2);

    if(i == -1 || j == -1)
    {
        cout << "One or both cities do not exist.\n";
        return;
    }

    if(i == j)
    {
        cout << "Cannot connect a city to itself.\n";
        return;
    }

    roadMatrix[i][j] = 1;
    roadMatrix[j][i] = 1;

    cout << "Road added successfully between "
         << city1 << " and " << city2 << endl;
}

// TASK 2B
void addBudget()
{
    string city1, city2;
    float budget;

    cin.ignore();

    cout << "Enter the name of the first city: ";
    getline(cin, city1);
    city1=trim(city1);

    cout << "Enter the name of the second city: ";
    getline(cin, city2);
    city2=trim(city2);

    int i = getCityIndex(city1);
    int j = getCityIndex(city2);

    if(i == -1 || j == -1)
    {
        cout << "One or both cities do not exist.\n";
        return;
    }

    if(roadMatrix[i][j] == 0)
    {
        cout << "No road exists between these cities.\n";
        return;
    }

    cout << "Enter the budget for the road: ";
    cin >> budget;

    budgetMatrix[i][j] = budget;
    budgetMatrix[j][i] = budget;

    cout << "Budget added successfully for the road between "
         << city1 << " and " << city2 << endl;
}

// TASK 4A
void editCity()
{
    int index;
    string newName;

    cout << "Enter the index of the city to edit: ";
    cin >> index;
    cin.ignore();

    if(index < 1 || index > cities.size())
    {
        cout << "Invalid city index.\n";
        return;
    }

    cout << "Enter the new name for city: ";
    getline(cin, newName);

    if(getCityIndex(newName) != -1)
    {
        cout << "City name already exists.\n";
        return;
    }

    cities[index - 1] = newName;

    cout << "City updated successfully.\n";
}

// TASK 4B
void searchCity()
{
    int index;

    cout << "Enter the city index: ";
    cin >> index;

    if(index >= 1 && index <= cities.size())
    {
        cout << "City found: "
             << cities[index - 1] << endl;
    }
    else
    {
        cout << "City not found.\n";
    }
}

// TASK 5
void displayCities()
{
    cout << "\nCities:\n";

    for(int i = 0; i < cities.size(); i++)
    {
        cout << i + 1 << ". "
             << cities[i] << endl;
    }
}

void displayRoads()
{
    displayCities();

    cout << "\nRoad Adjacency Matrix:\n";

    for(int i = 0; i < cities.size(); i++)
    {
        for(int j = 0; j < cities.size(); j++)
        {
            cout << roadMatrix[i][j] << " ";
        }

        cout << endl;
    }
}

void displayAllData()
{
    displayCities();

    cout << "\nRoad Adjacency Matrix:\n";

    for(int i = 0; i < cities.size(); i++)
    {
        for(int j = 0; j < cities.size(); j++)
        {
            cout << roadMatrix[i][j] << " ";
        }

        cout << endl;
    }

    cout << "\nBudget Adjacency Matrix:\n";

    for(int i = 0; i < cities.size(); i++)
    {
        for(int j = 0; j < cities.size(); j++)
        {
            cout << fixed << setprecision(1)
                 << budgetMatrix[i][j] << " ";
        }

        cout << endl;
    }
}

// TASK 3
void saveToFiles()
{
    ofstream cityFile("cities.txt");

    cityFile << "Index\tCity_Name\n";

    for(int i = 0; i < cities.size(); i++)
    {
        cityFile << i + 1
                 << "\t"
                 << cities[i]
                 << endl;
    }

    cityFile.close();

    ofstream roadFile("roads.txt");

    roadFile << "Nbr\tRoad\t\tBudget\n";

    int count = 1;

    for(int i = 0; i < cities.size(); i++)
    {
        for(int j = i + 1; j < cities.size(); j++)
        {
            if(roadMatrix[i][j] == 1)
            {
                roadFile << count << ".\t"
                         << cities[i] << "-"
                         << cities[j] << "\t\t"
                         << fixed << setprecision(2)
                         << budgetMatrix[i][j]
                         << endl;

                count++;
            }
        }
    }

    roadFile.close();
}

int main()
{
    int choice;

    do
    {
        cout << "\n------------- MENU -------------\n";

        cout << "1. Add new city(ies)\n";
        cout << "2. Add roads between cities\n";
        cout << "3. Add the budget for roads\n";
        cout << "4. Edit city\n";
        cout << "5. Search for a city using its index\n";
        cout << "6. Display cities\n";
        cout << "7. Display roads\n";
        cout << "8. Display recorded data on console\n";
        cout << "9. Exit\n";

//        cout << "Enter your choice: ";
//        cin >> choice;

		cout << "Enter your choice: ";
		while(!(cin>>choice)){
			cout<< "Invalid	input.Enter a number  between 1-9: ";
			cin.clear();
			cin.ignore(1000,'\n');
		}
		if(choice<1 || choice >9 ){
			cout<< "Your choice must be valid number from 1-9 ";
			continue;
		}

        switch(choice)
        {
            case 1:
                addCities();
                break;

            case 2:
                addRoad();
                break;

            case 3:
                addBudget();
                break;

            case 4:
                editCity();
                break;

            case 5:
                searchCity();
                break;

            case 6:
                displayCities();
                break;

            case 7:
                displayRoads();
                break;

            case 8:
                displayAllData();
                break;

            case 9:
                saveToFiles();
                cout << "Program exited successfully.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while(choice != 9);

    return 0;
}