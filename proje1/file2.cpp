#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>



int nextEmpId(const std::string& fileName); 
    // TODO: en büyük ID'yi bul, +1 döndür


 
void addEmployee(const std::string& fileName,
                 const std::string& name, const std::string& dept,
                 double salary, int years);
    // TODO: nextEmpId ile ID üret
    // TODO: id,name,dept,salary,years formatında append
 


void listEmployees(const std::string& fileName); 
    // TODO: satır satır oku, ID | Ad | Departman | Maas TL | X yil



void giveRaise(const std::string& fileName, int targetId, double rate); 
    // TODO: temp dosya
    // TODO: ID eşleşirse: yeniMaas = eskiMaas * (1 + rate/100.0)
    // TODO: remove + rename

 

void listByDept(const std::string& fileName, const std::string& dept); 
    // TODO: sadece departman eşleşenleri yazdır
    // TODO: en sonda "Departman toplam maas gideri: X TL" göster


 
void deleteEmployee(const std::string& fileName, int targetId); 
    // TODO: temp dosya, ID eşleşeni atla
    // TODO: remove + rename


int main() {
    std::string fileName = "employees.txt";
    int choice;

    while (true) {
        std::cout << "\n===== EMPLOYEE SYSTEM =====\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. List Employees\n";
        std::cout << "3. Give Raise\n";
        std::cout << "4. List By Department\n";
        std::cout << "5. Delete Employee\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting...\n";
            break;
        }

        std::string name, dept;
        double salary, rate;
        int years, id;

        switch (choice) {

        case 1:
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Department: ";
            std::cin >> dept;
            std::cout << "Salary: ";
            std::cin >> salary;
            std::cout << "Years: ";
            std::cin >> years;

            addEmployee(fileName, name, dept, salary, years);
            break;

        case 2:
            listEmployees(fileName);
            break;

        case 3:
            std::cout << "Employee ID: ";
            std::cin >> id;
            std::cout << "Raise rate (%): ";
            std::cin >> rate;

            giveRaise(fileName, id, rate);
            break;

        case 4:
            std::cout << "Department: ";
            std::cin >> dept;

            listByDept(fileName, dept);
            break;

        case 5:
            std::cout << "Employee ID: ";
            std::cin >> id;

            deleteEmployee(fileName, id);
            break;

        default:
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}




int nextEmpId(const std::string& fileName) {
    std::ifstream read(fileName);
    if(!read) {
        std::cerr << "File not opened" << std::endl;
        return 1;
    }

    int id, maxId = 0;
    std::string name, dept;
    int years;
    double salary;

    while(read >> id >> name >> dept >> salary >> years) {
        if(id > maxId) {
            maxId = id;
        }
    }

    return maxId + 1;
}



void addEmployee(const std::string& fileName,
                 const std::string& name, const std::string& dept,
                 double salary, int years) {

    std::ofstream write(fileName, std::ios::app);
    if(!write) {
        std::cerr << "File not opened" << std::endl;
        return;
    }

    int id = nextEmpId(fileName);

    write << id << " "
          << name << " "
          << dept << " "
          << salary << " "
          << years << "\n";

    write.close();
}



void listEmployees(const std::string& fileName) {

    std::ifstream fileread(fileName);
    if(!fileread) {
        std::cerr << "file not opened" << std::endl;
        return;
    }

    int id, year;
    std::string name, dept;
    double salary;

    while (fileread >> id >> name >> dept >> salary >> year) {
        std::cout << id << " "
                  << name << " "
                  << dept << " "
                  << salary << " "
                  << year << std::endl;
    }

    fileread.close();
}



void giveRaise(const std::string& fileName, int targetId, double rate) {

    std::ifstream raiseread(fileName);
    std::ofstream raisewrite("temp.txt");

    if(!raiseread || !raisewrite) {
        std::cerr << "File not opened" << std::endl;
        return;
    }

    int id, year;
    std::string name, dept;
    double salary;

    while(raiseread >> id >> name >> dept >> salary >> year) {

        if(id == targetId) {
            salary = salary * (1 + rate / 100.0);
        }

        raisewrite << id << " "
                   << name << " "
                   << dept << " "
                   << salary << " "
                   << year << std::endl;
    }

    raiseread.close();
    raisewrite.close();

    std::remove(fileName.c_str());
    std::rename("temp.txt", fileName.c_str());
}



void listByDept(const std::string& fileName, const std::string& dept) {

    std::ifstream deptread(fileName);
    if(!deptread) {
        std::cerr << "File not opened" << std::endl;
        return;
    }

    std::string name, deptFile;
    int year, id;
    double salary;
    double total = 0;

    while(deptread >> id >> name >> deptFile >> salary >> year) {

        if(deptFile == dept) {
            std::cout << id << " "
                      << name << " "
                      << deptFile << " "
                      << salary << " "
                      << year << std::endl;

            total += salary;
        }
    }

    std::cout << "total salary: " << total << std::endl;

    deptread.close();
}



void deleteEmployee(const std::string& fileName, int targetId) {

    std::ifstream deleteread(fileName);
    std::ofstream deletewrite("temp.txt");

    if(!deleteread || !deletewrite) {
        std::cerr << "File not opened" << std::endl;
        return;
    }

    std::string name, dept;
    int year, id;
    double salary;

    while(deleteread >> id >> name >> dept >> salary >> year) {

        if(id != targetId) {
            deletewrite << id << " "
                        << name << " "
                        << dept << " "
                        << salary << " "
                        << year << std::endl;
        }
    }

    deleteread.close();
    deletewrite.close();

    std::remove(fileName.c_str());
    std::rename("temp.txt", fileName.c_str());
}