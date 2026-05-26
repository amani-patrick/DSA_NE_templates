#include <iostream>
using namespace std;

int main()
{
    int choice;

    do
    {
        cout << "\n===== MENU =====\n";

        cout << "1. Add\n";
        cout << "2. Display\n";
        cout << "3. Search\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";

        // INPUT VALIDATION
        while(!(cin >> choice))
        {
            cout << "Invalid input. Enter a number: ";

            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch(choice)
        {
            case 1:
                cout << "Add selected\n";
                break;

            case 2:
                cout << "Display selected\n";
                break;

            case 3:
                cout << "Search selected\n";
                break;

            case 4:
                cout << "Program exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while(choice != 4);

    return 0;
}