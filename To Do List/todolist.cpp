#include <iostream>
#include <cstdlib>
#include <string>

struct ToDo {
    std::string buffer;
    ToDo* next;
    int count;
    bool completed;  // New field to track completion status
};

ToDo* start = NULL;

void interface();
void seetodo();
void createtodo();
void deletetodo();
void markAsCompleted();  // New function to mark tasks as completed
void adjustcount();

int main() {
    int choice;
    interface();

    while (true) {
        std::cout << "1. To see your ToDo list\n";
        std::cout << "2. To create new ToDo\n";
        std::cout << "3. To delete your ToDo\n";
        std::cout << "4. To mark a task as completed\n";
        std::cout << "5. Exit\n";
        std::cout << "\n\n\nEnter your choice\t:\t";

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
            markAsCompleted();
            break;
        case 5:
            exit(0);
            break;
        default:
            std::cout << "\nInvalid Choice :-(\n";
            system("pause");
        }
    }
    return 0;
}

void interface() {
    std::cout << "\n\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\t} : } : } : } : } : } : } : } : } : WELCOME TO the TODO APP : { : { : { : { : { : { : { : {\n\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    system("pause");
}

void seetodo() {
    system("cls");
    ToDo* temp = start;

    if (start == NULL) {
        std::cout << "\n\nEmpty ToDo \n\n";
    }

    while (temp != NULL) {
        std::cout << temp->count << ".) ";
        std::cout << temp->buffer;
        std::cout << " [" << (temp->completed ? "Completed" : "Pending") << "]\n";  // Display status
        temp = temp->next;
    }

    std::cout << "\n\n\n";
    system("pause");
}

void createtodo() {
    char c;
    ToDo *add, *temp;
    system("cls");

    while (true) {
        std::cout << "\nWant to add new ToDo ?? Press 'y' for Yes and 'n' for No :-)\n\t\t";
        std::cin >> c;
        std::cin.ignore(); // Ignore newline character after char input

        if (c == 'n') {
            break;
        } else {
            if (start == NULL) {
                add = new ToDo();
                start = add;
                std::cout << "\nType it.....\n";
                std::getline(std::cin, add->buffer);
                add->count = 1;
                add->completed = false;  // Initialize as not completed
                start->next = NULL;
            } else {
                temp = new ToDo();
                std::cout << "\nType it.....\n";
                std::getline(std::cin, temp->buffer);
                temp->next = NULL;
                temp->completed = false;  // Initialize as not completed
                add->next = temp;
                add = add->next;
            }
            adjustcount();
        }
    }
}

void deletetodo() {
    system("cls");
    int x;
    ToDo *del, *temp;
    std::cout << "\nEnter the ToDo's number that you want to remove.\n\t\t";

    if (start == NULL) {
        std::cout << "\n\nThere is no ToDo for today :-)\n\n\n";
    } else {
        std::cin >> x;

        del = start;
        temp = start->next;

        while (true) {
            if (del->count == x) {
                start = start->next;
                delete del;
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

void markAsCompleted() {
    system("cls");
    int x;
    std::cout << "\nEnter the ToDo's number that you want to mark as completed.\n\t\t";

    if (start == NULL) {
        std::cout << "\n\nThere is no ToDo for today :-)\n\n\n";
    } else {
        std::cin >> x;
        ToDo* temp = start;

        while (temp != NULL) {
            if (temp->count == x) {
                temp->completed = true;  // Mark as completed
                std::cout << "Task " << x << " marked as completed.\n";
                break;
            }
            temp = temp->next;
        }

        if (temp == NULL) {
            std::cout << "Task not found.\n";
        }
    }
    system("pause");
}

void adjustcount() {
    ToDo* temp = start;
    int i = 1;

    while (temp != NULL) {
        temp->count = i;
        i++;
        temp = temp->next;
    }
}
