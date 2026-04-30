#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>

void addExpense(const std::string& fileName,
                const std::string& date, const std::string& category,
                const std::string& desc, double amount);

void listExpenses(const std::string& fileName);

double totalByCategory(const std::string& fileName, const std::string& category);

void deleteExpense(const std::string& fileName, const std::string& targetDesc);

int main() {
    std::string fileName = "expenses.txt";

    int choice;

    while (true) {
        std::cout << "\n===== EXPENSE TRACKER =====\n";
        std::cout << "1. Add Expense\n";
        std::cout << "2. List Expenses\n";
        std::cout << "3. Total by Category\n";
        std::cout << "4. Delete Expense (by description)\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        std::cin.ignore(); // buffer temizleme

        if (choice == 0) {
            std::cout << "Exiting...\n";
            break;
        }

        if (choice == 1) {
            std::string date, category, desc;
            double amount;

            std::cout << "Date (YYYY-MM-DD): ";
            getline(std::cin, date);

            std::cout << "Category: ";
            getline(std::cin, category);

            std::cout << "Description: ";
            getline(std::cin, desc);

            std::cout << "Amount: ";
            std::cin >> amount;
            std::cin.ignore();

            addExpense(fileName, date, category, desc, amount);
            std::cout << "Expense added.\n";
        }

        else if (choice == 2) {
            listExpenses(fileName);
        }

        else if (choice == 3) {
            std::string category;
            std::cout << "Category: ";
            getline(std::cin, category);

            double total = totalByCategory(fileName, category);
            std::cout << "Total for " << category << ": " << total << " TL\n";
        }

        else if (choice == 4) {
            std::string desc;
            std::cout << "Description to delete: ";
            getline(std::cin, desc);

            deleteExpense(fileName, desc);
        }

        else {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}

void addExpense(const std::string& fileName,
                const std::string& date, const std::string& category,
                const std::string& desc, double amount) {
                    
std::ofstream write(fileName,std::ios::app);  
if(!write) {
    std::cerr<<"File Not Opened"<<std::endl;
    return;
}

write<<date<<"|"<<category<<"|"<<desc<<"|"<<amount<<std::endl;
write.close();    
     }




void listExpenses(const std::string& fileName) {
    std::ifstream read(fileName);
    if(!read) {
        std::cerr<<"File not Opened"<<std::endl;
        return;
    }
        std::string line;
        int i = 1;
while(getline(read,line)) {
std::stringstream ss(line);
std::string dates,categroys,desc,a;
getline(ss,dates,'|');

getline(ss,categroys,'|');

getline(ss,desc,'|');

getline(ss,a,'|');

double amounts = std::stod(a);

std::cout<<i<<". "<<dates<<" | "<<categroys<<" | "<<desc<<" | "<<amounts<<"TL"<<std::endl;
i++;
}

read.close();
}





double totalByCategory(const std::string& fileName, const std::string& category) {
    std::ifstream totalread(fileName);
    if(!totalread) {
        std::cerr<<"File not Opened"<<std::endl;
        return 0;
    }


            std::string line;
        double total = 0;
            while(getline(totalread,line)) {
std::stringstream ss(line);

std::string dates,categroys,desc,a;
getline(ss,dates,'|');

getline(ss,categroys,'|');

getline(ss,desc,'|');

getline(ss,a,'|');


if (!a.empty() && categroys == category) {
            try {
                total += std::stod(a);
            } catch (...) {
                continue;
            }
        }

}
totalread.close();
return total;

}


void deleteExpense(const std::string& fileName, const std::string& targetDesc) {
    std::ifstream in(fileName);
    std::ofstream out("temp.txt");

    if (!in || !out) {
        std::cerr << "File not opened" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    while (getline(in, line)) {
        std::stringstream ss(line);

        std::string date, category, desc, amount;

        getline(ss, date, '|');
        getline(ss, category, '|');
        getline(ss, desc, '|');
        getline(ss, amount, '|');

        
        if (desc != targetDesc) {
            out << date << "|" << category << "|" << desc << "|" << amount << "\n";
        } else {
            found = true;
        }
    }

    in.close();
    out.close();

    std::remove(fileName.c_str());
    std::rename("temp.txt", fileName.c_str());

    if (!found) {
        std::cout << "Expense not found.\n";
    }
}