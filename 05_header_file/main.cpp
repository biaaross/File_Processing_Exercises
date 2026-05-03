#include "pharmacy.h"
#include <iostream>

int main() {
    std::string fileName = "medicines.txt";
    std::string today;

    int choice;

    do {
        std::cout << "\n===== PHARMACY SYSTEM =====\n";
        std::cout << "1. Add Medicine\n";
        std::cout << "2. List Medicines\n";
        std::cout << "3. Sell Medicine\n";
        std::cout << "4. Check Expired\n";
        std::cout << "5. Low Stock\n";
        std::cout << "6. Update Price\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch(choice) {

        case 1: {
            std::string barcode, name, expiry;
            int stock;
            double price;

            std::cout << "Barcode: ";
            std::cin >> barcode;
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Stock: ";
            std::cin >> stock;
            std::cout << "Price: ";
            std::cin >> price;
            std::cout << "Expiry (YYYY-MM-DD): ";
            std::cin >> expiry;

            addMedicine(fileName, barcode, name, stock, price, expiry);
            break;
        }

        case 2: {
            std::cout << "Enter today's date (YYYY-MM-DD): ";
            std::cin >> today;
            listMedicines(fileName, today);
            break;
        }

        case 3: {
            std::string barcode;
            int qty;

            std::cout << "Enter today's date (YYYY-MM-DD): ";
            std::cin >> today;

            std::cout << "Barcode: ";
            std::cin >> barcode;
            std::cout << "Quantity: ";
            std::cin >> qty;

            sellMedicine(fileName, barcode, qty, today);
            break;
        }

        case 4: {
            std::cout << "Enter today's date (YYYY-MM-DD): ";
            std::cin >> today;
            checkExpired(fileName, today);
            break;
        }

        case 5: {
            int threshold;
            std::cout << "Enter threshold: ";
            std::cin >> threshold;
            lowStock(fileName, threshold);
            break;
        }

        case 6: {
            std::string barcode;
            double newPrice;

            std::cout << "Barcode: ";
            std::cin >> barcode;
            std::cout << "New Price: ";
            std::cin >> newPrice;

            updatePrice(fileName, barcode, newPrice);
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice!\n";
        }

    } while(choice != 0);

    return 0;
}