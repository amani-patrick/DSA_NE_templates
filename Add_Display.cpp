#include <iostream>
#include <vector>

using namespace std;

vector<string> names;



// ADD DATA
void addData()
{
    int n;

    cout << "How many names: ";
    cin >> n;

    cin.ignore();

    for(int i = 0; i < n; i++)
    {
        string name;

        cout << "Enter name: ";
        getline(cin, name);

        names.push_back(name);
    }
}

// DISPLAY DATA
void displayData()
{
    cout << "\nRecorded Names:\n";

    for(int i = 0; i < names.size(); i++)
    {
        cout << i + 1 << ". "
             << names[i] << endl;
    }
}