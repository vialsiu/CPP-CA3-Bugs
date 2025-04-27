#include <iostream>
#include "Board.h"
#include "BugLifeGUI.h"

int main() {
    Board board;
    board.loadBugsFromFile("all-bugs.txt");

    int choice;
    bool running = true;

    while (running) {
        std::cout << "\nMenu:\n"
                  << "1. Display All Bugs\n"
                  << "2. Find a Bug\n"
                  << "3. Tap the Bug Board\n"
                  << "4. Life History\n"
                  << "5. Display All Cells\n"
                  << "6. Run Simulation\n"
                  << "7. Launch SFML GUI\n"
                  << "8. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        bool needReload = false;

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
                board.tapBoard(false);
                break;
            case 4:
                board.displayLifeHistory();
                break;
            case 5:
                board.displayAllCells();
                break;
            case 6:
                board.runSimulation();
                if (board.isGameOver()) needReload = true;
                break;
            case 7:
                    std::cout << "Launching GUI...\n";
            {
                Board guiBoard = runBugLifeGUI();
                guiBoard.displayLifeHistory();
            }
            break;

            case 8:
                std::cout << "Exiting...\n";
                board.writeLifeHistoryToFile();
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

        if (needReload && running) {
            std::cout << "\nReloading new board...\n";
            board = Board();
            board.loadBugsFromFile("all-bugs.txt");
        }
    }

    return 0;
}
