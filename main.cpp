#include "parking.h"
#include <iostream>
#include <string>

int main() {

    std::string fileName = "parking.txt";

    int choice;

    while (true) {
        std::cout << "\n========== PARKING SYSTEM ==========\n";
        std::cout << "1. Enter Parking\n";
        std::cout << "2. Exit Parking\n";
        std::cout << "3. List Parking\n";
        std::cout << "4. Daily Revenue\n";
        std::cout << "0. Exit Program\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting...\n";
            break;
        }

        std::string plate, spot, time;

        switch (choice) {

        case 1: {
            std::cout << "Plate: ";
            std::cin >> plate;

            std::cout << "Spot: ";
            std::cin >> spot;

            std::cout << "Entry Time (HH:MM): ";
            std::cin >> time;

            enterParking(fileName, plate, spot, time);
            break;
        }

        case 2: {
            std::cout << "Plate: ";
            std::cin >> plate;

            std::cout << "Exit Time (HH:MM): ";
            std::cin >> time;

            exitParking(fileName, plate, time);
            break;
        }

        case 3: {
            listParking(fileName);
            break;
        }

        case 4: {
            double revenue = dailyRevenue(fileName);
            std::cout << "Total Revenue: " << revenue << " TL\n";
            break;
        }

        default:
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}