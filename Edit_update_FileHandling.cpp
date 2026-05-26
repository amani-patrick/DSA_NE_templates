#include <iostream>
using namespace std;


#Edit/Save 
void editData()
{
    int index;

    cout << "Enter index to edit: ";
    cin >> index;

    cin.ignore();

    if(index >= 1 && index <= names.size())
    {
        string newName;

        cout << "Enter new name: ";
        getline(cin, newName);

        names[index - 1] = newName;

        cout << "Updated successfully\n";
    }
    else
    {
        cout << "Invalid index\n";
    }
}

#File handling


##include <fstream>

void saveToFile()
{
	// Writing to a file
    ofstream file("data.txt");

    file << "Index\tName\n";

    for(int i = 0; i < names.size(); i++)
    {
        file << i + 1
             << "\t"
             << names[i]
             << endl;
    }

    file.close();

    cout << "Data saved successfully\n";
    
    
    // Reading from a file
    ifstream file("data.txt");

    string line;

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}