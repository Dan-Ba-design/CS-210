#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ITEMS = 100;  // Maximum number of unique items we can track (A proper store would def need a bigger number)

int main() {
    string items[MAX_ITEMS];       // Array to store unique item names
    int counts[MAX_ITEMS] = { 0 }; // Parallel array that stores the value of the items (counting)
    int itemCount = 0;             // Number of unique items found

    ifstream inFile("CS210_Project_Three_Input_File.txt");
    if (!inFile) {
        cout << "Error: couldn't open input file." << endl;
        return 1;
    }

    string item;
    // This reads all items from the input file
    while (inFile >> item) {
        bool found = false;
        // Check if the item is already in the array
        for (int i = 0; i < itemCount; i++) {
            if (items[i] == item) {
                counts[i]++;  // Increase count for existing item
                found = true;
                break;
            }
        }
        // Add to the array if the item is not found
        if (!found) {
            if (itemCount < MAX_ITEMS) {
                items[itemCount] = item;
                counts[itemCount] = 1;
                itemCount++;
            }
            else {
                cout << "Too many unique items!" << endl;
                break;
            }
        }
    }
    inFile.close();

    int choice = 0;

    // Main menu loop
    while (choice != 4) {
        cout << "\n---- Menu ----\n";
        cout << "1. Search for item\n";
        cout << "2. Show all item frequencies\n";
        cout << "3. Show histogram\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        // Input validation for choice
        if (!(cin >> choice)) {
            cin.clear();               // Clear error flag
            cin.ignore(10000, '\n');   // Discard invalid input
            cout << "Invalid input. Please enter a number 1 2 3 or 4." << endl;
            choice = 0;                // Reset's the loop
            continue;                  // Restart's the loop
        }

        if (choice == 1) {
            string search;
            cout << "Enter item to search: ";
            cin >> search;
            bool found = false;
            // Search for the item and display count if found
            for (int i = 0; i < itemCount; i++) {
                if (items[i] == search) {
                    cout << search << " was purchased " << counts[i] << " time(s)." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << search << " was not an item purchased. Make sure the produce is capitalized and ends with an s. EX: Apples " << endl;
            }
        }
        else if (choice == 2) {
            // Display all items and their purchase counts
            for (int i = 0; i < itemCount; i++) {
                cout << items[i] << ": " << counts[i] << endl;
            }
        }
        else if (choice == 3) {
            // Display histogram of purchases. Asterisks are used to signoify the amount of items purchased. I think this is standard as it is very visible and uses the ASCII symbols.
            for (int i = 0; i < itemCount; i++) {
                cout << items[i] << ": ";
                for (int j = 0; j < counts[i]; j++) {
                    cout << "*";
                }
                cout << endl;
            }
        }
        else if (choice == 4) {
            cout << "Thank you for using the Corner Grocer item-tracking program!" << endl;
        }
        else {
            cout << "Invalid choice. Re-read the prompt and make sure the spelling is correct." << endl;
        }
    }

    return 0;
}