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
                  << "4. Life History\n"
                  << "5. Display All Cells\n"
                  << "6. Run Simulation\n"
                  << "7. Exit\n"
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
                board.displayLifeHistory();
            break;
            case 5:
                board.displayAllCells();
            break;
            case 6:
                board.runSimulation();
            break;
            case 7:
                std::cout << "Exiting...\n";
            board.writeLifeHistoryToFile();
            break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7 && !board.isGameOver());

    return 0;
}
