 #include <iostream>
#include "Board.h"

int main() {
    Board board;
    board.loadBugsFromFile("crawler-bugs.txt");

    int choice;
    do {
        std::cout << "\nMenu:\n"
                  << "1. Display All Bugs\n"
                  << "2. Find a Bug\n"
                  << "3. Tap the Bug Board\n"
                  << "4. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                board.displayAllBugs();
            break;
            case 2: {
                int searchId;
                std::cout << "Enter Bug ID to search: ";
                std::cin >> searchId;
                board.findBugById(searchId);
                break;
            }
            case 3:
                board.tapBoard();
            break;
            case 4:
                std::cout << "Exiting...";
            break;
            case 5:
                std::cout << "havent implemented";
            break;
            case 6:
                std::cout << "havent implemented";
            break;
            case 7:
                std::cout << "havent implemented";
            break;
            case 8:
                std::cout << "havent implemented";
            break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }  while (choice != 4);

    return 0;
}