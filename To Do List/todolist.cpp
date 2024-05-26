#include <iostream>
#include <cstdlib>
#include <string>

// Renaming structure to avoid the repetitive use of struct keyword
struct ToDo {
    // string as data part
    std::string buffer;

    // Pointer part to access addresses
    ToDo* next;

    // Count variable for counting the number of nodes
    int count;
};

// Declare start pointer as null in the beginning
ToDo* start = NULL;

// Function prototypes
void interface();
void seetodo();
void createtodo();
void deletetodo();
void adjustcount();

// Driver Code
int main() {
    int choice;
    interface();

    while (true) {
        

        // // Clear the console
        // system("cls");

        std::cout << "1. To see your ToDo list\n";
        std::cout << "2. To create new ToDo\n";
        std::cout << "3. To delete your ToDo\n";
        std::cout << "4. Exit";
        std::cout << "\n\n\nEnter your choice\t:\t";

        // Choice from the user
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline character after integer input

        switch (choice) {
        case 1:
            seetodo();
            break;
        case 2:
            createtodo();
            break;
        case 3:
            deletetodo();
            break;
        case 4:
            exit(0);
            break;
        default:
            std::cout << "\nInvalid Choice :-(\n";
            system("pause");
        }
    }
    return 0;
}

// Code for Splash screen
void interface() {
    // system("color 4F");
    std::cout << "\n\n\n\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~\n\n";
    std::cout << "\t} : } : } : } : } : } "
              << ": } : } : } : "
              << "WELCOME TO the TODO APP "
              << "	 : { : { : { : { : { "
              << ": { : { : { : {\n\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~~~~~~~~~~~~~~~"
              << "~~~~~~~~~~\n";

    // Pausing screen until user presses any key
    system("pause");
}

// To view all the todos
void seetodo() {
    // Clearing the console
    system("cls");

    // Pointer to the node for traversal
    ToDo* temp;

    // temp is made to point the start of linked list
    temp = start;

    // Condition for empty linked list
    if (start == NULL) {
        std::cout << "\n\nEmpty ToDo \n\n";
    }

    // Traverse until last node
    while (temp != NULL) {
        // Print number of the node
        std::cout << temp->count << ".)";

        // Print data of the node
        std::cout << temp->buffer << "\n";

        // Going to next node
        temp = temp->next;
    }

    std::cout << "\n\n\n";
    system("pause");
}

// Function to insert a node todo
void createtodo() {
    // Choose choice from user
    char c;

    // Pointers to node
    ToDo *add, *temp;
    system("cls");

    // Infinite loop which will break if "n" is pressed
    while (true) {
        std::cout << "\nWant to add new ToDo ?? Press 'y' for Yes and 'n' for No :-)\n\t\t";
        std::cin >> c;
        std::cin.ignore(); // Ignore newline character after char input

        if (c == 'n') {
            break;
        } else {
            // If start node is NULL
            if (start == NULL) {
                // Dynamically allocating memory to the newly created node
                add = new ToDo();

                // Using add pointer to create linked list
                start = add;
                std::cout << "\nType it.....\n";

                // Input from user
                std::getline(std::cin, add->buffer);

                // As first input so count is 1
                add->count = 1;

                // As first node so start's next is NULL
                start->next = NULL;
            } else {
                temp = new ToDo();
                std::cout << "\nType it.....\n";
                std::getline(std::cin, temp->buffer);

                // Insertion is at last so pointer part is NULL
                temp->next = NULL;

                // add is now pointing newly created node
                add->next = temp;
                add = add->next;
            }

            // Using the concept of insertion at the end, adding a todo

            // Calling function to adjust the count variable
            adjustcount();
        }
    }
}

// Function to delete the todo
void deletetodo() {
    system("cls");

    // To get the numbering of the todo to be deleted
    int x;

    ToDo *del, *temp;
    std::cout << "\nEnter the ToDo's number that you want to remove.\n\t\t";

    // Checking empty condition
    if (start == NULL) {
        std::cout << "\n\nThere is no ToDo for today :-)\n\n\n";
    } else {
        std::cin >> x;

        // del will point to start
        del = start;

        // temp will point to start's next so that traversal and deletion is achieved easily
        temp = start->next;

        // Running infinite loop so that user can delete and asked again for choice
        while (true) {
            // When the values matches, delete the node
            if (del->count == x) {
                // When the node to be deleted is first node
                start = start->next;

                // Deallocating the memory of the deleted node
                delete del;

                // Adjusting the count when node is deleted
                adjustcount();
                break;
            }

            if (temp != NULL && temp->count == x) {
                del->next = temp->next;
                delete temp;
                adjustcount();
                break;
            } else {
                del = temp;
                if (temp != NULL) {
                    temp = temp->next;
                }
            }
        }
    }
    system("pause");
}

// Function to adjust the numbering of the nodes
void adjustcount() {
    // For traversal, using a node pointer
    ToDo* temp;
    int i = 1;
    temp = start;

    // Running loop until last node and numbering it one by one
    while (temp != NULL) {
        temp->count = i;
        i++;
        temp = temp->next;
    }
}
