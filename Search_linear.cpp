#include <iostream>
using namespace std;


int searchName(string target)
{
    for(int i = 0; i < names.size(); i++)
    {
        if(names[i] == target)
        {
            return i;
        }
    }

    return -1;
}

#Usage example 
string name;

cout << "Enter name to search: ";
getline(cin, name);

int result = searchName(name);

if(result != -1)
{
    cout << "Found at position "
         << result + 1 << endl;
}
else
{
    cout << "Not found\n";
}